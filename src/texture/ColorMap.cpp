//
// Description......: color_map image mapping realization
//
#include "Tracer.h"
#include "texture/ColorMap.h"


void color_map::apply( Vector&,  surface_data& t   )
{
   double x = mod(   offs.x + scale.x * t.map_coord.x, map->width  );
   double y = mod(   offs.y + scale.y * t.map_coord.y, map->height );
   int   ix = (int)x;
   int   iy = (int)y;
   int   jx = ix+1;
   int   jy = iy+1;

   x -= ix;
   y -= iy;
   if(   jx >= map->width  )  jx = 0;
   if(   jy >= map->height )  jy = 0;

   // interpolate between corners
   rgb   c00   = map->get_pixel(ix,iy);
   rgb   c01   = map->get_pixel(ix,jy);
   rgb   c10   = map->get_pixel(jx,iy);
   rgb   c11   = map->get_pixel(jx,jy);

   t.color.x = ((1-x)*(1-y)*c00.r+(1-x)*y*c01.r+x*(1-y)*c10.r+x*y*c11.r)/255;
   t.color.y = ((1-x)*(1-y)*c00.g+(1-x)*y*c01.g+x*(1-y)*c10.g+x*y*c11.g)/255;
   t.color.z = ((1-x)*(1-y)*c00.b+(1-x)*y*c01.b+x*(1-y)*c10.b+x*y*c11.b)/255;
}
