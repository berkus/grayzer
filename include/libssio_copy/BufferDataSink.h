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
    }

    /*      void load(char *data, unsigned int len)
    {
        // data can be NULL if len is also 0
        assert(data!=0 || len==0);
        buf = buf_ptr = reinterpret_cast<unsigned char*>(data);
        size = len;
    };*/

    virtual ~BufferDataSink() {}

    void write1(uint32_t val) override
    {
        *buf_ptr++ = val & 0xff;
        if (getPos() > getSize()) throw "BufferDataSink overrun";
    }

    void write2(uint16_t val) override
    {
        *buf_ptr++ = val & 0xff;
        *buf_ptr++ = (val>>8) & 0xff;
        if (getPos() > getSize()) throw "BufferDataSink overrun";
    }

    void write2big(uint16_t val) override
    {
        *buf_ptr++ = (val>>8) & 0xff;
        *buf_ptr++ = val & 0xff;
        if (getPos() > getSize()) throw "BufferDataSink overrun";
    }

    void write4(uint32_t val) override
    {
        *buf_ptr++ = val & 0xff;
        *buf_ptr++ = (val>>8) & 0xff;
        *buf_ptr++ = (val>>16)&0xff;
        *buf_ptr++ = (val>>24)&0xff;
        if (getPos() > getSize()) throw "BufferDataSink overrun";
    }

    void write4big(uint32_t val) override
    {
        *buf_ptr++ = (val>>24)&0xff;
        *buf_ptr++ = (val>>16)&0xff;
        *buf_ptr++ = (val>>8) & 0xff;
        *buf_ptr++ = val & 0xff;
        if (getPos() > getSize()) throw "BufferDataSink overrun";
    }

    void write(char *b, int len) override
    {
        std::memcpy(buf_ptr, b, len);
        buf_ptr += len;
        if (getPos() > getSize()) throw "BufferDataSink overrun";
    }

    void seek(unsigned int pos) override {
        buf_ptr = const_cast<unsigned char *>(buf)+pos;
    }

    void skip(int pos) override {
        buf_ptr += pos;
    }

    size getSize() override {
        return size;
    }

    position getPos() override {
        return buf_ptr - buf;
    }

    unsigned char *getPtr() { return buf_ptr; }
};

} // libssio namespace
