//
//  File.........: planemap.hpp
//  Description..: planar mapping class plane_map
//
#pragma once

#include "map.hpp"

class plane_map : public map
{
    public:
        vector eu,ev;

        plane_map( vector& n, vector& e1 );

        virtual vector apply( vector& p );
        virtual void find_tangent( vector&, vector& tu, vector& tv );
};

inline plane_map::plane_map( vector& n, vector& e1 )
: eu( e1 - n * (n & e1) / (n & n) )
, ev( n ^ e1 )
{}

inline vector plane_map::apply( vector& p )
{
    return vector( p & eu, p & ev, 0 );
}

inline void vector::find_tangent( vector&, vector& tu, vector& tv )
{
    tu = eu;
    tv = ev;
}
