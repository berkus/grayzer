//
// Description......: DistributedRenderScene realization
//
/*#include <stdio.h>
#include <conio.h>*/
//---
#include "Render.h"
#include "image/Targa.h"
#include "Tracer.h"
#include "Externs.h"
#include "Ray.h"
#include "environment/Scene.h"

void distributed_render_scene(
   Scene* scene,
   double half_width, double half_height,
   int   nx,   int   ny,
   int   nx_sub,  int   ny_sub,
   char const* fname )
{
   double x,y;                // sample point
   Ray   ray;                 // pixel ray
   double hx = 2.0   * half_width / nx;      // pixel width
   double hy = 2.0   * half_height /   ny;      // pixel height
   double hx_sub =   hx / nx_sub;         // hz subdivision
   double hy_sub =   hy / ny_sub;         // vt subdivision
   int   i,j;
   int   primary_samples   = nx_sub * ny_sub; // # of samples for each  pixel
   Vector color;

   // make  next in  some higher-level module as: RenderOutFile = new Targa...
   auto tga = std::make_unique<TargaImage>( fname,nx,ny );
   rgb   c;

   for( i = 0, y =   half_height; i < ny; i++, y   -= hy )
   {
      for( j = 0, x =   -half_width; j < nx; j++, x   += hx )
      {
         double x1 = x -   0.5   * hx;
         double y1 = y -   0.5   * hy;
         color =  0;

         TotalPixels++;

         for( int iSub =   0; iSub  < nx_sub; iSub++ )
            for( int jSub =   0; jSub  < ny_sub; jSub++ )
            {
               scene->camera(x1 + hx_sub * (iSub + rnd()),
                     y1 +  hy_sub * (jSub + rnd()), ray );
               color += scene->trace(Grayzer::Medium::air, 1.0, ray);
            }
         color /= primary_samples;
         clip(color);

         c.r   = color.x * 255;
         c.g   = color.y * 255;
         c.b   = color.z * 255;

         tga->put_pixel(c);
      }
   }
}
