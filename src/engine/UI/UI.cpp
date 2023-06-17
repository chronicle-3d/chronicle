// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "UI.h"

#include <RmlUi/Core.h>

namespace chronicle
{

void UI::Init()
{
    _rendererBackend = std::make_unique<RenderBackend>();
    _systemBackend = std::make_unique<SystemBackend>();

    // Install the custom interfaces constructed by the backend before initializing RmlUi.
    Rml::SetSystemInterface(_systemBackend.get());
    Rml::SetRenderInterface(_rendererBackend.get());

    // RmlUi initialisation.
    Rml::Initialise();
}

void UI::Deinit()
{
    Rml::Shutdown();
}

} // namespace chronicle