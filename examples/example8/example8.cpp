#include "tracer.hpp"
#include "geometry.hpp"
#include "render.h"
#include "colors.h"
#include "noise.h"
#include "bumps.hpp"
#include "sphere.hpp"
#include "pointlit.hpp"
#include "environ.hpp"

void main()
{
    PSphere Sphere1;
    PLightSource Light1,Light2;

    Scene = new Environment;
    Sphere1 = new Sphere(Vector(0,0,0),4);

    Sphere1->Ambient(0.3);
    Sphere1->Diffuse(0.2);
    Sphere1->Specular(0.7);
    Sphere1->Reflection(0.0);
    Sphere1->Refraction(0.0);
    Sphere1->PhongSize(30);
    Sphere1->DefMaterial.Med = Glass;
    Sphere1->Color(Red);
    Sphere1->Add(new Bumps(7.0));

    Light1 = new PointLight(Vector(-10,8,-20),20);
    Light2 = new PointLight(Vector(10,8,-20),20);

    Scene->Add(Sphere1);
    Scene->Add(Light1);
    Scene->Add(Light2);

    Background = SkyBlue;

    InitNoise();
    SetCamera(Vector(0,0,-7),Vector(0,0,1),Vector(0,1,0));
    RenderScene(1.5,1.0,300,200,"SAMPLE80.TGA");
    DoneNoise();
}
