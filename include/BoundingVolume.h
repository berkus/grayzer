//
//  File.............: boundvol.hpp
//  Description......: class bounding_volume
//  Comments.........:
//    98/02/11
//      Modified bounding intersection methods. The old method of
//      reimplementing check(ray& r) has many disadvantages, so now
//      we use bounds object as bounding volume and can use common
//      bounding_volume class for many different types of BVs.
//
#pragma once

#include "types.h"
#include "geomobj.hpp"

class bounding_volume
{
    public:
        geometric_object * bounds;     // the bounds
        bounding_volume *  sub;        // subcontained bounding volume
        bounding_volume *  next;       // next bv of the same level
        geometric_object **obj_list;   // objects enclosed in this bv
        int obj_count, obj_limit;      // for dynamic object array

        bounding_volume();
       ~bounding_volume();

        void add( geometric_object * );
        void add( bounding_volume * );
        void set_bounds( geometric_object * );

        geometric_object *intersect( ray&, double& );
};
