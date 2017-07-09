//
//  Description..: planar mapping class plane_map
//
#pragma once

#include "map/Map.h"

class PlaneMap : public Map
{
    Vector eu, ev;

public:
    PlaneMap(Vector const& n, Vector const& e1)
        : eu( e1 - n * (n & e1) / (n & n) )
        , ev( n ^ e1 )
    {}

    Vector apply(Vector& p) override
    {
        return Vector( p & eu, p & ev, 0 );
    }

    void find_tangent(Vector&, Vector& tu, Vector& tv) override
    {
        tu = eu;
        tv = ev;
    }
};
