#include "Tracer.h"
#include "Render.h"
#include "Colors.h"
#include "Noise.h"
#include "texture/Bumps.h"
#include "geom/Sphere.h"
#include "light/PointLight.h"
#include "environment/Scene.h"

int main()
{
    Sphere* Sphere1;
    LightSource *Light1,*Light2;

    Scene* scene = new Scene;
    Sphere1 = new Sphere(Vector(0,0,0),4);

    Sphere1->ambient(0.3);
    Sphere1->diffuse(0.2);
    Sphere1->specular(0.7);
    Sphere1->reflection(0.0);
    Sphere1->ior(0.0);
    Sphere1->phong_size(30);
    Sphere1->medium(Grayzer::Medium::glass);
    Sphere1->color(Red);
    Sphere1->add(new Bumps(7.0));

    Light1 = new PointLight(Vector(-10,8,-20),20);
    Light2 = new PointLight(Vector(10,8,-20),20);

    scene->add(Sphere1);
    scene->add(Light1);
    scene->add(Light2);

    scene->setBackground(SkyBlue);

    init_noise();
    scene->setCamera(Vector(0,0,-7),Vector(0,0,1),Vector(0,1,0));
    render_scene(scene, 1.5,1.0,300,200,"SAMPLE80.TGA");
    done_noise();
}
