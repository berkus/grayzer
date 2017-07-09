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
    LightSourcePtrList light;
    SolidPtrList solid;

    std::shared_ptr<Fog> envFog;

    //
    //  camera parameters
    //
    Vector eye{0.0, 0.0, 0.0};
    Vector eye_dir{0.0, 0.0, 1.0};
    Vector view_x{1.0, 0.0, 0.0}, view_y{0.0, 1.0, 0.0};
    double aperture{0.0};// pадиус линзы
    double focus{0.0};   // фокусное pасстояние

public:
    Scene() {}
    virtual ~Scene() {}

    void add(LightSource *l) { light.emplace_back(l); }
    void add(GeometricObject *g) { solid.emplace_back(g); }

    virtual GeometricObject *intersect(Ray&, double&);
    virtual Vector shade_background(Ray&);

    void camera( double, double, Ray& );
    void setCamera( const Vector&, const Vector&, const Vector& );

    Color trace( Grayzer::Medium&, double, Ray& );
    Color shade( Grayzer::Medium&, double, Vector, Vector, GeometricObject * );
};
