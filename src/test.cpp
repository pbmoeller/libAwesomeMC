#include "test.h"

#include <zlib.h>

TEST_API const char *printVersion()
{
    return zlibVersion();
}