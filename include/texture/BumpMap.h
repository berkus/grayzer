//
//  Description......: Bump map texture
//
#ifndef _BUMPMAP_
#define _BUMPMAP_

#include "texture/Texture.h"
#include "image/Image.h"


class bump_map : public texture
{
    public:
        bump_map( image *i,double a );
       ~bump_map();

        virtual void apply( Vector&, surface_data& );

    public:
        image *map;
        double amount;
};


inline bump_map::bump_map( image *i, double a )
: texture()
, map( i )
, amount( a )
{}

inline bump_map::~bump_map()
{   delete map; }


#endif // _BUMPMAP_ //
