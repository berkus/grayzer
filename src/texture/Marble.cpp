//
// Description..: marble procedural texture realization
//
#include "texture/Marble.h"
#include "Tracer.h"
#include "Noise.h"


void marble::apply(  Vector&  p, surface_data& t )
{
   double x = p.x * scale.x + offs.x;
   double s = pow(   saw_wave( x + turb * turbulence(p,octaves) ), squeeze );

// if(!Tbl.IsEmpty())
// {
   t.color  = tbl.find_color(s);
//    return;
// }
}
