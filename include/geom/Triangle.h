//
//  @brief geometric object triangle
//
#pragma once

#include "geom/Rect.h"

class triangle : public rectangle
{
    public:
        triangle( Vector& l, Vector& s1, Vector& s2 ) : rectangle(l,s1,s2) {}

        virtual bool intersect( ray&, double& );
};
