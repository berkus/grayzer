//
//  File.............: dents.hpp
//  Description......: Dents procedural perturbation texture
//
#ifndef _DENTS_
#define _DENTS_

#include "texture/Texture.h"


class dents : public texture
{
    public:
        double amount;

        dents( double a = 1.0 ) : texture(), amount( a ) {}

        virtual void apply( Vector&, surface_data& );
};


#endif // _DENTS_ //
