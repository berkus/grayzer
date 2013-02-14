//
// Description......: bumps realization
//
#include "Noise.h"
#include "SurfaceData.h"
#include "texture/Bumps.h"


void bumps::apply( Vector& p, surface_data&  t )
{
   if(   amount == 0.0 )   return;  // no bumps

   t.n   += noise_3d(p) * amount;
   t.n   = normalize(t.n);

/* see BookId: COMGR_BS_95
   t.n   += 2 * ( noise_3d(2  * p) - vector(0.5) );
   t.n   = normalize(t.n);
*/
}
