// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "RenderBackend.h"

namespace chronicle
{
void RenderBackend::RenderGeometry(Rml::Vertex *vertices, int num_vertices, int *indices, int num_indices,
                                   Rml::TextureHandle texture, const Rml::Vector2f &translation)
{
}

//Rml::CompiledGeometryHandle RenderBackend::CompileGeometry(Rml::Vertex *vertices, int num_vertices, int *indices,
//                                                           int num_indices, Rml::TextureHandle texture)
//{
//    return Rml::CompiledGeometryHandle();
//}
//
//void RenderBackend::RenderCompiledGeometry(Rml::CompiledGeometryHandle geometry, const Rml::Vector2f &translation)
//{
//}
//
//void RenderBackend::ReleaseCompiledGeometry(Rml::CompiledGeometryHandle geometry)
//{
//}

void RenderBackend::EnableScissorRegion(bool enable)
{
}

void RenderBackend::SetScissorRegion(int x, int y, int width, int height)
{
}

bool RenderBackend::LoadTexture(Rml::TextureHandle &texture_handle, Rml::Vector2i &texture_dimensions,
                                const Rml::String &source)
{
    //Rml::FileInterface *file_interface = Rml::GetFileInterface();
    //Rml::FileHandle file_handle = file_interface->Open(source);
    //if (!file_handle)
    //    return false;
    //
    //file_interface->Seek(file_handle, 0, SEEK_END);
    //size_t buffer_size = file_interface->Tell(file_handle);
    //file_interface->Seek(file_handle, 0, SEEK_SET);
    //
	//RMLUI_ASSERTMSG(buffer_size > sizeof(RmlUi::TGAHeader),
    //                "Texture file size is smaller than TGAHeader, file must be corrupt or otherwise invalid");
    //if (buffer_size <= sizeof(TGAHeader))
    //{
    //    file_interface->Close(file_handle);
    //    return false;
    //}
    //
    //char *buffer = new char[buffer_size];
    //file_interface->Read(buffer, buffer_size, file_handle);
    //file_interface->Close(file_handle);
    //
    //
    //delete[] buffer;

    return false;
}

bool RenderBackend::GenerateTexture(Rml::TextureHandle &texture_handle, const Rml::byte *source,
                                    const Rml::Vector2i &source_dimensions)
{
    return false;
}

void RenderBackend::ReleaseTexture(Rml::TextureHandle texture)
{
}

//void RenderBackend::SetTransform(const Rml::Matrix4f *transform)
//{
//}

} // namespace chronicle