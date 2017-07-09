//
// Description..: ripples procedural normal modifier
//
#include "Tracer.h"
#include "texture/Ripples.h"


void Ripples::apply( Vector& p,  Grayzer::SurfaceData& t   )
{
   Vector r = p - center;
   double l = !r;

   if(   l >   0.0001 ) r /= l;

   t.n   += r * amount *   sin(2 *  M_PI * l / wave_len  + phase) / (1 +   l *   l);
   t.n   = normalize( t.n );
}
