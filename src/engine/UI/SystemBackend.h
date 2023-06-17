// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#pragma once

#include "Common/Common.h"

#include <RmlUi/Core.h>

namespace chronicle
{

class SystemBackend : public Rml::SystemInterface
{
  public:
    double GetElapsedTime() override;

    bool LogMessage(Rml::Log::Type type, const Rml::String &message) override;
};

} // namespace chronicle