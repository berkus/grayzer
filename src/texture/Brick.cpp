//
// Description..: brick procedural  texture
//
#include "Tracer.h"
#include "texture/Brick.h"


void brick::apply( Vector& p, surface_data&  t )
{
   Vector r = (p *   scale +  offs) /  brick_size;
   double bx,by,bz;

   if(   mod(r.y,1) <= mortar_size.y   )
   {
      t.color  = mortar_color;
      return;
   }

   by = mod(0.5*r.y,1);

   if(   (bx   = mod(r.x,1)) <= mortar_size.x && by <=   0.5   )
   {
      t.color  = mortar_color;
      return;
   }

   if(   (bx   += 0.5)  >= 1.0 )
      bx -= 1.0;

   if(   bx <= mortar_size.x  && by >  0.5   )
   {
      t.color  = mortar_color;
      return;
   }

   if(   (bz   = mod(r.z,1)) <= mortar_size.z && by > 0.5 )
   {
      t.color  = mortar_color;
      return;
   }

   if(   (bz   += 0.5)  >= 1.0 )
      bz -= 1.0;

   if(   bz <= mortar_size.z  && by <= 0.5 )
   {
      t.color  = mortar_color;
      return;
   }

   t.color  = brick_color;
}
