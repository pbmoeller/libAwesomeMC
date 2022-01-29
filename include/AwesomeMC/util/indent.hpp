#ifndef AWESOMEMC_UTIL_INDENT_HPP
#define AWESOMEMC_UTIL_INDENT_HPP

// STL
#include <iostream>

namespace util
{

class Indent
{
public:
    Indent() = default;
    Indent(int indentationSize, char indentationCharacter = ' ');
    Indent(const Indent &other) = default;
    Indent(Indent &&other) noexcept = default;
    ~Indent() = default;

    Indent& operator=(const Indent &other) = default;
    Indent& operator=(Indent &&other) noexcept = default;

    void inc();
    void dec();

    Indent& operator++();
    Indent operator++(int);
    Indent& operator--();
    Indent operator--(int);

    friend std::ostream& operator<<(std::ostream &out, const Indent &indent);

private:
    int m_indentation           = 0;
    char m_indentationCharacter = ' ';
    const int m_indentationSize = 2;
};

std::ostream& operator<<(std::ostream &out, const Indent &indent);

} // namespace util

#endif // AWESOMEMC_UTIL_INDENT_HPP