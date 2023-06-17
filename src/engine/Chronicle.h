// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#pragma once

#include "Common/Common.h"
#include "Platform/Platform.h"

namespace chronicle
{

class Chronicle
{
  public:
    static void Init();
    static void Deinit();
    static void Run();

  private:
    //static inline Unique<Platform> _platform{};
    static inline SharedPtr<Window> _window{};
    static inline wgpu::TextureView _depthStencilView;
    static inline wgpu::RenderPipeline _renderPipeline;
    static inline wgpu::BindGroup _bindGroup;
    static inline wgpu::Texture _texture;
    static inline wgpu::Buffer _indexBuffer;
    static inline wgpu::Buffer _vertexBuffer;
    static inline wgpu::Sampler _sampler;
    static inline wgpu::Queue _queue;

    static void InitBuffers();
    static void InitTextures();

    static void CreateDepthStencilView();
    static void CreatePipeline();
};

} // namespace chronicle