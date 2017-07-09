//
//  @brief basic class Image for images manipulation
//
#pragma once

#include "image/RGB.h"

class Image
{
    public:
        int width, height;

        Image() {}
        virtual ~Image() {}

        virtual rgb get_pixel( int, int ) = 0;
        virtual void put_pixel( rgb ) = 0;
};
