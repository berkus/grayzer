#pragma once

#include "math/Matrix.h"

class Transformation
{
public:
    Matrix m;   // direct transform
    Matrix inv; // inverse transform

    Transformation() : m(1), inv(1) {}
    //
    //  MTransformVector(result,trans,vector)
    //
    friend Vector operator * (Transformation const&, Vector const&);
    //
    //  MInverseTransformVector
    //
    friend Vector operator / (Transformation const&, Vector const&);
    // MTransVector??,MInvTransVector??,MTransNormal??

    //
    //  Compose two transformations into one
    //
    Transformation& operator *= (Transformation const&);
    friend Transformation operator * (Transformation const&,
                                      Transformation const&);
};

// clashes with `matrix scale( const vector& )'
Transformation t_scale(Vector const&);
Transformation t_translate(Vector const&);
Transformation t_rotate(Vector const&);
//Transformation t_inversion();
