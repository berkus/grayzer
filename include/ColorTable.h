//
//  @brief Interpolated Color Table
//
#pragma once

#include "math/Vector.h"

class ColorTable
{
        class Entry
        {
            public:
                double ta,tb;
                Vector ca,cb;
        };

    public:
        ColorTable( int = 10 );
       ~ColorTable() { delete entries; }

        void add_entry( double, double, const Vector&, const Vector& );
        Vector find_color( double );

        bool is_empty() const { return !color_entries; }

    private:
        int color_entries;
        int max_entries;
        Entry *entries;
};
