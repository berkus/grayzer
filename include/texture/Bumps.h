//
//  Description......: Bumps noise texture
//
#pragma once

#include "texture/Texture.h"

class bumps : public texture
{
    public:
        double amount;

        bumps( double a = 1.0 ) : texture(), amount( a ) {}

        virtual void apply( Vector&, surface_data& );
};
