//
//  Description......: Brick procedural texture
//
#pragma once

#include "texture/Texture.h"

class brick : public texture
{
    public:
        brick(const Vector& bs, const Vector& ms, const Vector& bc, const Vector& mc);

        virtual void apply( Vector&, surface_data& );

    public:
        Vector
            brick_size,
            mortar_size,
            brick_color,
            mortar_color;
};

inline brick::brick(const Vector& bs, const Vector& ms, const Vector& bc, const Vector& mc)
: texture()
, brick_size( bs )
, mortar_size( ms / bs )
, brick_color( bc )
, mortar_color( mc )
{}
