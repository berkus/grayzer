//
//  Description......: Bozo procedural texture
//
#pragma once

#include "texture/Texture.h"
#include "ColorTable.h"

class Bozo : public Texture
{
    public:
        Bozo( double t = 0.0 )
            : Texture()
            , tbl()
        {
            turb = t;
        }

        void apply( Vector&, Grayzer::SurfaceData& ) override;

    public:
        ColorTable tbl;
};
