//
//  @brief adaptive_distributed_render_scene realization
//
//---
#include "Render.h"
#include "image/Targa.h"
#include "Tracer.h"
#include "Externs.h"
#include "Ray.h"
#include "environment/Scene.h"

void adaptive_distributed_render_scene(
   Scene* scene,
   double HalfWidth,double HalfHeight,
   int   nx,int ny,int nxSub,int nySub,
   double Variance,
   char const*PicFileName)
{
   double x,y;                // sample point
   Ray   ray;                 // pixel ray
   double hx = 2.0   * HalfWidth / nx;   // pixel width
   double hy = 2.0   * HalfHeight / ny;     // pixel height
   double hxSub = hx /  nxSub;
   double hySub = hy /  nySub;
   double Disp;               // dispersion squared
   int   i,j;
   Vector Color;
   Vector Sum;
   Vector Mean;
   int   Count;

   auto tga = std::make_unique<TargaImage>(PicFileName, nx, ny);
   rgb   c;

   for(i = 0, y = HalfHeight; i < ny; i++, y -= hy)
   {
      for(j = 0, x = -HalfWidth; j < nx; j++, x += hx)
      {
         double x1 = x - 0.5 * hx;
         double y1 = y - 0.5 * hy;
         double d;

         Sum   = 0;
         Disp  = 0;
         Count = 0;

         TotalPixels++;

         do {
            for(int  iSub = 0; iSub < nxSub; iSub++)
            {
               for(int  jSub = 0; jSub < nySub; jSub++)
               {
                  scene->camera(x1+hxSub*(iSub+rnd()),y1+hySub*(jSub+rnd()),ray);
                  Color = scene->trace( Grayzer::Medium::air, 1.0, ray );
                  Sum  += Color;
                  Disp += Color & Color;
                  Count++;
               }
            }
            Mean = Sum / Count;
            d =   (Disp /  Count -  (Mean &  Mean)) * Count / (Count - 1);
         } while(d / Count >= Variance && Count < 99);

         clip( Mean );
         c.r   = Mean.x * 255;
         c.g   = Mean.y * 255;
         c.b   = Mean.z * 255;

         tga->put_pixel(c);
      }
   }
}
