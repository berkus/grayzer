//
//  Description..: wood procedural texture
//
#pragma once

#include "texture/Texture.h"
#include "Noise.h"

class Wood : public Texture
{
    public:
        double ring_spacing;
        int    squeeze;

        Wood( double r, double t, int s = 1 )
            : Texture()
            , ring_spacing( r )
            , squeeze( s )
        {
            turb = t;
        }

        void apply( Vector&, Grayzer::SurfaceData& ) override;
};
