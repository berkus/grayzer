//
//  @brief spheric_light light source - casts soft shadows
//
#ifndef _SPHRCLIT_
#define _SPHRCLIT_

#include "light/LightSource.h"


class spheric_light : public light_source
{
    public:
        Vector loc;
        double radius;
        double dist_scale;

        spheric_light( Vector& l, double r, double d = 1.0 );

        virtual double shadow( Vector&, Vector& );
};


inline spheric_light::spheric_light( Vector& l, double r, double d )
: light_source()
, loc( l )
, radius( r )
, dist_scale( d )
{}


#endif // _SPHRCLIT_
