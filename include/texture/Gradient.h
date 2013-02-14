//
//  Description......: gradient color texture
//
#ifndef _GRADIENT_
#define _GRADIENT_

#include "texture/Texture.h"
#include "ColorTable.h"


class gradient : public texture
{
    public:
        Vector      grad;
        color_table tbl;

        gradient( Vector g ) : texture(), grad( g ), tbl() {}

        virtual void apply( Vector&, surface_data& );
};


#endif // _GRADIENT_ //
