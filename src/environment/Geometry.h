//
//  File.............: geometry.hpp
//  Description......: Some common geometric #defines
//
#pragma once

//
//  epsilon (object threshold)
//
#define EPS 0.01

#define GEOM_INFINITY 30000
#undef INFINITY // catch

/*
    min. ray length accounted for
    if ray length is less than this value => NO INTERSECTION
*/
extern double geom_threshold;
