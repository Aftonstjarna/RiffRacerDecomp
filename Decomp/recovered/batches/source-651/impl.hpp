#ifndef RIFF_SIGNED64_DIVIDE_HPP
#define RIFF_SIGNED64_DIVIDE_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_STDCALL __stdcall
#elif defined(__i386__)
#define RIFF_STDCALL __attribute__((stdcall))
#else
#define RIFF_STDCALL
#endif
// Truncates toward zero; MIN/-1 returns MIN. Divisor must be nonzero.
extern "C" int64_t RIFF_STDCALL recovered_signed64_divide(int64_t numerator,
                                                        int64_t divisor);
#endif
