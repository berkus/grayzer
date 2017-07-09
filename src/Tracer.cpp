//
//  @brief tracing support routines
//
#include <math.h>
#include <stdlib.h>
#include "Tracer.h"
#include "environment/Environment.h"
#include "geom/GeomObj.h"
#include "environment/Geometry.h"
#include "light/LightSource.h"

//
// Globals
//
Vector eye      (0, 0, 0); //camera
Vector eyeDir   (0, 0, 1); //camera

Vector viewX    (1, 0, 0); //camera
Vector viewY    (0, 1, 0); //camera

Color ambient   (1.0);
Color background (0.0, 0.05, 0.05);

Medium Medium::air   =   { 1.0, 0 };
Medium Medium::glass =   { 1.6, 0 };

SurfaceData defaultMaterial;

int   level    =  0;
int   maxLevel = 10;

double threshold     = 0.01;
double geomThreshold = 0.001;

Environment *scene;
extern unsigned long totalRays;


void initDefaultMaterial(double ka, double kd, double ks, double kr, double kt, Color color, Medium med, int phong)
{
   defaultMaterial.ka     = ka;
   defaultMaterial.kd     = kd;
   defaultMaterial.ks     = ks;
   defaultMaterial.kr     = kr;
   defaultMaterial.kt     = kt;
   defaultMaterial.color  = color;
   defaultMaterial.med    = med;
   defaultMaterial.p      = phong;
}


void setCamera(const Vector &org, const Vector &dir, const Vector &up)
{
   eye     = org;                  // eye point
   eyeDir  = dir;                  // viewing direction
   viewX   = normalize(up ^ dir);  // basis vectors
   viewY   = normalize(dir ^ viewX);
}

// Scene::trace??
// Casts a ray, computing its intersection with the scene objects and computes light coming with this ray.
Color trace(Medium& curMed, double weight, Ray& ray)
{
   GeometricObject *obj;
   double t = GEOM_INFINITY;
   Color color;

   level++;
   totalRays++;

   if((obj = scene->intersect(ray,t)) != 0)
   {
      color = shade(curMed, weight, ray.point(t), ray.dir, obj);
      if(curMed.beta > threshold) color *= exp(-t * curMed.beta);
   }
   else
      color = scene->shadeBackground(ray);
   //
   // added fog
   //
   if(scene->envFog) scene->envFog->shade(color, t);

   level--;
   return color;
}


double sawWave(double x)
{
   double offset, temp1;

   if(x >= 0.0) offset = frac(x);
   else
   {
      temp1  = -1.0 - floor(fabs(x));
      offset = x - temp1;
   }
   if(offset >= 0.5) return 2.0 * (1.0 -  offset);
   else              return 2.0 * offset;
}
