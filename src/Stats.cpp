//
//  Description..: misc statistics routines
//
#include <iostream>
// for box_printf
#include <stdarg.h>
#include <string.h>
//---
#include "Tracer.h"
#include "Externs.h"
#include "Stats.h"

long Stats::totalRays = 0;

long
    Options;
unsigned long
    TotalPixels = 0,
    BoxTestCount = 0, BoxTestMisses  = 0,
    CylinderTestCount =  0, CylinderTestMisses = 0,
    SphereTestCount   = 0, SphereTestMisses = 0,
    PlaneTestCount = 0,  PlaneTestMisses   = 0,
    RectTestCount =   0, RectTestMisses =  0,
    TriangleTestCount =  0, TriangleTestMisses = 0,
    NoiseCalls = 0,   Noise3dCalls = 0,
    TurbulenceCalls   = 0, Turbulence3dCalls = 0;

//
//  Печать заголовка рамочки
//
void box_header()
{
    std::cerr << "╔═══ Grayzer   Version 1.0.0  (c) 1995-1998, 2004, 2017 Metta Systems ═══╗\n";
}

void box_delim()
{
    std::cerr << "╟────────────────────────────────────────────────────────────────────────╢\n";
}

void box_footer()
{
    std::cerr << "╚═════════════════════════════════════════════════════ // by Berkus ═════╝\n";
}

//
//  Печать данных в рамочке (ширина 73 символа)
//
void box_printf(char const* fmt, ...)
{
    va_list marker;
    char buffer[160]{0};
    int len, i;

    std::cerr << "║ ";

    va_start(marker,fmt);
    vsprintf(buffer,fmt,marker);
    va_end(marker);
    len = strlen(buffer);

    for( i = len; i < 73; i++ )
       buffer[i] = ' ';

    std::cerr << buffer << "║\n";
}

//
//  print only non-zero values
//
#define NZ_PRINT1(txt,val)      if(val) box_printf(" %-30s",txt)
#define NZ_PRINT2(txt,val)      if(val) box_printf(" %-30s: %lu",txt,val)
#define NZ_PRINT3(txt,val,miss) if(val) box_printf(" %-30s: %lu/%lu, %3.2f%%",txt,val,miss,(double)val*100/miss)


void Stats::print()
{
    // uchar hrs,min,sec,hds;

    // timing(  time_used, hrs, min, sec, hds );

    box_header();
    // box_printf(" Rendered with: %s",tracer_name);
    // box_printf(" Elapsed time: %2d:%02d:%02d:%03d",hrs,min,sec,hds);
    box_delim();
    NZ_PRINT2("Rays cast",totalRays);
    NZ_PRINT2("Pixels calculated",TotalPixels);
//  NZ_PRINT2("Pixels supersampled",
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
}
