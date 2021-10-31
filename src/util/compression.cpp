#include "util/compression.hpp"

// ZLIB
#include <zlib.h>

// STL
#include <cstring>

namespace util
{

bool deflate(std::vector<unsigned char> &data)
{
    int ret = 0;
    z_stream zstrm;
    unsigned char buffer[ZlibChunkSize] = { 0 };
    std::vector<unsigned char> dataOut;

    std::memset(&zstrm, 0, sizeof(zstrm));
    if(deflateInit(&zstrm, Z_BEST_COMPRESSION) != Z_OK) {
        return false;
    }
    zstrm.next_in   = (Bytef*)data.data();
    zstrm.avail_in  = data.size();

    // deflate
    do {
        zstrm.next_out = reinterpret_cast<Bytef*>(buffer);
        zstrm.avail_out = ZlibChunkSize;

        ret = deflate(&zstrm, Z_FINISH);
        dataOut.insert(dataOut.end(), buffer, buffer + zstrm.total_out);
    } while(ret == Z_OK);

    deflateEnd(&zstrm);
    if(ret != Z_STREAM_END) {
        return false;
    }

    data = dataOut;
    return true;
}

bool inflate(std::vector<unsigned char> &data)
{
    int ret = 0;
    unsigned long prevOut = 0;
    z_stream zstrm;
    std::vector<unsigned char> dataIn;
    std::vector<unsigned char> dataOut;

    std::memset(&zstrm, 0, sizeof(zstrm));
    if(inflateInit(&zstrm) != Z_OK) {
        return false;
    }

    dataIn.insert(dataIn.end(), data.begin(), data.end());
    zstrm.next_in = (Bytef*)dataIn.data();
    zstrm.avail_in = dataIn.size();

    do {
        std::vector<unsigned char> buffer(ZlibChunkSize, 0);
        zstrm.next_out = (Bytef*)buffer.data();
        zstrm.avail_out = ZlibChunkSize;

        ret = inflate(&zstrm, 0);
        dataOut.insert(dataOut.end(), buffer.begin(), buffer.begin() + (zstrm.total_out - prevOut));
        prevOut = zstrm.total_out;
    } while(ret == Z_OK);

    inflateEnd(&zstrm);
    if(ret != Z_STREAM_END) {
        return false;
    }

    data.clear();
    data.insert(data.begin(), dataOut.begin(), dataOut.end());
    return true;
}

} // namespace util