// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "RenderBackend.h"

namespace chronicle
{
void RenderBackend::RenderGeometry(Rml::Vertex *vertices, int num_vertices, int *indices, int num_indices,
                                   Rml::TextureHandle texture, const Rml::Vector2f &translation)
{
}

Rml::CompiledGeometryHandle RenderBackend::CompileGeometry(Rml::Vertex *vertices, int num_vertices, int *indices,
                                                           int num_indices, Rml::TextureHandle texture)
{
    return Rml::CompiledGeometryHandle();
}

void RenderBackend::RenderCompiledGeometry(Rml::CompiledGeometryHandle geometry, const Rml::Vector2f &translation)
{
}

void RenderBackend::ReleaseCompiledGeometry(Rml::CompiledGeometryHandle geometry)
{
}

void RenderBackend::EnableScissorRegion(bool enable)
{
}

void RenderBackend::SetScissorRegion(int x, int y, int width, int height)
{
}

bool RenderBackend::LoadTexture(Rml::TextureHandle &texture_handle, Rml::Vector2i &texture_dimensions,
                                const Rml::String &source)
{
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

void RenderBackend::SetTransform(const Rml::Matrix4f *transform)
{
}

} // namespace chronicle