// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#pragma once

#include "WindowGLFW.h"

namespace chronicle::internal::glfw
{

struct ContextGLFW
{
    static inline std::set<WindowGLFW *> windows{};
};

} // namespace chronicle::internal::glfw