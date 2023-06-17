// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "SystemBackend.h"

namespace chronicle
{

double SystemBackend::GetElapsedTime()
{
    return 0.0;
}

bool SystemBackend::LogMessage(Rml::Log::Type type, const Rml::String &message)
{
    switch (type)
    {
    case Rml::Log::LT_ERROR:
    case Rml::Log::LT_ASSERT:
        CHRLOG_ERROR("RmlUI: {}", message);
        break;
    case Rml::Log::LT_WARNING:
        CHRLOG_WARN("RmlUI: {}", message);
        break;
    case Rml::Log::LT_INFO:
        CHRLOG_INFO("RmlUI: {}", message);
        break;
    case Rml::Log::LT_DEBUG:
        CHRLOG_DEBUG("RmlUI: {}", message);
        break;
    }

    return true;
}

} // namespace chronicle