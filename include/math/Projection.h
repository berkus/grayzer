#pragma once

#include "Matrix.h"

class Projection
{
   public:
      // - параллельные проекции
      // ортографические проекции
      static Matrix ortho_x(double dist);
      static Matrix ortho_y(double dist);
      static Matrix ortho_z(double dist);

      // аксонометрические проекции: три-, ди- и изометрические
      static Matrix axonometric(double angle_x,double angle_y,double angle_z);

      // косоугольные проекции
      static Matrix free_x();
      static Matrix free_y();
      static Matrix free_z();
      static Matrix cabinet_x();
      static Matrix cabinet_y();
      static Matrix cabinet_z();

      // - перспективные проекции: одно-, двух- и трехточечные
      static Matrix perspective(double dist_x, double dist_y, double dist_z);
};
