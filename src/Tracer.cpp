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

Color ambient   (1.0);
Color background (0.0, 0.05, 0.05);

Grayzer::Medium Grayzer::Medium::air   =   { 1.0, 0 };
Grayzer::Medium Grayzer::Medium::glass =   { 1.6, 0 };

SurfaceData defaultMaterial;

int   level    =  0;
int   maxLevel = 10;

double threshold      = 0.01;
double geom_threshold = 0.001;

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
