//
//  File.........: planemap.hpp
//  Description..: planar mapping class plane_map
//
#pragma once

#include "map.hpp"

class PlaneMap : public Map
{
    public:
        Vector eu,ev;

        PlaneMap( vector& n, vector& e1 )
            : eu( e1 - n * (n & e1) / (n & n) )
            , ev( n ^ e1 )
        {}

        Vector apply( vector& p ) override
        {
            return vector( p & eu, p & ev, 0 );
        }
        void find_tangent( vector&, vector& tu, vector& tv ) override
        {
            tu = eu;
            tv = ev;
        }
};
