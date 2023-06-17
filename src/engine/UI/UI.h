// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#pragma once

#include "Common/Common.h"

#include "FileBackend.h"
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
    static inline UniquePtr<RenderBackend> _rendererBackend{};
    static inline UniquePtr<SystemBackend> _systemBackend{};
    static inline UniquePtr<FileBackend> _fileBackend{};
};

} // namespace chronicle