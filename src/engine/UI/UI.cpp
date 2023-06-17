// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "UI.h"

#include <RmlUi/Core.h>

namespace chronicle
{

void UI::Init()
{
    _rendererBackend = MakeUnique<RenderBackend>();
    _systemBackend = MakeUnique<SystemBackend>();
    _fileBackend = MakeUnique<FileBackend>();

    // Install the custom interfaces constructed by the backend before initializing RmlUi.
    Rml::SetSystemInterface(_systemBackend.get());
    Rml::SetRenderInterface(_rendererBackend.get());
    Rml::SetFileInterface(_fileBackend.get());

    // RmlUi initialisation.
    Rml::Initialise();
}

void UI::Deinit()
{
    Rml::Shutdown();
}

} // namespace chronicle