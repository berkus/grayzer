//
//  Description......: Checker texture
//
#pragma once

#include "texture/Texture.h"

class Checker : public Texture
{
    public:
        Vector color1, color2;

        Checker( Vector c1, Vector c2 )
            : Texture()
            , color1( c1 )
            , color2( c2 )
        {}

        void apply( Vector&, Grayzer::SurfaceData& ) override;
};
