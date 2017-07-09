//
//  @brief surface_data & medium classes for objects props control
//
#pragma once

#include "math/Vector.h"

namespace Grayzer {

//
//  main properties of the medium
//
class Medium
{
    public:
        double ior;     // refraction coefficient (Index Of Refraction)
        double beta;    // attenuation coefficient

        static Medium air;
        static Medium glass;
};


//
//  surface characteristics at a given point
//
class SurfaceData
{
    public:
        double ka;          // ambient light coefficient
        double kd;          // diffuse light coefficient
        double ks;          // specular light coefficient
        double kr;          // reflected ray coefficient
        double kt;          // (transparent/refracted/transmitted) light coefficient
        Color color;        // object's color
        Medium med;         // medium of the object (ior/beta)
        int p;              // Phong's coefficient (cosine power)
        Vector n;           // normal at a given point
        Vector map_coord;   // mapping coordinates
};

} // Grayzer namespace
