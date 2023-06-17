// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#pragma once

#include "Platform/Window.h"

#include <GLFW/glfw3.h>
#include <dawn/native/DawnNative.h>
#include <dawn/webgpu_cpp.h>

namespace chronicle::internal::glfw
{

class WindowGLFW : public Window
{
  public:
    explicit WindowGLFW(dawn::native::Instance *instance, const wgpu::Device &device,
                        const WindowDescriptor &descriptor);
    ~WindowGLFW() override;

    void Close() override;

    bool Poll();

  private:
    dawn::native::Instance *_instance{};
    wgpu::Device _device{};

    GLFWwindow *_window{};
    wgpu::SwapChain _swapChain{};

    void CloseInternal();
    wgpu::TextureFormat GetPreferredSwapChainTextureFormat();
};

} // namespace chronicle::internal::glfw