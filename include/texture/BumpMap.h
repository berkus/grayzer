//
//  Description......: Bump map texture
//
#pragma once

#include "texture/Texture.h"
#include "image/Image.h"

class BumpMap : public Texture
{
    public:
        BumpMap(Image *i, double a)
            : Texture()
            , map(i)
            , amount(a)
        {}
       ~BumpMap()
        {
            delete map;
        }

        void apply( Vector&, Grayzer::SurfaceData& ) override;

    public:
        Image *map;
        double amount;
};
