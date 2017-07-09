//
// Description..: marble procedural texture realization
//
#include "texture/Marble.h"
#include "Tracer.h"
#include "Noise.h"

void Marble::apply(  Vector&  p, Grayzer::SurfaceData& t )
{
   double x = p.x * scale.x + offs.x;
   double s = pow(   sawWave( x + turb * turbulence(p,octaves) ), squeeze );

// if(!Tbl.IsEmpty())
// {
   t.color  = tbl.find_color(s);
//    return;
// }
}
