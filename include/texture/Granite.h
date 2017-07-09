//
//  Description..: granite procedural texture
//
#pragma once

#include "texture/Texture.h"
#include "ColorTable.h"

class granite : public texture
{
    public:
        color_table tbl;

        granite() : texture(), tbl() {}

        virtual void apply( Vector&, surface_data& );
};
