//
//  File.............: render.h
//  Description......: Rendering procs protos
//
#ifndef _RENDER_
#define _RENDER_


extern long * ticks_ptr;


#define START_TIME(x) { (x) = *ticks_ptr; }
#define STOP_TIME(x)  { (x) -= *ticks_ptr; if((x) < 0L) (x) = -(x); }


void render_scene(double,double,int,int,char *);
void distributed_render_scene(double,double,int,int,int,int,char *);
void adaptive_distributed_render_scene(double,double,int,int,int,int,double,char *);


#endif
