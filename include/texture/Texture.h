//
//  @brief base class texture
//
#ifndef _TEXTURE_
#define _TEXTURE_

#include "math/Vector.h"


class surface_data;
class geometric_object;


class texture
{
    public:
        texture *         next;
        geometric_object *object;
        double            turb;
        int               octaves;
        Vector            offs, scale;

        texture();
        virtual ~texture() {}

        virtual void apply( Vector&, surface_data& ) = 0;
};


inline texture::texture()
: next( 0 )
, object( 0 )
, turb( 0.0 )
, octaves( 6 )
, offs( 0 )
, scale( 1 )
{}


#endif // _TEXTURE_
