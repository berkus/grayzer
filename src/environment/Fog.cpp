//
//  @brief Fog realization
//
#include "environment/Scene.h"

void Fog::shade( Vector& color, double dist )
{
    double fog_factor, fog_factor_inv;

    fog_factor     = exp(-1.0 * dist / distance);
    fog_factor_inv = 1.0 - fog_factor;

    fog_color = fog_color * fog_factor + color * fog_factor_inv;
}
