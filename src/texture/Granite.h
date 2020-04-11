//
//  Description..: granite procedural texture
//
#pragma once

#include "texture/Texture.h"
#include "ColorTable.h"

class Granite : public Texture
{
public:
    ColorTable tbl;

    Granite() : Texture(), tbl() {}

    void apply( Vector&, Grayzer::SurfaceData& ) override;
};
