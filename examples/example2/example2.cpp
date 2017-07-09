#include "math/Vector.h"
#include "Tracer.h"
#include "Render.h"
#include "environment/Geometry.h"
#include "Colors.h"
#include "geom/Sphere.h"
#include "light/PointLight.h"
#include "environment/Scene.h"

int main()
{
    Sphere *s[16];
    PointLight  *light1;
    int i,j,k;

    Scene* scene = new Scene();

    for( i = k = 0 ; i < 4; i++ )
        for( j = 0; j < 4; j++, k++ )
        {
            s[k] = new Sphere( Vector(-3+j*2,2.15-i*1.45,5),0.7 );
            if(i > 0) s[k]->ambient(0.2);
            else s[k]->ambient(j*0.33);

            if(i < 1) s[k]->diffuse(0);
            else
            if(i == 1) s[k]->diffuse(j*0.33);
            else s[k]->diffuse(0.4);

            if(i < 2) s[k]->specular(0);
            else
            if(i == 2) s[k]->specular(j*0.33);
            else s[k]->specular(0.7);

            if(i < 3) s[k]->phong_size(10);
            else s[k]->phong_size(5+j*5);

            s[k]->transmittance(0);
            s[k]->reflection(0);
            s[k]->color(Green);
            s[k]->ior(1);
            s[k]->beta(0);

            scene->add( s[k] );
        }

    light1 = new PointLight( Vector(10,5,-10),15 );
    scene->add( light1 );

    background = SkyBlue;
    scene->setCamera(Vector(0,0,-10), Vector(0,0,1), Vector(0,1,0) );
//  RenderScene(0.3,0.2,300,200,"SAMP0010.TGA");
//  DistributedRenderScene(0.3,0.2,300,200,5,5,"SAMP0011.TGA");
    adaptive_distributed_render_scene(scene, 0.3,0.2,300,200,3,3,0.01,"SAMP0012.TGA");
}
