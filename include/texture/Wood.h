//
//  Description..: wood procedural texture
//
#ifndef _WOOD_
#define _WOOD_

#include "texture/Texture.h"
#include "Noise.h"


class wood : public texture
{
    public:
        double ring_spacing;
        int    squeeze;

        wood( double r, double t, int s = 1 );

        virtual void apply( Vector&, surface_data& );
};


inline wood::wood( double r, double t, int s )
: texture()
, ring_spacing( r )
, squeeze( s )
{
    turb = t;
}


#endif // _WOOD_
