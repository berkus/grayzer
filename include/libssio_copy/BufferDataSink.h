#pragma once

#include <assert.h>
#include "DataSink.h"

namespace libssio {

   class BufferDataSink : public DataSink
   {
      protected:
         /* const solely so that no-one accidentally modifies it.
          data is being passed 'non-const' anyway */
         const unsigned char *buf;
         unsigned char *buf_ptr;
         std::size_t size;

      public:
         BufferDataSink(char *data, unsigned int len)
         {
            // data can be NULL if len is also 0
            assert(data!=0 || len==0);
            buf = buf_ptr = reinterpret_cast<unsigned char*>(data);
            size = len;
         };

         /*      void load(char *data, unsigned int len)
          {
          // data can be NULL if len is also 0
          assert(data!=0 || len==0);
          buf = buf_ptr = reinterpret_cast<unsigned char*>(data);
          size = len;
          };*/

         virtual ~BufferDataSink() {};

         virtual void write1(uint32_t val)
         {
            *buf_ptr++ = val & 0xff;
            if (getPos() > getSize()) throw "BufferDataSink overrun";
         };

         virtual void write2(uint16_t val)
         {
            *buf_ptr++ = val & 0xff;
            *buf_ptr++ = (val>>8) & 0xff;
            if (getPos() > getSize()) throw "BufferDataSink overrun";
         };

         virtual void write2big(uint16_t val)
         {
            *buf_ptr++ = (val>>8) & 0xff;
            *buf_ptr++ = val & 0xff;
            if (getPos() > getSize()) throw "BufferDataSink overrun";
         };


         virtual void write4(uint32_t val)
         {
            *buf_ptr++ = val & 0xff;
            *buf_ptr++ = (val>>8) & 0xff;
            *buf_ptr++ = (val>>16)&0xff;
            *buf_ptr++ = (val>>24)&0xff;
            if (getPos() > getSize()) throw "BufferDataSink overrun";
         };

         virtual void write4big(uint32_t val)
         {
            *buf_ptr++ = (val>>24)&0xff;
            *buf_ptr++ = (val>>16)&0xff;
            *buf_ptr++ = (val>>8) & 0xff;
            *buf_ptr++ = val & 0xff;
            if (getPos() > getSize()) throw "BufferDataSink overrun";
         };

         virtual void write(char *b, int len)
         {
            std::memcpy(buf_ptr, b, len);
            buf_ptr += len;
            if (getPos() > getSize()) throw "BufferDataSink overrun";
         };

         virtual void seek(unsigned int pos) { buf_ptr = const_cast<unsigned char *>(buf)+pos; };

         virtual void skip(int pos) { buf_ptr += pos; };

         virtual unsigned int getSize() { return size; };

         virtual unsigned int getPos() { return (buf_ptr-buf); };

         unsigned char *getPtr() { return buf_ptr; };
   };

} // libssio namespace
