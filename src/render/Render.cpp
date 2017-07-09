//
//  @brief render_scene realization
//
// #include <stdio.h>
// #include <conio.h>
//---
#include "Render.h"
#include "image/Targa.h"
#include "Tracer.h"
#include "Externs.h"
#include "Ray.h"
#include "environment/Scene.h"

void render_scene(Scene* scene, double half_width, double half_height,
               int nx, int ny,
               char const* fname)
{
   double x, y;
   double hx = 2.0   * half_width  /   nx;
   double hy = 2.0   * half_height /   ny;
   Ray   ray;
   Vector color;
   int   i, j;

   auto tga = std::make_unique<TargaImage>( fname, nx, ny );
   rgb   c;

/* $NB$ what is it? where it from?  how   it got here?

   left unused: does much unnecessary work   (I think so),
            produces very funny  TGA   files (pixels intermixed)
   for(int  yfactor  = 16; yfactor >   0; yfactor--)
      for(int  xfactor  = 16; xfactor >   0; xfactor--)
         for(i=0,y=HalfHeight;i<ny;i+=yfactor,y-=hy*yfactor)
         {
            for(j=0,x=-HalfWidth;j<nx;j+=xfactor,x+=hx*xfactor)
*/
   for( i = 0, y =   half_height; i < ny; i++, y   -= hy )
   {
      for( j = 0, x =   -half_width; j < nx; j++, x   += hx )
      {
         TotalPixels++;

         scene->camera(x, y, ray);

         color = scene->trace( Grayzer::Medium::air, 1.0, ray );
         clip( color );

         c.r   = color.x * 255;
         c.g   = color.y * 255;
         c.b   = color.z * 255;

         tga->put_pixel(c);
      }
   }
}
