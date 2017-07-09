//
//  @brief PointLight light source realization
//
#include "light/PointLight.h"
#include "SurfaceData.h"
#include "geom/GeomObj.h"
#include "environment/Scene.h"
#include "Tracer.h"

using Grayzer::SurfaceData;

double PointLight::shadow(   Vector&  p, Vector& l )
{
   l =   loc   - p;
   double t;
   double dist = !l;
   double attenuation = dist_scale  / dist;
   attenuation = attenuation *   attenuation;

   l /= dist;

   Ray   r(p,l);
   SurfaceData texture;
   GeometricObject *occlude;

   while( (occlude   = scene->intersect(r,t)) !=   0   && dist  > t   )
   {
      r.org =  r.point(t);

      occlude->find_texture( r.org, texture );

      if(   texture.kt < threshold ) return  0; // объект непрозрачен
      if(   (attenuation *=   texture.kt) < threshold ) return 0;
      dist -=  t;
   }
   return attenuation;
}
