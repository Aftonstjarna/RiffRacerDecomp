# Range-append exception metadata and adjacent adjustors

These findings concern the supported original Game.exe SHA256
`2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2`.
They are original-byte interpretations, not additional reconstructed spans.
Coverage remains **67,129 / 8,635,392 bytes (0.77737062%)**.

## Exception metadata

The already reconstructed handler at VA 0x8FFA20 loads FuncInfo VA 0xB77FD4
and tail-dispatches to the recovered `__CxxFrameHandler3` import thunk. Original
`.rdata` bytes at [0xB77FD4,0xB7802C) decode into the following 88-byte graph:

| Original VA | Structure | Meaning |
| --- | --- | --- |
| 0xB77FD4 | FuncInfo, 36 bytes | Magic 0x19930522; maxState 2; unwind map 0xB77FF8; one try block at 0xB78008; IP-map count/pointer 0; exception-specification pointer 0; EHFlags 1 |
| 0xB77FF8 | Two unwind entries, 16 bytes | Both entries have toState -1 and null action |
| 0xB78008 | TryBlockMap entry, 20 bytes | tryLow 0, tryHigh 0, catchHigh 1, one catch, handler array 0xB7801C |
| 0xB7801C | HandlerType, 16 bytes | Adjectives 0x40; null type; catch-object displacement 0; handler VA 0x45000D |

The handler pointer independently identifies the EH-only cleanup that Ghidra
omits from the ordinary range-append function extent. Its machine code frees
heap storage when capacity is at least 8, sets capacity to 7 and length to 0,
writes the inline WCHAR terminator, then calls `_CxxThrowException(0,0)` to
rethrow. Null type and the handler's original behavior are consistent with a
catch-all; no typed exception object is bound by this record.

Structure field order and 32-bit sizes were cross-checked against the supplied
Ghidra 12.2 source archive:
`Ghidra/Features/MicrosoftCodeAnalyzer/lib/MicrosoftCodeAnalyzer-src.zip`,
specifically `EHFunctionInfoModel.java`, `EHUnwindModel.java`,
`EHTryBlockModel.java` and `EHCatchHandlerModel.java` in
`ghidra/app/cmd/data/exceptionhandling/`.
The interpretations above were checked against the original `.rdata` words;
they are not accepted merely because a tool inferred a structure.

This graph has not yet been rebuilt from structured source or registered with
the strict comparator. None of its 88 bytes earns coverage credit in this commit.

## Adjacent code is a different object lifetime

Immediately following range append's `RET 12`, two eight-byte routines are
present at [0x45004F,0x450057) and [0x450057,0x45005F). They subtract 0x10 or
0x14 from ECX respectively, then tail-jump to VA 0x44EAE0. They are not more
range-append cleanup simply because they follow that routine in the file.

The common target occupies [0x44EAE0,0x44EB02). It preserves the adjusted `this`
in ESI, calls destructor body 0x44EB10, tests bit 0 of the stack flags byte,
conditionally invokes operator delete through IAT 0x92D4B0, returns the original
adjusted object pointer in EAX and uses `RET 4`. This is scalar-deleting-
destructor behavior. The exact class identity is not established here.

Ghidra assigned the 0x45004F adjustor a discontiguous body including the shared
target, whereas the second adjustor export lists only its local eight bytes.
Do not count the shared target twice or equate these inferred function extents
with distinct non-overlapping source-built fragments. Its destructor body is
not yet reconstructed in this batch.

## Provenance

Private evidence: `/tmp/reriff-recovery-resume/exception-exports/`,
`exception-ghidra.log`, and the earlier range-append disassembly/exports in
that same directory. The Ghidra project is a private copy of the earlier Strings
database; shared analysis databases and the original executable were unchanged.

Reproduce original inspection inside `development` using `objdump -s` over
[0xB77FD4,0xB7802C), and `objdump -d -Mintel --insn-width=16` over the code
ranges above. Run `ExportRecovery.java` for 0045004f, 00450057, 0044eae0 and
0044eb10; retain its warning that exported C is research, not verified source.
