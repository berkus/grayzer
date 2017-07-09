#include "Noise.h"
#include "Render.h"
#include "Colors.h"
#include "Tracer.h"
#include "environment/Geometry.h"
#include "light/PointLight.h"
#include "environment/Scene.h"
#include "Externs.h"
#include "geom/Rect.h"
// textures
#include "texture/Gloss.h"
#include "texture/Bozo.h"
#include "texture/Checker.h"
#include "texture/Bumps.h"
#include "texture/Gradient.h"
#include "texture/Wrinkles.h"
#include "texture/Dents.h"
#include "texture/Wood.h"
#include "texture/Marble.h"
#include "texture/Granite.h"
#include "texture/Ripples.h"
#include "texture/Brick.h"


int main()
{
   Rectangle *r[12];
   PointLight *Light1;

   initDefaultMaterial();
   defaultMaterial.color = Green;
   defaultMaterial.p = 30;

   Scene* scene = new Scene;

//
// screen area 22 x 13
// grid 5 x 4 w/ interval 5.5 x 4.3
//
   for( int y = 0;   y <   4; y++ )
      for( int x = 0;   x <   5; x++ )
         r[y*4+x] = new Rectangle(Vector(-11+5.5*x,6.5-4.3*y,10),Vector(5,0,0),Vector(0,-4,0));

   Wood *woo = new Wood (15,7,5);

   Marble *marb = new Marble (0.7,1);
   marb->tbl.add_entry(0.0,0.8,Vector(0.8,0.8,0.6),Vector(0.8,0.4,0.4));
   marb->tbl.add_entry(0.8,1.0,Vector(0.8,0.4,0.4),Vector(0.8,0.2,0.2));

   Granite  *granit  = new Granite;
   granit->tbl.add_entry(0.000,0.178,Vector(0.831,0.631,0.569),Vector(0.925,0.831,0.714));
   granit->tbl.add_entry(0.178,0.356,Vector(0.925,0.831,0.714),Vector(0.871,0.702,0.659));
   granit->tbl.add_entry(0.356,0.525,Vector(0.871,0.702,0.659),Vector(0.831,0.631,0.569));
   granit->tbl.add_entry(0.525,0.729,Vector(0.831,0.631,0.569),Vector(0.937,0.882,0.820));
   granit->tbl.add_entry(0.729,1.000,Vector(0.937,0.882,0.820),Vector(0.831,0.631,0.569));

   Checker  *checkr = new Checker (SkyBlue,Yellow);

   Gradient *grad = new Gradient (Vector(1,1,0));
   grad->tbl.add_entry(0,.5,Black,White);
   grad->tbl.add_entry(.5,1,White,Aquamarine);
   grad->offs = Vector(30,20,0);

   Wrinkles *wrink = new Wrinkles (7.0);

   Dents *dent = new Dents (3.0);

   Gloss *glos = new Gloss;

   // from  palace.pov
   Bozo *boz = new Bozo (0.5);
   boz->tbl.add_entry(0.0,0.5,Vector(.25,.25,.5),Vector(.25,.25,.5));
   boz->tbl.add_entry(0.5,0.6,Vector(.25,.25,.5),Vector(.7,.7,.7));
   boz->tbl.add_entry(0.6,1.001,Vector(.7,.7,.7),Vector(.3,.3,.3));

   Bumps *bump = new Bumps (7.0);

   Brick *brik = new Brick (Vector(11,6,5),Vector(0.1),Red,Gray);
   brik->scale = Vector(4);

   Ripples  *ripp = new Ripples(Vector(8.5,-4.5,10),4.0,0.4);

   // wood,marble,granite,checker
   // gradient,wrinkles,dents,gloss
   // bozo,bumps,brick,ripples
   r[0]->add(woo);
   r[1]->add(marb);
   r[2]->add(granit);
   r[3]->add(checkr);

   r[4]->specular(0.7);
   r[4]->add(grad);

   r[5]->phong_size(10);
   r[5]->color(Aquamarine);
   r[5]->add(wrink);

   r[6]->color(Goldenrod);
   r[6]->add(dent);
   r[7]->color(Coral);
   r[7]->add(glos);

   r[8]->color(Black);  // since Bozo does +=
   r[8]->ambient(0.6);
   r[8]->diffuse(0.4);
   r[8]->add(boz);
   r[9]->add(bump);
   r[10]->add(brik);
   r[11]->add(ripp);

   Light1 = new PointLight(Vector(10,5,-30),40);

   for(int i = 0; i < 12; i++)
      scene->add(r[i]);

   scene->add(Light1);
// Scene->Fog = new Fog(200,White);

   init_noise();
   scene->setCamera(Vector(0),Vector(0,0,1.5),Vector(0,1,0));
//   render_scene(1.6,1.0,320,200,"SAMPLEB0.TGA");
// distributed_render_scene(1.6,1.0,320,200,5,5,"SAMPLEB1.TGA");
   adaptive_distributed_render_scene(scene, 1.6,1.0,1280,1024,5,5,0.01,"SAMPLEB2.TGA");
   done_noise();
}
