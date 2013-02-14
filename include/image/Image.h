//
//  @brief basic class Image for images manipulation
//
#ifndef _IMAGE_
#define _IMAGE_

#include "image/RGB.h"


class image
{
    public:
        int width, height;

        image() {}
        virtual ~image() {}
        virtual rgb get_pixel( int, int ) = 0;
        virtual void put_pixel( rgb ) = 0;
};


#endif // _IMAGE_ //
