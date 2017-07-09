//
//  @brief geometric object triangle
//
#pragma once

#include "geom/Rect.h"

class Triangle : public Rectangle
{
    public:
        Triangle( Vector& l, Vector& s1, Vector& s2 ) : Rectangle(l,s1,s2) {}

        bool intersect(Ray&, double&) override;
};
