// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#pragma once

#include "Common/Common.h"

#include <RmlUi/Core.h>

namespace chronicle
{

class RenderBackend : public Rml::RenderInterface
{
  public:
    void RenderGeometry(Rml::Vertex *vertices, int num_vertices, int *indices, int num_indices,
                        Rml::TextureHandle texture, const Rml::Vector2f &translation) override;

    Rml::CompiledGeometryHandle CompileGeometry(Rml::Vertex *vertices, int num_vertices, int *indices, int num_indices,
                                                Rml::TextureHandle texture) override;

    void RenderCompiledGeometry(Rml::CompiledGeometryHandle geometry, const Rml::Vector2f &translation) override;

    void ReleaseCompiledGeometry(Rml::CompiledGeometryHandle geometry) override;

    void EnableScissorRegion(bool enable) override;

    void SetScissorRegion(int x, int y, int width, int height) override;

    bool LoadTexture(Rml::TextureHandle &texture_handle, Rml::Vector2i &texture_dimensions,
                     const Rml::String &source) override;

    bool GenerateTexture(Rml::TextureHandle &texture_handle, const Rml::byte *source,
                         const Rml::Vector2i &source_dimensions) override;

    void ReleaseTexture(Rml::TextureHandle texture) override;

    void SetTransform(const Rml::Matrix4f *transform) override;
};

} // namespace chronicle