#include "Noise.h"
#include "Render.h"
#include "Colors.h"
#include "Tracer.h"
#include "texture/Marble.h"
#include "texture/Granite.h"
#include "environment/Scene.h"
#include "light/PointLight.h"
#include "geom/Sphere.h"

int main()
{
    Sphere *s1,*s2,*s3,*s4;
    PointLight *Light1;

    initDefaultMaterial();

    Marble *m1=new Marble(.7,1);
    Marble *m2=new Marble(.1,1);
    Granite *g1=new Granite;
    Granite *g2=new Granite;
    Scene* scene = new Scene;
    s1 = new Sphere(Vector(-2.2,2.2,10),2);
    s2 = new Sphere(Vector(2.2,2.2,10),2);
    s3 = new Sphere(Vector(-2.2,-2.2,10),2);
    s4 = new Sphere(Vector(2.2,-2.2,10),2);
    /*
        color_map {
            [0 .8 color Gray90 color Gray50]
            [.8 1 color Gray50 color Gray20]
        }
    */
    m1->tbl.add_entry(0.0,0.8,Vector(0.9),Vector(0.5));
    m1->tbl.add_entry(0.8,1.0,Vector(0.5),Vector(0.2));

    m2->tbl.add_entry(0.0,0.8,Vector(0.8,0.8,0.6),Vector(0.8,0.4,0.4));
    m2->tbl.add_entry(0.8,1.0,Vector(0.8,0.4,0.4),Vector(0.8,0.2,0.2));

    g1->tbl.add_entry(0.000,0.178,Vector(0.831,0.631,0.569),Vector(0.925,0.831,0.714));
    g1->tbl.add_entry(0.178,0.356,Vector(0.925,0.831,0.714),Vector(0.871,0.702,0.659));
    g1->tbl.add_entry(0.356,0.525,Vector(0.871,0.702,0.659),Vector(0.831,0.631,0.569));
    g1->tbl.add_entry(0.525,0.729,Vector(0.831,0.631,0.569),Vector(0.937,0.882,0.820));
    g1->tbl.add_entry(0.729,1.000,Vector(0.937,0.882,0.820),Vector(0.831,0.631,0.569));

    g2->tbl.add_entry(0.000,0.241,Vector(0.973,0.973,0.976),Vector(0.973,0.973,0.976));
    g2->tbl.add_entry(0.241,0.284,Vector(0.973,0.973,0.976),Vector(0.600,0.741,0.608));
    g2->tbl.add_entry(0.284,0.336,Vector(0.600,0.741,0.608),Vector(0.820,0.643,0.537));
    g2->tbl.add_entry(0.336,0.474,Vector(0.820,0.643,0.537),Vector(0.886,0.780,0.714));
    g2->tbl.add_entry(0.474,0.810,Vector(0.886,0.780,0.714),Vector(0.996,0.643,0.537));
    g2->tbl.add_entry(0.810,0.836,Vector(0.996,0.643,0.537),Vector(0.973,0.973,0.976));
    g2->tbl.add_entry(0.836,1.000,Vector(0.973,0.973,0.976),Vector(0.973,0.973,0.976));

    s1->diffuse(0.6);
    s1->specular(0.7);
    s1->reflection(0.0);
    s1->phong_size(30);
    s1->color(Yellow);
    s1->add(m1);

    s2->surface_data(s1->surface_data());
    s2->add(m2);

    s3->surface_data(s1->surface_data());
    s3->add(g1);

    s4->surface_data(s1->surface_data());
    s4->add(g2);

    Light1 = new PointLight(Vector(10,5,-10),17);

    scene->add(s1);
    scene->add(s2);
    scene->add(s3);
    scene->add(s4);
    scene->add(Light1);

    scene->setBackground(SkyBlue);

    init_noise();
    scene->setCamera(Vector(0),Vector(0,0,2),Vector(0,1,0));
    render_scene(scene, 1.6,1.2,320,240,"SAMPLE70.TGA");
    distributed_render_scene(scene, 1.6,1.0,320,200,5,5,"SAMPLE71.TGA");
    adaptive_distributed_render_scene(scene, 1.6,1.2,320,240,5,5,0.1,"SAMPLE72.TGA");
    done_noise();
}
