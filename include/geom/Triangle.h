//
//  @brief geometric object triangle
//
#pragma once

#include "geom/Rect.h"

class Triangle : public Rectangle
{
public:
    Triangle( const Vector& l, const Vector& s1, const Vector& s2 ) : Rectangle(l,s1,s2) {}

    bool intersect(Ray&, double&) override;
};
