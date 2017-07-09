#include <stdio.h>
//#include "model.h"
#include "math/Vector.h"
#include "Tracer.h"
#include "environment/Geometry.h"
#include "environment/Scene.h"
#include "geom/Sphere.h"
#include "geom/Plane.h"
#include "light/PointLight.h"
#include "texture/Texture.h"
#include "Render.h"

int main()
{
    Sphere *Solid;
    Sphere *Solid2;
    Plane *plane;
    PointLight *Light1,*Light2;
#ifndef DEBUG
    printf("Rendering scene.It may take a few minutes.Please wait...");
#endif
    scene=new Scene();
    plane=new Plane(5,5,25,15); /////////|
    Solid=new Sphere(Vector(15,10,-30),15);
    Solid2=new Sphere(Vector(10,-40,-5),15);
    Light1=new PointLight(Vector(30,-23,15),90);
    Light2=new PointLight(Vector(-20,20,-25),90);
    printf("\nSetting up texture maps\n");
    Solid->ambient(0.0);
    Solid->diffuse(0.0);
    Solid->specular(0.3);
    Solid->transmittance(0.7);
    Solid->phong_size(5);
    Solid->color(Vector(15,15,11));
    Solid->def_material.med=Grayzer::Medium::glass;
    Solid2->ambient(0.2);
    Solid2->diffuse(0.4);
    Solid2->specular(0.0);
    Solid2->transmittance(0.0);
    Solid2->phong_size(3);
    Solid2->color(Vector(0,0,10));
    Solid2->def_material.med=Grayzer::Medium::glass;
    printf("\nAdding objects to scene\n");
    scene->add(plane); /////////////|
    scene->add(Solid);
    scene->add(Solid2);
    scene->add(Light1);
    scene->add(Light2);

    setCamera(Vector(0,10,20),Vector(-5,-32,-35),Vector(1,1,1));
    render_scene(160,100,320,200,"PIC01.OUT");
}
