// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "Platform.h"

#include "GLFW/PlatformGLFW.h"

#include <chrono>

namespace chronicle
{

struct PlatformContext
{
    static inline UniquePtr<internal::glfw::PlatformGLFW> platform{};
    static inline std::chrono::steady_clock::time_point initTime{};
    static inline std::chrono::steady_clock::time_point lastFrameTime{};
};

void Platform::Init()
{
    PlatformContext::platform = MakeUnique<internal::glfw::PlatformGLFW>();
    PlatformContext::initTime = std::chrono::high_resolution_clock::now();
    PlatformContext::lastFrameTime = PlatformContext::initTime;
}

void Platform::Deinit()
{
    PlatformContext::platform.reset();
}

bool Platform::Poll()
{
    auto frameTime = std::chrono::high_resolution_clock::now();
    _deltaTime = std::chrono::duration<double>(frameTime - PlatformContext::lastFrameTime).count();
    _elapsedTime = std::chrono::duration<double>(frameTime - PlatformContext::initTime).count();
    PlatformContext::lastFrameTime = frameTime;

    return PlatformContext::platform->Poll();
}

wgpu::Device Platform::GetDevice()
{
    return PlatformContext::platform->GetDevice();
}

SharedPtr<Window> Platform::CreateWindow(const WindowDescriptor &descriptor)
{
    return PlatformContext::platform->CreateWindow(descriptor);
}

} // namespace chronicle