//
// Description..: wood  procedural texture realization
//
#include "texture/Wood.h"
#include "Colors.h"
#include "Tracer.h"
#include "SurfaceData.h"


void wood::apply( Vector& p, surface_data& t )
{
   double x = p.x * scale.x + offs.x;
   double y = p.y * scale.y + offs.y;
   double s = pow(   sine_wave( ring_spacing * sqrt(  x *   x +   y *   y )   +
            turb  * turbulence(p,   octaves) ), squeeze  );

   t.color  = LightWood * (1 - s) + DarkWood * s;
   t.ks *=  0.3   * s   + 0.7;
}
