//
//  @brief basic geometric object sphere
//
#pragma once

#include "geom/GeomObj.h"

class Sphere : public GeometricObject
{
    public:
        Vector loc;             // center
        double radius,radius2;  // radius & radius squared

        Sphere(Vector const& c, double r)
            : loc(c)
            , radius(r)
            , radius2(r * r)
        {}

        bool intersect(Ray&, double&) override;
        Vector find_normal(Vector&) override;
};
