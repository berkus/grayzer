//
//  @brief TargaImage realization
//
#include <string.h>
#include "image/Targa.h"

void targa_header::save(DataSink& ds)
{
    ds.write1(text_size);
    ds.write1(map_type);
    ds.write1(data_type);
    ds.write2(map_org);
    ds.write2(map_len);
    ds.write1(cmap_bits);
    ds.write2(x_offset);
    ds.write2(y_offset);
    ds.write2(width);
    ds.write2(height);
    ds.write1(data_bits);
    ds.write1(im_type);
}

TargaImage::TargaImage( char const*name, int width, int height, char *comment )
{
    FILE *fp = fopen(name, "wb");
    file = new FileDataSink(fp);
    buf_size = 1000;
    buffer = new rgb [buf_size];
    pos = 0;

    memset(  &hdr, 0, sizeof(hdr) );
    hdr.data_type =   2;
    hdr.width = width;
    hdr.height = height;
    hdr.data_bits =   24;
    hdr.im_type = 32;

    if(comment) hdr.text_size = strlen(comment)+1;

    hdr.save(*file);

    if(hdr.text_size > 0) file->write(comment, hdr.text_size);
}


TargaImage::~TargaImage()
{
    if(pos > 0) flush();
    delete buffer;
    delete file;
}


void TargaImage::put_pixel( rgb color )
{
    buffer[pos].r =   color.b; // swap red & blue   colors
    buffer[pos].g =   color.g;
    buffer[pos].b =   color.r;

    if( ++pos >= buf_size ) flush();
}


void TargaImage::flush()
{
    file->write((char *)buffer, pos * sizeof(rgb));
    pos = 0;
}
