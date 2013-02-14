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
#include "Draw.h"


void render_scene( double half_width, double half_height,
               int nx, int ny,
               char  *fname )
{
   double x, y;
   double hx = 2.0   * half_width  /   nx;
   double hy = 2.0   * half_height /   ny;
   ray   ray;
   Vector color;
   int   i, j;

   targa_image *tga = new targa_image( fname, nx, ny );
   rgb   c;
//    display_init(nx,ny);

//   START_TIME( time_used );

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

         camera(  x, y, ray );

         color =  trace( air, 1.0, ray );
         clip( color );

         c.r   = color.x * 255;
         c.g   = color.y * 255;
         c.b   = color.z * 255;

         tga->put_pixel(c);
//         draw_pixel( j, i, color );

/*         if(   kbhit()  )
         {
            while( kbhit() ) getch();
            goto endRender;
         }*/
      }
   }
// endRender:
//   STOP_TIME( time_used );
   delete tga;
//   display_close();
//   stats("render_scene");
}
