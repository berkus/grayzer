#include "vector.hpp"
#include "tracer.hpp"
#include "render.h"
#include "geometry.hpp"
#include "colors.h"
#include "sphere.hpp"
#include "pointlit.hpp"
#include "environ.hpp"

void main()
{
	sphere *s[16];
	point_light	*light1;
	int	i,j,k;

	scene =	new	environment();

	for( i = k = 0 ; i < 4;	i++	)
		for( j = 0;	j <	4; j++,	k++	)
		{
			s[k] = new sphere( vector(-3+j*2,2.15-i*1.45,5),0.7	);
			if(i > 0) s[k]->def_material.ka	= 0.2;
			else s[k]->def_material.ka = j*0.33;

			if(i < 1) s[k]->def_material.kd	= 0;
			else
			if(i ==	1) s[k]->def_material.kd = j*0.33;
			else s[k]->def_material.kd = 0.4;

			if(i < 2) s[k]->DefMaterial.Ks = 0;
			else
			if(i ==	2) s[k]->DefMaterial.Ks	= j*0.33;
			else s[k]->DefMaterial.Ks =	0.7;

			if(i < 3) s[k]->DefMaterial.p =	10;
			else s[k]->DefMaterial.p = 5+j*5;

			s[k]->DefMaterial.kt = 0;
			s[k]->DefMaterial.kr = 0;
			s[k]->DefMaterial.color	= Green;
			s[k]->DefMaterial.med.ior =	1;
			s[k]->DefMaterial.med.beta = 0;

			scene->add(	s[k] );
		}

	light1 = new point_light( vector(10,5,-10),15 );
	scene->add(	light1 );

	background = SkyBlue;
	set_camera(	vector(0,0,-10), vector(0,0,1),	vector(0,1,0) );
//	RenderScene(0.3,0.2,300,200,"SAMP0010.TGA");
//	DistributedRenderScene(0.3,0.2,300,200,5,5,"SAMP0011.TGA");
	adaptive_distributed_render_scene(0.3,0.2,300,200,3,3,0.01,"SAMP0012.TGA");
}
