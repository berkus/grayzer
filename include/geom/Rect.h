//
//  @brief rectangle geometric object
//
#pragma once

#include "geom/GeomObj.h"

class Rectangle : public GeometricObject
{
public:
    Vector loc;
    Vector side1, side2;
    Vector n;
    Vector ku, kv;
    double u0,v0;

    Rectangle( const Vector&, const Vector&, const Vector& );

    bool intersect(Ray&, double&) override;
    Vector find_normal(Vector&) override { return n; }
};
