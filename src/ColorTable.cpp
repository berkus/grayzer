//
// @brief ColorTable realization
//
#include "ColorTable.h"

ColorTable::ColorTable(int size)
{
   entries = new Entry [max_entries = size];
   color_entries = 0;
}

void ColorTable::add_entry(double a, double b, Vector const& c1, Vector const& c2)
{
   if (color_entries < max_entries - 1)
   {
      entries[color_entries].ta = a;
      entries[color_entries].tb = b;
      entries[color_entries].ca = c1;
      entries[color_entries].cb = c2;
      color_entries++;
   }
}

Vector ColorTable::find_color(double value)
{
   if (color_entries < 1) return Vector(0);

   if (value <= entries[0].ta) return entries[0].ca;

   for (int i = 0; i < color_entries; ++i)
      if (value <= entries[i].tb)
      {
         double t = (value - entries[i].ta)/(entries[i].tb-entries[i].ta);
         return entries[i].ca*(1-t)+entries[i].cb*t;
         //Entries[i].ca+t*(Entries[i].cb-Entries[i].ca);
      }
   return entries[color_entries - 1].cb;
}
