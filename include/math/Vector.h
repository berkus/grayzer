#pragma once

#include <math.h>
#include <stdlib.h>

class Vector
{
    public:
        double x, y, z;

        Vector() {};
        Vector(double v) { x = y = z = v; };
        Vector(const Vector& v) { x = v.x;y = v.y;z = v.z; };
        Vector(double vx,double vy,double vz) { x = vx;y = vy;z = vz; };
        Vector& operator = (const Vector& v) { x = v.x;y = v.y; z = v.z; return *this; };
        Vector& operator = (double v) { x=y=z=v; return *this; };
        Vector operator - () const;
        Vector& operator += (const Vector&);
        Vector& operator -= (const Vector&);
        Vector& operator *= (const Vector&);
        Vector& operator *= (double);
        Vector& operator /= (double);

        friend Vector operator + ( const Vector&, const Vector& );
        friend Vector operator - ( const Vector&, const Vector& );
        friend Vector operator * ( const Vector&, const Vector& );
        friend Vector operator * ( double, const Vector& );
        friend Vector operator * ( const Vector&, double ); // $???$
        friend Vector operator / ( const Vector&, double );
        friend Vector operator / ( const Vector&, const Vector& );
        //
        //  Dot product -- gives scalar angle between Vectors
        //
        friend double operator & ( const Vector& u,const Vector& v )
        {
            return u.x*v.x + u.y*v.y + u.z*v.z;
        }
        //
        //  Cross product
        //
        friend Vector operator ^ ( const Vector& u,const Vector& v )
        {
            return Vector (u.y*v.z - u.z*v.y,u.z*v.x - u.x*v.z,u.x*v.y - u.y*v.x);
        }
        // length
        double operator ! () { return (double)sqrt(x*x+y*y+z*z); }
        // component
        double& operator [](int n) { return(*(&x+n)); };
        // comparison
        int operator < (double v) { return x < v && y < v && z < v; };
        int operator > (double v) { return x > v && y > v && z > v; };
//        int operator < (const Vector&); $$

        static Vector rnd_vector();
};

/*inline int Vector::operator < (const Vector& v)
{
    return x < v.x &&
           y < v.y &&
           z < v.z;
}*/

inline Vector Vector::operator - () const
{
    return Vector ( -x,-y,-z );
}

inline Vector operator + ( const Vector& u, const Vector& v )
{
    return Vector ( u.x + v.x, u.y + v.y, u.z + v.z );
}

inline Vector operator - ( const Vector& u, const Vector& v )
{
    return Vector ( u.x - v.x, u.y - v.y, u.z - v.z);
}

inline Vector operator * ( const Vector& u, const Vector& v )
{
    return Vector ( u.x * v.x, u.y * v.y, u.z * v.z );
}

inline Vector operator * ( const Vector& u, double f )
{
    return Vector ( u.x * f, u.y * f, u.z * f );
}

inline Vector operator * ( double f, const Vector& v )
{
    return Vector ( v.x * f, v.y * f, v.z * f );
}

inline Vector operator / ( const Vector& u, const Vector& v )
{
    return Vector ( u.x / v.x, u.y / v.y, u.z / v.z );
}

inline Vector operator / ( const Vector& v, double f )
{
    return Vector ( v.x / f, v.y / f, v.z / f );
}

inline Vector& Vector::operator += (const Vector& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

inline Vector& Vector::operator -= (const Vector& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

inline Vector& Vector::operator *= (double v)
{
    x *= v;
    y *= v;
    z *= v;
    return *this;
}

inline Vector& Vector::operator *= (const Vector& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

inline Vector& Vector::operator /= (double v)
{
    x /= v;
    y /= v;
    z /= v;
    return *this;
}

//
//  Funcs
//
inline Vector normalize( Vector v )
{
    return v / !v;
}

//
//  Halfway between two Vectors
//
inline Vector halfway( Vector u, Vector v )
{
    return (u + v) * 0.5;
}

//
//  Random Vector
//
inline Vector Vector::rnd_vector()
{
    Vector v (rand()-0.5*RAND_MAX,rand()-0.5*RAND_MAX,rand()-0.5*RAND_MAX);
    return normalize(v);
}

inline Vector clip(Vector v)
{
    if(v.x < 0.0) v.x = 0.0;
    else
    if(v.x > 1.0) v.x = 1.0;

    if(v.y < 0.0) v.y = 0.0;
    else
    if(v.y > 1.0) v.y = 1.0;

    if(v.z < 0.0) v.z = 0.0;
    else
    if(v.z > 1.0) v.z = 1.0;

    return v;
}

// A handy type substitution.
typedef Vector Color;
