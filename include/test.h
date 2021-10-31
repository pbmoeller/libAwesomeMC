#ifndef TEST_H
#define TEST_H

#ifdef _MSC_VER
    #ifdef TEST_EXPORT
        #define TEST_API _declspec(dllexport)
    #else
        #define TEST_API _declspec(dllimport)
    #endif
#else
    #define TEST_API __attribute__((__visibility__("default")))
#endif

TEST_API const char *printVersion();

#endif // TEST_H