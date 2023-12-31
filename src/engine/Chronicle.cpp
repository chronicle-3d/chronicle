// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "Chronicle.h"

#include "UI/UI.h"

#include <dawn/utils/ComboRenderPipelineDescriptor.h>
#include <dawn/utils/WGPUHelpers.h>

namespace chronicle
{

void Chronicle::Init()
{
    Platform::Init();
    _window = Platform::CreateWindow({});
    _queue = Platform::GetDevice().GetQueue();

    UI::Init();

    InitBuffers();
    InitTextures();
    CreateDepthStencilView();
    CreatePipeline();
}

void Chronicle::Deinit()
{
    UI::Deinit();
    Platform::Deinit();
}

void Chronicle::Run()
{
    auto device = Platform::GetDevice();
    auto swapChain = _window->GetSwapChain();

    // Create a context to display documents within.
    Rml::Context *context = Rml::CreateContext("main", Rml::Vector2i(_window->GetWidth(), _window->GetHeight()));

    // Tell RmlUi to load the given fonts.
    Rml::LoadFontFace("LatoLatin-Regular.ttf");
    // Fonts can be registered as fallback fonts, as in this case to display emojis.
    Rml::LoadFontFace("NotoEmoji-Regular.ttf", true);

    Rml::ElementDocument *document = context->LoadDocument("demo.rml");
    document->Show();

    while (Platform::Poll())
    {
        if (swapChain.Get() != _window->GetSwapChain().Get())
        {
            swapChain = _window->GetSwapChain();
            CreateDepthStencilView();
            CreatePipeline();
        }

        context->Update();

        wgpu::TextureView backbufferView = swapChain.GetCurrentTextureView();

        dawn::utils::ComboRenderPassDescriptor renderPass({backbufferView}, _depthStencilView);

        wgpu::CommandEncoder encoder = device.CreateCommandEncoder();
        {
            wgpu::RenderPassEncoder pass = encoder.BeginRenderPass(&renderPass);
            pass.SetPipeline(_renderPipeline);
            pass.SetBindGroup(0, _bindGroup);
            pass.SetVertexBuffer(0, _vertexBuffer);
            pass.SetIndexBuffer(_indexBuffer, wgpu::IndexFormat::Uint32);
            pass.DrawIndexed(3);

            context->Render();

            pass.End();
        }

        wgpu::CommandBuffer commands = encoder.Finish();
        _queue.Submit(1, &commands);
    }
}

void Chronicle::InitBuffers()
{
    auto device = Platform::GetDevice();

    static const uint32_t indexData[3] = {
        0,
        1,
        2,
    };
    _indexBuffer = dawn::utils::CreateBufferFromData(device, indexData, sizeof(indexData), wgpu::BufferUsage::Index);

    static const float vertexData[12] = {
        0.0f, 0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, -0.5f, 0.0f, 1.0f,
    };
    _vertexBuffer =
        dawn::utils::CreateBufferFromData(device, vertexData, sizeof(vertexData), wgpu::BufferUsage::Vertex);
}

void Chronicle::InitTextures()
{
    auto device = Platform::GetDevice();

    wgpu::TextureDescriptor descriptor;
    descriptor.dimension = wgpu::TextureDimension::e2D;
    descriptor.size.width = 1024;
    descriptor.size.height = 1024;
    descriptor.size.depthOrArrayLayers = 1;
    descriptor.sampleCount = 1;
    descriptor.format = wgpu::TextureFormat::RGBA8Unorm;
    descriptor.mipLevelCount = 1;
    descriptor.usage = wgpu::TextureUsage::CopyDst | wgpu::TextureUsage::TextureBinding;
    _texture = device.CreateTexture(&descriptor);

    _sampler = device.CreateSampler();

    // Initialize the texture with arbitrary data until we can load images
    std::vector<uint8_t> data(4 * 1024 * 1024, 0);
    for (size_t i = 0; i < data.size(); ++i)
    {
        data[i] = static_cast<uint8_t>(i % 253);
    }

    wgpu::Buffer stagingBuffer = dawn::utils::CreateBufferFromData(
        device, data.data(), static_cast<uint32_t>(data.size()), wgpu::BufferUsage::CopySrc);
    wgpu::ImageCopyBuffer imageCopyBuffer = dawn::utils::CreateImageCopyBuffer(stagingBuffer, 0, 4 * 1024);
    wgpu::ImageCopyTexture imageCopyTexture = dawn::utils::CreateImageCopyTexture(_texture, 0, {0, 0, 0});
    wgpu::Extent3D copySize = {1024, 1024, 1};

    wgpu::CommandEncoder encoder = device.CreateCommandEncoder();
    encoder.CopyBufferToTexture(&imageCopyBuffer, &imageCopyTexture, &copySize);

    wgpu::CommandBuffer copy = encoder.Finish();
    _queue.Submit(1, &copy);
}

void Chronicle::CreateDepthStencilView()
{
    wgpu::TextureDescriptor descriptor{};
    descriptor.dimension = wgpu::TextureDimension::e2D;
    descriptor.size.width = _window->GetSwapChain().GetCurrentTexture().GetWidth();
    descriptor.size.height = _window->GetSwapChain().GetCurrentTexture().GetHeight();
    descriptor.size.depthOrArrayLayers = 1;
    descriptor.sampleCount = 1;
    descriptor.format = wgpu::TextureFormat::Depth24PlusStencil8;
    descriptor.mipLevelCount = 1;
    descriptor.usage = wgpu::TextureUsage::RenderAttachment;
    auto depthStencilTexture = Platform::GetDevice().CreateTexture(&descriptor);
    _depthStencilView = depthStencilTexture.CreateView();
}

void Chronicle::CreatePipeline()
{
    auto device = Platform::GetDevice();

    wgpu::ShaderModule vsModule = dawn::utils::CreateShaderModule(device, R"(
        @vertex fn main(@location(0) pos : vec4f)
                            -> @builtin(position) vec4f {
            return pos;
        })");

    wgpu::ShaderModule fsModule = dawn::utils::CreateShaderModule(device, R"(
        @group(0) @binding(0) var mySampler: sampler;
        @group(0) @binding(1) var myTexture : texture_2d<f32>;

        @fragment fn main(@builtin(position) FragCoord : vec4f)
                              -> @location(0) vec4f {
            return vec4(1.0, 0.0, 0.0, 1.0f);
            //return textureSample(myTexture, mySampler, FragCoord.xy / vec2f(640.0, 480.0));
        })");

    auto bgl = dawn::utils::MakeBindGroupLayout(
        device, {
                    {0, wgpu::ShaderStage::Fragment, wgpu::SamplerBindingType::Filtering},
                    {1, wgpu::ShaderStage::Fragment, wgpu::TextureSampleType::Float},
                });

    wgpu::PipelineLayout pl = dawn::utils::MakeBasicPipelineLayout(device, &bgl);

    dawn::utils::ComboRenderPipelineDescriptor descriptor;
    descriptor.layout = dawn::utils::MakeBasicPipelineLayout(device, &bgl);
    descriptor.vertex.module = vsModule;
    descriptor.vertex.bufferCount = 1;
    descriptor.cBuffers[0].arrayStride = 4 * sizeof(float);
    descriptor.cBuffers[0].attributeCount = 1;
    descriptor.cAttributes[0].format = wgpu::VertexFormat::Float32x4;
    descriptor.cFragment.module = fsModule;
    descriptor.cTargets[0].format = _window->GetSwapChain().GetCurrentTexture().GetFormat();
    descriptor.EnableDepthStencil(wgpu::TextureFormat::Depth24PlusStencil8);

    _renderPipeline = device.CreateRenderPipeline(&descriptor);

    wgpu::TextureView view = _texture.CreateView();
    auto width = _texture.GetWidth();

    _bindGroup = dawn::utils::MakeBindGroup(device, bgl, {{0, _sampler}, {1, view}});
}

} // namespace chronicle