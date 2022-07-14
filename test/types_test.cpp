// gtest
#include <gtest/gtest.h>

TEST(Types, Size)
{
    EXPECT_EQ(sizeof(char), 1);
    EXPECT_EQ(sizeof(unsigned char), 1);
    EXPECT_EQ(sizeof(short), 2);
    EXPECT_EQ(sizeof(unsigned short), 2);
    EXPECT_EQ(sizeof(int), 4);
    EXPECT_EQ(sizeof(unsigned int), 4);
    EXPECT_EQ(sizeof(long long), 8);
    EXPECT_EQ(sizeof(unsigned long long), 8);
    EXPECT_EQ(sizeof(float), 4);
    EXPECT_EQ(sizeof(double), 8);
    EXPECT_EQ(sizeof(size_t), 8);

#if defined(_MSC_VER) && defined(_WIN64)
    EXPECT_EQ(sizeof(long), 4);
    EXPECT_EQ(sizeof(unsigned long), 4);
#elif defined(__GNUC__)
    #if defined(__x86_64__)
        EXPECT_EQ(sizeof(long), 8);
        EXPECT_EQ(sizeof(unsigned long), 8);
    #elif defined(__i386__)
        EXPECT_EQ(sizeof(long), 4);
        EXPECT_EQ(sizeof(unsigned long), 4);
    #endif
#endif
}