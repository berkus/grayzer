//═══════════════════════════════════════════════════════════════════════════
// class Projection
//═══════════════════════════════════════════════════════════════════════════

#include "math/Projection.h"

//───────────────────────────────────────────────────────────────────────────
// ортографическое проецирование вдоль оси OX на плоскость YZ
Matrix Projection::ortho_x(double dist)
{
   Matrix out(1); // create identity

   out.x[0][0] = 0;
   out.x[3][0] = dist;

   return out;
}

//───────────────────────────────────────────────────────────────────────────
// ортографическое проецирование вдоль оси OY на плоскость XZ
Matrix Projection::ortho_y(double dist)
{
   Matrix out(1); // create identity

   out.x[1][1] = 0;
   out.x[3][1] = dist;

   return out;
}

//───────────────────────────────────────────────────────────────────────────
// ортографическое проецирование вдоль оси OZ на плоскость XY
Matrix Projection::ortho_z(double dist)
{
   Matrix out(1); // create identity

   out.x[2][2] = 0;
   out.x[3][2] = dist;

   return out;
}

//───────────────────────────────────────────────────────────────────────────
Matrix Projection::axonometric(double angle_x,double angle_y,double angle_z)
{
   Matrix out(1); // create identity
   // THINK!
   return out;
}

//───────────────────────────────────────────────────────────────────────────
// косоугольная свободная проекция вдоль оси OX
Matrix Projection::free_x()
{
   Matrix out(1); // create identity
   return out;
}

//───────────────────────────────────────────────────────────────────────────
// косоугольная свободная проекция
Matrix Projection::free_y()
{
   Matrix out(1); // create identity
   return out;
}

//───────────────────────────────────────────────────────────────────────────
// косоугольная свободная проекция
Matrix Projection::free_z()
{
   Matrix out(1); // create identity
   return out;
}

//───────────────────────────────────────────────────────────────────────────
// косоугольная кабинетная проекция вдоль оси OX
Matrix Projection::cabinet_x()
{
   Matrix out(1); // create identity
   return out;
}

//───────────────────────────────────────────────────────────────────────────
// косоугольная кабинетная проекция вдоль оси OY
Matrix Projection::cabinet_y()
{
   Matrix out(1); // create identity
   return out;
}

//───────────────────────────────────────────────────────────────────────────
// косоугольная кабинетная проекция вдоль оси OZ
Matrix Projection::cabinet_z()
{
   Matrix out(1); // create identity
   return out;
}

//───────────────────────────────────────────────────────────────────────────
Matrix Projection::perspective(double dist_x, double dist_y, double dist_z)
{
   Matrix out(1); // create identity
   return out;
}
