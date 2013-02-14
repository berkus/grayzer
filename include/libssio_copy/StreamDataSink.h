#ifndef _STREAMDATASINK_H
#define _STREAMDATASINK_H

#include <fstream>
#include "DataSink.h"

namespace libssio {

   class StreamDataSink : public DataSink
   {
      private:
         std::ofstream *out;

      public:
         StreamDataSink(std::ofstream *data_stream)
         {
            out = data_stream;
         };

         virtual ~StreamDataSink() {};

         /*
          *	Write a 1-byte value.
          */
         virtual void write1(uint32_t val)
         {
            out->put(static_cast<char>(val&0xff));
         }

         /*
          *	Write a 2-byte value, lsb first.
          */
         virtual void write2(uint16_t val)
         {
            out->put(static_cast<char>(val&0xff));
            out->put(static_cast<char>((val>>8)&0xff));
         }

         /*
          *	Write a 2-byte value, msb first.
          */
         virtual void write2big(uint16_t val)
         {
            out->put(static_cast<char>((val>>8)&0xff));
            out->put(static_cast<char>(val&0xff));
         }

         /*
          *	Write a 4-byte value, lsb first.
          */
         virtual void write4(uint32_t val)
         {
            out->put(static_cast<char>(val&0xff));
            out->put(static_cast<char>((val>>8)&0xff));
            out->put(static_cast<char>((val>>16)&0xff));
            out->put(static_cast<char>((val>>24)&0xff));
         }

         /*
          *	Write a 4-byte value, msb first.
          */
         virtual void write4big(uint32_t val)
         {
            out->put(static_cast<char>((val>>24)&0xff));
            out->put(static_cast<char>((val>>16)&0xff));
            out->put(static_cast<char>((val>>8)&0xff));
            out->put(static_cast<char>(val&0xff));
         }

         virtual void write(char *b, int len) { out->write(b, len); };

         virtual void seek(unsigned int pos) { out->seekp(pos); };

         virtual void skip(int pos) { out->seekp(pos, std::ios::cur); };

         virtual unsigned int getSize()
         {
            long pos = out->tellp();
            out->seekp(0, std::ios::end);
            long len = out->tellp();
            out->seekp(pos);
            return len;
         };

         virtual unsigned int getPos() { return out->tellp(); };
   };

};

#endif /* _STREAMDATASINK_H */
