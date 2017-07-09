#pragma once

#include <fstream>
#include "DataSource.h"

namespace libssio {

class StreamDataSource : public DataSource
{
private:
    std::ifstream *in;

public:
    StreamDataSource(std::ifstream *data_stream) {
        in = data_stream;
    }

    virtual ~StreamDataSource() {}

    /*
    *	Read a 1-byte value.
    */
    uint32_t read1() override {
        return static_cast<uint32_t>(in->get());
    }

    /*
    *	Read a 2-byte value, lsb first.
    */
    uint16_t read2() override
    {
        uint16_t val = 0;
        val |= static_cast<uint16_t>(in->get());
        val |= static_cast<uint16_t>(in->get()<<8);
        return val;
    }

    /*
    *	Read a 2-byte value, msb first.
    */
    uint16_t read2big() override
    {
        uint16_t val = 0;
        val |= static_cast<uint16_t>(in->get()<<8);
        val |= static_cast<uint16_t>(in->get());
        return val;
    }

    /*
    *	Read a 4-byte long value, lsb first.
    */
    uint32_t read4() override
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
    uint32_t read4big() override
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
    void read(char *b, uint32_t len) override {
        in->read(b, len);
    }

    void seek(unsigned int pos) override {
        in->seekg(pos);
    }

    void skip(int pos) override {
        in->seekg(pos, std::ios::cur);
    }

    size getSize() override
    {
        long pos = in->tellg();
        in->seekg(0, std::ios::end);
        long len = in->tellg();
        in->seekg(pos);
        return len;
    }

    position getPos() override {
        return in->tellg();
    }
};

} // libssio namespace
