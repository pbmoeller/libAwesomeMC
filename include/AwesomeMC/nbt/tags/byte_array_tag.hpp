#ifndef AWESOMEMC_NBT_TAGS_BYTE_ARRAY_TAG_HPP
#define AWESOMEMC_NBT_TAGS_BYTE_ARRAY_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>

// STL
#include <cstdint>
#include <string>
#include <vector>

namespace nbt
{

class ByteArrayTag : public AbstractTag
{
public:
    enum { Type = static_cast<int>(TagType::ByteArray) };

    ByteArrayTag();
    ByteArrayTag(const ByteArrayTag &other);
    ByteArrayTag(ByteArrayTag &&other) noexcept;
    ByteArrayTag(const std::string &name);
    ByteArrayTag(const std::vector<int8_t> &value);
    ByteArrayTag(const std::string &name, const std::vector<int8_t> &value);
    virtual ~ByteArrayTag();

    ByteArrayTag& operator=(const ByteArrayTag &other);
    ByteArrayTag& operator=(ByteArrayTag &&other) noexcept;

    virtual AbstractTag* clone();

    constexpr virtual TagType getType() const override
    {
        return TagType::ByteArray;
    }

    std::vector<unsigned char> getData(bool isListEntry) override;

    bool isEmpty() const;
    void clear();
    bool erase(size_t index);
    bool insert(size_t index, int8_t value);
    void pushBack(int8_t value);
    size_t size() const;
    int8_t& at(size_t index);
    const int8_t& at(size_t index) const;

    std::vector<int8_t>& getValue();
    void setValue(const std::vector<int8_t> &value);

protected:
    virtual bool isEqual(const AbstractTag &other) const override;

private:
    std::vector<int8_t> m_value;
};

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_BYTE_ARRAY_TAG_HPP