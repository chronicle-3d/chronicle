// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "WindowGLFW.h"

#include "ContextGLFW.h"

#include <webgpu/webgpu_glfw.h>

namespace chronicle::internal::glfw
{

WindowGLFW::WindowGLFW(dawn::native::Instance *instance, const wgpu::Device &device, const WindowDescriptor &descriptor)
    : _instance(instance), _device(device), _title(descriptor.title), _width(descriptor.width),
      _height(descriptor.height)
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
    _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
    if (!_window)
    {
        throw WindowError("Cannot create window");
    }

    glfwSetWindowUserPointer(_window, this);
    glfwSetFramebufferSizeCallback(_window, FramebufferSizeCallback);

    CreateSurface();
    CreateSwapChain();

    ContextGLFW::windows.insert(this);
}

WindowGLFW::~WindowGLFW()
{
    CloseInternal();
}

void WindowGLFW::Close()
{
    CloseInternal();
}

bool WindowGLFW::Poll()
{
    if (!_window)
    {
        return false;
    }

    if (glfwWindowShouldClose(_window))
    {
        Close();
        return false;
    }

    _swapChain.Present();

    return true;
}

void WindowGLFW::CloseInternal()
{
    if (_window)
    {
        glfwDestroyWindow(_window);
        _window = nullptr;
    }
}

void WindowGLFW::CreateSurface()
{
    const auto &backendProcs = dawn::native::GetProcs();
    auto surfaceChainedDesc = wgpu::glfw::SetupWindowAndGetSurfaceDescriptor(_window);

    WGPUSurfaceDescriptor surfaceDesc{};
    surfaceDesc.nextInChain = std::bit_cast<WGPUChainedStruct *>(surfaceChainedDesc.get());
    _surface = wgpu::Surface::Acquire(backendProcs.instanceCreateSurface(_instance->Get(), &surfaceDesc));
}

void WindowGLFW::CreateSwapChain()
{
    const auto &backendProcs = dawn::native::GetProcs();

    WGPUSwapChainDescriptor swapChainDesc{};
    swapChainDesc.usage = WGPUTextureUsage_RenderAttachment;
    swapChainDesc.format = static_cast<WGPUTextureFormat>(GetPreferredSwapChainTextureFormat());
    swapChainDesc.width = _width;
    swapChainDesc.height = _height;
    swapChainDesc.presentMode = WGPUPresentMode_Force32;

    auto backendSwapChain = backendProcs.deviceCreateSwapChain(_device.Get(), _surface.Get(), &swapChainDesc);
    _swapChain = wgpu::SwapChain::Acquire(backendSwapChain);
}

wgpu::TextureFormat WindowGLFW::GetPreferredSwapChainTextureFormat() const
{
    // TODO(dawn:1362): Return the adapter's preferred format when implemented.
    return wgpu::TextureFormat::BGRA8Unorm;
}

void WindowGLFW::FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    auto *windowGLFW = static_cast<WindowGLFW *>(glfwGetWindowUserPointer(window));
    windowGLFW->_width = width;
    windowGLFW->_height = height;
    windowGLFW->CreateSwapChain();
}

} // namespace chronicle::internal::glfw