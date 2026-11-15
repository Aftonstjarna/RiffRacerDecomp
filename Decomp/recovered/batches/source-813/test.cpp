#include "impl.hpp"
using namespace riff;
extern "C" Value* __attribute__((regparm(3))) original_script_table_new_key(unsigned,Table*,State*,const Value*);
extern "C" Node* __attribute__((fastcall)) original_script_table_main_bucket(Table*,const Value*);
extern "C" void test_write(const char*,unsigned);
static Node* mainBucket(Table* t,const Value* k) { return original_script_table_main_bucket(t,k); }
static unsigned unexpected;
static void noRehash(State*,Table*,const Value*) { unexpected=1; }
static Value* noEnsure(State*,Table*,const Value*) { unexpected=1; return 0; }
static const Services vm={mainBucket,noRehash,noEnsure};
static bool equal(const void* a,const void* b,unsigned n) {
 const uint8_t* p=static_cast<const uint8_t*>(a);
 const uint8_t* q=static_cast<const uint8_t*>(b);
 for(unsigned i=0;i<n;++i) { if(p[i]!=q[i]) return false; }
 return true;
}
static void fill(void* p,unsigned n) {
 for(unsigned i=0;i<n;++i) static_cast<uint8_t*>(p)[i]=uint8_t(19+i*37);
}
struct Fixture { uint32_t guard; Table t; Node nodes[8]; State s; Global g; uint8_t object[16]; Value key; uint32_t tail; };
static Fixture f,before,after;
static void setup(unsigned kind,unsigned marks,unsigned tableMarks,bool collectable) {
 fill(&f,sizeof f);
 f.s.global=&f.g;f.g.grayAgain=reinterpret_cast<Table*>(uintptr_t(0x12345678));
 f.t.nodes=f.nodes;f.t.lastFree=f.nodes+8;f.t.hashLog2=3;f.t.header[5]=uint8_t(tableMarks);
 f.object[5]=uint8_t(marks);
 f.key.payload=collectable?uint32_t(uintptr_t(f.object)):1;
 f.key.tag=collectable?5:-7;
 for(unsigned i=0;i<8;++i) { f.nodes[i].value.tag=0;f.nodes[i].key.tag=0;f.nodes[i].next=0; }
 unsigned b=f.key.payload%7;
 Node* n=f.nodes+b;
 if(kind==0) return;
 n->key.payload=b;n->key.tag=-1;n->value.tag=3;
 if(kind==1 || kind==4) { // occupant belongs to this bucket; preserve existing chain
  n->next=f.nodes+((b+1)%7);
 }
 if(kind==2 || kind==3) { // displaced occupant, direct or deep predecessor
  unsigned owner=(b+1)%7;
  n->key.payload=owner;
  f.nodes[owner].key.payload=owner;f.nodes[owner].key.tag=-1;f.nodes[owner].value.tag=3;
  f.nodes[owner].next=n;
  if(kind==3) {
   unsigned mid=(b+2)%7;
   f.nodes[owner].next=f.nodes+mid;
   f.nodes[mid].next=n;f.nodes[mid].key.tag=-1;f.nodes[mid].key.payload=owner;f.nodes[mid].value.tag=3;
  }
  n->next=f.nodes+((b+3)%7);
 }
 if(kind==4) {
  // Last free entry is the first node: scan includes the base address.
  // Choose bucket 1 for this source of noncollectable keys.
  for(unsigned i=1;i<8;++i) f.nodes[i].key.tag=-1;
  f.nodes[0].key.tag=0;
 }
 if(kind==5) { n->value.tag=0;n->key.tag=-1;n->next=f.nodes+7; }
}
static int compare(unsigned kind,unsigned marks,unsigned tm,bool gc) {
 setup(kind,marks,tm,gc);before=f;
 Value* a=original_script_table_new_key(0,&f.t,&f.s,&f.key);after=f;
 f=before;unexpected=0;
 Value* b=f.s.newKey(&f.t,&f.key,vm);
 if(unexpected||a!=b||!equal(&f,&after,sizeof f)) return 1;
 if(!equal(f.object,before.object,sizeof f.object)||!equal(&f.s,&before.s,sizeof f.s))return 2;
 // Complete snapshot comparison above includes all padding, guards and stale payloads.
 if(b->tag!=0 || !equal(&reinterpret_cast<Node*>(b)->key,&f.key,8))return 3;
 bool barrier=gc&&(marks&3)&&(tm&4);
 if(barrier) {
  if(f.t.header[5]!=(tm&~4u)||f.t.gcLink!=before.g.grayAgain||f.g.grayAgain!=&f.t)return 4;
 } else if(f.t.header[5]!=tm||f.t.gcLink!=before.t.gcLink||f.g.grayAgain!=before.g.grayAgain)return 5;
 return 0;
}
static unsigned order,bad;
static const Value* expectedKey;
static void rehashBoundary(State* s,Table* t,const Value* k) {
 if(order++!=0||s!=&f.s||t!=&f.t||k!=expectedKey||uintptr_t(t->lastFree)!=uintptr_t(t->nodes)-sizeof(Node))bad=1;
}
static Value* ensureBoundary(State* s,Table* t,const Value* k) {
 if(order++!=1||s!=&f.s||t!=&f.t||k!=expectedKey)bad=1;
 return &f.nodes[3].value;
}
extern "C" int test_main() {
 for(unsigned kind=0;kind<6;++kind)for(unsigned m=0;m<8;++m)for(unsigned tm=0;tm<16;++tm) {
  int r=compare(kind,m,tm,false);if(r)return 10+r;
  if(kind!=4) { r=compare(kind,m,tm,true);if(r)return 20+r; }
 }
 // Growth calls cannot be executed in the original: 0x4f0800 and 0x4f0c50
 // are not accepted oracle spans. Check only the recovered forwarding boundary.
 const Services growth={mainBucket,rehashBoundary,ensureBoundary};
 for(unsigned mode=0;mode<2;++mode) {
  setup(1,0,0,false);
  for(unsigned i=0;i<8;++i)f.nodes[i].key.tag=-1;
  if(mode)f.t.lastFree=f.nodes;
  expectedKey=&f.key;order=bad=0;
  if(f.s.newKey(&f.t,&f.key,growth)!=&f.nodes[3].value||bad||order!=2)return 30;
 }
 const char msg[]="new-key: 1408 original differential cases passed; growth boundary checked separately\n";
 test_write(msg,sizeof(msg)-1);return 0;
}
extern "C" void* memcpy(void* d,const void* s,size_t n) {
 for(size_t i=0;i<n;++i) static_cast<uint8_t*>(d)[i]=static_cast<const uint8_t*>(s)[i];
 return d;
}
extern "C" void* memset(void* d,int c,size_t n) {
 for(size_t i=0;i<n;++i) static_cast<uint8_t*>(d)[i]=uint8_t(c);
 return d;
}
