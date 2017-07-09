#include "Noise.h"
#include "Render.h"
#include "Colors.h"
#include "Tracer.h"
#include "geom/Sphere.h"
#include "light/PointLight.h"
#include "environment/Scene.h"
#include "Externs.h"
#include "geom/Rect.h"
#include "texture/Bumps.h"
#include "texture/Gloss.h"
#include "texture/Bozo.h"
#include "texture/Checker.h"
#include "texture/Gradient.h"
#include "texture/Wrinkles.h"
#include "texture/Dents.h"
#include "texture/Wood.h"

int main()
{
    initDefaultMaterial();

    Scene* scene = new Scene;
    Sphere *s1 = new Sphere(Vector(-2.2,2.2,10),1.2); // tl
    Sphere *s2 = new Sphere(Vector(2.2,2.2,10),1.2);  // tr
    Sphere *s3 = new Sphere(Vector(-2.2,-2.2,10),1.2);// bl
    Sphere *s4 = new Sphere(Vector(2.2,-2.2,10),1.2); // br
    Sphere *s5 = new Sphere(Vector(0,0,9),1.2); // mid
    Rectangle* r = new Rectangle(Vector(-5,-5,15),Vector(9,0,0),Vector(0,6,0));

    s1->diffuse(0.6);
    s1->specular(0.7);
    s1->phong_size(30);
    Gradient* g = new Gradient (Vector(0,1,0));
    g->tbl.add_entry(0,.5,Black,White);
    g->tbl.add_entry(.5,1,White,Black);
    s1->add(g);

    // from palace.pov
    Bozo *bozo = new Bozo (0.5);
    bozo->tbl.add_entry(0.0,0.5,Vector(.25,.25,.5),Vector(.25,.25,.5));
    bozo->tbl.add_entry(0.5,0.6,Vector(.25,.25,.5),Vector(.7,.7,.7));
    bozo->tbl.add_entry(0.6,1.001,Vector(.7,.7,.7),Vector(.3,.3,.3));

    s2->surface_data(s1->surface_data());
    s2->ambient(0.6);
    s2->diffuse(0.4);
    s2->add(bozo);

    s3->surface_data(s1->surface_data());
    s3->phong_size(10);
    s3->color(Aquamarine);
    s3->add(new Wrinkles(7.0));

    s4->surface_data(s1->surface_data());
    s4->color(Goldenrod);
    s4->add(new Dents(3.0));

    s5->surface_data(s1->surface_data());
    s5->transmittance(0.7);
    s5->color(Coral);
    s5->add(new Gloss);

    r->add(new Wood(15,7,5));

    PointLight *Light1 = new PointLight(Vector(10,5,-30),40);

    scene->add(s1);
    scene->add(s2);
    scene->add(s3);
    scene->add(s4);
    scene->add(s5);
    scene->add(r);
    scene->add(Light1);

    scene->setFog(std::make_shared<Fog>(200,White));
    scene->setBackground(Black);

    init_noise();
    scene->setCamera(Vector(0),Vector(0,0,1.5),Vector(0,1,0));
//  Aperture = 5.0;
//  Focus = 12.0;
    render_scene(scene, 1.6,1.0,320,200,"SAMPLEA0.TGA");
    distributed_render_scene(scene, 1.6,1.0,320,200,5,5,"SAMPLEA1.TGA");
    adaptive_distributed_render_scene(scene, 1.6,1.0,320,200,5,5,0.01,"SAMPLEA2.TGA");
    done_noise();
}
