//
//  @brief point_light light source
//
#ifndef _POINTLIT_
#define _POINTLIT_

#include "light/LightSource.h"


class point_light : public light_source
{
    public:
        Vector loc;
        double dist_scale;

        point_light( const Vector& l, double d = 1.0 );

        virtual double shadow( Vector&, Vector& );
};


inline point_light::point_light( const Vector& l, double d )
: light_source()
, loc( l )
, dist_scale( d )
{}


#endif // _POINTLIT_
