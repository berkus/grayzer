//
//  Description..: wrinkles procedural perturbation texture
//
#pragma once

#include "texture/Texture.h"

class Wrinkles : public Texture
{
    public:
        double amount;

        Wrinkles( double a = 1.0 ) : Texture(), amount( a ) {}

        void apply( Vector&, Grayzer::SurfaceData& ) override;
};
