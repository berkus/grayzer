//
//  File.........: spotlit.hpp
//  Description..: spot_light light source
//
#pragma once

#include "light/LightSource.h"

class spot_light : public light_source
{
    public:
        Vector loc;
        Vector dir;
        double cone_angle,
               end_cone_angle;
        int    beam_distribution;
        double dist_scale;

        spot_light( Vector& l, Vector& d, double a, double da,
                                          int bd, double ds = 1.0 );

        virtual double shadow( Vector&, Vector& );
};

inline spot_light::spot_light( Vector& l, Vector& d,
                               double a, double da,
                               int bd, double ds )
: light_source()
, loc( l )
, dir( d )
, cone_angle( a )
, end_cone_angle( da )
, beam_distribution( bd )
, dist_scale( ds )
{}
