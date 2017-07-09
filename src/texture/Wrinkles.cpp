//
// Description..: wrinkles procedural perturbation texture  realization
//
#include "texture/Wrinkles.h"
#include "Noise.h"
#include "SurfaceData.h"

void Wrinkles::apply( Vector& p, Grayzer::SurfaceData& t )
{
   Vector result (0.0);
   Vector value;
   double scale = 1.0;
   int   i;

   if(   amount == 0.0 )   return;

   for( i = 0; i <   10;   scale *= 2.0, i++ )
   {
      value =  noise_3d( p * scale  );
      result.x += fabs(value.x / scale);
      result.y += fabs(value.y / scale);
      result.z += fabs(value.z / scale);
   }
   t.n   += result * amount;
   t.n   = normalize( t.n );
}
