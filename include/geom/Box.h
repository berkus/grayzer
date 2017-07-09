//
//  @brief Box basic geometric object
//
#ifndef _BOX_
#define _BOX_

#include "math/Vector.h"
#include "geom/GeomObj.h"


class box : public geometric_object
{
    public:
        Vector loc;      // origin
        Vector e1,e2,e3; // edges

        box( Vector&, Vector&, Vector&, Vector& );
        box( Vector&, double, double, double );

        virtual bool intersect( ray&, double& );
        virtual Vector find_normal( Vector& );

    protected:
        Vector n[3];            // normals to sides
        double d1[3],d2[3];     // distances for plane equation
        Vector center;          // center of
    private:
        void init_normals();
};


#endif // _BOX_ //
