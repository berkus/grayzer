//
//  Description......: gradient color texture
//
#pragma once

#include "texture/Texture.h"
#include "ColorTable.h"

class Gradient : public Texture
{
    public:
        Vector     grad;
        ColorTable tbl;

        Gradient( Vector g ) : Texture(), grad( g ), tbl() {}

        void apply(Vector&, Grayzer::SurfaceData&) override;
};
