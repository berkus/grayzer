#include "vector.hpp"
#include "tracer.hpp"
#include "render.h"
#include "geometry.hpp"
#include "colors.h"
#include "brick.hpp"
#include "environ.hpp"
#include "pointlit.hpp"
#include "rect.hpp"
#include "sphere.hpp"
#include "ripples.hpp"

extern unsigned _stklen = 64000U;

void main()
{
	PointLight *Light1,*Light2;
    Rect *Facet1,*Facet2,*Facet3;
    Sphere *Sphere1,*Sphere2,*Sphere3;

    Scene = new Environment;
    Facet1 = new Rect(Vector(-50,-50,-53),Vector(200,0,0),Vector(0,0,200));
    Facet2 = new Rect(Vector(-50,-50,-53),Vector(0,0,200),Vector(0,200,0));
    Facet3 = new Rect(Vector(-50,-50,-53),Vector(0,200,0),Vector(200,0,0));
    Sphere1 = new Sphere(Vector(15,10,-30),15);
    Sphere2 = new Sphere(Vector(10,-40,-5),15);
    Sphere3 = new Sphere(Vector(45,-10,-20),15);
	Light1 = new PointLight(Vector(-20,20,-25),40); //SphericLight(Vector(-20,20,-25),50,40);
	Light2 = new PointLight(Vector(30,-23,15),40);
	Facet1->Add(new Brick(Vector(11,6,5),Vector(0.1),Firebrick,Vector(0.5)));
	Facet2->Add(new Brick(Vector(11,6,5),Vector(0.1),Firebrick,Vector(0.5)));
	Facet3->Add(new Brick(Vector(11,6,5),Vector(0.1),Firebrick,Vector(0.5)));
    Facet1->DefMaterial.Ka = 0.25;
	Facet1->DefMaterial.Kt = 0.0;
	Facet1->DefMaterial.Kr = 0.0;
	Facet1->DefMaterial.Ks = 0.0;
	Facet1->DefMaterial.Kd = 1.0;
    Facet1->DefMaterial.p = 1;
    Facet1->DefMaterial.Med = Air;
    Facet2->DefMaterial = Facet1->DefMaterial;
	Facet3->DefMaterial = Facet1->DefMaterial;
	Sphere1->Add(new Ripples(Vector(0,0,5),2,0.3));
    Sphere1->DefMaterial.Ka = 0.25;
    Sphere1->DefMaterial.Kd = 0.0;
    Sphere1->DefMaterial.Ks = 0.3;
    Sphere1->DefMaterial.Kr = 0.3;
    Sphere1->DefMaterial.Kt = 0.8;
    Sphere1->DefMaterial.p = 100;
	Sphere1->DefMaterial.Med.ior = 1.35;
    Sphere1->DefMaterial.Med.Betta = 0;
    Sphere1->DefMaterial.Color = 0;
    Sphere2->DefMaterial.Ka = 0.25;
    Sphere2->DefMaterial.Kd = 0.4;
    Sphere2->DefMaterial.Ks = 0.0;
    Sphere2->DefMaterial.Kr = 0.0;
    Sphere2->DefMaterial.Kt = 0.0;
    Sphere2->DefMaterial.p = 3;
    Sphere2->DefMaterial.Med = Glass;
    Sphere2->DefMaterial.Color = Blue;
    Sphere3->DefMaterial = Sphere1->DefMaterial;
    Scene->Add(Facet1);
    Scene->Add(Facet2);
    Scene->Add(Facet3);
    Scene->Add(Sphere1);
    Scene->Add(Sphere2);
    Scene->Add(Sphere3);
    Scene->Add(Light1);
    Scene->Add(Light2);
    Threshold = 0.05;
    SetCamera(Vector(30,180,200),Vector(-50,-320,-350),Vector(0,1,0));
	RenderScene(160,100,320,200,"SAMP0030.TGA");
//  DistributedRenderScene(150,100,300,200,3,3,"SAMP0031.TGA");
//	AdaptiveDistributedRenderScene(128,120,256,240,3,3,0.01,"SAMP0032.TGA");
}
