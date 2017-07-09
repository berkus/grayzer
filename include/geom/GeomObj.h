//
//  @brief base class geometric_object
//  Comments.....:
//    98/01/26
//      added Translate,Scale,Rotate transforms
//
#ifndef _GEOMOBJ_
#define _GEOMOBJ_

#include "math/Vector.h"
#include "Ray.h"
#include "SurfaceData.h"
#include "texture/Texture.h"
#include "map/Map.h"


extern surface_data default_material;


class geometric_object
{
    public:
        surface_data def_material;
        map *mapping;
        texture *material;
//      transformation *transform;

    public:
        geometric_object();
        virtual ~geometric_object();

        void find_texture( Vector&, surface_data& );

        void add( texture * );

        virtual bool intersect( ray&, double& ) = 0;
        virtual Vector find_normal( Vector& ) = 0;

        //
        //  transformations
        //
        void scale( const Vector& scale );
        void translate( const Vector& loc );
        void rotate( const Vector& rotate );
        //
        //  texture/material manage
        //
        void ambient( double ka ) { def_material.ka = ka; }
        void diffuse( double kd ) { def_material.kd = kd; }
        void specular( double ks ) { def_material.ks = ks; }
        void reflection( double kr ) { def_material.kr = kr; }
        void transmittance( double kt ) { def_material.kt = kt; }
        void ior( double ior ) { def_material.med.ior = ior; }
        void phong_size( int p ) { def_material.p = p; }
        void color( Vector c ) { def_material.color = c; }
        void map_coord( Vector c ) { def_material.map_coord = c; }

        const double ambient() const { return def_material.ka; }
        const double diffuse() const { return def_material.kd; }
        const double specular() const { return def_material.ks; }
        const double reflection() const { return def_material.kr; }
        const double transmittance() const { return def_material.kt; }
        const double ior() const { return def_material.med.ior; }
        const int phong_size() const { return def_material.p; }
        const Vector& color() const { return def_material.color; }
        const Vector& map_coord() const { return def_material.map_coord; }
};


inline geometric_object::geometric_object()
: def_material( default_material )
, mapping( 0 )
, material( 0 )
//, transform( 0 )
{}


#endif // _GEOMOBJ_
