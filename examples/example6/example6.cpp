#include "tracer.hpp"
#include "geometry.hpp"
#include "render.h"
#include "colors.h"
#include "wood.hpp"
#include "box.hpp"
#include "pointlit.hpp"
#include "environ.hpp"

void
main()
{
	Box *b=new Box(Vector(-1,-1,-2),Vector(2,0,0),Vector(0,2,0),Vector(0,0,4));
	PPointLight Light1,Light2;

	Scene = new Environment;
	b->Ambient(0.3);
	b->Diffuse(0.7);
	b->Specular(0.5);
	b->DefMaterial.Kr=0.0;
	b->DefMaterial.Kt=0.0;
	b->PhongSize(30);
	b->DefMaterial.Color=Yellow;
	b->DefMaterial.Med=Glass;
	b->Add(new Wood(35,6,5));

	Light1 = new PointLight(Vector(10,5,-10),17);
	Light2 = new PointLight(Vector(-10,-5,-10),17);

	Scene->Add(b);
	Scene->Add(Light1);
	Scene->Add(Light2);
	Background = SkyBlue;
    InitNoise();
    SetCamera(Vector(-4,8,-4),Vector(2,-5,2),Vector(0,1,0));
	RenderScene(1.6,1.0,320,200,"SAMPLE50.TGA");
	DoneNoise();
}