//
// Description..: gradient procedural texture realization
//
#include "texture/Gradient.h"
#include "Noise.h"
#include "SurfaceData.h"
#include "Tracer.h" // only for frac() -- move it  from there


void gradient::apply( Vector& p, surface_data& t )
{
   Vector r = p * scale + offs;

   if(   turb !=  0.0   ) r   += turbulence_3d(r,octaves)   * turb;

   if(   tbl.is_empty() ) return;

   double value = 0.0;
   double n;

   if(   grad.x != 0.0 )
   {
      n =   fabs(r.x);
      value += frac(n);
   }
   if(   grad.y != 0.0 )
   {
      n =   fabs(r.y);
      value += frac(n);
   }
   if(   grad.z != 0.0 )
   {
      n =   fabs(r.z);
      value += frac(n);
   }
   value =  ( (value > 1.0)   ? fmod(value,1.0) :  value );
   t.color  = tbl.find_color( value );
}
