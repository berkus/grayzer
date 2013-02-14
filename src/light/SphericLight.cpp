//
//  @brief spheric_light light source realization
//
#include "light/SphericLight.h"
#include "SurfaceData.h"
#include "go/GeomObj.h"
#include "environment/Environment.h"
#include "Tracer.h"


double spheric_light::shadow( Vector& p, Vector& l )
{
   l =   loc   - p   + Vector::rnd_vector() * radius;
   double dist = !l;
   double attenuation = dist_scale  / dist;
   double t;

   l /= dist;  // normalize vector l
   ray   ray(p,l);
   surface_data texture;
   geometric_object *occlude;

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
