//
//  File.........: transfrm.hpp
//  Description..: class transformation
//
#ifndef _TRANSFRM_
#define _TRANSFRM_


#ifndef _MATRIX_
#include "math/Matrix.h"
#endif


class transformation
{
    public:
        matrix m;   // direct transform
        matrix inv; // inverse transform

        transformation() : m(1), inv(1) {}
        //
        //  MTransformVector(result,trans,vector)
        //
        friend vector operator * ( const transformation&, const vector& );
        //
        //  MInverseTransformVector
        //
        friend vector operator / ( const transformation&, const vector& );
        // MTransVector??,MInvTransVector??,MTransNormal??

        //
        //  Compose two transformations into one
        //
        transformation& operator *= ( const transformation& );
        friend transformation operator * ( const transformation&,
                                           const transformation& );
};


// clashes with `matrix scale( const vector& )'
transformation t_scale( const vector& );
transformation t_translate( const vector& );
transformation t_rotate( const vector& );
//transformation tinversion();


#endif // _TRANSFRM_ //
