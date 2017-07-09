//
//  @brief rectangle geometric object realization
//
#include "Externs.h"
#include "environment/Geometry.h"
#include "geom/Rect.h"


rectangle::rectangle( const Vector& l, const Vector& s1, const Vector& s2  )
{
   loc   = l;
   side1 =  s1;
   side2 =  s2;
   n =   normalize( side1 ^ side2 );

   double s11 = side1 & side1;
   double s12 = side1 & side2;
   double s22 = side2 & side2;
   double d = s11 * s22 - s12 * s22; // determinant

   ku = (side1 * s22 -  side2 *  s12) / d;
   kv = (side2 * s11 -  side1 *  s12) / d;
   u0 = -(loc & ku);
   v0 = -(loc & kv);
}


bool rectangle::intersect( ray&  r, double& t )
{
   STAT( RectTestCount++  );
   STAT( RectTestMisses++ );

   double vd = n &   r.dir;

   if(   vd > -EPS && vd   < EPS )
   {
      STAT( RectTestMisses++ );
      return false;
   }

   if(   (t = ((loc - r.org)  & n) / vd) < geom_threshold   )
   {
      STAT( RectTestMisses++ );
      return false;
   }

   Vector p = r.point(t);
   double u = u0 +   (p & ku);
   double v = v0 +   (p & kv);

#ifdef STATISTICS
   if(   u >   0 && v > 0 && u   < 1   && v < 1 )
      return true;
   else
   {
      RectTestMisses++;
      return false;
   }
#else
   return u > 0 &&   v >   0 && u < 1 && v   < 1;
#endif
}
