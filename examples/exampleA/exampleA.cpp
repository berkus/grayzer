#include <noise.h>
#include <render.h>
#include <colors.h>
#include <tracer.hpp>
#include <geometry.hpp>
#include "sphere.hpp"
#include "pointlit.hpp"
#include "environ.hpp"
#include "gloss.hpp"
#include "bozo.hpp"
#include "checker.hpp"
#include "externs.h"
#include "bumps.hpp"
#include "rect.hpp"

#include "gradient.hpp"
#include "wrinkles.hpp"
#include "dents.hpp"
#include "wood.hpp"


unsigned _stklen = 64000;

void
main()
{
//  Options = OPT_DEBUG;

    PSphere s1,s2,s3,s4;
    PPointLight Light1;
    PBozo bozo;

    InitDefaultMaterial();

    Scene = new Environment;
    s1 = new Sphere(Vector(-2.2,2.2,10),1.2); // tl
    s2 = new Sphere(Vector(2.2,2.2,10),1.2);  // tr
    s3 = new Sphere(Vector(-2.2,-2.2,10),1.2);// bl
    s4 = new Sphere(Vector(2.2,-2.2,10),1.2); // br
    PSphere s5 = new Sphere(Vector(0,0,9),1.2); // mid
    PRect r = new Rect(Vector(-5,-5,15),Vector(9,0,0),Vector(0,6,0));

    s1->Diffuse(0.6);
    s1->Specular(0.7);
    s1->PhongSize(30);
    PGradient g = new Gradient (Vector(0,1,0));
    g->Tbl.AddEntry(0,.5,Black,White);
    g->Tbl.AddEntry(.5,1,White,Black);
    s1->Add(g);

    // from palace.pov
    bozo = new Bozo (0.5);
    bozo->Tbl.AddEntry(0.0,0.5,Vector(.25,.25,.5),Vector(.25,.25,.5));
    bozo->Tbl.AddEntry(0.5,0.6,Vector(.25,.25,.5),Vector(.7,.7,.7));
    bozo->Tbl.AddEntry(0.6,1.001,Vector(.7,.7,.7),Vector(.3,.3,.3));

    s2->DefMaterial = s1->DefMaterial;
    s2->Ambient(0.6);
    s2->Diffuse(0.4);
    s2->Add(bozo);

    s3->DefMaterial = s1->DefMaterial;
    s3->PhongSize(10);
    s3->Color(Aquamarine);
    s3->Add(new Wrinkles(7.0));

    s4->DefMaterial = s1->DefMaterial;
    s4->Color(Goldenrod);
    s4->Add(new Dents(3.0));

    s5->DefMaterial = s1->DefMaterial;
    s5->Transmittance(0.7);
    s5->Color(Coral);
    s5->Add(new Gloss);

    r->Add(new Wood(15,7,5));

    Light1 = new PointLight(Vector(10,5,-30),40);

    Scene->Add(s1);
    Scene->Add(s2);
    Scene->Add(s3);
    Scene->Add(s4);
    Scene->Add(s5);
    Scene->Add(r);
    Scene->Add(Light1);
    Scene->Fog = new Fog(200,White);

    Background = Black;

    InitNoise();
    SetCamera(Vector(0),Vector(0,0,1.5),Vector(0,1,0));
//  Aperture = 5.0;
//  Focus = 12.0;
    RenderScene(1.6,1.0,320,200,"SAMPLE90.TGA");
//  DistributedRenderScene(1.6,1.0,320,200,5,5,"SAMPLE91.TGA");
//  AdaptiveDistributedRenderScene(1.6,1.0,320,200,5,5,0.01,"SAMPLE92.TGA");
    DoneNoise();
}
