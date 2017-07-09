//
//  @brief Environment
//
#include "environment/Scene.h"
#include "geom/GeomObj.h"
#include "light/LightSource.h"
#include "environment/Geometry.h"
#include "Tracer.h"
#include "Stats.h"

using Grayzer::SurfaceData;
using Grayzer::Medium;

GeometricObject *Scene::intersect(Ray& r, double& t)
{
    std::shared_ptr<GeometricObject> closest_obj;
    double           closest_dist = GEOM_INFINITY;

    for(int i = 0; i < solid.size(); ++i)
        if( solid[i]->intersect(r,t) )
            if( t < closest_dist )
            {
                closest_dist = t;
                closest_obj = solid[i];
            }
    t = closest_dist;
    return closest_obj.get();
}

Vector Scene::shade_background(Ray&)
{
    return background;
}

// Camera control section

void Scene::camera(double x, double y, Ray& ray)
{
    ray.org  = eye;
    if (aperture > 0.0) // камера не точечная, исп с AdaptiveDistRenderScene
    {
        // построить случайную точку на  линзе
        Vector lens_point = (view_x * (double)rand() + view_y * (double)rand()) * aperture / RAND_MAX;
        ray.org += lens_point;
        ray.dir = eye_dir * focus + view_x * x + view_y * y - lens_point;
        ray.dir = normalize(ray.dir);
    } else {
        ray.dir  = normalize(eye_dir + view_x * x + view_y * y);
    }
}

void Scene::setCamera(const Vector &org, const Vector &dir, const Vector &up)
{
   eye     = org;                  // eye point
   eye_dir = dir;                  // viewing direction
   view_x  = normalize(up ^ dir);  // basis vectors
   view_y  = normalize(dir ^ view_x);
}

// end Camera control section

// Casts a ray, computing its intersection with the scene objects and computes light coming with this ray.
Color Scene::trace(Grayzer::Medium& curMed, double weight, Ray& ray)
{
   GeometricObject *obj;
   double t = GEOM_INFINITY;
   Color color;

   level++;
   Stats::raysCast();

   if((obj = intersect(ray,t)) != 0)
   {
      color = shade(curMed, weight, ray.point(t), ray.dir, obj);
      if(curMed.beta > threshold) color *= exp(-t * curMed.beta);
   }
   else
      color = shade_background(ray);
   //
   // added fog
   //
   if (envFog) envFog->shade(color, t);

   level--;
   return color;
}

// compute light coming from point `p' in the direction `view'
// using Whitted's (advanced (from 8.94)) illumination model
Color Scene::shade(Medium& curMed, double weight, Vector p, Vector view, GeometricObject *obj)
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

   obj->find_texture(p, txt);
   if((vn = view & txt.n) > 0) // force (-View,n) > 0
   {
      txt.n = -txt.n;
      vn = -vn;
      entering = false;
   }

   ray.org = p;
   color = ambient * txt.color * txt.ka; // get ambient light

   for(i = 0; i < light.size(); i++)
   {
      if((sh = light[i]->shadow(this, p,l)) > threshold)
      {
         if((ln = (l & txt.n)) > threshold) //  light is visible
         {
            // Diffuse
            if(txt.kd > threshold)
               color += light[i]->color * txt.color * (txt.kd * sh * ln);

            // Specular & Phong-like
            if(txt.ks > threshold)
            {
               h = normalize(l - view);
               color += light[i]->color * txt.ks * sh * pow(txt.n & h, txt.p);
            }
         }
         else
         if(txt.kt > threshold && ln < -threshold)
         {
            t = -txt.kd * txt.kt * sh * ln;

            if(t > threshold)
               color += light[i]->color * txt.color * t;

            t = txt.ks * txt.kt * sh;

            if(t > threshold)
            {
               if((view - l) > threshold)
               {
                  double eta = (entering ? txt.med.ior : Grayzer::Medium::air.ior) / curMed.ior;
                  h = normalize( -view - l * eta );
                  color += light[i]->color * t * pow(txt.n & h, txt.p);
               }
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
      double eta = curMed.ior / (entering ? txt.med.ior : Grayzer::Medium::air.ior);
      double ci = -vn; //  cosine of incident angle
      double ctSq = 1 + eta * eta * (ci *  ci - 1);

      if(ctSq > threshold) // not a Total Internal Reflection
      {
         ray.dir = view * eta + txt.n * (eta * ci - sqrt(ctSq));
         if(entering) // ray enters object
            color += txt.kt * trace(txt.med, tWeight, ray);
         else          // ray leaves object
            color += txt.kt * trace(Grayzer::Medium::air, tWeight, ray);
      }
   }
   return color;
}
