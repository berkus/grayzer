/*
 * Scene
 */
#ifndef _ENVIRON_
#define _ENVIRON_

#include "math/Vector.h"
#include <qptrlist.h>

class Ray;
class LightSource;
class GeometricObject;


class Fog
{
    public:
        double distance;
        Vector fog_color;

        fog( double d, Vector& c ) : distance( d ), fog_color( c ) {}

        virtual void shade( Vector& color, double dist );
};

typedef QPtrList<LightSource> LightSourcePtrList;
typedef QPtrList<GeometricObject> SolidPtrList;

class Scene
{
    public:
        LightSourcePtrList light;
        SolidPtrList solid;

        Fog *envFog;

	Scene() : envFog(0) { light.setAutoDelete(TRUE); solid.setAutoDelete(TRUE); };
        virtual ~Scene();

        void add(LightSource *);
        void add(GeometricObject *);

        virtual GeometricObject *intersect(Ray&, double&);
        virtual Vector shadeBackground(Ray&);
};


#endif // _ENVIRON_
