#ifndef _FILEDATASINK_H
#define _FILEDATASINK_H

#include <stdio.h>
#include "DataSink.h"

namespace libssio {

   using namespace std;

   class FileDataSink : public DataSink
   {
      private:
         FILE *f;

      public:
         FileDataSink(FILE *fp)
         {
            f = fp;
         };

         virtual ~FileDataSink() {};

         virtual void write01(uint32_t val)
         {
	    puts("Unimplemented");
            fputc(static_cast<char>(val&0xff),f);
         };

         virtual void write04(uint32_t val)
         {
	    puts("Unimplemented");
            fputc(static_cast<char>(val&0xff),f);
         };

         virtual void write1(uint32_t val)
         {
            fputc(static_cast<char>(val&0xff),f);
         };

         virtual void write2(uint16_t val)
         {
            fputc(static_cast<char>(val&0xff),f);
            fputc(static_cast<char>((val>>8)&0xff),f);
         };

         virtual void write2big(uint16_t val)
         {
            fputc(static_cast<char>((val>>8)&0xff),f);
            fputc(static_cast<char>(val&0xff),f);
         };

         virtual void write4(uint32_t val)
         {
            fputc(static_cast<char>(val&0xff),f);
            fputc(static_cast<char>((val>>8)&0xff),f);
            fputc(static_cast<char>((val>>16)&0xff),f);
            fputc(static_cast<char>((val>>24)&0xff),f);
         };

         virtual void write4big(uint32_t val)
         {
            fputc(static_cast<char>((val>>24)&0xff),f);
            fputc(static_cast<char>((val>>16)&0xff),f);
            fputc(static_cast<char>((val>>8)&0xff),f);
            fputc(static_cast<char>(val&0xff),f);
         };

         virtual void write(char *b, int len)
         {
            fwrite(b, 1, len, f);
         };

         virtual void seek(position pos) { fseek(f, pos, SEEK_SET); };

         virtual void skip(offset pos) { fseek(f, pos, SEEK_CUR); };

         virtual size getSize()
         {
            long pos = ftell(f);
            fseek(f, 0, SEEK_END);
            long len = ftell(f);
            fseek(f, pos, SEEK_SET);
            return len;
         };

         virtual position getPos()
         {
            return ftell(f);
         };
   };

};

#endif /* _FILEDATASINK_H */
