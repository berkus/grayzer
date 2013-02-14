//
//  @brief Environment
//
#include "environment/Environment.h"
#include "go/GeomObj.h"
#include "light/LightSource.h"
#include "environment/Geometry.h"
#include "Tracer.h"


Scene::~Scene()
{
	light.clear();
	solid.clear();
	if(envFog) delete envFog;
}


void Scene::add(LightSource *l)
{
  light.append(l);
}


void Scene::add(GeometricObject *g)
{
  solid.append(g);
}


geometric_object *environment::intersect( ray& r, double& t	)
{
	geometric_object *closest_obj  = 0;
	double			  closest_dist = GEOM_INFINITY;
	int	i;

	for( i = 0;	i <	solids_count; i++ )
		if(	solid[i]->intersect(r,t) )
			if(	t <	closest_dist )
			{
				closest_dist = t;
				closest_obj	= solid[i];
			}
	t =	closest_dist;
	return closest_obj;
}


Vector environment::shade_background( ray& )
{
	return background;
}
