//
//  Description......: Bozo procedural texture
//
#ifndef _BOZO_
#define _BOZO_

#include "texture/Texture.h"
#include "ColorTable.h"


class bozo : public texture
{
    public:
        bozo( double t = 0.0 );

        virtual void apply( Vector&, surface_data& );

    public:
        color_table tbl;
};


inline bozo::bozo( double t )
: texture()
, tbl()
{
    turb = t;
}


#endif // _BOZO_ //
