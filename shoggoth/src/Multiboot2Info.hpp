#ifndef MULTIBOOT2
#define MULTIBOOT2

#include <stdint.h>

class Multiboot2Info {
    uint32_t size;
    uint32_t reserved;

public:
    static const uint32_t MagicNumber;

    enum class Type : uint32_t {
        End = 0,
        Module = 3,
        BasicMemory = 4,
    };

    struct Tag {
        Type type;
        uint32_t size;
    };

    struct BasicMemory : public Tag {
        uint32_t lower;
        uint32_t higher;
    } __attribute__((packed));

    struct Module : public Tag {
        uint32_t start;
        uint32_t end;
        uint8_t stringStart;
    } __attribute__ ((packed));

    template <Type T>
    struct TagType;

    template <Type T>
    typename TagType<T>::type getTag(Tag *lastTag = nullptr);

private:
    Tag *getFirstTag(void);
    Tag *findNext(Tag *start, Type);
} __attribute__((packed));

template <>
struct Multiboot2Info::TagType<Multiboot2Info::Type::Module> {
    typedef Module* type;
};

template <>
struct Multiboot2Info::TagType<Multiboot2Info::Type::BasicMemory> {
    typedef BasicMemory* type;
};

template <Multiboot2Info::Type T>
typename Multiboot2Info::TagType<T>::type Multiboot2Info::getTag(Tag *lastTag) {
    Tag *first = this->getFirstTag();

    if(first->type == T && lastTag == nullptr) {
        return reinterpret_cast<typename Multiboot2Info::TagType<T>::type>(first);
    }
    else {
        return reinterpret_cast<typename Multiboot2Info::TagType<T>::type>(this->findNext((lastTag == nullptr) ? first : lastTag, T));
    }
}
#endif
