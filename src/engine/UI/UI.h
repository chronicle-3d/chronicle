// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#pragma once

#include "Common/Common.h"

#include "RenderBackend.h"
#include "SystemBackend.h"

namespace chronicle
{

class UI
{
  public:
    static void Init();
    static void Deinit();

  private:
    static inline Unique<RenderBackend> _rendererBackend{};
    static inline Unique<SystemBackend> _systemBackend{};
};

} // namespace chronicle