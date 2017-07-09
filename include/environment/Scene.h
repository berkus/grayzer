/*
 * Scene
 */
#pragma once

#include "math/Vector.h"
#include <vector>
#include <memory>
#include "light/LightSource.h"
#include "geom/GeomObj.h"

class Ray;

class Fog
{
    public:
        double distance;
        Vector fog_color;

        Fog( double d, Vector& c ) : distance( d ), fog_color( c ) {}

        virtual void shade( Vector& color, double dist );
};

using LightSourcePtrList = std::vector<std::shared_ptr<LightSource>>;
using SolidPtrList = std::vector<std::shared_ptr<GeometricObject>>;

class Scene
{
    public:
        LightSourcePtrList light;
        SolidPtrList solid;

        std::shared_ptr<Fog> envFog;

        Scene() {};
        virtual ~Scene() {}

        void add(LightSource *l) { light.emplace_back(l); }
        void add(GeometricObject *g) { solid.emplace_back(g); }

        virtual GeometricObject *intersect(Ray&, double&);
        virtual Vector shade_background(Ray&);
};
