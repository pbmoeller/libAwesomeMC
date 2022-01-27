#ifndef AWESOMEMC_NBT_TAGS_VALUE_TAG_HPP
#define AWESOMEMC_NBT_TAGS_VALUE_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>
#include <AwesomeMC/util/byte_stream.hpp>

// STL
#include <utility>

namespace nbt
{

template<typename T, TagType TAG>
class ValueTag : public AbstractTag
{
public:
    enum { Type = static_cast<int>(TAG) };

public:
    // Constructors, Destructor & Assignments
    ValueTag()
        : AbstractTag()
        , m_value()
    { }
    ValueTag(const ValueTag &other)
        : AbstractTag(other.m_name)
        , m_value(other.m_value)
    { }
    ValueTag(ValueTag &&other) noexcept
        : AbstractTag(std::move(other.m_name))
        , m_value(std::move(other.m_value))
    { }
    ValueTag(const std::string &name) requires(!std::same_as<T, std::string>)
        : AbstractTag(name)
        , m_value()
    { }
    ValueTag(const T &value)
        : AbstractTag()
        , m_value(value)
    { }
    ValueTag(const std::string &name, const T &value)
        : AbstractTag(name)
        , m_value(value)
    { }
    virtual ~ValueTag()
    { }

    ValueTag<T, TAG>& operator=(const ValueTag<T, TAG> &other)
    {
        if(this != &other) {
            m_name  = other.m_name;
            m_value = other.m_value;
        }
        return *this;
    }

    ValueTag<T, TAG>& operator=(ValueTag<T, TAG> &&other) noexcept
    {
        if(this != &other) {
            m_name  = std::move(other.m_name);
            m_value = std::move(other.m_value);
        }
        return *this;
    }
    
    // Tag functions
    virtual AbstractTag* clone() const override {
        return new ValueTag<T, TAG>(*this);
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

    T getValue() const {
        return m_value;
    }
    
    void setValue(const T &value) {
        m_value = value;
    }

protected:
    virtual bool isEqual(const AbstractTag &other) const override
    {
        const ValueTag<T, TAG> &otherTag = static_cast<const ValueTag<T, TAG>&>(other);

        return m_name == otherTag.m_name
            && getType() == otherTag.getType()
            && m_value == otherTag.m_value;
    }

private:
    T m_value;
};

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_VALUE_TAG_HPP