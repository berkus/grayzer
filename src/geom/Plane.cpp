//
//  @brief plane geometric object
//
#include "Externs.h"
#include "environment/Geometry.h"
#include "geom/Plane.h"

//
// plane constructor: equation   ax + by  + cz + d = 0
//
Plane::Plane( double a, double b, double c,  double d )
{
   normal = Vector(a,b,c);
   double norm = !normal;

   normal /= norm;
   dist = d / norm;
}

bool Plane::intersect(Ray& r, double& t)
{
   STAT( PlaneTestCount++  );

   double vd = normal & r.dir;

   if(   vd > -EPS && vd   < EPS )
   {
      STAT( PlaneTestMisses++ );
      return false;
   }

   t =   -((normal & r.org) + dist) / vd;

   if(   t >   geom_threshold )
      return true;
   else
   {
      STAT(PlaneTestMisses++);
      return false;
   }
}
