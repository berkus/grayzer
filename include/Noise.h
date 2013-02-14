//
//  @brief noise & turbulence functions
//
#ifndef _NOISE_
#define _NOISE_

#include "math/Vector.h"


#define max_noise_size 267
#define REALSCALE      (2.0 / 65535.0)
#define MINX           -10000
#define MINY           MINX
#define MINZ           MINX


void init_noise();
void done_noise();
double noise( const Vector& );
Vector noise_3d( const Vector& );
double turbulence( const Vector&, int );
Vector turbulence_3d( const Vector&, int );


#endif
