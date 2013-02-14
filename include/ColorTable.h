//
//  @brief Interpolated Color Table
//
#ifndef _COLORTBL_
#define _COLORTBL_

#include "math/Vector.h"


class color_table_entry
{
    public:
        double ta,tb;
        Vector ca,cb;
};


class color_table
{
    public:
        color_table( int = 10 );
       ~color_table() { delete entries; }

        void add_entry( double, double, const Vector&, const Vector& );
        Vector find_color( double );

        bool is_empty() const { return !color_entries; }

    private:
        int color_entries;
        int max_entries;
        color_table_entry *entries;
};


#endif // _COLORTBL_
