//
//	File.........: bmp.cpp
//	Description..: bmp_image class for .BMP	images handling	realization
//
#include <string.h>
//---
#include "image/BMP.h"
#include "libssio_copy/FileDataSink.h"


#define	BI_RGB	0L
#define	BI_RLE8	1L
#define	BI_RLE4	2L


struct bmp_header
{
	short type;	// file	type 'BM'
	int	  size;	// size	of file	in bytes
	int	  reserved;
	int	  off_bits;	// offset from this	header to actual data
};

struct bmp_info_header
{
	long  size;
	long  width;			// width of	bitmap in pels
	long  height;			// height of bitmap	in pels
	short planes;			// # of	planes
	short bit_count;		// bits	per	pixel
	long  compression;		// type	of compression
	long  size_image;		// size	of image in	bytes
	long  x_pels_per_meter;	// hz res of target	device
	long  y_pels_per_meter;	// vt res of target	device
	long  clr_used;
	long  clr_important;
};

struct rgb_quad
{
	unsigned char r,g,b,i;
};


bmp_image::bmp_image( char *fname )
{
	bmp_header		hdr;
	bmp_info_header	info_hdr;
	rgb_quad		pal	[256];
	short			num_colors;
	unsigned long		num_bytes;
	unsigned short		x, y;
	unsigned char *		buf;
	unsigned char *		ptr;
	int			i;

	file_io	io ( fname,	file_io::read );

	//
	// read	header data
	//
	io.read_chars( (char *)&hdr, sizeof(hdr) );
	io.read_chars( (char *)&info_hdr, sizeof(info_hdr) );

	num_colors = 1 << info_hdr.bit_count;
	num_bytes =	io.size() -	hdr.off_bits;

	buf	= new uchar	[num_bytes];
	if(	!buf )
		throw alloc_error();

	ptr	= buf;

	width =	info_hdr.width;
	height = info_hdr.height;

	palette	= new rgb [num_colors];
	if(	!palette )
		throw alloc_error();

	data = new uchar [width	* height];
	if(	!data )
		throw alloc_error();

	//
	// prepare palette
	//
	io.read_chars( (char *)pal,	num_colors * sizeof(rgb_quad) );

	for( i = 0;	i <	num_colors;	i++	)
	{
		palette[i].r = pal[i].r;
		palette[i].g = pal[i].g;
		palette[i].b = pal[i].b;
	}
	//
	// read	raw	data
	//
	io.seek( hdr.off_bits, SEEK_SET	);

	io.read_uchars(	buf, num_bytes );

	io.deinit(); //	close stream

	memset(	data, 0, info_hdr.width	* info_hdr.height );

	if(	info_hdr.compression ==	BI_RGB )
	{
		if(	info_hdr.bit_count == 4	) // 16-color uncompressed
		{
			int	shift =	info_hdr.width / 4;
			for( y = height	- 1; y >= 0; y--, ptr += shift )
				for( x = 0;	x <	width; x +=	2, ptr++ )
				{
					data [y	* width	+ x]	 = (*ptr) >> 4;
					data [y	* width	+ x	+ 1] = (*ptr) &	0x0F;
				}
		}
		else
		if(	info_hdr.bit_count == 8	) // 256-color uncompressed
		{
			for( y = height; y >= 0; y-- )
				for( x = 0;	x <	width; x++,	ptr++ )
					data [y	* width	+ x] = *ptr;
		}
	}
	delete buf;
}

bmp_image::~bmp_image()
{
	if(	palette	)
		delete palette;

	if(	data )
		delete data;
}


rgb	bmp_image::get_pixel( int x, int y )
{
	return palette [data [y	* width	+ x]];
}
