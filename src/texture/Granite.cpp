//
// Description..: granite procedural texture realization
//
#include "texture/Granite.h"
#include "SurfaceData.h"
#include "Noise.h"

void Granite::apply( Vector& p,  Grayzer::SurfaceData& t   )
{
   double _noise =   0.0, freq = 1.0, temp;
   int   i;

   for( i = 0; i <   6; freq  *= 2.0,  i++   )
   {
      temp = fabs( 0.5 - noise(p * 4 * freq) );
      _noise += temp / freq;
   }

   if(   !tbl.is_empty()   )
   {
      t.color  = tbl.find_color( _noise );
      return;
   }

   t.color  = _noise; // white noise

/* see BookId: COMGR_BS_95
   double s = 0.5 * Turbulence(3*p,5);
   t.Color  = Tbl.FindColor(s);
*/
}
