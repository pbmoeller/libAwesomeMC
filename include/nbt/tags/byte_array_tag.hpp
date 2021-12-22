#ifndef NBT_TAGS_BYTE_ARRAY_TAG_HPP
#define NBT_TAGS_BYTE_ARRAY_TAG_HPP

// nbt
#include "abstract_tag.hpp"

// STL
#include <string>
#include <vector>

namespace nbt
{

class ByteArrayTag : public AbstractTag
{
public:
    enum { Type = TagType::ByteArray };

    ByteArrayTag();
    ByteArrayTag(const ByteArrayTag &other);
    ByteArrayTag(ByteArrayTag &&other) noexcept;
    ByteArrayTag(const std::string &name);
    ByteArrayTag(const std::vector<char> &value);
    ByteArrayTag(const std::string &name, const std::vector<char> &value);
    virtual ~ByteArrayTag();

    ByteArrayTag& operator=(const ByteArrayTag &other);
    ByteArrayTag& operator=(ByteArrayTag &&other) noexcept;

    virtual AbstractTag* clone();

    constexpr virtual TagType getType() const override;

    std::vector<unsigned char> getData(bool isListEntry) override;

    bool isEmpty() const;
    void clear();
    bool erase(size_t index);
    bool insert(size_t index, char value);
    void pushBack(char value);
    size_t size() const;
    char& at(size_t index);
    const char& at(size_t index) const;

    std::vector<char>& getValue();
    void setValue(const std::vector<char> &value);

protected:
    virtual bool isEqual(const AbstractTag &other) const override;

private:
    std::vector<char> m_value;
};

} // namespace nbt

#endif // NBT_TAGS_BYTE_ARRAY_TAG_HPP