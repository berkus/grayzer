//
//  @brief cylinder
//
#include "Externs.h"
#include "environment/Geometry.h"
#include "geom/Cylinder.h"

Cylinder::Cylinder(Vector& l, Vector& d, double r)
{
   loc   = l;
   dir   = d;
   len2 = dir & dir;
   len   = (double)sqrt(len2);
   radius = r;
   radius2  = r * r;
   radius4  = radius2 * radius2;

   if (fabs(dir.x) + fabs(dir.y) > fabs(dir.z))
      e1 = Vector(dir.y,-dir.x,0.0);
   else
      e1 = Vector(0.0,dir.z,-dir.y);

   e1 = normalize(e1) * radius;
   e2 = normalize(dir ^ e1) * radius;
   d1 = -(loc & dir);
   d2 = -((loc + dir) & dir);
}

bool Cylinder::intersect(Ray& r,double& t)
{
   STAT(CylinderTestCount++);

   Vector l = r.org - loc;
   double u0 = l &   e1;
   double u1 = r.dir &  e1;
   double v0 = l &   e2;
   double v1 = r.dir &  e2;
   double l0 = l &   dir;
   double l1 = r.dir &  dir;
   double a = u1*u1+v1*v1;
   double b = u0*u1+v0*v1;
   double c = u0*u0+v0*v0-radius4;
   double d = b*b-a*c;

   if(d <=  0.0)
   {
      STAT(CylinderTestMisses++);
      return false;
   }
   d =   sqrt(d);
   double t1 = (-b-d)/a;
   double t2 = (-b+d)/a;
   double len1 = (l0+t1*l1)/len2;
   double len2 = (l0+t2*l1)/len2;
   Vector p;

   // now check for top/bottom   intersections
   if(   l1 > EPS )
   {
      if(   len1 < 0.0 )   // bottom intersection
      {
         t1 = -((r.org &   dir)+d1)/l1;
         p =   r.point(t1) - loc;
         if(   (p & p)  >= radius2 ) t1   = -1;
      }
      else
      if(   len1 > 1.0 )   // top intersection
      {
         t1 = -((r.org &   dir)+d2)/l1;
         p =   r.point(t1) - loc -  dir;
         if(   (p & p)  >= radius2 ) t1   = -1;
      }
      if(   len2 < 0.0 )
      {
         t2 = -((r.org &   dir)+d1)/l1;
         p =   r.point(t2) - loc;
         if(   (p & p)  >= radius2 ) t2   = -1;
      }
      else
      if(   len2 > 1.0 )
      {
         t2 = -((r.org &   dir)+d2)/l1;
         p =   r.point(t2) - loc -  dir;
         if(   (p & p)  >= radius2 ) t2   = -1;
      }
   }
   else
   if(   l1 < -EPS)
   {
      if(   len1 < 0.0 )
      {
         t1 = -((r.org &   dir)+d2)/l1;
         p =   r.point(t1) - loc -  dir;
         if(   (p & p)  >= radius2 ) t1   = -1;
      }
      else
      if(   len1 > 1.0 )
      {
         t1 = -((r.org &   dir)+d1)/l1;
         p =   r.point(t1) - loc;
         if(   (p & p)  >= radius2 ) t1   = -1;
      }
      if(   len2 < 0.0 )
      {
         t2 = -((r.org &   dir)+d2)/l1;
         p =   r.point(t2) - loc -  dir;
         if(   (p & p)  >= radius2 ) t2   = -1;
      }
      else
      if(   len2 > 1.0 )
      {
         t2 = -((r.org &   dir)+d1)/l1;
         p =   r.point(t2) - loc;
         if(   (p & p)  >= radius2 ) t2   = -1;
      }
   }
   if(   t1 > geom_threshold  )
   {
      t =   t1;
      return true;
   }
   t =   t2;
   if(   t >   geom_threshold )
      return true;
   else
   {
      STAT(CylinderTestMisses++);
      return false;
   }
}

Vector Cylinder::find_normal(Vector& p)
{
   double t = ((p - loc) & dir)/len2;
   Vector n;

   if(t < EPS)
      n = -dir/len;
   else
      if(t > 1.0 - EPS)
         n =   dir   / len;
      else
         n =   normalize( p - loc - dir * t );

   return n;
}
