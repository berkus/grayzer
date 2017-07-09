//
//  Description......: Marble procedural texture
//
#pragma once

#include "texture/Texture.h"
#include "ColorTable.h"

class marble : public texture
{
    public:
        int         squeeze;
        color_table tbl;

        marble( double t = 1.0, int s = 1 );

        virtual void apply( Vector&, surface_data& );
};

inline marble::marble( double t, int s )
: texture()
, squeeze( s )
, tbl()
{
    turb = t;
}
