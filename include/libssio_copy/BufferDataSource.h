#pragma once

#include "DataSource.h"

namespace libssio {

   class BufferDataSource : public DataSource
   {
      protected:
         /* const solely so that no-one accidentally modifies it.
          data is being passed 'non-const' anyway */
         const unsigned char *buf;
         unsigned char *buf_ptr;
         std::size_t size;

      public:
         BufferDataSource(char *data, unsigned int len)
         {
            // data can be NULL if len is also 0
            assert(data!=0 || len==0);
            buf = buf_ptr = reinterpret_cast<unsigned char*>(data);
            size = len;
         };

         void load(char *data, unsigned int len)
         {
            // data can be NULL if len is also 0
            assert(data!=0 || len==0);
            buf = buf_ptr = reinterpret_cast<unsigned char*>(data);
            size = len;
         };

         virtual ~BufferDataSource() {};

         virtual uint32_t read1()
         {
            unsigned char b0;
            b0 = static_cast<unsigned char>(*buf_ptr++);
            return (b0);
         };

         virtual uint16_t read2()
         {
            unsigned char b0, b1;
            b0 = static_cast<unsigned char>(*buf_ptr++);
            b1 = static_cast<unsigned char>(*buf_ptr++);
            return (b0 | (b1 << 8));
         };

         virtual uint16_t read2big()
         {
            unsigned char b0, b1;
            b1 = static_cast<unsigned char>(*buf_ptr++);
            b0 = static_cast<unsigned char>(*buf_ptr++);
            return (b0 | (b1 << 8));
         };

         virtual uint32_t read4()
         {
            unsigned char b0, b1, b2, b3;
            b0 = static_cast<unsigned char>(*buf_ptr++);
            b1 = static_cast<unsigned char>(*buf_ptr++);
            b2 = static_cast<unsigned char>(*buf_ptr++);
            b3 = static_cast<unsigned char>(*buf_ptr++);
            return (b0 | (b1<<8) | (b2<<16) | (b3<<24));
         };

         virtual uint32_t read4big()
         {
            unsigned char b0, b1, b2, b3;
            b3 = static_cast<unsigned char>(*buf_ptr++);
            b2 = static_cast<unsigned char>(*buf_ptr++);
            b1 = static_cast<unsigned char>(*buf_ptr++);
            b0 = static_cast<unsigned char>(*buf_ptr++);
            return (b0 | (b1<<8) | (b2<<16) | (b3<<24));
         };

         virtual void read(char *b, uint32_t len)
         {
            std::memcpy(b, buf_ptr, len);
            buf_ptr += len;
         };

         virtual void seek(unsigned int pos) { buf_ptr = const_cast<unsigned char *>(buf)+pos; };

         virtual void skip(int pos) { buf_ptr += pos; };

         virtual unsigned int getSize() { return size; };

         virtual unsigned int getPos() { return (buf_ptr-buf); };

         unsigned char *getPtr() { return buf_ptr; };
   };

} // libssio namespace
