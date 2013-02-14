//
//  Description..: granite procedural texture
//
#ifndef _GRANITE_
#define _GRANITE_

#include "texture/Texture.h"
#include "ColorTable.h"


class granite : public texture
{
    public:
        color_table tbl;

        granite() : texture(), tbl() {}

        virtual void apply( Vector&, surface_data& );
};


#endif // _GRANITE_ //
