//
//  Description..: wrinkles procedural perturbation texture
//
#ifndef _WRINKLES_
#define _WRINKLES_

#include "texture/Texture.h"


class wrinkles : public texture
{
    public:
        double amount;

        wrinkles( double a = 1.0 ) : texture(), amount( a ) {}

        virtual void apply( Vector&, surface_data& );
};


#endif // _WRINKLES_
