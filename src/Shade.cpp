//
// @brief shading routine
//
#include "Tracer.h"
#include "go/GeomObj.h"
#include "environment/Environment.h"
#include "light/LightSource.h"
#include "Externs.h"

// Scene::shade?
// compute light coming from point `p' in the direction `view'
// using Whitted's (advanced (from 8.94)) illumination model
Color shade(Medium& curMed, double weight, Vector p, Vector view, GeometricObject *obj)
{
   SurfaceData txt;
   Ray   ray;
   Color color;
   Vector l;   // light vector
   double sh;  // light shadow coeff.
   Vector h;   // vector between -View and light
   double ln, vn;
   double t;
   bool entering = true; // flag whether we're entering object
   int   i;

   obj->findTexture(p, txt);
   if((vn = view & txt.n) > 0) // force (-View,n) > 0
   {
      txt.n = -txt.n;
      vn = -vn;
      entering = false;
   }

   ray.org = p;
   color = ambient * txt.color * txt.ka; // get ambient light

   for(i = 0; i < scene->lightsCount; i++)
   {
      if((sh = scene->light[i]->shadow(p,l)) > threshold)
      {
         if((ln = (l & txt.n)) > threshold) //  light is visible
         {
            // Diffuse
            if(txt.kd > threshold)
               color += scene->light[i]->color * txt.color * (txt.kd * sh * ln);

            // Specular & Phong-like
            if(txt.ks > threshold)
            {
               h = normalize(l - view);
               color += scene->light[i]->color * txt.ks * sh * pow(txt.n & h, txt.p);
            }
         }
         else
         if(txt.kt > threshold && ln < -threshold)
         {
            t = -txt.kd * txt.kt * sh * ln;

            if(t > threshold)
               color += scene->light[i]->color * txt.color * t;

            t = txt.ks * txt.kt * sh;

            if(t > threshold)
               if((view - l) > threshold)
               {
                  double eta = (entering ? txt.med.ior : air.ior) / curMed.ior;
                  h = normalize( -view - l * eta );
                  color += scene->light[i]->color * t * pow(txt.n & h, txt.p);
               }
         }
      }
   }

   double rWeight = weight * txt.kr; // reflected
   double tWeight = weight * txt.kt; // transmitted

   // check for reflected ray
   if(rWeight > threshold && level < maxLevel)
   {
      ray.dir = view - txt.n * (2 * vn); // get reflected ray
      color += txt.kr * trace(curMed, rWeight, ray);
   }

   // check for transmitted ray
   if(tWeight > threshold && level < maxLevel)
   {
      double eta = curMed.ior / (entering ? txt.med.ior : air.ior);
      double ci = -vn; //  cosine of incident angle
      double ctSq = 1 + eta * eta * (ci *  ci - 1);

      if(ctSq > threshold) // not a Total Internal Reflection
      {
         ray.dir = view * eta + txt.n * (eta * ci - sqrt(ctSq));
         if(entering) // ray enters object
            color += txt.kt * trace(txt.med, tWeight, ray);
         else          // ray leaves   object
            color += txt.kt * trace(air, tWeight, ray);
      }
   }
   return color;
}
