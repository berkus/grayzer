//
//  Comments.........:
//    98/02/11
//      Modified bounding intersection methods. The old method of
//      reimplementing check(ray& r) has many disadvantages, so now
//      we use bounds object as bounding volume and can use common
//      BoundingVolume class for many different types of BVs.
//
#pragma once

#include "types.h"
#include "geom/GeomObj.hpp"

class BoundingVolume
{
    public:
        GeometricObject * bounds;     // the bounds
        BoundingVolume *  sub;        // subcontained bounding volume
        BoundingVolume *  next;       // next bv of the same level
        GeometricObject **obj_list;   // objects enclosed in this bv
        int obj_count, obj_limit;      // for dynamic object array

        BoundingVolume();
       ~BoundingVolume();

        void add( GeometricObject * );
        void add( BoundingVolume * );
        void set_bounds( GeometricObject * );

        GeometricObject *intersect( Ray&, double& );
};
