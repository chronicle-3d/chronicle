// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#pragma once

#include "Common/Common.h"

#include <dawn/webgpu_cpp.h>

namespace chronicle
{

class WindowError : public std::runtime_error
{
  public:
    using runtime_error::runtime_error;

    explicit WindowError(const std::string &message) : runtime_error(message.c_str())
    {
    }
};

struct WindowDescriptor
{
    std::string title{};
    uint32_t width{800};
    uint32_t height{600};
};

class Window
{
  public:
    virtual ~Window() = default;

    virtual void Close() = 0;

    [[nodiscard]] virtual const std::string &GetTitle() const = 0;
    [[nodiscard]] virtual uint32_t GetWidth() const = 0;
    [[nodiscard]] virtual uint32_t GetHeight() const = 0;
    [[nodiscard]] virtual wgpu::SwapChain GetSwapChain() const = 0;
};

} // namespace chronicle