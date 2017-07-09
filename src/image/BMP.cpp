//
//  Description..: BmpImage class for .BMP images handling realization
//
#include <string.h>
//---
#include "image/BMP.h"
#include "libssio_copy/FileDataSource.h"

using namespace libssio;

#define BI_RGB  0L

struct bmp_header
{
    short type; // file type 'BM'
    int   size; // size of file in bytes
    int   reserved;
    int   off_bits; // offset from this header to actual data

    void load(DataSource& ds)
    {
        type = ds.read2();
        size = ds.read4();
        reserved = ds.read4();
        off_bits = ds.read4();
    }
};

struct bmp_info_header
{
    long  size;
    long  width;            // width of bitmap in pels
    long  height;           // height of bitmap in pels
    short planes;           // # of planes
    short bit_count;        // bits per pixel
    long  compression;      // type of compression
    long  size_image;       // size of image in bytes
    long  x_pels_per_meter; // hz res of target device
    long  y_pels_per_meter; // vt res of target device
    long  clr_used;
    long  clr_important;

    void load(DataSource& ds)
    {
        size = ds.read4();
        width = ds.read4();
        height = ds.read4();
        planes = ds.read2();
        bit_count = ds.read2();
        compression = ds.read4();
        size_image = ds.read4();
        x_pels_per_meter = ds.read4();
        y_pels_per_meter = ds.read4();
        clr_used = ds.read4();
        clr_important = ds.read4();
    }
};

struct rgb_quad
{
    unsigned char r,g,b,i;

    void load(DataSource& ds)
    {
        r = ds.read1();
        g = ds.read1();
        b = ds.read1();
        i = ds.read1();
    }
};

BmpImage::BmpImage(char const* fname)
{
    bmp_header      hdr;
    bmp_info_header info_hdr;
    short           num_colors;
    unsigned long       num_bytes;
    unsigned short      x, y;
    unsigned char *     buf;

    FILE *fp = fopen(fname, "r");
    FileDataSource io(fp);

    //
    // read header data
    //
    hdr.load(io);
    info_hdr.load(io);

    num_colors = 1 << info_hdr.bit_count;
    num_bytes = info_hdr.size_image == 0 ? io.getSize() - hdr.off_bits : info_hdr.size_image;

    buf = new unsigned char [num_bytes];
    if( !buf )
        throw alloc_error();

    width = info_hdr.width;
    height = info_hdr.height;

    palette = new rgb [num_colors];
    if( !palette )
        throw alloc_error();

    data = new unsigned char [width * height];
    if( !data )
        throw alloc_error();

    //
    // prepare palette
    //
    for(int i = 0; i < num_colors; i++)
    {
        rgb_quad q;
        q.load(io);

        palette[i].r = q.r;
        palette[i].g = q.g;
        palette[i].b = q.b;
    }

    //
    // read raw data
    //
    io.seek(hdr.off_bits);

    io.read( (char*)buf, num_bytes );

    fclose(fp);

    memset( data, 0, info_hdr.width * info_hdr.height );

    unsigned char *ptr = buf;

    if( info_hdr.compression == BI_RGB )
    {
        if( info_hdr.bit_count == 4 ) // 16-color uncompressed
        {
            int shift = info_hdr.width / 4;
            for( y = height - 1; y >= 0; y--, ptr += shift )
                for( x = 0; x < width; x += 2, ptr++ )
                {
                    data [y * width + x]     = (*ptr) >> 4;
                    data [y * width + x + 1] = (*ptr) & 0x0F;
                }
        }
        else
        if( info_hdr.bit_count == 8 ) // 256-color uncompressed
        {
            for( y = height; y >= 0; y-- )
                for( x = 0; x < width; x++, ptr++ )
                    data [y * width + x] = *ptr;
        }
    }
    delete buf;
}

BmpImage::~BmpImage()
{
    if( palette )
        delete palette;

    if( data )
        delete data;
}

rgb BmpImage::get_pixel( int x, int y )
{
    return palette [data [y * width + x]];
}
