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
#include "Draw.h"

auto& air = Grayzer::Medium::air;

void distributed_render_scene(
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
   TargaImage *tga = new TargaImage( fname,nx,ny );
   rgb   c;

//    display_init( nx,ny  );

//    START_TIME( time_used );

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
               camera(x1 + hx_sub * (iSub + rnd()),
                     y1 +  hy_sub * (jSub + rnd()), ray );
               color += trace(   air, 1.0, ray );
            }
         color /= primary_samples;
         clip(color);

         c.r   = color.x * 255;
         c.g   = color.y * 255;
         c.b   = color.z * 255;

         tga->put_pixel(c);
//          draw_pixel(j,i,color);
/*         if(kbhit())
         {
            if(!getch())
               getch();
            goto end_render;
         }*/
      }
   }
// end_render:
//    STOP_TIME( time_used );

   delete tga;
//    display_close();

//    stats("distributed_render_scene");
}
