#pragma once

#include <fstream>
#include "DataSource.h"

namespace libssio {

   class StreamDataSource : public DataSource
   {
      private:
         std::ifstream *in;

      public:
         StreamDataSource(std::ifstream *data_stream)
         {
            in = data_stream;
         };

         virtual ~StreamDataSource() {};

         /*
          *	Read a 1-byte value.
          */
         virtual uint32_t read1()
         {
            return static_cast<uint32_t>(in->get());
         }

         /*
          *	Read a 2-byte value, lsb first.
          */
         virtual uint16_t read2()
         {
            uint16_t val = 0;
            val |= static_cast<uint16_t>(in->get());
            val |= static_cast<uint16_t>(in->get()<<8);
            return val;
         }

         /*
          *	Read a 2-byte value, msb first.
          */
         virtual uint16_t read2big()
         {
            uint16_t val = 0;
            val |= static_cast<uint16_t>(in->get()<<8);
            val |= static_cast<uint16_t>(in->get());
            return val;
         }

         /*
          *	Read a 4-byte long value, lsb first.
          */
         virtual uint32_t read4()
         {
            uint32_t val = 0;
            val |= static_cast<uint32_t>(in->get());
            val |= static_cast<uint32_t>(in->get()<<8);
            val |= static_cast<uint32_t>(in->get()<<16);
            val |= static_cast<uint32_t>(in->get()<<24);
            return val;
         }

         /*
          *	Read a 4-byte long value, msb first.
          */
         virtual uint32_t read4big()
         {
            uint32_t val = 0;
            val |= static_cast<uint32_t>(in->get()<<24);
            val |= static_cast<uint32_t>(in->get()<<16);
            val |= static_cast<uint32_t>(in->get()<<8);
            val |= static_cast<uint32_t>(in->get());
            return val;
         }

         /*
          * Read buffer of arbitrary length.
          */
         void read(char *b, uint32_t len) { in->read(b, len); };

         virtual void seek(unsigned int pos) { in->seekg(pos); };

         virtual void skip(int pos) { in->seekg(pos, std::ios::cur); };

         virtual unsigned int getSize()
         {
            long pos = in->tellg();
            in->seekg(0, std::ios::end);
            long len = in->tellg();
            in->seekg(pos);
            return len;
         };

         virtual unsigned int getPos() { return in->tellg(); };
   };

} // libssio namespace
