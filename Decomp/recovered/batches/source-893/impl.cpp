#include "impl.hpp"
namespace riff {
uint32_t State::separate_finalizable(uint32_t force) {
    Global* g=global;
    Object** link=g->root_link;
    uint32_t bytes=0;
    while (Object* object=*link) {
        if (((object->marks & 3)!=0 || force!=0) && !(object->marks & 8)) {
            Table* table=object->metatable;
            bool has_finalizer=false;
            if (table && !(table->absent_events & 4)) {
                // x86 SHL masks its count to five bits, even for malformed exponents.
                uint32_t mask=(uint32_t(1) << (table->hash_exponent & 31))-1;
                Node* node=table->nodes+(g->finalizer_name->hash & mask);
                while (node && !(node->key_tag==4 && node->key==g->finalizer_name))
                    node=node->next;
                // The original reads the nil TValue at 0x99a41c on a miss.
                // Its tag is zero; a port need not dereference that fixed address.
                has_finalizer=node && node->value_tag!=0;
                if (!has_finalizer) table->absent_events |= 4;
            }
            object->marks |= 8;
            if (has_finalizer) {
                bytes += uint32_t(24)+object->payload_size;
                *link=object->next;
                Object* tail=g->finalizer_tail;
                if (!tail) object->next=object;
                else { object->next=tail->next; tail->next=object; }
                g->finalizer_tail=object;
                continue;
            }
        }
        link=&object->next;
    }
    return bytes;
}
}
