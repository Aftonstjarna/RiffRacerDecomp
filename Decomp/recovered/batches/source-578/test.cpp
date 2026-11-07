#include "impl.hpp"
extern "C" riff::RecordReference32* __attribute__((thiscall))
original_record32_index_reference(const riff::RecordIndex32*, riff::RecordReference32*, uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static uint32_t arena[64], before[64], expected[64];
static uint32_t address(const void* p) { return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(p)); }
static int run(uint32_t base, uint32_t index, uint32_t records, unsigned out_word) {
    for (unsigned i=0;i<64;++i) arena[i]=0x97130000u+i*7919u;
    arena[1]=address(arena+12);
    arena[2]=address(arena+24);
    arena[14]=base;
    arena[27]=records;
    for (unsigned i=0;i<64;++i) before[i]=arena[i];
    riff::RecordIndex32* self=reinterpret_cast<riff::RecordIndex32*>(arena);
    riff::RecordReference32* out=reinterpret_cast<riff::RecordReference32*>(arena+out_word);
    riff::RecordReference32* result=original_record32_index_reference(self,out,index);
    if (result!=out || test_get_fs_head()!=0x13579bdfu) return 1;
    const uint32_t want=records+((base+index)<<5);
    for (unsigned i=0;i<64;++i) {
        uint32_t value=before[i];
        if (i==out_word) value=0xba2150u;
        if (i==out_word+1) value=want;
        if (i==out_word+2) value=address(arena+24);
        if (arena[i]!=value) return 2;
        expected[i]=arena[i];
    }
    for (unsigned i=0;i<64;++i) arena[i]=before[i];
    result=self->index_reference(out,index);
    if (result!=out) return 3;
    for (unsigned i=0;i<64;++i) if (arena[i]!=expected[i]) return 4;
    return 0;
}
extern "C" int test_main() {
    uint32_t fs_storage[4]={0x13579bdfu,0,0,0};
    if (test_install_fs(fs_storage)!=0) return 10;
    const uint32_t values[]={0,1,2,3,0x07ffffffu,0x08000000u,0x7fffffffu,0x80000000u,0xfffffffeu,0xffffffffu};
    const uint32_t arrays[]={0,0x1000,0xfffffff0u,0x80000001u};
    const unsigned outputs[]={40,0,1,2,12,13,14,24,25,27};
    for (unsigned b=0;b<10;++b)
      for (unsigned i=0;i<10;++i)
        for (unsigned a=0;a<4;++a)
          for (unsigned o=0;o<10;++o) {
            int error=run(values[b],values[i],arrays[a],outputs[o]);
            if (error) return 20+error;
          }
    test_write("record32-index-reference: 4000 cases passed\n",43);
    return 0;
}
