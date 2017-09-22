#include "Multiboot2Info.hpp"

const uint32_t Multiboot2Info::MagicNumber = 0x36d76289;

Multiboot2Info::Tag *Multiboot2Info::getFirstTag(void) {
    return reinterpret_cast<Tag*>(&this->reserved + 1);
}

Multiboot2Info::Tag *Multiboot2Info::findNext(Tag *start, Type type) {
    uint8_t *ptr = reinterpret_cast<uint8_t*>(start);
    Tag *header = start;

    //find the next tag
    //size includes the header fields, but not padding
    ptr += header->size;
    //tags are 8 byte aligned and followed by padding if required
    if(reinterpret_cast<uint32_t>(ptr) & 0x7) {
        ptr += 0x8 - (reinterpret_cast<uint32_t>(ptr) & 0x7);
    }

    header = reinterpret_cast<Tag*>(ptr);

    while(ptr < reinterpret_cast<uint8_t*>(this + this->size)) {
        if(header->type == type) {
            return reinterpret_cast<Tag*>(ptr);
        }
        else
        if(header->type == Type::End) {
            return nullptr;
        }
        else {
            //size includes the header fields, but not padding
            ptr += header->size;
            //tags are 8 byte aligned and followed by padding if required
            if(reinterpret_cast<uint32_t>(ptr) & 0x7) {
                ptr += 0x8 - (reinterpret_cast<uint32_t>(ptr) & 0x7);
            }

            header = reinterpret_cast<Tag*>(ptr);
        }
    }

    return nullptr;
}
