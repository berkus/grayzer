//
//  Description......: Rendering procs protos
//
#pragma once

class Scene;

void render_scene(Scene*,double,double,int,int,char const*);
void distributed_render_scene(Scene*,double,double,int,int,int,int,char const*);
void adaptive_distributed_render_scene(Scene*,double,double,int,int,int,int,double,char const*);
