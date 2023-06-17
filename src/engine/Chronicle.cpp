// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "Chronicle.h"

namespace chronicle
{

void Chronicle::Init()
{
    _platform = Platform::Create();
    _window = _platform->CreateWindow({});
}

void Chronicle::Run()
{
    while (_platform->Poll())
    {
    }
}

} // namespace chronicle