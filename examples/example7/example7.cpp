#include "noise.h"
#include "render.h"
#include "colors.h"
#include "tracer.hpp"
#include "marble.hpp"
#include "granite.hpp"
#include "environ.hpp"
#include "pointlit.hpp"
#include "sphere.hpp"

void
main()
{
    PSphere s1,s2,s3,s4;
    PPointLight Light1;

    InitDefaultMaterial();

    PMarble m1=new Marble(.7,1);
    PMarble m2=new Marble(.1,1);
    PGranite g1=new Granite;
    PGranite g2=new Granite;
    Scene = new Environment;
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
    m1->Tbl.AddEntry(0.0,0.8,Vector(0.9),Vector(0.5));
    m1->Tbl.AddEntry(0.8,1.0,Vector(0.5),Vector(0.2));

    m2->Tbl.AddEntry(0.0,0.8,Vector(0.8,0.8,0.6),Vector(0.8,0.4,0.4));
    m2->Tbl.AddEntry(0.8,1.0,Vector(0.8,0.4,0.4),Vector(0.8,0.2,0.2));

    g1->Tbl.AddEntry(0.000,0.178,Vector(0.831,0.631,0.569),Vector(0.925,0.831,0.714));
    g1->Tbl.AddEntry(0.178,0.356,Vector(0.925,0.831,0.714),Vector(0.871,0.702,0.659));
    g1->Tbl.AddEntry(0.356,0.525,Vector(0.871,0.702,0.659),Vector(0.831,0.631,0.569));
    g1->Tbl.AddEntry(0.525,0.729,Vector(0.831,0.631,0.569),Vector(0.937,0.882,0.820));
    g1->Tbl.AddEntry(0.729,1.000,Vector(0.937,0.882,0.820),Vector(0.831,0.631,0.569));

    g2->Tbl.AddEntry(0.000,0.241,Vector(0.973,0.973,0.976),Vector(0.973,0.973,0.976));
    g2->Tbl.AddEntry(0.241,0.284,Vector(0.973,0.973,0.976),Vector(0.600,0.741,0.608));
    g2->Tbl.AddEntry(0.284,0.336,Vector(0.600,0.741,0.608),Vector(0.820,0.643,0.537));
    g2->Tbl.AddEntry(0.336,0.474,Vector(0.820,0.643,0.537),Vector(0.886,0.780,0.714));
    g2->Tbl.AddEntry(0.474,0.810,Vector(0.886,0.780,0.714),Vector(0.996,0.643,0.537));
    g2->Tbl.AddEntry(0.810,0.836,Vector(0.996,0.643,0.537),Vector(0.973,0.973,0.976));
    g2->Tbl.AddEntry(0.836,1.000,Vector(0.973,0.973,0.976),Vector(0.973,0.973,0.976));

    s1->Diffuse(0.6);
    s1->Specular(0.7);
    s1->Reflection(0.0);
    s1->PhongSize(30);
    s1->DefMaterial.Color=Yellow;
    s1->Add(m1);

    s2->DefMaterial = s1->DefMaterial;
    s2->Add(m2);

    s3->DefMaterial = s1->DefMaterial;
    s3->Add(g1);

    s4->DefMaterial = s1->DefMaterial;
    s4->Add(g2);

    Light1 = new PointLight(Vector(10,5,-10),17);

    Scene->Add(s1);
    Scene->Add(s2);
    Scene->Add(s3);
    Scene->Add(s4);
    Scene->Add(Light1);

    Background = SkyBlue;

    InitNoise();
    SetCamera(Vector(0),Vector(0,0,2),Vector(0,1,0));
    RenderScene(1.6,1.2,320,240,"SAMP0060.TGA");
//  DistributedRenderScene(1.6,1.0,320,200,5,5,"SAMPLE61.TGA");
//  AdaptiveDistributedRenderScene(1.6,1.2,320,240,5,5,0.1,"SAMP0062.TGA");
    DoneNoise();
}
