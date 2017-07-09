//
//  Description..: wrinkles procedural perturbation texture
//
#pragma once

#include "texture/Texture.h"

class wrinkles : public texture
{
    public:
        double amount;

        wrinkles( double a = 1.0 ) : texture(), amount( a ) {}

        virtual void apply( Vector&, surface_data& );
};
