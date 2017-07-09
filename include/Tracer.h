//
//  @brief Some common raytracing globals/protos/inlines
//
#pragma once

#include <math.h>
#include <stdlib.h>

#include "math/Vector.h"
#include "SurfaceData.h"

class GeometricObject;
class Scene;
class Ray;

//
//  Globals
//
extern Grayzer::SurfaceData defaultMaterial;

extern int level;
extern int maxLevel;
extern double threshold;

extern Color ambient;
extern Color background;

extern long timeUsed;

//
//  Function prototypes
//
void initDefaultMaterial( double ka = 0.3, double kd = 0.7, double ks = 0.0,
                          double kr = 0.0, double kt = 0.0, Color color = 0,
                          Grayzer::Medium med = Grayzer::Medium::glass, int phong = 1 );

void error( bool, char *, ... );
void stats( char *tracer_name ); // print some statistics

const bool // errors types
    NONFATAL = false,
    FATAL    = true;

extern double sawWave( double x );

inline double sineWave( double x )
{
    return 0.5 * (1.0 + sin( x ));
}

inline double mod( double x, double y )
{
    if( (x = fmod(x,y)) < 0 )
        return x+y;
    else
        return x;
}

// @todo replace with std::random
inline double rnd()
{
    return (double)rand() / (double)RAND_MAX;
}

inline double frac(double x)
{
    return x - floor(x);
}
