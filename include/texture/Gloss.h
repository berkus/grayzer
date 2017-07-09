//
//  Description......: gloss procedural texture
//
#pragma once

#include "texture/Texture.h"

class Gloss : public Texture
{
    public:
        Gloss() : Texture() {}

        void apply(Vector&, Grayzer::SurfaceData&) override;
};
