//
// Description......: checker realization
//
#include "Tracer.h"
#include "texture/Checker.h"


void checker::apply( Vector& p,  surface_data& t   )
{
   Vector r = p * scale + offs;

   int   ix = (int)( r.x   < 0   ? 1-r.x  : r.x );
   int   iy = (int)( r.y   < 0   ? 1-r.y  : r.y );
   int   iz = (int)( r.z   < 0   ? 1-r.z  : r.z );

   if(   (ix   + iy + iz) & 1 )
      t.color  = color2;
   else
      t.color  = color1;
}
