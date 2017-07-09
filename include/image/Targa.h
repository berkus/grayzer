//
//  @brief targa_image class for .TGA images handling
//
#pragma once

#include "image/Image.h"
#include "libssio_copy/FileDataSink.h"

using libssio::DataSink;
using libssio::FileDataSink;

class targa_header
{
    public:
        char text_size;
        char map_type;
        char data_type;
        short  map_org;
        short  map_len;
        char cmap_bits;
        short  x_offset;
        short  y_offset;
        short  width;
        short  height;
        char data_bits;
        char im_type;

        void save(DataSink &ds);
};

class TargaImage : public Image
{
    public:
        TargaImage( char const*, int, int, char *comment = 0 );
       ~TargaImage();

        virtual rgb get_pixel( int, int ) { return rgb(0); } // $NB$
        virtual void put_pixel( rgb );

    private:
        targa_header hdr;
        rgb *        buffer;
        int          buf_size;
        int          pos;
        FileDataSink *file;

    private:
        void flush();
};
