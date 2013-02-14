#include "tracer.hpp"
#include "geometry.hpp"
#include "render.h"
#include "colors.h"
#include "map.hpp"
#include "bmp.hpp"
#include "planemap.hpp"

void main()
{
	Box *b = new Box(Vector(0,-2,5),Vector(8,0,3),Vector(-8,0,3),Vector(0,-3,0));
//	Sphere *s = new Sphere(Vector(0,0,5),50);
	LightSource *Light1 = new PointLight(Vector(7,10,-10),20);
	BmpImage *img = new BmpImage("backgnd.bmp");
	ColorMap *cmap = new ColorMap(img);

	cmap->Scale = 25;

	Scene = new Environment;

	b->Mapping = new PlaneMap(Vector(0,-1,-1),Vector(1,0,0));
	b->Add(cmap);
	b->Ambient(0.3);
	b->Diffuse(0.8);
	b->Specular(0.3);
	b->Reflection(0.0);
	b->Refraction(0.0);
	b->PhongSize(5);
	b->DefMaterial.Med = Glass;
	b->DefMaterial.Color = 1;

	Scene->Add(b);
	Scene->Add(Light1);

	Background = SkyBlue;
	SetCamera(Vector(0),Vector(0,0,1),Vector(0,1,0));
	RenderScene(1.6,1.0,320,200,"SAMP0080.TGA");
}
