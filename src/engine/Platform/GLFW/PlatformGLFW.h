// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#pragma once

#include "Platform/Platform.h"

#include <dawn/native/DawnNative.h>
#include <dawn/webgpu_cpp.h>

namespace chronicle::internal::glfw
{

class PlatformGLFW : public Platform
{
  public:
    explicit PlatformGLFW();
    ~PlatformGLFW() override;

    bool Poll() override;

    [[nodiscard]] wgpu::Device GetDevice() const override
    {
        return _device;
    }

    [[nodiscard]] double GetDelta() const override
    {
        return _delta;
    }

    [[nodiscard]] Ref<Window> CreateWindow(const WindowDescriptor &descriptor) override;

  private:
    Unique<dawn::native::Instance> _instance{};
    wgpu::Device _device{};

    double _delta{};
};

} // namespace chronicle::internal::glfw