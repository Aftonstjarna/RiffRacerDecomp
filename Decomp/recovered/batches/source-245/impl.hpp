#ifndef RIFF_MESSAGE_PUMP_HPP
#define RIFF_MESSAGE_PUMP_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_STDCALL __stdcall
#else
#define RIFF_STDCALL __attribute__((stdcall))
#endif
namespace riff {
// Win32 MSG layout, including POINT. No ownership or object state.
struct Message {
    uint32_t window, message, wparam;
    int32_t lparam;
    uint32_t time;
    int32_t x, y;
};
typedef int32_t (RIFF_STDCALL *Peek)(Message*, uint32_t, uint32_t, uint32_t, uint32_t);
typedef int32_t (RIFF_STDCALL *Translate)(const Message*);
typedef int32_t (RIFF_STDCALL *Dispatch)(const Message*);
struct Imports { Peek peek; Dispatch dispatch; Translate translate; };
extern Imports imports;
void message_pump();
}
#endif
