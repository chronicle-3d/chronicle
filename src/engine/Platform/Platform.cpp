// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "Platform.h"

#include "GLFW/PlatformGLFW.h"

namespace chronicle
{

Unique<Platform> Platform::Create()
{
    return std::make_unique<internal::glfw::PlatformGLFW>();
}

} // namespace chronicle