//
//  Description..: planar mapping class plane_map
//
#pragma once

#include "map/Map.h"

class PlaneMap : public Map
{
public:
    Vector eu,ev;

    PlaneMap(Vector& n, Vector& e1)
        : eu( e1 - n * (n & e1) / (n & n) )
        , ev( n ^ e1 )
    {}

    Vector apply(Vector& p) override
    {
        return vector( p & eu, p & ev, 0 );
    }
    void find_tangent(Vector&, Vector& tu, Vector& tv) override
    {
        tu = eu;
        tv = ev;
    }
};
