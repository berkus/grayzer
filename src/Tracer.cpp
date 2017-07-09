//
//  @brief tracing support routines
//
#include <math.h>
#include <stdlib.h>
#include "Tracer.h"
#include "environment/Scene.h"
#include "geom/GeomObj.h"
#include "environment/Geometry.h"
#include "light/LightSource.h"

using namespace Grayzer;

//
// Globals
//
Vector eye      (0, 0, 0); //camera
Vector eye_dir  (0, 0, 1); //camera

Vector view_x   (1, 0, 0); //camera
Vector view_y   (0, 1, 0); //camera

Color ambient   (1.0);
Color background (0.0, 0.05, 0.05);

Grayzer::Medium Grayzer::Medium::air   =   { 1.0, 0 };
Grayzer::Medium Grayzer::Medium::glass =   { 1.6, 0 };

SurfaceData defaultMaterial;

int   level    =  0;
int   maxLevel = 10;

double threshold      = 0.01;
double geom_threshold = 0.001;

Scene *scene;
extern unsigned long totalRays;


void initDefaultMaterial(double ka, double kd, double ks, double kr, double kt, Color color, Grayzer::Medium med, int phong)
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
   eye_dir = dir;                  // viewing direction
   view_x  = normalize(up ^ dir);  // basis vectors
   view_y  = normalize(dir ^ view_x);
}

// Scene::trace??
// Casts a ray, computing its intersection with the scene objects and computes light coming with this ray.
Color trace(Grayzer::Medium& curMed, double weight, Ray& ray)
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
      color = scene->shade_background(ray);
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
