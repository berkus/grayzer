//
//  @brief plane geometric object
//
#include "Externs.h"
#include "environment/Geometry.h"
#include "geom/Plane.h"


//
// plane constructor: equation   ax + by  + cz + d = 0
//
plane::plane( double a, double b, double c,  double d )
{
   normal = Vector(a,b,c);
   double norm = !normal;

   normal /= norm;
   dist = d / norm;
}


bool plane::intersect( ray&   r, double& t )
{
   STAT( PlaneTestCount++  );
   STAT( PlaneTestMisses++ );

   double vd = normal & r.dir;

   if(   vd > -EPS && vd   < EPS )
   {
      STAT( PlaneTestMisses++ );
      return false;
   }

   t =   -((normal & r.org) + dist) / vd;

#ifdef STATISTICS
   if(   t >   geom_threshold )
      return true;
   else
   {
      PlaneTestMisses++;
      return false;
   }
#else
    return  t >   geom_threshold;
#endif
}
