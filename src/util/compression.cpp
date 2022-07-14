#include <AwesomeMC/util/compression.hpp>

// ZLIB
#include <zlib.h>

// STL
#include <cstring>

namespace amc
{

bool isGzipCompressed(std::vector<unsigned char> &data)
{
    return (data[0] == 0x1F && data[1] == 0x8B);
}

bool isZlibCompressed(std::vector<unsigned char> &data)
{
    return (data[0] == 0x78 
            && (data[1] == 0x01 
                || data[1] == 0x5E
                || data[1] == 0x9C
                || data[1] == 0xDA));
}

bool isUncompressed(std::vector<unsigned char> &data)
{
    return !isGzipCompressed(data)
        && !isZlibCompressed(data);
}

CompressionType getCompression(std::vector<unsigned char> &data)
{
    if(isGzipCompressed(data)) {
        return CompressionType::GZip;
    } else if(isZlibCompressed(data)) {
        return CompressionType::Zlib;
    } else {
        return CompressionType::Uncompressed;
    }
}

bool deflate_zlib(std::vector<unsigned char> &data)
{
    int ret = 0;
    z_stream zstrm;
    std::vector<unsigned char> buffer(ZlibChunkSize, 0);
    std::vector<unsigned char> dataOut;

    std::memset(&zstrm, 0, sizeof(zstrm));
    if(deflateInit(&zstrm, Z_BEST_COMPRESSION) != Z_OK) {
        return false;
    }
    zstrm.next_in   = reinterpret_cast<Bytef*>(data.data());
    zstrm.avail_in  = static_cast<uInt>(data.size());

    // deflate
    do {
        zstrm.next_out = reinterpret_cast<Bytef*>(buffer.data());
        zstrm.avail_out = ZlibChunkSize;

        ret = deflate(&zstrm, Z_FINISH);
        dataOut.insert(dataOut.end(), buffer.begin(), buffer.begin() + zstrm.total_out);
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
    zstrm.next_in = reinterpret_cast<Bytef*>(dataIn.data());
    zstrm.avail_in = static_cast<uInt>(dataIn.size());

    do {
        std::vector<char> buffer(ZlibChunkSize, 0);
        zstrm.next_out = reinterpret_cast<Bytef*>(buffer.data());
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

bool deflate_gzip(std::vector<unsigned char> &data, int level)
{
    // Check if we have data
    if(data.size() == 0) {
        return true;
    }

    // Init zstream
    z_stream zstrm;
    zstrm.zalloc    = Z_NULL;
    zstrm.zfree     = Z_NULL;
    zstrm.opaque    = Z_NULL;
    zstrm.next_in   = Z_NULL;
    zstrm.avail_in  = 0;

    int ret = deflateInit2(&zstrm, std::max(-1, std::min(9, level)), Z_DEFLATED, 15 + 16, 8, Z_DEFAULT_STRATEGY);
    if(ret != Z_OK) {
        return false;
    }

    // Reserve as much data as we have (should almost always be enough ?!?)
    //std::vector<unsigned char> dataOut(data.size(), 0);
    std::vector<unsigned char> dataOut;
    char *inputData = reinterpret_cast<char*>(data.data());
    int remainingData = static_cast<int>(data.size());

    // Compress
    int flush = 0;
    do {
        // Get current chunk size
        int chunkSize = std::min(GzipChunkSize, remainingData);

        // Calculate new intermediate values
        zstrm.next_in = reinterpret_cast<unsigned char*>(inputData);
        zstrm.avail_in = chunkSize;

        inputData += chunkSize;
        remainingData -= chunkSize;

        // Check if this is the last chunk of data
        flush = (remainingData <= 0 ? Z_FINISH : Z_NO_FLUSH);
        
        do {
            std::vector<char> out(GzipChunkSize, 0);

            zstrm.next_out = reinterpret_cast<unsigned char*>(out.data());
            zstrm.avail_out = GzipChunkSize;

            ret = deflate(&zstrm, flush);

            // Check errors
            if(ret == Z_STREAM_ERROR) {
                // Clean up and report error
                deflateEnd(&zstrm);
                return false;
            }

            int compressedDataSize = (GzipChunkSize - zstrm.avail_out);

            if(compressedDataSize > 0) {
                dataOut.insert(dataOut.end(), out.begin(), out.begin() + compressedDataSize);
            }

        } while(zstrm.avail_out == 0);
    } while(flush != Z_FINISH);

    deflateEnd(&zstrm);
    dataOut.resize(zstrm.total_out);
    data = std::move(dataOut);
    return ret == Z_STREAM_END;
}

bool inflate_gzip(std::vector<unsigned char> &data)
{
    if(data.size() == 0) {
        return true;
    }

    bool done = false;
    std::vector<unsigned char> dataOut(data.size(), 0);
    const size_t halfLength = data.size() / 2;

    z_stream zstrm;
    zstrm.next_in   = reinterpret_cast<Bytef*>(data.data());
    zstrm.avail_in  = static_cast<uInt>(data.size());
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
        zstrm.next_out = reinterpret_cast<Bytef*>(dataOut.data() + zstrm.total_out);
        zstrm.avail_out = static_cast<uInt>(dataOut.size() - zstrm.total_out);

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
    char *uncompressed = reinterpret_cast<char*>(calloc(uncompressedLength, sizeof(char)));

    z_stream zstrm;
    zstrm.next_in = reinterpret_cast<Bytef*>(data.data());
    zstrm.avail_in = static_cast<uInt>(data.size());
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
            char* uncompressed2 = reinterpret_cast<char*>(calloc(uncompressedLength + halfLength, sizeof(char)));
            std::memcpy(uncompressed2, uncompressed, uncompressedLength);
            uncompressedLength += halfLength;
            free(uncompressed);
            uncompressed = uncompressed2;
        }
        zstrm.next_out = reinterpret_cast<Bytef*>(uncompressed + zstrm.total_out);
        zstrm.avail_out = static_cast<uInt>(uncompressedLength - zstrm.total_out);

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

} // namespace amc