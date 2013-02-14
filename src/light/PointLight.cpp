//
//  @brief point_light light source realization
//
#include "light/PointLight.h"
#include "SurfaceData.h"
#include "go/GeomObj.h"
#include "environment/Environment.h"
#include "Tracer.h"


double point_light::shadow(   Vector&  p, Vector& l )
{
   l =   loc   - p;
   double t;
   double dist = !l;
   double attenuation = dist_scale  / dist;
   attenuation = attenuation *   attenuation;

   l /= dist;
   ray   r(p,l);
   surface_data texture;
   geometric_object *occlude;

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
