#ifndef RIFF_APPLICATION_ENTRY_HPP
#define RIFF_APPLICATION_ENTRY_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RR_STDCALL __stdcall
#define RR_THISCALL __thiscall
#else
#define RR_STDCALL __attribute__((stdcall))
#define RR_THISCALL __attribute__((thiscall))
#endif
namespace riff {
// Original x86 MSVC strings: 16 bytes of inline storage, size, capacity.
// Wide strings have eight UTF-16 code units inline, not host wchar_t.
struct NarrowString {
    union { char small[16]; char* heap; } storage;
    uint32_t size, capacity;
    char* data() { return capacity >= 16 ? storage.heap : storage.small; }
};
struct WideString {
    union { uint16_t small[8]; uint16_t* heap; } storage;
    uint32_t size, capacity;
    uint16_t* data() { return capacity >= 8 ? storage.heap : storage.small; }
};
struct Object { void** vtable; };
// Only accessed fields are modeled. Object internals remain separate recoveries.
struct Stage { unsigned char prefix[0x18]; WideString directory, error; };
struct Graphics { unsigned char prefix[0x460]; void* events[2]; unsigned char gap[0x738]; uint8_t stop; };
struct Worker { void** vtable; uint32_t unknown4; void* handle; uint32_t unknownC; char* command; };
struct Services { void** vtable; unsigned char unknown[0x29]; uint8_t stop; };
struct State {
    void** mutex;                 // C0D610
    int64_t* frequency;           // C00B48
    double* frequencyPerMicrosecond; // C00B50
    uint32_t* threadId;           // BFCC3C
    uint8_t* initialized;         // C0D428
    void** service;               // BFCC2C
    Stage** stage;                // BFCD2C
    void** directoryService;      // BFCD08
    Graphics** graphics;         // BFCC44
    Worker** worker;             // BFCCFC
    Services** services;         // BFCBBC
};
// Dependency injection preserves the caller's observable sequence, without
// claiming recovery of the startup graph. Addresses document binding evidence.
struct Dependencies {
    void* (RR_STDCALL *createMutex)(void*,int,const char*); // IAT 92D034
    uint32_t (RR_STDCALL *lastError)(); // 92D108
    int (RR_STDCALL *closeHandle)(void*); // 92D0D4
    int (RR_STDCALL *queryFrequency)(int64_t*); // 92D0F0
    int (RR_STDCALL *messageA)(void*,const char*,const char*,unsigned); // 92D598
    uint32_t (RR_STDCALL *currentThread)(); // 92D0EC
    int32_t (RR_STDCALL *coInitialize)(void*,unsigned); // 92D698
    void (*initializeOnce)(); // 452D30
    void (RR_THISCALL *constructCommand)(NarrowString*,const char*); // 415B00
    // 5C2740 uses ECX=result, EDX=begin and caller-popped stack arguments.
    // A semantic adapter is required; this is deliberately NOT a false ABI cast.
    void (*transform)(char** result,char* begin,char* end,char* dest,int (*)(int));
    int (*lowercase)(int); // IAT 92D4D4, signed char passed as int
    void (*initializeServices)(); // 44EBE0
    void* (*allocate)(uint32_t); // IAT 92D4B4
    void* (RR_THISCALL *constructService)(void*); // 48CE90
    void (*ensureStage)(); // 5CFBE0
    bool (RR_THISCALL *checkStage)(Stage*); // 560310
    void (RR_THISCALL *assignError)(WideString*,const uint16_t*,uint32_t); // 44F9B0
    void (RR_THISCALL *copyError)(WideString*,WideString*,uint32_t,uint32_t); // 44FB30
    Object* (*getMessages)(); // 6D86BB
    // 44F490: ECX=destination, EDX=UTF-16 source, caller-pop register ABI.
    void (*constructWide)(WideString*,const uint16_t*);
    int (RR_STDCALL *messageW)(void*,const uint16_t*,const uint16_t*,unsigned); // 92D594
    void (*deallocate)(void*); // IAT 92D4B0
    int (RR_STDCALL *setDllDirectory)(const uint16_t*); // 92D074
    void (*ensureDirectoryService)(); // 5CFC60
    void (RR_THISCALL *setupDirectoryService)(void*); // 535EC0
    bool (*checkStartup)(); // 510F30
    void (*ensureGraphics)(); // 5CFB60
    bool (RR_THISCALL *startGraphics)(Graphics*,void*,char*,int); // 4A0480
    void (*ensureWorker)(); // 5CFB10
    void (*pumpMessages)(); // 48CE10
    uint32_t (RR_STDCALL *wait)(void*,uint32_t); // 92D124
    void (RR_THISCALL *frame)(Graphics*); // 4A0AF0
    int (RR_STDCALL *setEvent)(void*); // 92D120
    void (RR_THISCALL *shutdownGraphics)(Graphics*); // 4A08E0
    // 8F92EF returns signed int64 conversion in XMM0 (not ordinary GCC double ABI).
    double (*convertFrequency)(int64_t);
};
// Semantic port adapter for VA 005CFC90 (922 bytes). Original ABI is
// int __stdcall WinMain(void* instance, void* previous, char* command, int show).
// State points to live global slots, not snapshots, since callbacks can replace them.
int applicationEntry(void* instance, void* previous, const char* command, int show,
                     State& state, const Dependencies& d);
}
#endif
