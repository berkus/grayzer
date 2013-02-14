//
//	File.........: misc.cpp
//	Description..: misc	& statistics routines
//
#include <stdio.h>
#include <conio.h>
// for box_printf
#include <stdarg.h>
#include <string.h>
//---
#include "tracer.hpp"
#include "externs.h"


long * ticks_ptr = (long *)0x46CL;
long time_used;
long
	Options;
ulong
	TotalRays =	0, TotalPixels = 0,
	BoxTestCount = 0, BoxTestMisses	= 0,
	CylinderTestCount =	0, CylinderTestMisses =	0,
	SphereTestCount	= 0, SphereTestMisses =	0,
	PlaneTestCount = 0,	PlaneTestMisses	= 0,
	RectTestCount =	0, RectTestMisses =	0,
	TriangleTestCount =	0, TriangleTestMisses =	0,
	NoiseCalls = 0,	Noise3dCalls = 0,
	TurbulenceCalls	= 0, Turbulence3dCalls = 0;

char *visionary_copyrite =
	"\nVisionary  Version 1.0.0  Copyrite (c) 1995-8  Cyberk // Kendo\n";

//
//	Печать заголовка рамочки
//
void box_header()
{
	fprintf(stderr,"╔═══ Visionary  Version 1.0.0  Copyrite (c) 1995-8 Kendo Incorporated ═══╗\n");
}

void box_delim()
{
	fprintf(stderr,"╟────────────────────────────────────────────────────────────────────────╢\n");
}

void box_footer()
{
	fprintf(stderr,"╚═════════════════════════════════════════════════════ // by Cyberk ═════╝\n");
}

//
//	Печать данных в	рамочке	(ширина	73 символа)
//
void box_printf( char *fmt,	...	)
{
	va_list	marker;
	char buffer[160];
	int	len, i;

	buffer[0] =	'║';
	va_start(marker,fmt);
	vsprintf(buffer+1,fmt,marker);
	va_end(marker);
	len	= strlen (buffer);

	for( i = len; i	< 73; i++ )
	   buffer[i] = ' ';

	strcpy(buffer+73,"║\n");

	fprintf(stderr,buffer);
}

void timing( ulong time, uchar&	hrs, uchar&	min, uchar&	sec, uchar&	hds	)
{
	hrs	= (uchar)(time/(3600*TICKS_PER_SEC));
	min	= (uchar)((time	- hrs*(3600*TICKS_PER_SEC))/(60*TICKS_PER_SEC));
	sec	= (uchar)((time	- hrs*(3600*TICKS_PER_SEC) - min*(60*TICKS_PER_SEC)) / TICKS_PER_SEC);
	hds	= (uchar) (time	- hrs*(3600*TICKS_PER_SEC) - min*(60*TICKS_PER_SEC)	- sec*TICKS_PER_SEC);
}

//
//	print only non-zero	values
//
#define	NZ_PRINT1(txt,val)		if(val)	box_printf(" %-30s",txt)
#define	NZ_PRINT2(txt,val)		if(val)	box_printf(" %-30s: %lu",txt,val)
#define	NZ_PRINT3(txt,val,miss)	if(val)	box_printf(" %-30s: %lu/%lu, %3.2f%%",txt,val,miss,(double)val*100/miss)


void stats(	char *tracer_name )
{
	uchar hrs,min,sec,hds;

	timing(	time_used, hrs,	min, sec, hds );

	box_header();
	box_printf(" Rendered with: %s",tracer_name);
	box_printf(" Elapsed time: %2d:%02d:%02d:%03d",hrs,min,sec,hds);
	box_delim();
	NZ_PRINT2("Rays cast",TotalRays);
	NZ_PRINT2("Pixels calculated",TotalPixels);
//	NZ_PRINT2("Pixels supersampled",
	NZ_PRINT3("Box tests",BoxTestCount,BoxTestMisses);
	NZ_PRINT3("Cylinder tests",CylinderTestCount,CylinderTestMisses);
	NZ_PRINT3("Sphere tests",SphereTestCount,SphereTestMisses);
	NZ_PRINT3("Plane tests",PlaneTestCount,PlaneTestMisses);
	NZ_PRINT3("Rect tests",RectTestCount,RectTestMisses);
	NZ_PRINT3("Triangle tests",TriangleTestCount,TriangleTestMisses);
	box_delim();
	NZ_PRINT2("Noise calls",NoiseCalls);
	NZ_PRINT2("Noise3D calls",Noise3dCalls);
	NZ_PRINT2("Turbulence calls",TurbulenceCalls);
	NZ_PRINT2("Turbulence3D calls",Turbulence3dCalls);
	box_footer();
	// waitkey()
	while( kbhit() ) getch();
	getch();
	while( kbhit() ) getch();
}
