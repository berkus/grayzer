#pragma once

#include <fstream>
#include "DataSink.h"

namespace libssio {

class StreamDataSink : public DataSink
{
private:
    std::ofstream *out;

public:
    StreamDataSink(std::ofstream *data_stream) {
        out = data_stream;
    }

    virtual ~StreamDataSink() {}

    /*
    *	Write a 1-byte value.
    */
    void write1(uint32_t val) override {
        out->put(static_cast<char>(val&0xff));
    }

    /*
    *	Write a 2-byte value, lsb first.
    */
    void write2(uint16_t val) override
    {
        out->put(static_cast<char>(val&0xff));
        out->put(static_cast<char>((val>>8)&0xff));
    }

    /*
    *	Write a 2-byte value, msb first.
    */
    void write2big(uint16_t val) override
    {
        out->put(static_cast<char>((val>>8)&0xff));
        out->put(static_cast<char>(val&0xff));
    }

    /*
    *	Write a 4-byte value, lsb first.
    */
    void write4(uint32_t val) override
    {
        out->put(static_cast<char>(val&0xff));
        out->put(static_cast<char>((val>>8)&0xff));
        out->put(static_cast<char>((val>>16)&0xff));
        out->put(static_cast<char>((val>>24)&0xff));
    }

    /*
    *	Write a 4-byte value, msb first.
    */
    void write4big(uint32_t val) override
    {
        out->put(static_cast<char>((val>>24)&0xff));
        out->put(static_cast<char>((val>>16)&0xff));
        out->put(static_cast<char>((val>>8)&0xff));
        out->put(static_cast<char>(val&0xff));
    }

    void write(char *b, int len) override {
        out->write(b, len);
    }

    void seek(unsigned int pos) override {
        out->seekp(pos);
    }

    void skip(int pos) override {
        out->seekp(pos, std::ios::cur);
    }

    size getSize() override
    {
        long pos = out->tellp();
        out->seekp(0, std::ios::end);
        long len = out->tellp();
        out->seekp(pos);
        return len;
    }

    position getPos() override {
        return out->tellp();
    }
};

} // libssio namespace
