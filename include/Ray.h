//
//  File.........: ray.hpp
//  Description..: class ray
//
#pragma once

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
