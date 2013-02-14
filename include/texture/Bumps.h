//
//  Description......: Bumps noise texture
//
#ifndef _BUMPS_
#define _BUMPS_

#include "texture/Texture.h"


class bumps : public texture
{
    public:
        double amount;

        bumps( double a = 1.0 ) : texture(), amount( a ) {}

        virtual void apply( Vector&, surface_data& );
};


#endif // _BUMPS_
