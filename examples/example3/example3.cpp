#include "math/Vector.h"
#include "Tracer.h"
#include "Render.h"
#include "environment/Geometry.h"
#include "environment/Scene.h"
#include "geom/Sphere.h"
#include "geom/Plane.h"
#include "light/PointLight.h"
#include "Colors.h"

int main()
{
    Sphere *s1,*s2,*s3;
    Plane *p;
    PointLight *Light1;

    Scene* scene = new Scene();
    s1 = new Sphere(Vector(0,1,5),1.5);
    s2 = new Sphere(Vector(-3,0,4),1);
    s3 = new Sphere(Vector(3,0,4),1);
    p = new Plane(Vector(0,1,0),1);
    s1->ambient(0.2);
    s1->diffuse(0.5);
    s1->specular(0.6);
    s1->reflection(0.0);
    s1->transmittance(0.0);
    s1->phong_size(30);
    s1->color(Yellow);
    s1->medium(Grayzer::Medium::glass);

    s2->surface_data(s1->surface_data());
    s2->color(Red);

    s3->surface_data(s1->surface_data());
    s3->color(Blue);

    p->surface_data(s1->surface_data());
    p->ambient(0.1);
    p->diffuse(0.5);
    p->specular(0.4);
    p->reflection(0.4);
    p->color(Blue);

    s1->reflection(0.3);

    Light1 = new PointLight(Vector(10,5,-10),17);
    scene->add(s1);
    scene->add(s2);
    scene->add(s3);
    scene->add(p);
    scene->add(Light1);
    scene->setBackground(SkyBlue);
    scene->setCamera(Vector(0),Vector(0,0,1),Vector(0,1,0));
    render_scene(scene, 1.5,1.0,300,200,"SAMPLE30.TGA");
    distributed_render_scene(scene, 1.5,1.0,300,200,5,5,"SAMPLE31.TGA");
}
