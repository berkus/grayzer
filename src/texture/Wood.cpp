//
// Description..: wood  procedural texture realization
//
#include "texture/Wood.h"
#include "Colors.h"
#include "Tracer.h"
#include "SurfaceData.h"

void Wood::apply( Vector& p, Grayzer::SurfaceData& t )
{
   double x = p.x * scale.x + offs.x;
   double y = p.y * scale.y + offs.y;
   double s = pow(   sineWave( ring_spacing * sqrt(  x *   x +   y *   y )   +
            turb  * turbulence(p,   octaves) ), squeeze  );

   t.color  = LightWood * (1 - s) + DarkWood * s;
   t.ks *=  0.3   * s   + 0.7;
}
