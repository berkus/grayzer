//
// Description..: Transformation realization
//
#include "Transformation.h"


//
// Combine  two   transformations   into one
//
transformation operator * (   const transformation& orig,
                     const transformation& newt )
{
   transformation combined;

   combined.m = orig.m  * newt.m;
   combined.inv = newt.inv * orig.inv;

   return combined;
}


transformation&   transformation::operator *=   ( const  transformation&   newt )
{
   return *this = *this * newt;
}


transformation t_scale( const vector& v   )
{
   transformation t;

   t.m   = scale(v);
   t.inv =  inv_scale(v);

   return t;
}


transformation t_translate(   const vector& v   )
{
   transformation t;

   t.m   = translate(v);
   t.inv =  inv_translate(v);

   return t;
}


transformation t_rotate( const vector& v )
{
   transformation t;
   vector radian =   v *   M_PI/180.0;
   double cosx,sinx,cosy,siny,cosz,sinz;
   matrix matrix;

   cosx = cos(radian.x);
   sinx = sin(radian.x);
   cosy = cos(radian.y);
   siny = sin(radian.y);
   cosz = cos(radian.z);
   sinz = sin(radian.z);

   t.m.x[1][1] = cosx;
   t.m.x[2][2] = cosx;
   t.m.x[1][2] = sinx;
   t.m.x[2][1] = -sinx;

   t.inv =  t.m;
   t.inv.transpose();

   matrix.x[0][0] = cosy;
   matrix.x[2][2] = cosy;
   matrix.x[0][2] = -siny;
   matrix.x[2][0] = siny;

   t.m   *= matrix;
   matrix.transpose();
   t.inv =  matrix * t.inv;   // $NB$  !!

   matrix.identity();
   matrix.x[0][0] = cosz;
   matrix.x[1][1] = cosz;
   matrix.x[0][1] = sinz;
   matrix.x[1][0] = -sinz;

   t.m   *= matrix;
   matrix.transpose();
   t.inv =  matrix * t.inv;

   return t;
}
