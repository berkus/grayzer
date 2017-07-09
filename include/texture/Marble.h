//
//  Description......: Marble procedural texture
//
#pragma once

#include "texture/Texture.h"
#include "ColorTable.h"

class Marble : public Texture
{
    public:
        int        squeeze;
        ColorTable tbl;

        Marble( double t = 1.0, int s = 1 )
            : Texture()
            , squeeze( s )
            , tbl()
        {
            turb = t;
        }

        void apply( Vector&, Grayzer::SurfaceData& ) override;
};
