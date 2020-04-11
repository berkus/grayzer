//
//  @brief base geometric object plane
//
#pragma once

#include "math/Vector.h"
#include "geom/GeomObj.h"

//
//  уравнение плоскости: (normal,r) + dist = 0
//
class Plane : public GeometricObject
{
public:
    Vector normal;          // единичный вектор нормали к плоскости
    double dist;            // расстояние от начала координат

    Plane(Vector const& n, double d)
        : normal(n)
        , dist(d)
    {}
    Plane( double, double, double, double ); // ax + by + cz + d = 0

    bool intersect(Ray&, double& ) override;
    Vector find_normal( Vector& ) override { return normal; }
};
