// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "FileBackend.h"

namespace chronicle
{

Rml::FileHandle FileBackend::Open(const Rml::String &path)
{
    auto newPath = fmt::format("{}/{}", ASSETS_DEBUG_PATH, path);
    return (Rml::FileHandle)fopen(newPath.c_str(), "rb");
}

void FileBackend::Close(Rml::FileHandle file)
{
    fclose((FILE *)file);
}

size_t FileBackend::Read(void *buffer, size_t size, Rml::FileHandle file)
{
    return fread(buffer, 1, size, (FILE *)file);
}

bool FileBackend::Seek(Rml::FileHandle file, long offset, int origin)
{
    return fseek((FILE *)file, offset, origin) == 0;
}

size_t FileBackend::Tell(Rml::FileHandle file)
{
    return ftell((FILE *)file);
}

//size_t RenderBackend::Length(Rml::FileHandle file)
//{
//    return size_t();
//}
//
//bool RenderBackend::LoadFile(const Rml::String &path, Rml::String &out_data)
//{
//    return false;
//}

} // namespace chronicle