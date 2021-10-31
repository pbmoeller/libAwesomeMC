// gtest
#include <gtest/gtest.h>

namespace testing
{
namespace internal
{

enum GTestColor
{
    COLOR_DEFAULT,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
};

extern void ColoredPrintf(GTestColor color, const char* fmt, ...);

} // namespace internal

} // namespace testing

#define TEST_PRINTF(...)                                                                            \
    do {                                                                                            \
        testing::internal::ColoredPrintf(testing::internal::COLOR_GREEN, "[          ] ");          \
        testing::internal::ColoredPrintf(testing::internal::COLOR_YELLOW, __VA_ARGS__);             \
    } while(0)                                                                                      \

class TestCout : public std::stringstream
{
public:
    ~TestCout()
    {
        TEST_PRINTF("%s", str().c_str());
    }
};

#define TEST_COUT TestCout()