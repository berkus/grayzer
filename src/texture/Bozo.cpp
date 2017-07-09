//
// Description..: bozo  realization
//
#include "texture/Bozo.h"
#include "SurfaceData.h"
#include "Noise.h"
//#include "externs.h"
//#include "colortbl.hpp"

void Bozo::apply( Vector& p, Grayzer::SurfaceData& t )
{
   if(   turb !=  0.0   )
   {
      Vector bozo_turb = turbulence_3d( p, octaves );
      p += bozo_turb * turb;
   }

   double _noise =   noise(p);

   if(   !tbl.is_empty()   )
   {
      // in POV, found color is added  to existing object color; why __??
      t.color  += tbl.find_color(_noise);
      return;
   }

   if(   _noise < 0.4 )
   {
      t.color  += 1.0;
      return;
   }
   if(   _noise < 0.6 )
   {
      t.color.y += 1.0;
      return;
   }
   if(   _noise < 0.8 )
   {
      t.color.z += 1.0;
      return;
   }

   t.color.x += 1.0;
   return;
}
