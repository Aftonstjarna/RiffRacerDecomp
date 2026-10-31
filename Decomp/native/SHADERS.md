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

## Creation and cleanup callees

Three additional symbolic assembly bodies preserve the original calling
conventions, conditional branches and null checks:

- `shader_pair_create.S`: [0x52D840,0x52D8FD), 189 bytes. ECX points to four
  pointers: vertex shader, its constant table, pixel shader, its constant table.
  Two stack arguments supply shader data; RET 8 cleans them. Signed HRESULT
  tests gate each allocation. Failure releases only the resources reached on
  that path and clears the same original slots. Success sets AL=1; failure
  sets AL=0. The imported constant-table call remains at IAT 0x92D64C.
- `shader_release.S`: [0x52F4C0,0x52F55A), 154 bytes. Calls 0x52F5B0 first,
  then traverses 280 pointers through the array at this+0xE18. Non-null entries
  receive their first virtual method with argument 1 and are cleared. Next,
  225 four-pointer shader records at this+8 release vertex constant table,
  vertex shader, pixel constant table, pixel shader, in that order, clearing
  each pointer. The callback array's exact class name remains unresolved.
- `shader_binding_cleanup.S`: [0x52F5B0,0x52F5F3), 67 bytes. Traverses 280
  columns of six pointer tables beginning at this+0xE1C with 0x460-byte table
  stride, calling vtable offset 0x10 on non-null entries. It does not itself
  clear pointers. The descriptive filename does not establish the virtual
  method's original name or its internal semantics.

Evidence comes from matching-address Ghidra exports and original objdump
instructions. Ghidra excludes the three-byte LEA alignment instructions at
0x52F4CD and 0x52F5CD from its discontiguous bodies; the original unconditional
branches skip these internal padding instructions. They are reconstructed as
LEA mnemonics, not copied data. Trailing INT3 padding after RET is excluded.
There are no inline data tables or shared external tails in these spans.
The success finalizer at 0x530200 and embedded shader data remain unrecovered.

## Finalization body

`shader_finalize.S` recovers [0x530200,0x535631), 21,553 bytes, as 5,506 symbolic
instructions. Original disassembly and the 00530200 Ghidra export establish
function extent and control flow. Ghidra's two internal gaps, 0x53540A..0x53540F
and 0x535448..0x53544F, are skipped LEA/NOP alignment instructions, not data.
The source includes those mnemonics and excludes trailing padding. Its rebuilt
SHA-256 is `cc7c3bdfe3311b8a93904991dd0f2f0d3ae09b6e671f167e423293d82e0f60f8`.

The original ECX object pointer is saved at EBP-0x18. The routine points the
array at this+0xE18 into this+0xE1C, allocates objects using the imported operator
new at IAT 0x92D4B4, and invokes the original constructors with their precise
argument/register state. Null-allocation branches store the original null
result; no invented early failure or retry is added. The repeated allocation
blocks retain exception-state writes at EBP-4 and temporary allocations at
EBP-0x10. Stack and SSE memory operations remain in their original order.

The tail copies 11 initial table entries into each of five additional tables
with 0x460-byte stride. It then fills three 269-entry ranges starting at offsets
0x1708, 0x1FC8 and 0x2428 from the pointers at 0xE7C, 0xE6C and 0xE98, followed
by the original individual pointer overrides. These are shared pointers, not
new object allocations. The callback classes and all constructors still require
separate semantic recovery; the matching caller does not establish their behavior.

The body installs the original FS:[0] exception frame and restores it before
return. Ghidra incorrectly presents extra allocator arguments derived from the
cookie setup; the assembly preserves the actual instruction-level contract.
The external handler at 0x906264 checks the cookie via 0x8F8958 and dispatches
with metadata address 0xB7D300 through 0x8F8968. The handler, unwind metadata,
constructor bodies and referenced constants earn no credit from this fragment.
No claim is made that this isolated body can execute independently of them.

All 69 registered fragments match after compiling this addition; matching tests
and assembly-drafter acceptance/rejection tests pass. Total source-built fragment
coverage is 59,024 / 8,635,392 bytes (0.68351269%), not a complete PE rebuild.

## Basic2d constructor and finalizer exception thunk

`shader_basic2d_ctor.S` covers [0x52CA50,0x52CC23), 467 bytes. Ghidra identifies
its original vtable as wsShaderBasic2d at 0x9FE83C. The reviewed instructions
call the base constructor at 0x5421B0 and select a shader record using the
stack argument multiplied by 16 and the global at 0xBFCD04. Vertex/pixel shader
and constant-table pointers populate offsets 4, 8, 0x10 and 0x14.

The two direct constant-table lookups resolve matWorldViewProj and gMtxTexture.
Further calls to 0x542340 preserve original names for palette, lighting, camera,
world matrices, fake walls/floors and screen size. Three 64-byte regions at
0x98, 0xD8 and 0x118 are zeroed through the original memset target. The byte at
0x158 is set exactly when the constructor argument equals 3. EAX returns the
object and RET 4 removes the argument. Exception registration and restoration
remain intact; the constructor's external handler at 0x905468 is unresolved.
These shader parameter names do not establish gameplay collision behavior.

`shader_finalize_handler.S` covers [0x906264,0x90627F), 27 bytes, excluding the
trailing INT3. It obtains the establisher frame from [ESP+8], derives the cookie
from [EDX-0x2C] XOR (EDX+0xC), calls the already recovered check at 0x8F8958,
loads metadata address 0xB7D300 into EAX, and tail-jumps to 0x8F8968. Ghidra
includes the shared import thunk in its function body; this fragment explicitly
excludes it to avoid conflating shared code with the local handler. The thunk
jumps through IAT 0x92D4C4 to __CxxFrameHandler3. Unwind metadata is not credited.

Both files are mnemonic assembly drafted from contiguous original instruction
ranges and reviewed against Ghidra exports. No data blobs, masks or external
helper bodies are counted as reconstructed code by these additions.

## Shared base initialization and name lookup

`shader_base_ctor.S` covers [0x5421B0,0x542222), 114 bytes. It installs the
wsShader vtable at 0x9FE7E0 and returns ECX in EAX. It clears only the DWORDs
at offsets 0x0C through 0x38 inclusive, plus 0x44, 0x50 and 0x54. The remaining
fields are not initialized here; replacing this with whole-object zeroing would
change original behavior.

`shader_parameter_lookup.S` covers [0x542340,0x5423D5), 149 bytes. Two stack
arguments supply the constant table and requested name; RET 8 removes them.
A null table or nonzero return from vtable offset 0x14 returns zero. Otherwise
it enumerates the reported constant count through vtable offset 0x20 with a
null parent, skips null handles, and obtains one descriptor through offset
0x18. It does not check that descriptor call's return status. Its inlined,
case-sensitive byte comparison examines two characters per loop, terminates
at NUL, and returns the first matching handle; exhaustion returns zero. The
reconstruction preserves original assumptions about valid name/descriptor
pointers and does not add defensive behavior absent from the executable.

`shader_basic2d_handler.S` covers [0x905468,0x905483), 27 bytes. It derives the
cookie from [EDX-0x10] XOR (EDX+0x0C), calls 0x8F8958, loads the original
metadata pointer 0xB7D1E0, and tail-jumps to 0x8F8968. This differs from the
finalizer handler's cookie displacement and metadata; those differences are
preserved. The referenced unwind metadata is still unresolved and uncredited.

All three ranges are contiguous instruction bodies with no embedded tables;
trailing alignment is excluded. Evidence: same-address Ghidra exports and
original objdump listings, followed by assembly and unmasked native-check.

## Common parameters and DrawPrim construction

`shader_common_parameters.S` reconstructs [0x542230,0x542335), 261 bytes.
The ECX object is retained in ESI. Sixteen ordered calls to 0x542340 store
handles at the original offsets: reposition parameters from both constant
tables, pixel fog/height/alpha/specular/ambient/diffuse parameters, vertex
shadowMapPos, pixel maskColor and shadowColor, and vertex skinMatrixArray and
g_morphAmounts. Null lookup results are stored as-is; there is no early exit.
The original string addresses are referenced, not credited as reconstructed data.

`shader_drawprim_ctor.S` reconstructs [0x5675A0,0x5676E7), 327 bytes. Ghidra
identifies wsShaderDrawPrim at vtable 0xA00CD4. After the recovered base
constructor, it selects the shader record using argument*16 plus the global
at 0xBFCD04, and installs shader/constant-table pointers. Named lookups populate
matrix, inverse-projection, softness, distortion, light-position, light-color
and eye-direction handles. The byte at object+0xC0 is true exactly for argument
0x11. The eyeDir result is stored at 0xB4, then the shared parameter binder runs.
EAX returns the object; RET 4 removes the index argument.

The constructor preserves the FS:[0] frame and uses the already recovered
0x905468 handler. Matching its local code does not reconstruct the external
unwind metadata or vtable. Both functions were reviewed against same-address
Ghidra exports and original disassembly; no embedded data or external shared
tails lie inside the registered ranges. Trailing padding is excluded.
