//
//  Description......: gloss procedural texture
//
#ifndef _GLOSS_
#define _GLOSS_

#include "texture/Texture.h"


class gloss : public texture
{
    public:
        gloss() : texture() {}

        virtual void apply( Vector&, surface_data& );
};


#endif // _GLOSS_
