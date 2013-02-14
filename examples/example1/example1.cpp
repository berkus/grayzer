#include <stdio.h>
#include <conio.h>
#include "model.h"
#include "vector.h"
#include "tracer.h"
#include "geometry.h"
#include "render.h"

#define	MAX_SOLIDS 100

class SimpleScene :	public Environment {
public:
		GeometricObject	*Solid[MAX_SOLIDS];
		int	SolidsCount;
		SimpleScene() {	SolidsCount=0; }
		~SimpleScene();
		virtual	void AddObject(GeometricObject *);
		virtual	GeometricObject	*Intersect(Ray&,float&);
		virtual	void ShadeBackground(Ray&,Vector&);
};
SimpleScene::~SimpleScene()
{
		for(int	i=0;i<SolidsCount;i++) delete Solid[i];
}
void SimpleScene::AddObject(GeometricObject	*o)
{
		if(SolidsCount<MAX_SOLIDS-1) Solid[SolidsCount++]=o;
}
GeometricObject	* SimpleScene::Intersect(Ray& ray,float& t)
{
		GeometricObject	*ClosestObj=NULL;
		float ClosestDist=INFINITY;
		for(int	i=0;i<SolidsCount;i++)
				if(Solid[i]->Intersect(ray,t)) if(t<ClosestDist)
				{
						ClosestDist=t;
						ClosestObj=Solid[i];
				}
		t=ClosestDist;
		return ClosestObj;
}
void SimpleScene::ShadeBackground(Ray&,Vector& color)
{
		color=Background;
}

void main(void)
{
		SimpleSphere *Solid;
		SimpleSphere *Solid2;
		SimplePlane	*Plane;
		PointLight *Light1,*Light2;
		clrscr();
		_setcursortype(_NOCURSOR);
#ifndef	DEBUG
		printf("Rendering scene.It may take a few minutes.Please wait...");
#endif
		Scene=new SimpleScene();
		Plane=new SimplePlane(5,5,25,15); /////////|
		Solid=new SimpleSphere(Vector(15,10,-30),15);
		Solid2=new SimpleSphere(Vector(10,-40,-5),15);
		Light1=new PointLight(Vector(30,-23,15),90);
		Light2=new PointLight(Vector(-20,20,-25),90);
		printf("\nSetting up texture maps\n");
		Solid->Texture.Ka=0.0;
		Solid->Texture.Kd=0.0;
		Solid->Texture.Ks=0.3;
		Solid->Texture.Kt=0.7;
		Solid->Texture.p=5;
		Solid->Texture.Color=Vector(15,15,11);
		Solid->Texture.Med=Glass;
		Solid2->Texture.Ka=0.2;
		Solid2->Texture.Kd=0.4;
		Solid2->Texture.Ks=0.0;
		Solid2->Texture.Kt=0.0;
		Solid2->Texture.p=3;
		Solid2->Texture.Color=Vector(0,0,10);
		Solid2->Texture.Med=Glass;
		printf("\nAdding objects to scene\n");
		Scene->AddObject(Plane); /////////////|
		Scene->AddObject(Solid);
		Scene->AddObject(Solid2);
		Scene->AddLight(Light1);
		Scene->AddLight(Light2);
		SetCamera(Vector(0,10,20),Vector(-5,-32,-35),Vector(1,1,1));
		RenderScene(160,100,320,200,"PIC01.OUT");
		unlink("PIC01.OUT");
		_setcursortype(_NORMALCURSOR);
}
