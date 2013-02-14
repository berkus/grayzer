//
//  Description......: Checker texture
//
#ifndef _CHECKER_
#define _CHECKER_

#include "texture/Texture.h"


class checker : public texture
{
    public:
        Vector color1, color2;

        checker( Vector c1, Vector c2 );

        virtual void apply( Vector&, surface_data& );
};


inline checker::checker( Vector c1, Vector c2 )
: texture()
, color1( c1 )
, color2( c2 )
{}


#endif // _CHECKER_
