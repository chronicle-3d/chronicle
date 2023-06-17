// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "PlatformGLFW.h"
#include "ContextGLFW.h"
#include "WindowGLFW.h"

#include <GLFW/glfw3.h>
#include <dawn/dawn_proc.h>

namespace chronicle::internal::glfw
{

// Default to D3D12, Metal, Vulkan, OpenGL in that order as D3D12 and Metal are the preferred on
// their respective platforms, and Vulkan is preferred to OpenGL
#if defined(DAWN_ENABLE_BACKEND_D3D12)
constexpr wgpu::BackendType backendType = wgpu::BackendType::D3D12;
#elif defined(DAWN_ENABLE_BACKEND_D3D11)
constexpr wgpu::BackendType backendType = wgpu::BackendType::D3D11;
#elif defined(DAWN_ENABLE_BACKEND_METAL)
constexpr wgpu::BackendType backendType = wgpu::BackendType::Metal;
#elif defined(DAWN_ENABLE_BACKEND_VULKAN)
constexpr wgpu::BackendType backendType = wgpu::BackendType::Vulkan;
#elif defined(DAWN_ENABLE_BACKEND_OPENGLES)
constexpr wgpu::BackendType backendType = wgpu::BackendType::OpenGLES;
#elif defined(DAWN_ENABLE_BACKEND_DESKTOP_GL)
constexpr wgpu::BackendType backendType = wgpu::BackendType::OpenGL;
#else
#error
#endif

void PrintDeviceError(WGPUErrorType errorType, const char *message, void *)
{
    CHRLOG_ERROR("Device error: {} ({})", message, magic_enum::enum_name(errorType));
}

void DeviceLostCallback(WGPUDeviceLostReason reason, const char *message, void *)
{
    CHRLOG_ERROR("Device lost: {} ({})", message, magic_enum::enum_name(reason));
}

void PrintGLFWError(int code, const char *message)
{
    CHRLOG_ERROR("GLFW: {} ({})", message, code);
}

void DeviceLogCallback(WGPULoggingType type, const char *message, void *)
{
    switch (type)
    {
    case WGPULoggingType_Verbose:
        CHRLOG_DEBUG("Device: {}", message);
        break;
    case WGPULoggingType_Info:
        CHRLOG_INFO("Device: {}", message);
        break;
    case WGPULoggingType_Warning:
        CHRLOG_WARN("Device: {}", message);
        break;
    case WGPULoggingType_Force32:
    case WGPULoggingType_Error:
        CHRLOG_ERROR("Device: {}", message);
        break;
    }
}

PlatformGLFW::PlatformGLFW()
{
    _instance = MakeUnique<dawn::native::Instance>();
    _instance->DiscoverDefaultPhysicalDevices();

    // Get an adapter for the backend to use, and create the device.
    dawn::native::Adapter backendAdapter;
    {
        std::vector<dawn::native::Adapter> adapters = _instance->GetAdapters();
        auto adapterIt =
            std::ranges::find_if(adapters.begin(), adapters.end(), [](const dawn::native::Adapter adapter) {
                wgpu::AdapterProperties properties;
                adapter.GetProperties(&properties);
                return properties.backendType == backendType;
            });
        assert(adapterIt != adapters.end());
        backendAdapter = *adapterIt;
    }

    wgpu::DeviceDescriptor deviceDesc{};
    _device = wgpu::Device::Acquire(backendAdapter.CreateDevice(&deviceDesc));

    const auto &backendProcs = dawn::native::GetProcs();
    backendProcs.deviceSetUncapturedErrorCallback(_device.Get(), PrintDeviceError, nullptr);
    backendProcs.deviceSetDeviceLostCallback(_device.Get(), DeviceLostCallback, nullptr);
    backendProcs.deviceSetLoggingCallback(_device.Get(), DeviceLogCallback, nullptr);
    dawnProcSetProcs(&backendProcs);

    glfwSetErrorCallback(PrintGLFWError);
    glfwInit();
}

PlatformGLFW::~PlatformGLFW()
{
    glfwTerminate();

    // must release before destroy instance
    _device.Release();
}

bool PlatformGLFW::Poll()
{
    if (ContextGLFW::windows.empty())
    {
        return false;
    }

    std::set<WindowGLFW *> windowsToErase{};
    for (auto *window : ContextGLFW::windows)
    {
        if (!window->Poll())
        {
            windowsToErase.insert(window);
        }
    }

    for (auto *window : windowsToErase)
    {
        ContextGLFW::windows.erase(window);
    }

    glfwPollEvents();

    return true;
}

SharedPtr<Window> PlatformGLFW::CreateWindow(const WindowDescriptor &descriptor)
{
    return MakeShared<WindowGLFW>(_instance.get(), _device, descriptor);
}

} // namespace chronicle::internal::glfw