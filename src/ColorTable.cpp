//
// @brief color_table realization
//
#include "ColorTable.h"


color_table::color_table( int size )
{
   entries  = new color_table_entry [max_entries = size];
   color_entries =   0;
}


void color_table::add_entry( double a,double b,const Vector& c1,const Vector& c2 )
{
   if(   color_entries <   max_entries - 1   )
   {
      entries[color_entries].ta =   a;
      entries[color_entries].tb =   b;
      entries[color_entries].ca =   c1;
      entries[color_entries].cb =   c2;
      color_entries++;
   }
}


Vector color_table::find_color(  double value )
{
   if(   color_entries <   1 )   return Vector(0);

   if(   value <= entries[0].ta ) return  entries[0].ca;

   for( int i = 0;   i <   color_entries; i++ )
      if(   value <= entries[i].tb )
      {
         double t = (value -  entries[i].ta)/(entries[i].tb-entries[i].ta);
         return entries[i].ca*(1-t)+entries[i].cb*t;
         //Entries[i].ca+t*(Entries[i].cb-Entries[i].ca);
      }
   return entries[color_entries - 1].cb;
}
