//
//  @brief Environment
//
#include "environment/Scene.h"
#include "geom/GeomObj.h"
#include "light/LightSource.h"
#include "environment/Geometry.h"
#include "Tracer.h"

GeometricObject *Scene::intersect(Ray& r, double& t)
{
    std::shared_ptr<GeometricObject> closest_obj;
    double           closest_dist = GEOM_INFINITY;

    for(int i = 0; i < solid.size(); ++i)
        if( solid[i]->intersect(r,t) )
            if( t < closest_dist )
            {
                closest_dist = t;
                closest_obj = solid[i];
            }
    t = closest_dist;
    return closest_obj.get();
}

Vector Scene::shade_background(Ray&)
{
    return background;
}
