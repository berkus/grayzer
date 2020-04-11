//
//  @brief Box basic geometric object
//
#pragma once

#include "math/Vector.h"
#include "geom/GeomObj.h"

class Box : public GeometricObject
{
public:
    Vector loc;      // origin
    Vector e1,e2,e3; // edges

    Box(Vector const& l, Vector const& s1, Vector const& s2, Vector const& s3)
        : loc( l )
        , e1( s1 )
        , e2( s2 )
        , e3( s3 )
    {
        center = loc + (e1 + e2 + e3) * 0.5;
        init_normals();
    }

    Box(Vector const& l, double a, double b, double c)
        : loc( l )
        , e1( Vector(a,0,0) )
        , e2( Vector(0,b,0) )
        , e3( Vector(0,0,c) )
    {
        center = loc + (e1 + e2 + e3) * 0.5;
        init_normals();
    }

    bool intersect(Ray&, double&) override;
    Vector find_normal(Vector&) override;

protected:
    Vector n[3];            // normals to sides
    double d1[3],d2[3];     // distances for plane equation
    Vector center;          // center of
private:
    void init_normals();
};
