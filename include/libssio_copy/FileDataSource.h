#ifndef _FILEDATASOURCE_H
#define _FILEDATASOURCE_H

#include <stdio.h>  // for FILE, puts()
#include <stdlib.h> // for exit()
#include "DataSource.h"

namespace libssio {

   using namespace std;

   class FileDataSource : public DataSource
   {
      private:
         FILE *f;

      public:
         FileDataSource(FILE *fp)
         {
            f = fp;
         };

         virtual ~FileDataSource() {};

	 virtual uint32_t read01()
	 {
	    puts("Unimplemented"); exit(1);
	 };
	 
	 virtual uint32_t read04()
	 {
	    puts("Unimplemented"); exit(1);
	 };
	 
         virtual uint32_t read1()
         {
            unsigned char b0;
            b0 = fgetc(f);
            return (b0);
         };

         virtual uint16_t read2()
         {
            unsigned char b0, b1;
            b0 = fgetc(f);
            b1 = fgetc(f);
            return (b0 | (b1 << 8));
         };

         virtual uint16_t read2big()
         {
            unsigned char b0, b1;
            b1 = fgetc(f);
            b0 = fgetc(f);
            return (b0 | (b1 << 8));
         };

         virtual uint32_t read4()
         {
            unsigned char b0, b1, b2, b3;
            b0 = fgetc(f);
            b1 = fgetc(f);
            b2 = fgetc(f);
            b3 = fgetc(f);
            return (b0 | (b1<<8) | (b2<<16) | (b3<<24));
         };

         virtual uint32_t read4big()
         {
            unsigned char b0, b1, b2, b3;
            b3 = fgetc(f);
            b2 = fgetc(f);
            b1 = fgetc(f);
            b0 = fgetc(f);
            return (b0 | (b1<<8) | (b2<<16) | (b3<<24));
         };

         void read(char *b, uint32_t len)
         {
            fread(b, 1, len, f);
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

#endif /* _FILEDATASOURCE_H */
