#include "Tracer.h"
#include "Render.h"
#include "Colors.h"
#include "texture/Wood.h"
#include "geom/Box.h"
#include "light/PointLight.h"
#include "environment/Scene.h"

int main()
{
    Scene* scene = new Scene;

    Box* b=new Box(Vector(-1,-1,-2),Vector(2,0,0),Vector(0,2,0),Vector(0,0,4));
    b->ambient(0.3);
    b->diffuse(0.7);
    b->specular(0.5);
    b->reflection(0.0);
    b->transmittance(0.0);
    b->phong_size(30);
    b->color(Yellow);
    b->medium(Grayzer::Medium::glass);
    b->add(new Wood(35,6,5));

    PointLight* Light1 = new PointLight(Vector(10,5,-10),17);
    PointLight* Light2 = new PointLight(Vector(-10,-5,-10),17);

    scene->add(b);
    scene->add(Light1);
    scene->add(Light2);
    scene->setBackground(SkyBlue);

    init_noise();
    scene->setCamera(Vector(-4,8,-4),Vector(2,-5,2),Vector(0,1,0));
    render_scene(scene, 1.6,1.0,320,200,"SAMPLE60.TGA");
    done_noise();
}
