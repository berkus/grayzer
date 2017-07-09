//
//  Description......: Color map texture
//
#pragma once

#include "texture/Texture.h"
#include "image/Image.h"

class color_map : public texture
{
    public:
        image *map;

        color_map( image *i ) : texture(), map( i ) {}
       ~color_map() { delete map; }

        virtual void apply( Vector&, surface_data& );
};
