//
//  @brief geometric object Box
//
#include "Externs.h"
#include "environment/Geometry.h"
#include "geom/Box.h"


box::box( Vector& l, Vector& s1, Vector& s2, Vector& s3	)
: loc( l )
, e1( s1 )
, e2( s2 )
, e3( s3 )
{
	center = loc + (e1 + e2	+ e3) *	0.5;

	init_normals();
}

box::box( Vector& l, double	a, double b, double	c )
: loc( l )
, e1( Vector(a,0,0)	)
, e2( Vector(0,b,0)	)
, e3( Vector(0,0,c)	)
{
	center = loc + (e1 + e2	+ e3) *	0.5;

	init_normals();
}


void box::init_normals()
{
	int	i;

	n  [0] = normalize(	e1 ^ e2	);
	d1 [0] = -(	n[0] & loc );
	d2 [0] = -(	n[0] & (loc	+ e3) );

	n  [1] = normalize(	e1 ^ e3	);
	d1 [1] = -(	n[1] & loc );
	d2 [1] = -(	n[1] & (loc	+ e2) );

	n  [2] = normalize(	e2 ^ e3	);
	d1 [2] = -(	n[2] & loc );
	d2 [2] = -(	n[2] & (loc	+ e1) );

	for( i = 0;	i <	3; i++ )
		if(	d1[i] >	d2[i] )
		{
			d1[i] =	-d1[i];
			d2[i] =	-d2[i];
			n[i]  =	-n[i];
		}
}


bool box::intersect( ray& r, double& t )
{
#ifdef STATISTICS
	BoxTestCount++;
	BoxTestMisses++;
#endif

	double tNear = -INFINITY;
	double tFar	 = INFINITY;
	double t1,t2;
	double vd,vo;
	int	i;

	for( i = 0;	i <	3; i++ )
	{
		vd = r.dir & n[i];
		vo = r.org & n[i];

		if(	vd > EPS )
		{
			t1 = -(vo +	d2[i]) / vd;
			t2 = -(vo +	d1[i]) / vd;
		}
		else
		if(vd <	-EPS)
		{
			t1 = -(vo +	d1[i]) / vd;
			t2 = -(vo +	d2[i]) / vd;
		}
		else //	ray	is parallel	to slab
		{
			if(	vo < d1[i] || vo > d2[i] )
			{
#ifdef STATISTICS
				BoxTestMisses++;
#endif
				return false;
			}
			else
				continue;
		}
		if(	t1 > tNear )
			tNear =	t1;
		if(	t2 < tFar )
			if(	(tFar =	t2)	< geom_threshold )
			{
#ifdef STATISTICS
				BoxTestMisses++;
#endif
				return false;
			}
		if(	tNear >	tFar )
		{
#ifdef STATISTICS
			BoxTestMisses++;
#endif
			return false;
		}
	}
	t =	tNear;
#ifdef STATISTICS
	if(	t >	geom_threshold )
		return true;
	else
	{
		BoxTestMisses++;
		return false;
	}
#else
	return t > geom_threshold;
#endif
}

Vector box::find_normal( Vector& p )
{
	double MinDist = INFINITY;
	int	index =	0;
	double d,Dist1,Dist2;
	Vector normal;
	int	i;

	for( i = 0;	i <	3; i++ )
	{
		d =	p &	n[i];
		Dist1 =	fabs(d + d1[i]);
		Dist2 =	fabs(d + d2[i]);

		if(	Dist1 <	MinDist	)
		{
			MinDist	= Dist1;
			index =	i;
		}
		if(	Dist2 <	MinDist	)
		{
			MinDist	= Dist2;
			index =	i;
		}
	}
	normal = n[index];
	if(	((p	- center) &	normal)	< 0.0 )
		normal = -normal;

	return normal;
}
