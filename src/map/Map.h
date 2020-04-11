//
//  @brief base class Map for mapping coords support
//
#pragma once

#include "math/Vector.h"

class Map
{
public:
    virtual ~Map() {}

    // проектирует точку согласно типа проектирования
    virtual Vector apply( Vector& ) = 0;

    // определяет касательные векторы к координатным линиям
    // (u = const,v = const) в заданной точке
    virtual void find_tangent( Vector&, Vector&, Vector& ) = 0;
};
