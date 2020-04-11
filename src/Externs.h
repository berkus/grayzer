//
//  Description..: some external statistic vars declaration
//
#pragma once

//
//  Remark this and recompile to remove statistics code
//
#define STATISTICS

//
//  Options values
//
#define OPT_DISPLAY   1
#define OPT_DEBUG   128

extern unsigned long
    TotalPixels,
    BoxTestCount,BoxTestMisses,
    CylinderTestCount,CylinderTestMisses,
    SphereTestCount,SphereTestMisses,
    PlaneTestCount,PlaneTestMisses,
    RectTestCount,RectTestMisses,
    TriangleTestCount,TriangleTestMisses,
    // Noise routines
    NoiseCalls, Noise3dCalls,
    TurbulenceCalls, Turbulence3dCalls;

extern long
    Options;

#ifdef STATISTICS
#define STAT(x) x
#else
#define STAT(x)
#endif
