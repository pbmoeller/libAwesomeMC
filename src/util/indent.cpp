#include <AwesomeMC/util/indent.hpp>

namespace amc
{

Indent::Indent(int indentationSize, 
               char indentationCharacter)
    : m_indentationSize(indentationSize)
    , m_indentationCharacter(indentationCharacter)
{

}

void Indent::inc()
{
    m_indentation += m_indentationSize;
}

void Indent::dec()
{
    m_indentation -= m_indentationSize;
    if(m_indentation < 0) {
        m_indentation = 0;
    }
}

Indent& Indent::operator++()
{
    inc();
    return *this;
}

Indent Indent::operator++(int)
{
    Indent tmp(*this);
    inc();
    return tmp;
}

Indent& Indent::operator--()
{
    dec();
    return *this;
}

Indent Indent::operator--(int)
{
    Indent tmp(*this);
    dec();
    return tmp;
}

std::ostream& operator<<(std::ostream &out, const Indent &indent) {
    out << std::string(indent.m_indentation, indent.m_indentationCharacter);
    return out;
}

} // namespace amc