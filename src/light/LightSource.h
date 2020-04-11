//
//  @brief base class LightSource for light sources control
//
#pragma once

#include "math/Vector.h"

class Scene;

class LightSource
{
public:
    Vector color;

    LightSource() : color(1.0) {}
    virtual ~LightSource() {}

    virtual double shadow(Scene* scene, Vector&, Vector&) = 0;
};
