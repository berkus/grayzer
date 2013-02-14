//
//  @brief basic geometric object sphere
//
#ifndef _SPHERE_
#define _SPHERE_

#include "go/GeomObj.h"


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


#endif // _SPHERE_
