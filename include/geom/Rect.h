//
//  @brief rectangle geometric object
//
#ifndef _RECT_
#define _RECT_

#include "geom/GeomObj.h"


class rectangle : public geometric_object
{
    public:
        Vector loc;
        Vector side1, side2;
        Vector n;
        Vector ku, kv;
        double u0,v0;

        rectangle( const Vector&, const Vector&, const Vector& );

        virtual bool intersect( ray&, double& );
        virtual Vector find_normal( Vector& ) { return n; }
};


#endif // _RECT_
