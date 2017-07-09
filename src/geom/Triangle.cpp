//
//  @brief triangle geometric object realization
//
#include "Externs.h"
#include "environment/Geometry.h"
#include "geom/Triangle.h"


bool triangle::intersect( ray& r, double& t  )
{
   STAT( TriangleTestCount++  );
   STAT( TriangleTestMisses++ );

   double vd = n &   r.dir;

   if(   vd > -EPS && vd   < EPS )
   {
      STAT( TriangleTestMisses++ );
      return false;
   }

   if(   (t = ((loc - r.org)  & n) / vd) < geom_threshold   )
   {
      STAT( TriangleTestMisses++ );
      return false;
   }

   Vector p = r.point(t);
   double u = u0 +   (p & ku);
   double v = v0 +   (p & kv);

#ifdef STATISTICS
   if(   u >   0 && v > 0 && u   + v   < 1   )
      return true;
   else
   {
      TriangleTestMisses++;
      return false;
   }
#else
   return u > 0 &&   v >   0 && u + v < 1;
#endif
}
