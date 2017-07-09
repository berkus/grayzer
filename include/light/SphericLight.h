//
//  @brief spheric_light light source - casts soft shadows
//
#pragma once

#include "light/LightSource.h"

class SphericLight : public LightSource
{
public:
    Vector loc;
    double radius;
    double dist_scale;

    SphericLight( Vector& l, double r, double d = 1.0 )
        : LightSource()
        , loc( l )
        , radius( r )
        , dist_scale( d )
    {}

    double shadow(Scene* scene, Vector&, Vector&) override;
};
