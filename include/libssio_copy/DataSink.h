#pragma once

#include "DataTypes.h"

namespace libssio {

   class DataSink
   {
      public:
         DataSink() {};
         virtual ~DataSink() {};

         virtual void write01(uint32_t)   =0; // write one bit
         virtual void write04(uint32_t)   =0; // write four bits
         virtual void write1(uint32_t)    =0; // write byte
         virtual void write2(uint16_t)    =0; // write two bytes
         virtual void write2big(uint16_t) =0; // bigendian
         virtual void write4(uint32_t)    =0; // write four bytes
         virtual void write4big(uint32_t) =0; // bigendian
         virtual void writecstr(char *str)
         {
            while (*str++)
               write1(*str);
            write1(0);
         }
         virtual void writepstr(char *str, int len)
         {
            len = len <? 255; // no more 255 bytes
            write1(len);
            write(str, len);
         }
         virtual void write(char *, int)  =0;

         virtual void seek(position)      =0;
         virtual void skip(offset)        =0;
         virtual size getSize()           =0;
         virtual position getPos()        =0;
   };

} // libssio namespace
