#include "impl.hpp"
extern "C" ArchiveEntry* __attribute__((thiscall)) original_archive_component_lookup(ArchiveLookup*, const char*, const ArchiveEntry*);
static ArchiveEntry entries[7];
static char names[0x40010];
static ArchiveLookup archive;
static ArchiveEntry parent;
static void put(unsigned off, const char* s) { do { names[off++] = *s; } while (*s++); }
static int check(const char* name, ArchiveEntry* expected) {
    ArchiveEntry saved[7];
    char saved_names[0x40010];
    ArchiveLookup saved_archive = archive;
    ArchiveEntry saved_parent = parent;
    for (unsigned i=0;i<7;++i) saved[i]=entries[i];
    for (unsigned i=0;i<sizeof(names);++i) saved_names[i]=names[i];
    ArchiveEntry* a = archive.lookup(name, &parent);
    ArchiveEntry* b = original_archive_component_lookup(&archive, name, &parent);
    if (a != expected || b != expected) return 1;
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&archive);
    const unsigned char* q = reinterpret_cast<const unsigned char*>(&saved_archive);
    for (unsigned i=0;i<sizeof(archive);++i) if (p[i]!=q[i]) return 2;
    p=reinterpret_cast<const unsigned char*>(&parent); q=reinterpret_cast<const unsigned char*>(&saved_parent);
    for (unsigned i=0;i<sizeof(parent);++i) if (p[i]!=q[i]) return 3;
    p=reinterpret_cast<const unsigned char*>(entries); q=reinterpret_cast<const unsigned char*>(saved);
    for (unsigned i=0;i<sizeof(entries);++i) if (p[i]!=q[i]) return 4;
    for (unsigned i=0;i<sizeof(names);++i) if (names[i]!=saved_names[i]) return 5;
    return 0;
}
extern "C" int test_main() {
    archive.entries=entries; archive.names=names;
    for (unsigned i=0;i<5;++i) archive.unknown_04[i]=0x12340000+i;
    parent.first_child=0xffff;
    if (check("absent",0)) return 1;
    put(0,"alpha"); put(0x10004,"beta"); put(0x20009,""); put(0x30002,"alphabet");
    entries[3].name_offset_low=0; entries[3].next=1; entries[3].flags_and_index=0x1234;
    entries[1].name_offset_low=4; entries[1].next=5; entries[1].flags_and_index=0x4567;
    entries[5].name_offset_low=9; entries[5].next=2; entries[5].flags_and_index=0x89ab;
    entries[2].name_offset_low=2; entries[2].next=0xffff; entries[2].flags_and_index=0xcdef;
    parent.first_child=3;
    if (check("alpha",entries+3) || check("beta",entries+1) || check("",entries+5) || check("alphabet",entries+2)) return 2;
    if (check("Alpha",0) || check("alph",0) || check("alphabeta",0) || check("betb",0)) return 3;
    // Duplicate names select the first entry in chain order.
    entries[1].name_offset_low=0; entries[1].flags_and_index=0;
    if (check("alpha",entries+3)) return 4;
    parent.first_child=1;
    if (check("alpha",entries+1)) return 5;
    return 0;
}
