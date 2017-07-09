//
//  Description......: Color map texture
//
#pragma once

#include <memory>
#include "texture/Texture.h"
#include "image/Image.h"

class ColorMap : public Texture
{
    public:
        std::shared_ptr<Image> map;

        ColorMap( Image *i ) : Texture(), map(i) {}
       ~ColorMap() {}

        void apply(Vector&, Grayzer::SurfaceData&) override;
};
