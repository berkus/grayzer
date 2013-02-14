//
//  @brief base class LightSource for light sources control
//
#ifndef _LIGHTSRC_
#define _LIGHTSRC_

#include "math/Vector.h"


class light_source
{
    public:
        Vector color;

        light_source() : color( 1 ) {}
        virtual ~light_source() {}

        virtual double shadow( Vector&, Vector& ) = 0;
};


#endif // _LIGHTSRC_
