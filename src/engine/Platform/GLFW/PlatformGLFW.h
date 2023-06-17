// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#pragma once

#include "Platform/Platform.h"

#include <dawn/native/DawnNative.h>
#include <dawn/webgpu_cpp.h>

namespace chronicle::internal::glfw
{

class PlatformGLFW
{
  public:
    explicit PlatformGLFW();
    ~PlatformGLFW();

    bool Poll();

    [[nodiscard]] wgpu::Device GetDevice() const
    {
        return _device;
    }

    [[nodiscard]] SharedPtr<Window> CreateWindow(const WindowDescriptor &descriptor);

  private:
    UniquePtr<dawn::native::Instance> _instance{};
    wgpu::Device _device{};
};

} // namespace chronicle::internal::glfw