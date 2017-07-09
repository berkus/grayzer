//
//  @brief point_light light source
//
#pragma once

#include "light/LightSource.h"

class PointLight : public LightSource
{
public:
    Vector loc;
    double dist_scale;

    PointLight( const Vector& l, double d = 1.0 )
        : LightSource()
        , loc( l )
        , dist_scale( d )
    {}

    double shadow( Vector&, Vector& ) override;
};
