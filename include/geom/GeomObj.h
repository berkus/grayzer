//
//  @brief base class geometric_object
//  Comments.....:
//    98/01/26
//      added Translate,Scale,Rotate transforms
//
#pragma once

#include "math/Vector.h"
#include "Ray.h"
#include "SurfaceData.h"
#include "map/Map.h"

extern Grayzer::SurfaceData defaultMaterial;
class Texture;

class GeometricObject
{
    public:
        Grayzer::SurfaceData def_material;
        Map *mapping;
        Texture *material;
//      Transformation *transform;

    public:
        GeometricObject()
            : def_material(defaultMaterial)
            , mapping(0)
            , material(0)
            //, transform(0)
        {}

        virtual ~GeometricObject();

        void find_texture(Vector&, Grayzer::SurfaceData&);

        void add(Texture*);

        virtual bool intersect(Ray&, double&) = 0;
        virtual Vector find_normal(Vector&) = 0;

        //
        //  transformations
        //
        void scale( const Vector& scale );
        void translate( const Vector& loc );
        void rotate( const Vector& rotate );
        //
        //  texture/material manage
        //
    void surface_data(Grayzer::SurfaceData mat) { def_material = mat; }
    void ambient( double ka ) { def_material.ka = ka; }
    void diffuse( double kd ) { def_material.kd = kd; }
    void specular( double ks ) { def_material.ks = ks; }
    void reflection( double kr ) { def_material.kr = kr; }
    void transmittance( double kt ) { def_material.kt = kt; }
    void medium(Grayzer::Medium med) { def_material.med = med; }
    void ior( double ior ) { def_material.med.ior = ior; }
    void beta(double beta) { def_material.med.beta = beta; }
    void phong_size( int p ) { def_material.p = p; }
    void color( Vector c ) { def_material.color = c; }
    void map_coord( Vector c ) { def_material.map_coord = c; }

    Grayzer::SurfaceData const surface_data() const { return def_material; }
    double const ambient() const { return def_material.ka; }
    double const diffuse() const { return def_material.kd; }
    double const specular() const { return def_material.ks; }
    double const reflection() const { return def_material.kr; }
    double const transmittance() const { return def_material.kt; }
    Grayzer::Medium const medium() const { return def_material.med; }
    double const ior() const { return def_material.med.ior; }
    double const beta() const { return def_material.med.beta; }
    int const    phong_size() const { return def_material.p; }
    Vector const& color() const { return def_material.color; }
    Vector const& map_coord() const { return def_material.map_coord; }
};
