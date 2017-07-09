//
//  @brief SpotLight light source realization
//
#include "light/SpotLight.h"
#include "SurfaceData.h"
#include "geom/GeomObj.h"
#include "environment/Scene.h"
#include "Tracer.h"

using Grayzer::SurfaceData;

double SpotLight::shadow( Vector& p, Vector& l )
{
   l =   loc   - p;
   double dist = !l;
   double attenuation = dist_scale  / dist;

   l /= dist;
   double ld = -(dir &  l);
   if(   ld < end_cone_angle  ) return 0;

   double f1 = pow( ld, beam_distribution );
   double f2 = ld > cone_angle   ? 1.0 :  (ld   - end_cone_angle) /
            (cone_angle - end_cone_angle);
   double t;

   Ray   ray(p,l);
   SurfaceData texture;
   GeometricObject *occlude;

   attenuation *= attenuation * f1  * f2;

   while( (occlude = scene->intersect(ray,t)) != 0 && dist >  t )
   {
      ray.org  = ray.point(t);
      occlude->find_texture( ray.org,  texture  );

      if(   texture.kt < threshold) return 0; // объект  непрозрачен
      if(   (attenuation *=   texture.kt) < threshold ) return 0;

      dist -=  t;
   }
   return attenuation;
}
