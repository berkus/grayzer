//
// Description..: gloss procedural  texture  realization
//
#include "texture/Gloss.h"
#include "SurfaceData.h"
#include "Noise.h"
#include "Externs.h"
// #include "debug.h"

void Gloss::apply( Vector& p, Grayzer::SurfaceData&  t )
{
   double t1, t2;

   t1 = noise(p) *   scale.x;

//    if(   Options  & OPT_DEBUG )
//       DEBUG(("gloss at <%g %g %g>, noise %g",p.x,p.y,p.z,t1));

   t2 = 1.0 - t1;

   t.ks +=  t.kd * t1;
   t.kd *=  t2;
   t.p   = 1.0 +  1000 * t1;
}
