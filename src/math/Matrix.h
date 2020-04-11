// @todo Perhaps Eigen is better for this
#pragma once

#include "math/Vector.h"

class Matrix
{
public:
    double x[4][4];

    Matrix( double = 1.0 ); // Identity by default

    Matrix& operator += ( const Matrix& );
    Matrix& operator -= ( const Matrix& );
    Matrix& operator *= ( const Matrix& );
    Matrix& operator *= ( double );
    Matrix& operator /= ( double );

    void identity();
    void invert();
    void transpose();

    friend Matrix operator + ( const Matrix&, const Matrix& );
    friend Matrix operator + ( const Matrix&, double );

    friend Matrix operator - ( const Matrix&, const Matrix& );

    friend Matrix operator * ( const Matrix&, const Matrix& );
    friend Vector operator * ( const Matrix&, const Vector& );
};

Matrix translate( const Vector& );
Matrix inv_translate( const Vector& );

Matrix scale( const Vector& );
Matrix inv_scale( const Vector& );

Matrix rotate_x( double );
Matrix rotate_y( double );
Matrix rotate_z( double );
Matrix rotate( const Vector&, double );

Matrix mirror_x();
Matrix mirror_y();
Matrix mirror_z();
