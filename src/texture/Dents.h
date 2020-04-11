//
//  File.............: dents.hpp
//  Description......: Dents procedural perturbation texture
//
#pragma once

#include "texture/Texture.h"

class Dents : public Texture
{
public:
    double amount;

    Dents( double a = 1.0 ) : Texture(), amount( a ) {}

    void apply(Vector&, Grayzer::SurfaceData&) override;
};
