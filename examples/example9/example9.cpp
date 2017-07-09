#include "Tracer.h"
#include "Render.h"
#include "Colors.h"
#include "map/Map.h"
#include "image/BMP.h"
#include "map/PlaneMap.h"
#include "geom/Box.h"
#include "environment/Scene.h"
#include "light/PointLight.h"
#include "texture/ColorMap.h"

int main()
{
    Box *b = new Box(Vector(0,-2,5),Vector(8,0,3),Vector(-8,0,3),Vector(0,-3,0));
//  Sphere *s = new Sphere(Vector(0,0,5),50);
    LightSource *Light1 = new PointLight(Vector(7,10,-10),20);
    BmpImage *img = new BmpImage("backgnd.bmp");
    ColorMap *cmap = new ColorMap(img);

    cmap->scale = 25;

    Scene* scene = new Scene;

    b->mapping = new PlaneMap(Vector(0,-1,-1),Vector(1,0,0));
    b->add(cmap);
    b->ambient(0.3);
    b->diffuse(0.8);
    b->specular(0.3);
    b->reflection(0.0);
    b->ior(0.0);
    b->phong_size(5);
    b->medium(Grayzer::Medium::glass);
    b->color(1);

    scene->add(b);
    scene->add(Light1);

    scene->setBackground(SkyBlue);
    scene->setCamera(Vector(0),Vector(0,0,1),Vector(0,1,0));
    render_scene(scene, 1.6,1.0,320,200,"SAMPLE90.TGA");
}
