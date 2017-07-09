//
//  @brief base class geometric_object realization
//
#include "geom/GeomObj.h"


geometric_object::~geometric_object()
{
	texture	*m;

	if(mapping) delete mapping;

	for( m = material; m !=	0; m = material )
	{
		material = material->next;
		delete m;
	}

//	if(transform) delete transform;
}


void geometric_object::add(texture *m)
{
	m->next	= material;
	m->object =	this;
	material = m;
}


void geometric_object::find_texture( Vector& p, surface_data& t	)
{
	texture	*m;

	t =	def_material;
	t.n	= find_normal(p);

	if(mapping) t.map_coord = mapping->apply(p);

	for( m = material; m !=	0; m = m->next) m->apply(p,t);
}


void geometric_object::scale( const Vector& factor )
{
/*	if(	!transform ) transform = new transformation;

	(*transform) *=	t_scale(factor);
*/
}


void geometric_object::translate( const	Vector&	loc	)
{
/*	if(	!transform)	transform =	new	transformation;

	(*transform) *=	t_translate(loc);
*/
}


void geometric_object::rotate( const Vector& rot )
{
/*	if(	!transform ) transform = new transformation;

	(*transform) *=	t_rotate(rot);
*/
}
