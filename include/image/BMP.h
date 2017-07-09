//
//  @brief class BmpImage for .BMP images handling
//
#pragma once

#include "image/Image.h"

class BmpImage : public Image
{
public:
    class error {};
    class alloc_error : public error {};

public:
    rgb   *palette;
    unsigned char *data;

    BmpImage( char * );
    ~BmpImage();

    virtual rgb get_pixel( int, int );
    inline void put_pixel( rgb ) {}
};
