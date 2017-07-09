//
//  @brief Cylinder basic geometric object
//
#pragma once

#include "math/Vector.h"
#include "geom/GeomObj.h"

class Cylinder : public GeometricObject
{
public:
    Vector loc;
    Vector dir;
    double radius;

    Cylinder( Vector&, Vector&, double );

    bool intersect( Ray&, double& ) override;
    Vector find_normal( Vector& ) override;

protected:
    Vector e1, e2;
    double d1, d2;
    double len, len2;
    double radius2, radius4; // radius squared and radius fourth power
};
