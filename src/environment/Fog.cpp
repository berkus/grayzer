//
//  @brief Fog realization
//
#include "environment/Environment.h"


void fog::shade( Vector& Color,	double dist )
{
	double fog_factor, fog_factor_inv;

	fog_factor	   = exp(-1.0 *	dist / distance);
	fog_factor_inv = 1.0 - fog_factor;

	fog_color = fog_color *	fog_factor + Color * fog_factor_inv;
}
