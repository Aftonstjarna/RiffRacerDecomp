# Original matrix scaling recovery

Supported Game.exe: 8,635,392 bytes; SHA256
`2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2`.

`elMatrix.scaleBy` is MethodDef token `0x06001651`, native RVA `0x58810`.
The reviewed span is VA `0x00458810` through `0x004588A1` inclusive: 146 bytes,
34 instructions, ending in `RET 12`. `ui_matrix_scale.S` contains mnemonics,
not copied executable bytes or an embedded original fragment.

ECX points to the matrix. The three stack arguments are single-precision X,
Y and Z factors. Original SSE scalar operations multiply floats 0..2 by X,
3..5 by Y and 6..8 by Z. Translation floats 9..11 are untouched. The function
returns void, preserves its EBP frame and consumes 12 argument bytes. It has no
calls, branches, unwind metadata, embedded data or relocations in this span.
No claim about the semantics of a screen render group follows from this helper.

Evidence reviewed: original PE/CLI metadata, contiguous original disassembly,
and a read-only Ghidra export generated using `Decomp/ExportRecovery.java`.
Ghidra displayed an incorrect six-byte function extent and an inferred return
through EAX despite decompiling all nine multiplies. Its guessed signature is
not the ABI authority; original instructions and the metadata establish the
boundary, argument cleanup and void return.

Validation, from the repository root inside development Distrobox:

```
make -C Decomp OUT=../build/decomp-container coverage test-draft -j2
```

`ui-matrix-scale-comparison.json` reports 146/146 equal, zero different bytes,
zero masked bytes. Candidate and reference fragment SHA256:
`08634d9df20df96dd105332e4256ac7b2885b1b55be0c6e46499ce6e4a57f927`.
All 111 registered spans match: 67,275 / 8,635,392 bytes (0.77906133%).
This is exact source-built fragment recovery, not a full matching executable or
recovery of the original high-level C++ source. ReRiff behavior changes remain
outside this matching fragment.
