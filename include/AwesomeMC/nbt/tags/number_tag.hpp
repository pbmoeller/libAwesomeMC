#ifndef AWESOMEMC_NBT_TAGS_NUMBER_TAG
#define AWESOMEMC_NBT_TAGS_NUMBER_TAG

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>
#include <AwesomeMC/util/byte_stream.hpp>

// STL
#include <utility>

namespace nbt
{

template<typename T, TagType TAG>
class NumberTag : public AbstractTag
{
public:
    enum { Type = static_cast<int>(TAG) };

    NumberTag()
        : AbstractTag()
        , m_value()
    { }
    NumberTag(const NumberTag &other)
        : AbstractTag(other.m_name)
        , m_value(other.m_value)
    { }
    NumberTag(NumberTag &&other) noexcept
        : AbstractTag(std::move(other.m_name))
        , m_value(other.m_value)
    { }
    NumberTag(const std::string &name)
        : AbstractTag(name)
        , m_value()
    { }
    NumberTag(T value)
        : AbstractTag()
        , m_value(value)
    { }
    NumberTag(const std::string &name, T value)
        : AbstractTag(name)
        , m_value(value)
    { }
    virtual ~NumberTag()
    { }

    NumberTag<T, TAG>& operator=(const NumberTag<T, TAG> &other)
    {
        if(this != &other) {
            m_name = other.m_name;
            m_value = other.m_value;
        }
        return *this;
    }

    NumberTag<T, TAG>& operator=(NumberTag<T, TAG> &&other) noexcept
    {
        if(this != &other) {
            m_name = std::move(other.m_name);
            m_value = other.m_value;
        }
        return *this;
    }
    
    virtual AbstractTag* clone() 
    {
        return new NumberTag<T, TAG>(*this);
    }

    constexpr virtual TagType getType() const override {
        return TAG;
    }

    std::vector<unsigned char> getData(bool isListEntry) override
    {
        util::ByteStream stream(util::ByteStream::Swap::SwapEndian);

        if(!isListEntry) {
            stream << static_cast<int8_t>(getType());
            stream << static_cast<int16_t>(m_name.size());
            stream << m_name;
        }
        stream << m_value;

        return stream.vbuf();
    }

    T getValue() const 
    {
        return m_value;
    }
    
    void setValue(T value)
    {
        m_value = value;
    }

protected:
    virtual bool isEqual(const AbstractTag &other) const override
    {
        const NumberTag<T, TAG> &otherTag = static_cast<const NumberTag<T, TAG>&>(other);

        return m_name == otherTag.m_name
            && getType() == otherTag.getType()
            && m_value == otherTag.m_value;
    }

private:
    T m_value;
};

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_NUMBER_TAG