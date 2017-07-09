//
//  Description..: spot_light light source
//
#pragma once

#include "light/LightSource.h"

class SpotLight : public LightSource
{
public:
    Vector loc;
    Vector dir;
    double cone_angle,
           end_cone_angle;
    int    beam_distribution;
    double dist_scale;

    SpotLight( Vector& l, Vector& d, double a, double da,
                                      int bd, double ds = 1.0 )
        : LightSource()
        , loc( l )
        , dir( d )
        , cone_angle( a )
        , end_cone_angle( da )
        , beam_distribution( bd )
        , dist_scale( ds )
    {}

    double shadow( Vector&, Vector& ) override;
};
