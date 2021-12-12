#include "util/compression.hpp"

// ZLIB
#include <zlib.h>

// STL
#include <cstring>

namespace util
{

bool deflate_zlib(std::vector<unsigned char> &data)
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

bool inflate_zlib(std::vector<unsigned char> &data)
{
    int ret = 0;
    unsigned long prevOut = 0;
    z_stream zstrm;
    std::vector<char> dataIn;
    std::vector<char> dataOut;

    std::memset(&zstrm, 0, sizeof(zstrm));
    if(inflateInit(&zstrm) != Z_OK) {
        return false;
    }

    dataIn.insert(dataIn.end(), data.begin(), data.end());
    zstrm.next_in = (Bytef*)dataIn.data();
    zstrm.avail_in = dataIn.size();

    do {
        std::vector<char> buffer(ZlibChunkSize, 0);
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

bool inflate_gzip(std::vector<unsigned char> &data)
{
    if(data.size() == 0) {
        return true;
    }

    int ret = 0;
    bool done = false;
    std::vector<unsigned char> dataOut(data.size(), 0);
    const size_t halfLength = data.size() / 2;

    z_stream zstrm;
    zstrm.next_in   = (Bytef*)data.data();
    zstrm.avail_in  = data.size();
    zstrm.total_out = 0;
    zstrm.zalloc    = Z_NULL;
    zstrm.zfree     = Z_NULL;

    if(inflateInit2(&zstrm, (16 + MAX_WBITS)) != Z_OK) {
        return false;
    }

    while(!done) {
        if(zstrm.total_out >= dataOut.size()) {
            dataOut.resize(dataOut.size() + halfLength);
        }
        zstrm.next_out = (Bytef*)(dataOut.data() + zstrm.total_out);
        zstrm.avail_out = dataOut.size() - zstrm.total_out;

        int err = inflate(&zstrm, Z_SYNC_FLUSH);
        if(err == Z_STREAM_END) {
            done = true;
        } else if(err != Z_OK) {
            break;
        }
    }

    if(inflateEnd(&zstrm) != Z_OK) {
        return false;
    }

    dataOut.resize(zstrm.total_out);
    data = std::move(dataOut);
    return true;
}

/*
 * https://windrealm.org/tutorials/decompress-gzip-stream.php
 */
bool inflate_gzip2(std::vector<unsigned char> &data)
{
    if(data.size() == 0) {
        return true;
    }

    size_t fullLength = data.size();
    size_t halfLength = data.size() / 2;

    size_t uncompressedLength = fullLength;
    char *uncompressed = (char*)calloc(uncompressedLength, sizeof(char));

    z_stream zstrm;
    zstrm.next_in = (Bytef*)data.data();
    zstrm.avail_in = data.size();
    zstrm.total_out = 0;
    zstrm.zalloc = Z_NULL;
    zstrm.zfree = Z_NULL;

    bool done = false;
    if(inflateInit2(&zstrm, (16 + MAX_WBITS)) != Z_OK) {
        free(uncompressed);
        return false;
    }

    while(!done) {
        if(zstrm.total_out >= uncompressedLength) {
            char* uncompressed2 = (char*) calloc(uncompressedLength + halfLength, sizeof(char));
            std::memcpy(uncompressed2, uncompressed, uncompressedLength);
            uncompressedLength += halfLength;
            free(uncompressed);
            uncompressed = uncompressed2;
        }
        zstrm.next_out = (Bytef*)(uncompressed + zstrm.total_out);
        zstrm.avail_out = uncompressedLength - zstrm.total_out;

        int err = inflate(&zstrm, Z_SYNC_FLUSH);
        if(err == Z_STREAM_END) {
            done = true;
        } else if(err != Z_OK){
            break;
        }
    }

    if(inflateEnd(&zstrm) != Z_OK) {
        free(uncompressed);
        return false;
    }

    data = std::vector<unsigned char>(zstrm.total_out, 0);
    memcpy(data.data(), uncompressed, zstrm.total_out);
    free(uncompressed);
    return true;
}

} // namespace util