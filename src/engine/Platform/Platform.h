// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#pragma once

#include "Common/Common.h"
#include "Window.h"

namespace chronicle
{

class Platform
{
  public:
    virtual ~Platform() = default;

    virtual bool Poll() = 0;

    [[nodiscard]] virtual wgpu::Device GetDevice() const = 0;
    [[nodiscard]] virtual double GetDelta() const = 0;

    [[nodiscard]] virtual Ref<Window> CreateWindow(const WindowDescriptor &descriptor) = 0;

    static Unique<Platform> Create();
};

} // namespace chronicle