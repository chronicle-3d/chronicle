// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#pragma once

#include "Common/Common.h"

#include <RmlUi/Core.h>

namespace chronicle
{

class FileBackend : public Rml::FileInterface
{
  public:
    Rml::FileHandle Open(const Rml::String &path) override;
    void Close(Rml::FileHandle file) override;
    size_t Read(void *buffer, size_t size, Rml::FileHandle file) override;
    bool Seek(Rml::FileHandle file, long offset, int origin) override;
    size_t Tell(Rml::FileHandle file) override;
    //size_t Length(Rml::FileHandle file) override;
    //bool LoadFile(const Rml::String &path, Rml::String &out_data) override;
};

} // namespace chronicle