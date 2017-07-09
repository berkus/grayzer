//
//  @brief sphere geometric  object
//  @sa mesh_sphere mesh   object
//
#include "Externs.h"
#include "environment/Geometry.h"
#include "geom/Sphere.h"

bool Sphere::intersect(Ray& ray, double& t)
{
   STAT( SphereTestCount++  );
   STAT( SphereTestMisses++ );

   Vector l = loc - ray.org;
   double l20c = l   & l;
   double tca = l & ray.dir;
   double t2hc = radius2 - l20c + tca * tca;
   double t2;

   if(   t2hc <=  0.0   )
   {
      STAT( SphereTestMisses++ );
      return false;
   }

   t2hc = sqrt(t2hc);

   if(   tca   < t2hc)  // we are inside
   {
      t  = tca + t2hc;
      t2 = tca - t2hc;
   }
   else        // we are outside
   {
      t  = tca - t2hc;
      t2 = tca + t2hc;
   }

   if(   fabs(t)  < geom_threshold ) t = t2;

#ifdef STATISTICS
   if(   t >   geom_threshold )
      return true;
   else
   {
      SphereTestMisses++;
      return false;
   }
#else
   return t > geom_threshold;
#endif
}


Vector Sphere::find_normal(   Vector&  p )
{
   return (p - loc) / radius;
}
