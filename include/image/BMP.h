//
//  @brief class BmpImage for .BMP images handling
//
#pragma once

#include "image/Image.h"

class bmp_image : public image
{
    public:
        class error {};
        class alloc_error : public error {};

    public:
        rgb   *palette;
        unsigned char *data;

        bmp_image( char * );
       ~bmp_image();

        virtual rgb get_pixel( int, int );
        inline void put_pixel( rgb ) {}
};
