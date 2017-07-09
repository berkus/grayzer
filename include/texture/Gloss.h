//
//  Description......: gloss procedural texture
//
#pragma once

#include "texture/Texture.h"

class gloss : public texture
{
    public:
        gloss() : texture() {}

        virtual void apply( Vector&, surface_data& );
};
