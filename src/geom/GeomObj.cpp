//
//  @brief base class GeometricObject realization
//
#include "geom/GeomObj.h"
#include "texture/Texture.h"

using Grayzer::SurfaceData;

GeometricObject::~GeometricObject()
{
    Texture *m;

    if(mapping) delete mapping;

    for( m = material; m != 0; m = material )
    {
        material = material->next;
        delete m;
    }

//  if(transform) delete transform;
}

void GeometricObject::add(Texture *m)
{
    m->next = material;
    m->object = this;
    material = m;
}

void GeometricObject::find_texture(Vector& p, SurfaceData& t)
{
    Texture *m;

    t = def_material;
    t.n = find_normal(p);

    if(mapping) t.map_coord = mapping->apply(p);

    for( m = material; m != 0; m = m->next) m->apply(p,t);
}

void GeometricObject::scale(Vector const& factor)
{
/*  if( !transform ) transform = new transformation;

    (*transform) *= t_scale(factor);
*/
}

void GeometricObject::translate(Vector const& loc)
{
/*  if( !transform) transform = new transformation;

    (*transform) *= t_translate(loc);
*/
}


void GeometricObject::rotate(Vector const& rot)
{
/*  if( !transform ) transform = new transformation;

    (*transform) *= t_rotate(rot);
*/
}
