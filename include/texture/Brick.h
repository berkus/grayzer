//
//  Description......: Brick procedural texture
//
#pragma once

#include "texture/Texture.h"

class Brick : public Texture
{
    public:
        Brick(const Vector& bs, const Vector& ms, const Vector& bc, const Vector& mc)
            : Texture()
            , brick_size( bs )
            , mortar_size( ms / bs )
            , brick_color( bc )
            , mortar_color( mc )
        {}

        void apply( Vector&, Grayzer::SurfaceData& ) override;

    public:
        Vector
            brick_size,
            mortar_size,
            brick_color,
            mortar_color;
};
