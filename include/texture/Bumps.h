//
//  Description......: Bumps noise texture
//
#pragma once

#include "texture/Texture.h"

class Bumps : public Texture
{
    public:
        double amount;

        Bumps( double a = 1.0 ) : Texture(), amount(a) {}

        void apply(Vector&, Grayzer::SurfaceData&) override;
};
