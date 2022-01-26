#ifndef AWESOMEMC_NBT_TAGS_ABSTRACT_VECTOR_TAG_HPP
#define AWESOMEMC_NBT_TAGS_ABSTRACT_VECTOR_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>

// STL
#include <vector>

namespace nbt
{

class AbstractVectorTag : public AbstractTag
{
public:
    using iterator          = typename std::vector<AbstractTag*>::iterator;
    using const_iterator    = typename std::vector<AbstractTag*>::const_iterator;

public:
    // Constructors, Destructors & Assignments
    AbstractVectorTag();
    AbstractVectorTag(const AbstractVectorTag &other);
    AbstractVectorTag(AbstractVectorTag &&other) noexcept;
    AbstractVectorTag(const std::string &name);
    virtual ~AbstractVectorTag();

    AbstractVectorTag& operator=(const AbstractVectorTag &other);
    AbstractVectorTag& operator=(AbstractVectorTag &&other) noexcept;

    // Tag Stuff
    constexpr virtual TagType getType() const override = 0;

    virtual AbstractTag* clone() override = 0;
    virtual std::vector<unsigned char> getData(bool isListEntry) override = 0;

    void setValue(std::vector<AbstractTag*> &value);
    // !!! Do not delete these items - the container keeps the ownership 
    //     -> use getValueCopy, if you want to modify the data !!!
    std::vector<AbstractTag*>& getValue();
    const std::vector<AbstractTag*>& getValue() const;
    std::vector<AbstractTag*> getValueCopy() const;

    void clear();
protected:
    bool isEqual(const AbstractTag &other) const;
    void copy(const std::vector<AbstractTag*> &otherValue);

public:
    // Vector Operations
    constexpr iterator begin() noexcept {
        return m_value.begin();
    }
    constexpr iterator end() noexcept {
        return m_value.end();
    }
    constexpr const_iterator begin() const noexcept {
        return m_value.begin();
    }
    constexpr const_iterator end() const noexcept {
        return m_value.end();
    }

    constexpr bool isEmpty() const noexcept {
        return m_value.empty();
    }
    constexpr size_t size() const noexcept {
        return m_value.size();
    }
    bool erase(size_t index);

    // !!! This functions removes the item from the container - transfers ownership !!!
    AbstractTag* takeAt(size_t index);
    // !!! Do not delete the item - the container keeps the ownership !!!
    // Does range checking -> throws
    AbstractTag* at(size_t index);
    // !!! Do not delete the item - the container keeps the ownership !!!
    // Does range checking -> throws
    const AbstractTag* at(size_t index) const;

    // !!! Do not delete the item - the container keeps the ownership !!!
    // Does not do range checking. Assert in debug
    AbstractTag* operator[](const size_t index);
    // !!! Do not delete the item - the container keeps the ownership !!!
    // Does not do range checking. Assert in debug
    const AbstractTag* operator[](const size_t index) const;

    // !!! Takes ownership of value - do not delete the object after !!!
    virtual bool insert(size_t index, AbstractTag *value);
    // !!! Takes ownership of value - do not delete the object after !!!
    virtual bool pushBack(AbstractTag* value);

protected:
    std::vector<AbstractTag*> m_value;
};

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_ABSTRACT_VECTOR_TAG_HPP