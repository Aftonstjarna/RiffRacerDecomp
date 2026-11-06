#ifndef RIFF_DOUBLE_INTEGER_PARITY_HPP
#define RIFF_DOUBLE_INTEGER_PARITY_HPP
// Original VA 0x8fc420, 133 bytes. cdecl double argument, integer in EAX.
// 0: not a finite integer; 1: odd integer; 2: even integer.
int double_integer_parity(double value);
#endif
