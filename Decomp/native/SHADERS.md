# Original shader initialization

`shader_setup.S` reconstructs VA 0x0052DB30 through 0x0052F4BA inclusive
(6,539 bytes) of Game.exe SHA-256
`2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2`.
This is symbolic x86 assembly, assembled and fixed-address linked; no original
machine-code blobs are included. It is not a recovered original C++ translation
unit or a complete matching executable.

Evidence: Ghidra ExportRecovery exports for 0052db30, 0052d840, 0052f4c0 and
00530200 in analysis/ghidra/recovery, and original objdump disassembly of the
half-open range [0x52db30,0x52f4bb). Ghidra identifies a contiguous body ending
in RET; padding before the next function is excluded. The assembly drafter
transcribed 1,596 instructions. Review confirmed the straight-line creation
sequence and the two terminal paths; no jump table or embedded data is present.

The caller supplies the object through ECX, saved in ESI. Each of 225 calls to
0x52D840 supplies two original shader-data addresses and an object slot through
ECX. That helper creates vertex and pixel shader objects and their D3DX constant
tables, releasing partial allocations on failure. The setup routine preserves
all call ordering, data addresses and slot offsets, including repeated shader
addresses. These referenced shader blobs are not reconstructed or credited.

EBX accumulates creation failures through TEST AL, MOVZX EBX,BL and CMOVE EBX,EDI
with EDI=1. Creation continues after failure. The final AL and accumulated BL
select the outcome: failure calls 0x52F4C0 and returns AL=0; success calls
0x530200 and returns AL=1. EBX, ESI and EDI are restored on both paths. Only AL
is the boolean return contract; no invented full-EAX normalization is added.

Ghidra's setup prototype omits the ECX object argument and renders the failure
accumulator as 225 nested boolean tests. The original instruction stream is
authoritative for those details. Helper semantics are research evidence only:
none of the three callees gains byte credit from this source file.

Reproduce with `make -C Decomp OUT=../build/decomp-container coverage test
 test-draft -j2` inside development. The native-check target compares every
byte of the assembled routine against the hash-pinned original. Coverage
rechecks every registered span and rejects overlap. Full PE layout, original
shader data, relocations and the large finalization routine remain unresolved.
