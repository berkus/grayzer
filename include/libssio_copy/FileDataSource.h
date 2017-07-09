#pragma once

#include <stdio.h>  // for FILE, puts()
#include <stdlib.h> // for exit()
#include "DataSource.h"

namespace libssio {

class FileDataSource : public DataSource
{
private:
    FILE *f;

public:
    FileDataSource(FILE *fp) {
        f = fp;
    }

    virtual ~FileDataSource() {}

    uint32_t read01() override
    {
        puts("Unimplemented");
        exit(1);
    }

    uint32_t read04() override
    {
        puts("Unimplemented");
        exit(1);
    }

    uint32_t read1() override
    {
        unsigned char b0;
        b0 = fgetc(f);
        return (b0);
    }

    uint16_t read2() override
    {
        unsigned char b0, b1;
        b0 = fgetc(f);
        b1 = fgetc(f);
        return (b0 | (b1 << 8));
    }

    uint16_t read2big() override
    {
        unsigned char b0, b1;
        b1 = fgetc(f);
        b0 = fgetc(f);
        return (b0 | (b1 << 8));
    }

    uint32_t read4() override
    {
        unsigned char b0, b1, b2, b3;
        b0 = fgetc(f);
        b1 = fgetc(f);
        b2 = fgetc(f);
        b3 = fgetc(f);
        return (b0 | (b1<<8) | (b2<<16) | (b3<<24));
    }

    uint32_t read4big() override
    {
        unsigned char b0, b1, b2, b3;
        b3 = fgetc(f);
        b2 = fgetc(f);
        b1 = fgetc(f);
        b0 = fgetc(f);
        return (b0 | (b1<<8) | (b2<<16) | (b3<<24));
    }

    void read(char *b, uint32_t len) override {
        fread(b, 1, len, f);
    }

    void seek(position pos) override {
        fseek(f, pos, SEEK_SET);
    }

    void skip(offset pos) override {
        fseek(f, pos, SEEK_CUR);
    }

    size getSize() override
    {
        long pos = ftell(f);
        fseek(f, 0, SEEK_END);
        long len = ftell(f);
        fseek(f, pos, SEEK_SET);
        return len;
    }

    position getPos() override {
        return ftell(f);
    }
};

} // libssio namespace
