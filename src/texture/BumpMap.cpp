//
// Description......: bump_map   realization
//
#include "geom/GeomObj.h"
#include "Tracer.h"
#include "texture/BumpMap.h"


void BumpMap::apply( Vector& p, Grayzer::SurfaceData& t )
{
   double x = mod(   offs.x + scale.x * /*p.x*/ t.map_coord.x, map->width  );
   double y = mod(   offs.y + scale.y * /*p.y*/ t.map_coord.y, map->height );
   int   ix = (int)x;
   int   iy = (int)y;
   int   jx = ix  + 1;
   int   jy = iy  + 1;

   x -= ix;
   y -= iy;
   if(   jx >= map->width )
      jx = 0;
   if(   jy >= map->height )
      jy = 0;

   // interpolate between corners
   rgb   c00   = map->get_pixel( ix, iy );
   rgb   c01   = map->get_pixel( ix, jy );
   rgb   c10   = map->get_pixel( jx, iy );

   // calculate intensity (RGB   -> Grayscale)
   double i00 = (0.229  * c00.r  + 0.587  * c00.g  + 0.114  * c00.b) / 255;
   double i01 = (0.229  * c01.r  + 0.587  * c01.g  + 0.114  * c01.b) / 255;
   double i10 = (0.229  * c10.r  + 0.587  * c10.g  + 0.114  * c10.b) / 255;

   double du = (i10 - i00) * amount;
   double dv = (i01 - i00) * amount;

   Vector tu,tv;

   if(   object->mapping   )
      object->mapping->find_tangent( p,tu,tv );

   t.n   += du *  (t.n ^ tv) - dv   * (t.n ^ tu);
   t.n   = normalize(t.n);
}
