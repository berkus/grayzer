//
//  @brief base geometric object plane
//
#ifndef _PLANE_
#define _PLANE_

#include "math/Vector.h"
#include "geom/GeomObj.h"

//
//  уравнение плоскости: (normal,r) + dist = 0
//
class plane : public geometric_object
{
    public:
        Vector normal;          // единичный вектор нормали к плоскости
        double dist;            // расстояние от начала координат

        plane( Vector& n, double d );
        plane( double, double, double, double ); // ax + by + cz + d = 0

        virtual bool intersect( ray&, double& );
        virtual Vector find_normal( Vector& ) { return normal; }
};


inline plane::plane( Vector& n, double d )
: normal( n )
, dist( d )
{}


#endif // _PLANE_
