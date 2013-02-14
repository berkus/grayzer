//
// File.........: draw.cpp
// Description..: screen drawing support
//
// #include <conio.h>
// #include <stdio.h>
// #include <string>
//---
#include "Draw.h"
// #include "fileio.hpp"
// #include "Targa.h"
// #include "vesa.hpp"


void display_init(int w,int   h)
{
/*   vesa::set_video_mode( 640,480,8  );

   set_preview_palette();
*/
// gl_bar(0,0,w-1,h-1,glWhite);
}

void display_close()
{
//    vesa::restore_mode();
}

void set_preview_palette()
{
/*#ifndef  STD_PALETTE_MODE
   // 332 palette (from POV), needs hsv routines
   Char m,r,g,b;
   for   (r=0;r<8;r++)
      for   (g=0;g<8;g++)
         for   (b=0;b<4;b++) {
            m =   (r * 32  + g   * 4   + b);
            pal[m].r = r*9;
            pal[m].g = g*9;
            pal[m].b = b*21;
         }
#else
   //
   // standard old   preview  palette
   //
   int   i;
   rgb   palette[256];

   for( i = 0; i <   256; i++ )
   {
      palette[i].r = (63*(i & 7))/7;
      palette[i].g = (63*((i>>3) & 7))/7; // i/8   max:32
      palette[i].b = (63*((i>>6) & 3))/3; // i/64  max:4
   }
//   glWhite = 255;
#endif
   vesa::set_palette(palette,0,256);*/
// screen->SetPalette(pal);
// screen->RealizePalette();
}

void draw_pixel( int x, int   y, Vector& Color )
{
/*   int   r =   (int)(Color.x *   7 +   0.5);
   int   g =   (int)(Color.y *   7 +   0.5);
   int   b =   (int)(Color.z *   3 +   0.5);

   vesa::put_pixel( x,  y, r + (g << 3)   + (b <<  6) );*/
}

// struct color_data
// {
//    int   hue;  // color value
//    int   freq; // its frequency
// };
//
// int   color_data_compare(  const void *v1,   const void *v2 )
// {
//    return ((color_data  *)v2)->freq - ((color_data *)v1)->freq;
// }

void build_image_palette( char *color_trans, rgb *palette )
{
/*   int    min_dist;
   int    d;
   uint i,j;
   int    r,g,b;
   int    index;
   int    colors_count;

   color_data *color_table = new color_data [8192];
   if(   !color_table )
   {
      printf("\nNo memory for ColorTable\n");
      exit(1);
   }
   for( colors_count =  0, i = 0 ; i < 32768; i++ )
      if(   color_trans[i] > 0 && colors_count < 8192 )
      {
         color_table[colors_count].hue =  i;
         color_table[colors_count].freq = color_trans[i];
         colors_count++;
      }

   // sort  table by frequency
   qsort( color_table,  colors_count, sizeof(color_data),color_data_compare   );
   memset(  palette,0,256*sizeof(rgb) );

   // восстановить   огрубленные RGB   значения по их индексу
   for( i = 0; i <   256   && i < colors_count; i++ ) // build 5-bit values [0..31]
   {
      palette[i].r = ( color_table[i].hue       & 0x1F) << 1;
      palette[i].g = ((color_table[i].hue >> 5)  & 0x1F) << 1;
      palette[i].b = ((color_table[i].hue >> 10) & 0x1F) << 1;
   }
   // Find  darkest  color
   for( min_dist =   1024, i  = 0; i < 256; i++ )
   {
      d =   (int)palette[i].r +  (int)palette[i].g +  (int)palette[i].b;
      if(   d <   min_dist )
      {
         min_dist = d;
         index =  i;
      }
   }
   // And make it background color
   if(   index != 0 ) //   $NB$ always true
   {
      rgb   tmp   = palette[0];
      palette[0] = palette[index];
      palette[index] = tmp;
   }

   // init  translation to palette color 0
   memset(color_trans,0,32768);

   // for every used color find closest match
   for( i = 0; i <   colors_count; i++ )
   {
      // снова восстановить RGB по индексу
      r =   ( color_table[i].hue    & 0x1F)  <<1;
      g =   ((color_table[i].hue >> 5) & 0x1F)  <<1;
      b =   ((color_table[i].hue >> 10)   & 0x1F)  <<1;

      // найти ближайший цвет в палитре
      for( min_dist =   1024, j  = 0; j < 256; j++ )
      {
         d =   abs(r -  palette[j].r) +   abs(g -  palette[j].g) +   abs(b -  palette[j].b);
         if(   d <   min_dist )
         {
            min_dist = d;
            index =  j;
         }
      }
      color_trans[color_table[i].hue]  = index;
   }
   delete color_table;*/
}


void draw_targa_file( char *fname ) // $NB$  need use of targa lib
{
/*   targa_header hdr;
   int   i,j;
   int   r,g,b;
   int   index;
   rgb   palette[256];
   rgb   *line_buffer;
   char *color_trans;

   file_io  file (fname, file_io::read );

   file.read_uchars( (uchar *)&hdr, sizeof(hdr) ); // read  header

   if(   2 != hdr.data_type )
   {
      printf("\nUnsupported image type.");
      return;
   }

   file.seek( hdr.text_size, SEEK_CUR ); // skip comments

   if(   (color_trans = new char [32768]) == NULL )
   {
      printf("\nInsufficient memory for color_trans table");
      return;
   }
   if(   (line_buffer = new rgb [hdr.width]) == NULL  )
   {
      printf("\nInsufficient memory for line_buffer");
      return;
   }
   // init  frequencies
   memset(  color_trans, 0,   32768 );

   for( i = 0; i <   hdr.height; i++   )
   {
      file.read_uchars( (uchar *)line_buffer,   hdr.width*sizeof(rgb) );

      for( j = 0; j <   hdr.width; j++ )
      {
         // преобразовать TrueColor RGB в HiColor 15-bit RGB
         r =   line_buffer[j].b >>  3;
         g =   line_buffer[j].g >>  3;
         b =   line_buffer[j].r >>  3;
         index =  r |   (g << 5) | (b << 10);
         // account freqs of  all   colors
         if(   color_trans[index] < 255 ) color_trans[index]++;
      }
   }
   build_image_palette( color_trans, palette );
   // теперь ColorTrans содержит 8-bit индексы,
   // выбираемые кодированным 15-bit RGB

   display_init( hdr.width, hdr.height );
   vesa::set_palette( palette,   0, 256 );

   file.seek( sizeof(hdr)+hdr.text_size, SEEK_SET ); // seek back to start of image

   for( i = 0; i <   hdr.height; i++   )
   {
      file.read_uchars( (uchar *)line_buffer,   hdr.width * sizeof(rgb) );

      for( j = 0; j <   hdr.width; j++ )
      {
         r =   line_buffer[j].b >>  3;
         g =   line_buffer[j].g >>  3;
         b =   line_buffer[j].r >>  3;
         index =  r |   (g << 5) | (b << 10);
         vesa::put_pixel( j,i,color_trans[index]   );
      }
   }
   delete line_buffer;
   delete color_trans;
//   waitkey();
   while(kbhit()) getch();
   getch();
   while(kbhit()) getch();
//
   display_close();*/
}
