//
//  Description..: ripples procedural perturbation texture
//
#pragma once

#include "texture/Texture.h"

class Ripples : public Texture
{
    public:
        Vector center;
        double wave_len;
        double phase;
        double amount;

        Ripples( const Vector& c, double a, double l, double p = 0 )
            : Texture()
            , center( c )
            , wave_len( l )
            , phase( p )
            , amount( a )
        {}

        void apply( Vector&, Grayzer::SurfaceData& ) override;
};
