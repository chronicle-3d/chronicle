// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#pragma once

#include "Common/Common.h"
#include "Platform/Platform.h"

namespace chronicle
{

class Chronicle
{
  public:
    static void Init();
    static void Run();

  private:
    static inline Unique<Platform> _platform{};
    static inline Ref<Window> _window{};
};

} // namespace chronicle