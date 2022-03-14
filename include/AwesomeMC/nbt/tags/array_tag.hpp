#ifndef AWESOMEMC_NBT_TAGS_ARRAY_TAG_HPP
#define AWESOMEMC_NBT_TAGS_ARRAY_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>
#include <AwesomeMC/util/byte_stream.hpp>

// STL
#include <vector>
#include <utility>
#include <cstdint>
#include <cassert>
#include <stdexcept>

namespace amc
{

template<typename T, TagType TAG>
class ArrayTag : public AbstractTag
{
public:
    enum { Type = static_cast<int>(TAG) };

public:
    // Constructors, Destructor & Assignments
    ArrayTag()
        : AbstractTag()
        , m_value{}
    { }
    ArrayTag(const ArrayTag &other)
        : AbstractTag(other.m_name)
        , m_value{other.m_value}
    { }
    ArrayTag(ArrayTag &&other) noexcept
        : AbstractTag(std::move(other.m_name))
        , m_value{std::move(other.m_value)}
    { }
    ArrayTag(const std::string &name)
        : AbstractTag(name)
        , m_value{}
    { }
    ArrayTag(const std::vector<T> &value)
        : AbstractTag()
        , m_value{value}
    { }
    ArrayTag(const std::string &name, const std::vector<T> &value)
        : AbstractTag(name)
        , m_value{value}
    { }
    virtual ~ArrayTag()
    { }

    ArrayTag& operator=(const ArrayTag &other)
    {
        if(this != &other) {
            m_name  = other.m_name;
            m_value = other.m_value;
        }
        return *this;
    }
    ArrayTag& operator=(ArrayTag &&other) noexcept
    {
        if(this != &other) {
            m_name  = std::move(other.m_name);
            m_value = std::move(other.m_value);
        }
        return *this;
    }

    // Tag functions
    virtual AbstractTag* clone() const override {
        return new ArrayTag<T, TAG>(*this);
    }

    constexpr virtual TagType getType() const override {
        return TAG;
    }

    std::vector<unsigned char> getData(bool isListEntry) override
    {
        ByteStream stream(ByteStream::Swap::SwapEndian);

        if(!isListEntry) {
            stream << static_cast<int8_t>(getType());
            stream << static_cast<int16_t>(m_name.size());
            stream << m_name;
        }

        stream << static_cast<int32_t>(m_value.size());
        for(size_t i = 0; i < m_value.size(); ++i) {
            stream << m_value[i];
        }

        return stream.vbuf();
    }

    std::vector<T>& getValue() {
        return m_value;
    }
    const std::vector<T>& getValue() const {
        return m_value;
    }
    void setValue(const std::vector<T> &value) {
        m_value = value;
    }

    // Vector Operations
    constexpr bool isEmpty() const noexcept {
        return m_value.empty();
    }

    constexpr size_t size() const noexcept{
        return m_value.size();
    }

    constexpr void clear() noexcept {
        m_value.clear();
    }

    bool eraseAt(size_t index)
    {
        if(index >= m_value.size()) {
            return false;
        } else {
            m_value.erase(m_value.begin() + index);
            return true;
        }
    }

    bool insert(size_t index, T value)
    {
        if(index > m_value.size()) {
            return false;
        } else {
            m_value.insert(m_value.begin() + index, value);
            return true;
        }
    }

    constexpr void pushBack(const T &value) {
        m_value.push_back(value);
    }
    constexpr void pushBack(T &&value) {
        m_value.push_back(std::move(value));
    }

    T& at(size_t index)
    {
        if(index >= m_value.size()) {
            throw std::out_of_range("Index out of range!");
        }
        return m_value.at(index);
    }

    const T& at(size_t index) const
    {
        if(index >= m_value.size()) {
            throw std::out_of_range("Index out of range!");
        }
        return m_value.at(index);
    }

    T& operator[](size_t index)
    {
        assert(index < m_value.size());
        return m_value[index];
    }

    const T& operator[](size_t index) const
    {
        assert(index < m_value.size());
        return m_value[index];
    }

protected:
    virtual bool isEqual(const AbstractTag &other) const override
    {
        const ArrayTag<T, TAG> &otherTag = static_cast<const ArrayTag<T, TAG>&>(other);

        if(m_name != otherTag.m_name
           || getType() != otherTag.getType()
           || m_value.size() != otherTag.m_value.size()) {
            return false;
        }

        for(size_t i = 0; i < m_value.size(); ++i) {
            if(m_value[i] != otherTag.m_value[i]) {
                return false;
            }
        }
        return true;
    }

private:
    std::vector<T> m_value;
};

} // namespace amc

#endif // AWESOMEMC_NBT_TAGS_ARRAY_TAG_HPP