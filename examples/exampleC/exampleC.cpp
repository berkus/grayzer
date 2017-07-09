#include "math/Vector.h"
#include "Tracer.h"
#include "Render.h"
#include "Colors.h"
#include "texture/Brick.h"
#include "texture/Ripples.h"
#include "geom/Sphere.h"
#include "geom/Rect.h"
#include "environment/Scene.h"
#include "light/PointLight.h"
#include "light/SpotLight.h"

int main()
{
    LightSource *Light1,*Light2;
    Rectangle *Facet1;
    Sphere *Sphere1,*Sphere2,*Sphere3;

    Scene *scene = new Scene;
    Facet1 = new Rectangle(Vector(-160,-50,-100),Vector(320,0,0),Vector(0,0,200));
    Sphere1 = new Sphere(Vector(15,10,-30),15);
    Sphere2 = new Sphere(Vector(10,-40,-5),15);
    Sphere3 = new Sphere(Vector(45,-10,-20),15);
    Light1 = new PointLight(Vector(-20,20,-25),40);
    Light2 = new SpotLight(Vector(0,0,0),Vector(0,-50,0),0,1.7,3);

    Facet1->add(new Brick(Vector(11,6,5),Vector(0.75),Khaki,Vector(0.5)));
    Facet1->ambient(0.25);
    Facet1->transmittance(0.0);
    Facet1->reflection(0.0);
    Facet1->specular(0.0);
    Facet1->diffuse(1.0);
    Facet1->phong_size(1);
    Facet1->medium(Grayzer::Medium::air);

    Sphere1->ambient(0.25);
    Sphere1->diffuse(0.0);
    Sphere1->specular(0.3);
    Sphere1->reflection(0.3);
    Sphere1->transmittance(0.8);
    Sphere1->phong_size(100);
    Sphere1->ior(1.35);
    Sphere1->beta(0);
    Sphere1->color(0);

    Sphere2->ambient(0.25);
    Sphere2->diffuse(0.4);
    Sphere2->specular(0.0);
    Sphere2->reflection(0.0);
    Sphere2->transmittance(0.0);
    Sphere2->phong_size(3);
    Sphere2->medium(Grayzer::Medium::glass);
    Sphere2->color(Blue);
    Sphere3->surface_data(Sphere1->surface_data());

    Facet1->add(new Ripples(Vector(0,0,5),2,0.3));
    scene->add(Facet1);
    scene->add(Sphere1);
    scene->add(Sphere2);
    scene->add(Sphere3);
    scene->add(Light1);
    scene->add(Light2);

    threshold = 0.05;
    scene->setCamera(Vector(30,180,200),Vector(-50,-320,-350),Vector(0,1,0));
    render_scene(scene, 150,100,600,400,"SAMPLEC0.TGA");
}
