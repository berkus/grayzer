//
// File.............: camera.cpp
// Description......: camera realization
//
#include "Tracer.h"
#include "Ray.h"


double aperture   = 0.0; // pадиус линзы
double focus = 0.0;     // фокусное pасстояние


void camera( double  x,double y,ray&   ray   )
{
   ray.org  = eye;
   if(   aperture > 0.0 ) //  камера не точечная,  исп   с AdaptiveDistRenderScene
   {
      // построить случайную точку на  линзе
      Vector lens_point =  (view_x  * (double)rand() + view_y *   (double)rand())   * aperture/RAND_MAX;
      ray.org  += lens_point;
      ray.dir  = eye_dir * focus +  view_x * x + view_y  * y   - lens_point;
      ray.dir  = normalize( ray.dir );
   }
   else
      ray.dir  = normalize( eye_dir + view_x *  x +   view_y * y );
}
