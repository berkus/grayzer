//
//  File.............: render.h
//  Description......: Rendering procs protos
//
#pragma once

// Obsolete - replace with std::chrono
extern long * ticks_ptr;

#define START_TIME(x) { (x) = *ticks_ptr; }
#define STOP_TIME(x)  { (x) -= *ticks_ptr; if((x) < 0L) (x) = -(x); }
// end Obsolete - replace with std::chrono

void render_scene(double,double,int,int,char const*);
void distributed_render_scene(double,double,int,int,int,int,char const*);
void adaptive_distributed_render_scene(double,double,int,int,int,int,double,char const*);
