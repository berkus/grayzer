#pragma once

#include <stdio.h>
#include "DataSink.h"

namespace libssio {

class FileDataSink : public DataSink
{
private:
    FILE *f;

public:
    FileDataSink(FILE *fp) {
        f = fp;
    }

    virtual ~FileDataSink() {}

    void write01(uint32_t val) override
    {
        puts("Unimplemented");
        fputc(static_cast<char>(val&0xff),f);
    }

    void write04(uint32_t val) override
    {
        puts("Unimplemented");
        fputc(static_cast<char>(val&0xff),f);
    }

    void write1(uint32_t val) override {
        fputc(static_cast<char>(val&0xff),f);
    }

    void write2(uint16_t val) override
    {
        fputc(static_cast<char>(val&0xff),f);
        fputc(static_cast<char>((val>>8)&0xff),f);
    }

    void write2big(uint16_t val) override
    {
        fputc(static_cast<char>((val>>8)&0xff),f);
        fputc(static_cast<char>(val&0xff),f);
    }

    void write4(uint32_t val) override
    {
        fputc(static_cast<char>(val&0xff),f);
        fputc(static_cast<char>((val>>8)&0xff),f);
        fputc(static_cast<char>((val>>16)&0xff),f);
        fputc(static_cast<char>((val>>24)&0xff),f);
    }

    void write4big(uint32_t val) override
    {
        fputc(static_cast<char>((val>>24)&0xff),f);
        fputc(static_cast<char>((val>>16)&0xff),f);
        fputc(static_cast<char>((val>>8)&0xff),f);
        fputc(static_cast<char>(val&0xff),f);
    }

    void write(char *b, int len) override {
        fwrite(b, 1, len, f);
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
