//
//  @brief base class texture
//
#pragma once

#include "math/Vector.h"
#include "SurfaceData.h"
#include "geom/GeomObj.h"

class Texture
{
    public:
        Texture*          next;
        GeometricObject*  object;
        double            turb;
        int               octaves;
        Vector            offs, scale;

        Texture()
            : next( 0 )
            , object( 0 )
            , turb( 0.0 )
            , octaves( 6 )
            , offs( 0 )
            , scale( 1 )
        {}

        virtual ~Texture() {}

        virtual void apply( Vector&, Grayzer::SurfaceData& ) = 0;
};
