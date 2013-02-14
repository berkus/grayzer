//
//  @brief Cylinder basic geometric object
//
#ifndef _CYLINDER_
#define _CYLINDER_

#include "math/Vector.h"
#include "go/GeomObj.h"


class cylinder : public geometric_object
{
    public:
        Vector loc;
        Vector dir;
        double radius;

        cylinder( Vector&, Vector&, double );

        virtual bool intersect( ray&, double& );
        virtual Vector find_normal( Vector& );

    protected:
        Vector e1, e2;
        double d1, d2;
        double len, len2;
        double radius2, radius4; // radius squared and radius fourth power
};


#endif // _CYLINDER_ //
