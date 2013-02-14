#include "vector.hpp"
#include "tracer.hpp"
#include "render.h"
#include "geometry.hpp"
#include "colors.h"

extern unsigned _stklen = 64000U;

void main()
{
    Sphere *s1,*s2,*s3;
    Plane *p;
    PointLight *Light1;

    Scene = new Environment();
    s1 = new Sphere(Vector(0,1,5),1.5);
    s2 = new Sphere(Vector(-3,0,4),1);
    s3 = new Sphere(Vector(3,0,4),1);
    p = new Plane(Vector(0,1,0),1);
    s1->DefMaterial.Ka = 0.2;
    s1->DefMaterial.Kd = 0.5;
    s1->DefMaterial.Ks = 0.6;
    s1->DefMaterial.Kr = 0.0;
    s1->DefMaterial.Kt = 0.0;
    s1->DefMaterial.p = 30;
    s1->DefMaterial.Color = Yellow;
    s1->DefMaterial.Med = Glass;
    s2->DefMaterial = s1->DefMaterial;
    s2->DefMaterial.Color = Red;
    s3->DefMaterial = s1->DefMaterial;
    s3->DefMaterial.Color = Blue;
    p->DefMaterial = s1->DefMaterial;
    p->DefMaterial.Ka = 0.1;
    p->DefMaterial.Ks = 0.4;
    p->DefMaterial.Kd = 0.5;
    p->DefMaterial.Kr = 0.4;
    p->DefMaterial.Color = Blue;
    s1->DefMaterial.Kr = 0.3;
	Light1 = new PointLight(Vector(10,5,-10),17);
    Scene->Add(s1);
	Scene->Add(s2);
    Scene->Add(s3);
    Scene->Add(p);
    Scene->Add(Light1);
    Background = SkyBlue;
    SetCamera(Vector(0),Vector(0,0,1),Vector(0,1,0));
	RenderScene(1.5,1.0,300,200,"SAMPLE20.TGA");
	DistributedRenderScene(1.5,1.0,300,200,5,5,"SAMPLE21.TGA");
}