#ifndef _DATASOURCE_H
#define _DATASOURCE_H

#include "DataTypes.h"

namespace libssio {

   class DataSource
   {
      public:
         /* Basic Data Source doesn't provide functions for opening,
          * you should provide them in concrete subclasses.
          */
         DataSource() {};
         virtual ~DataSource() {};

         virtual uint32_t read01()       =0; // read 1 bit (got better names?)
         virtual uint32_t read04()       =0; // read 4 bits
         virtual uint32_t read1()        =0; // read byte as int
         virtual uint16_t read2()        =0; // read two bytes
         virtual uint16_t read2big()     =0; // bigendian
         virtual uint32_t read4()        =0; // read four bytes
         virtual uint32_t read4big()     =0; // bigendian
         virtual char *   readcstr()         // read C (0-terminated) string
         {                                   // virtual to allow optimization
            position pos = getPos();
            size     len = 0;

            while ((read1() != '\0') && (getPos() < getSize()))
               len++;
            len++; // count for \0 too

            seek(pos);
            char *str = new char [len];
            read(str, len);

            return str;
         }

         virtual char *   readpstr()         // read Pascal (w/ leading count byte) string
         {
            uint32_t size = read1();
            char *str = new char [size+1];
            read(str, size);
            str[size] = '\0';
            return str;
         }

         virtual void read(char *, uint32_t)  =0;

         virtual void seek(position)       =0;
         DataSource &operator [](position pos)
         {
            seek(pos);
            return *this;
         }
         virtual void skip(offset)         =0;
         virtual size getSize()            =0;
         virtual position getPos()         =0;
   };

};

#endif /* _DATASOURCE_H */
