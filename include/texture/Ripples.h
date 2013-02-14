//
//  Description..: ripples procedural perturbation texture
//
#ifndef _RIPPLES_
#define _RIPPLES_

#include "texture/Texture.h"


class ripples : public texture
{
    public:
        Vector center;
        double wave_len;
        double phase;
        double amount;

        ripples( const Vector& c, double a, double l, double p = 0 );

        virtual void apply( Vector&, surface_data& );
};


inline ripples::ripples(const Vector& c, double a, double l, double p)
: texture()
, center( c )
, wave_len( l )
, phase( p )
, amount( a )
{}


#endif // _RIPPLES_
