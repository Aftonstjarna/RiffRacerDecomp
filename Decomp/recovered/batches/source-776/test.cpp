#include "impl.hpp"
extern "C" riff::ScriptNode* RIFF_FASTCALL original_script_table_get_string(const riff::ScriptTable*, const riff::ScriptString*);
extern "C" void test_write(const char*, unsigned);
static void copyBytes(void* d, const void* s, unsigned n) {
    unsigned char* a = static_cast<unsigned char*>(d);
    const unsigned char* b = static_cast<const unsigned char*>(s);
    for (unsigned i=0;i<n;++i) a[i]=b[i];
}
static bool same(const void* a, const void* b, unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
extern "C" int test_main() {
    using namespace riff;
    ScriptTable table;
    ScriptNode nodes[8], chain[3];
    ScriptString strings[2];
    unsigned char tableBefore[sizeof(table)], nodesBefore[sizeof(nodes)], chainBefore[sizeof(chain)], stringsBefore[sizeof(strings)];
    for(unsigned i=0;i<sizeof(table);++i) reinterpret_cast<unsigned char*>(&table)[i]=static_cast<unsigned char>(i*19+5);
    for(unsigned i=0;i<sizeof(strings);++i) reinterpret_cast<unsigned char*>(strings)[i]=static_cast<unsigned char>(i*11+3);
    table.nodes=nodes;
    // All count bytes, including 32/64/... wrapping, and hashes with high bits.
    for(unsigned count=0;count<256;++count) for(unsigned h=0;h<8;++h) for(unsigned mode=0;mode<7;++mode) {
        table.logNodeCount=static_cast<uint8_t>(count);
        strings[0].hash=h | ((count%32==0)?0xfffffff8u:0u);
        strings[1].hash=strings[0].hash;
        unsigned index=strings[0].hash & ((uint32_t(1)<<(count&31))-1u);
        for(unsigned i=0;i<8;++i) {
            nodes[i].valueBits=0x12340000u+i; nodes[i].valueType=0x87650000u+i;
            nodes[i].key=&strings[1]; nodes[i].keyType=4; nodes[i].next=0;
        }
        for(unsigned i=0;i<3;++i) {
            chain[i].valueBits=0xfedc0000u+i; chain[i].valueType=i;
            chain[i].key=&strings[1]; chain[i].keyType=4; chain[i].next=i==2?0:&chain[i+1];
        }
        ScriptNode* expected=reinterpret_cast<ScriptNode*>(uintptr_t(0x99a41c));
        if(mode==0) { nodes[index].key=&strings[0]; expected=&nodes[index]; }
        if(mode>=1) nodes[index].next=chain;
        if(mode==1) { chain[0].key=&strings[0]; expected=chain; }
        if(mode==2) { chain[2].key=&strings[0]; expected=chain+2; }
        if(mode==3) { nodes[index].key=&strings[0]; nodes[index].keyType=3; }
        if(mode==4) { chain[1].key=&strings[0]; chain[1].keyType=0xffffffffu; }
        if(mode==5) { chain[0].key=0; chain[0].keyType=0; }
        if(mode==6) { chain[0].key=&strings[0]; chain[2].key=&strings[0]; expected=chain; }
        copyBytes(tableBefore,&table,sizeof(table)); copyBytes(nodesBefore,nodes,sizeof(nodes));
        copyBytes(chainBefore,chain,sizeof(chain)); copyBytes(stringsBefore,strings,sizeof(strings));
        ScriptNode* original=original_script_table_get_string(&table,strings);
        if(original!=expected) return 1;
        if(!same(tableBefore,&table,sizeof(table)) || !same(nodesBefore,nodes,sizeof(nodes)) || !same(chainBefore,chain,sizeof(chain)) || !same(stringsBefore,strings,sizeof(strings))) return 2;
        if(table.getString(strings)!=original) return 3;
        if(!same(tableBefore,&table,sizeof(table)) || !same(nodesBefore,nodes,sizeof(nodes)) || !same(chainBefore,chain,sizeof(chain)) || !same(stringsBefore,strings,sizeof(strings))) return 4;
    }
    test_write("script-table-get-string: passed\n",32);
    return 0;
}
