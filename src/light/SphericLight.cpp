//
//  @brief SphericLight light source realization
//
#include "light/SphericLight.h"
#include "SurfaceData.h"
#include "geom/GeomObj.h"
#include "environment/Scene.h"
#include "Tracer.h"

using Grayzer::SurfaceData;

double SphericLight::shadow( Vector& p, Vector& l )
{
   l =   loc   - p   + Vector::rnd_vector() * radius;
   double dist = !l;
   double attenuation = dist_scale  / dist;
   double t;

   l /= dist;  // normalize vector l

   Ray   ray(p,l);
   SurfaceData texture;
   GeometricObject *occlude;

   while( (occlude   = scene->intersect(ray,t)) != 0 && dist >  t )
   {
      ray.org  = ray.point(t);
      occlude->find_texture( ray.org,  texture  );

      // объект непрозрачен
      if(   texture.kt < threshold ) return  0;
      if(   (attenuation *=   texture.kt) < threshold ) return 0;

      dist -=  t;
   }
   return attenuation;
}
