//
//  File.........: draw.h
//  Description..: common screen drawing support
//
#pragma once

#include "math/Vector.h"

#define STD_PALETTE_MODE

class rgb;

void display_init(int w,int h);
void display_close();

void draw_pixel( int x, int y, Vector& color );

void set_preview_palette();
void build_image_palette( char *, rgb * );

void draw_targa_file( char *fname );
