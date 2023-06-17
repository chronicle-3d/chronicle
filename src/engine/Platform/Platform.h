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
    static void Init();
    static void Deinit();
    static bool Poll();

    [[nodiscard]] static wgpu::Device GetDevice();

    [[nodiscard]] static double GetDeltaTime()
    {
        return _deltaTime;
    }

    [[nodiscard]] static double GetElapsedTime()
    {
        return _elapsedTime;
    }

    [[nodiscard]] static Ref<Window> CreateWindow(const WindowDescriptor &descriptor);

  private:
    static inline double _deltaTime{};
    static inline double _elapsedTime{};
};

} // namespace chronicle