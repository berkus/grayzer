//
//  @brief basic geometric object sphere
//
#pragma once

#include "geom/GeomObj.h"

class sphere : public geometric_object
{
    public:
        Vector loc;             // center
        double radius,radius2;  // radius & radius squared

        sphere( Vector& c, double r );

        virtual bool intersect( ray&, double& );
        virtual Vector find_normal( Vector& );
};

inline sphere::sphere( Vector& c, double r )
: loc( c )
, radius( r )
, radius2( r * r )
{}
