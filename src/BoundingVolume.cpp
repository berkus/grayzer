//
// File.........: boundvol.cpp
// Description..: class bounding_volume realization
// Comments.....:
//   98/02/23
//    implemented new   intersection methods
//
#include <string>
//---
#include "BoundingVolume.h"
#include "Geometry.h"


bounding_volume::bounding_volume()
: bounds( nil )
, next(  nil   )
, sub( nil )
, obj_list( nil   )
, obj_count( 0 )
, obj_limit( 0 )
{}

bounding_volume::~bounding_volume()
{
   bounding_volume   *vol;
   int   i;

   while( (vol = sub) != nil )
   {
      sub   = vol->next;
      delete vol;
   }

   for( i = 0; i <   obj_count; i++ )
      delete obj_list   [i];

   delete [] obj_list;

   delete bounds;
}


void bounding_volume::add( geometric_object  *obj )
{
   if(   obj_count >= obj_limit) // need  to resize object pool
   {
      geometric_object **new_list   = new geometric_object * [obj_limit + 10];

      if(   obj_list != nil   && new_list != nil )
      {
         obj_limit += 10;

         memmove(new_list,obj_list,obj_count*sizeof(geometric_object *));

         delete obj_list;
      }
      obj_list = new_list;
   }
   obj_list [obj_count++] = obj;
}

void bounding_volume::add( bounding_volume *vol )
{
   vol->next = sub;
   sub   = vol;
}


void bounding_volume::set_bounds( geometric_object *bnd  )
{
   delete bounds;
   bounds = bnd;
}


geometric_object *bounding_volume::intersect( ray& ray,  double&  t )
{
   if(   !bounds->intersect(ray,t) )
      return nil;

   geometric_object *found = nil;
   geometric_object *tmp;
   bounding_volume   * vol =  sub;
   double t1;
   int   i;

   for( t = INFINITY; vol != nil; vol = vol->next )
//    if(vol->Intersect(ray,t1))
         if(   (tmp = vol->intersect(ray,t1)) != nil )
            if(t1 <  t)
            {
               found =  tmp;
               t =   t1;
            }

   for( i = 0; i <   obj_count; i++ )
      if(   obj_list [i]->intersect(ray,t1)  )
         if(t1 <  t)
         {
            found =  obj_list [i];
            t =   t1;
         }

   return found;
}
