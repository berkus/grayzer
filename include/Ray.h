//
//  File.........: ray.hpp
//  Description..: class ray
//
#ifndef _RAY_
#define _RAY_

#include "math/Vector.h"


class ray
{
    public:
        Vector org;
        Vector dir; // direction must be normalized

        ray() {};
        ray( Vector& o, Vector& d ) : org( o ), dir( d ) {}

        Vector point( double t ) { return org + dir * t; }
};


#endif // _RAY_
