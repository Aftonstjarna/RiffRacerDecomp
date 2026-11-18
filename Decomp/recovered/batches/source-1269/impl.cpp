#include "impl.hpp"
namespace riff {
static Value* lookup_finalizer(Table* table, String* name) {
 uint32_t mask=(uint32_t(1) << (table->exponent & 31))-1;
 Node* node=table->nodes + (name->hash & mask);
 while (node) {
  if (node->key_tag==4 && node->key==name) {
   if (node->value.tag) return &node->value;
   break;
  }
  node=node->next;
 }
 table->absent |= 4;
 return 0;
}
void State::finalize_one() {
 Global* g=global;
 Object* tail=g->pending;
 Object* object=tail->next;
 if (object==tail) g->pending=0;
 else tail->next=object->next;
 object->next=*g->root_link;
 *g->root_link=object;
 object->marked=uint8_t((object->marked & 0xf8) | (g->current_white & 3));
 Table* table=object->metatable;
 if (!table || (table->absent & 4)) return;
 Value* method=lookup_finalizer(table, global->finalizer_name);
 if (!method) return;
 uint32_t old_threshold=g->threshold;
 uint8_t old_hook=allow_hook;
 allow_hook=0;
 g->threshold=g->total*uint32_t(2);
 Value* function=top;
 function[0]=*method;
 function[1].payload=uint32_t(reinterpret_cast<uintptr_t>(object));
 function[1].tag=7;
 top+=2;
 invoke_finalizer(this,function,0);
 allow_hook=old_hook;
 g->threshold=old_threshold;
}
}
