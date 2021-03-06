//
// Description......:
//
#include "texture/Dents.h"
#include "Noise.h"
#include "SurfaceData.h"

void Dents::apply( Vector& p, Grayzer::SurfaceData&  t )
{
   if(   amount == 0.0 )   return;

   double _noise =   noise(p);
   _noise = _noise   * _noise * _noise *  amount;

   t.n   += noise_3d(p) * _noise;
   t.n   = normalize(t.n);
}
