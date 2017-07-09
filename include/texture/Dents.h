//
//  File.............: dents.hpp
//  Description......: Dents procedural perturbation texture
//
#pragma once

#include "texture/Texture.h"

class dents : public texture
{
    public:
        double amount;

        dents( double a = 1.0 ) : texture(), amount( a ) {}

        virtual void apply( Vector&, surface_data& );
};
