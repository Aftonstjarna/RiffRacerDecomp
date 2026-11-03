# Readable render-helper recovery

Three routines have C++ reconstructions with sampled behavioral validation
against freshly assembled, byte-checked original references. These are
**unmatched high-level source**, not a source-built matching EXE. Separate native
Windows compiler experiments are recorded below. The coverage ledger is unchanged.

| Routine | Original VA range (end exclusive) | Reference bytes | GCC C++ bytes |
|---|---|---:|---:|
| `elMatrix.scaleBy`, MethodDef `0x06001651` | `0x458810..0x4588a2` | 146 | 148 |
| `wsShader` base initializer | `0x5421b0..0x542222` | 114 | 103 |
| Shader binding callbacks | `0x52f5b0..0x52f5f3` | 67 | 102 |

The 327 reference bytes describe scope already present in the assembly ledger;
they are neither new matching credit nor a measure of port completion. The
unchanged `native-check` verifier rejects all three C++ fragments for wrong
size (exit 2); it does not write comparison JSON on that rejection.

## Observed behavior and limits

- Matrix scaling multiplies floats 0–2 by X, 3–5 by Y, and 6–8 by Z. Translation
  floats 9–11 remain unchanged. Scalar SSE order affects exceptional values.
- Base initialization stores the original `wsShader` vtable data address and
  clears only offsets `0x0c..0x38`, `0x44`, `0x50`, `0x54`. The gaps retain their
  previous contents. The C++ names describe offsets; original member names and
  the meaning of every cleared field remain unresolved.
- Binding cleanup visits 280 columns, each across six tables spaced `0x460`
  bytes apart, starting at `this+0xe1c`. Non-null entries receive a call through
  vtable slot 4 (`+0x10`, ECX=this). The routine neither clears entries nor
  deduplicates aliases. Callback mutations of future entries affect later calls.
  The callback's underlying operation and error/unwind behavior are unresolved;
  the name "cleanup" does not prove that slot 4 frees an object.

`render_helpers.hpp` records original 32-bit layouts and a GCC i386 `thiscall`
callback adapter. Recovered entry points use ordinary C ABI exports for the
test harness, unlike the original methods. The fixed vtable address is genuine
reference data, not a usable Linux vtable; tests do not dereference it. This is
not yet a drop-in game patch or a 64-bit portable renderer.

The reference sources are [ui_matrix_scale.S](../native/ui_matrix_scale.S),
[shader_base_ctor.S](../native/shader_base_ctor.S), and
[shader_binding_cleanup.S](../native/shader_binding_cleanup.S), with context in
[UI-MATRIX.md](../native/UI-MATRIX.md) and [SHADERS.md](../native/SHADERS.md).
The Ghidra exports for the latter functions corroborate control flow. All three
reference objects have no unapplied relocations. They are linked into the test
executable at new addresses; no game instructions are represented by byte arrays.
This per-function review does not certify the assembly tier as a whole.

## Reproduce the checks

From the repository root, use the existing development container. Supply the
preserved supported EXE and an already built, reviewed `reriff-match` checker:

```sh
distrobox enter development -- make -C "$PWD/Decomp/recovered" \
  OUT="$PWD/build/source-first-render" \
  GAME="/path/to/preserved/Game.exe" \
  MATCHER="$PWD/build/decomp-container/reriff-match" check-reference test
```

The Makefile records the tested GCC flags. Builds require GCC-compatible C++17
with i386/SSE2 output and GNU binutils; the freestanding Linux harness needs no
32-bit C/C++ runtime libraries. `test_runtime.S` contains only test entry, syscall
and MXCSR helpers, with no recovery credit. `validation.json` records the observed
tools, source evidence and results; it is a reproducibility record, not an
independent acceptance receipt or a pinned complete compiler distribution.

The accepted local test configuration was GCC 16.2.1 (Fedora build
16.2.1-2), binutils 2.46.1-1.fc44, `-O0`, scalar SSE2 and no fast math:

- **5,896 matrix cases:** 225 edge-pattern pairs plus 512 deterministic random
  cases, repeated under all four rounding modes and both flush-to-zero settings.
  Compare every output bit, untouched translation and complete MXCSR flags.
  Edges include signed zero, subnormals, infinities and distinct quiet/signaling
  NaN payloads. Exceptions are masked; DAZ remains off.
- **1,024 initializers:** random preexisting bytes, complete output structure and
  returned pointer comparison, including untouched gaps.
- **Five callback scenarios:** empty, sparse, full, aliased entries and callbacks
  mutating future entries. Compare call order/count/identity and complete table
  storage, including the untouched prefix.

**Known optimized-build difference:** with otherwise equivalent flags at `-O2`,
matrix input `0x7fc12345` and factor `0xffc54321` retain the input NaN payload in
the original, but GCC retains the factor payload at indices 2, 5 and 8. GCC
commutes multiply operands when reusing registers. Strict tests caught this;
`-O0` passes the recorded sample. Do not generalize that result to other flags,
compilers or CPUs, and do not weaken the oracle to hide the difference.

Untested: unmasked FP traps, DAZ-on, invalid pointers, concurrent mutation,
exceptions/nonlocal callback exits, full shader ownership/lifecycle, actual
rendering and Windows/native-game integration. No universal behavioral
equivalence, trusted isolation, or independently certified source match is claimed.

## Native Windows compiler candidates

The [MSVC source variants](msvc/) use original x86 member-method calling
conventions. Native Windows MSVC 18.00.40629, `/O2 /Oy- /GS- /GR- /EHsc /Zl /Gy
/arch:SSE2 /fp:precise`, reproduces four complete function fragments:

| Source | Original routine | Matching candidate bytes |
|---|---|---:|
| `matrix.cpp` | `ui-matrix-scale` | 146 |
| `binding.cpp` | `shader-binding-cleanup` | 67 |
| `release.cpp` | `resource-reference-release` | 18 |
| `shader.cpp` | `shader-base-ctor` | 114 |

The shader variant expresses the observed initialization as a constructor with
explicit member initializers. This restores the original scalar stores while
leaving the unnamed gaps untouched; the earlier loop-based method generated
different code. No instruction arrays, inline assembly, binary patching,
relocation masking or padding trimming is involved.

These **345 function bytes are now certified compiler-built matching source**
in the [source ledger](../../verification/source-coverage.json). The
[certification receipt](../../verification/source-certifications/msvc-render-helpers-v1/)
binds source hashes, native Windows builds, an independent original-free sandbox
rebuild with pinned MSVC, exact comparisons, actual compiled-fragment behavior
tests and controller source review. Replaying publication adds zero bytes.

Earlier `comparison.json` and `validation.json` files retain their historical
pending classification; a standalone comparison still grants no credit. The
source ledger is the acceptance authority. This is not a complete rebuilt
executable. Original fixed data addresses and x86 layouts remain unsuitable
for direct use in a Linux port. Callback exceptions, invalid objects,
concurrency and unmasked floating-point traps remain untested.

With the pinned x86 compiler on PATH, `msvc/build.cmd OUTPUT_DIRECTORY` rebuilds
the four objects. Build the inspection helper from the repository root with
`c++ -std=c++20 -I Decomp Decomp/recovered/msvc/compare.cpp -lcrypto -o build/msvc-compare`,
then run `build/msvc-compare ORIGINAL_EXE OBJECT_DIRECTORY BIN_DIRECTORY`.
Use the existing `reriff-match native-check` for independent fragment comparison.
The inspection helper never changes coverage or awards certification.

The existing `source-1`, `source-7`, and `source-25` implementations also compile
unchanged between GCC and MSVC after bounded type, layout and cdecl corrections.
Their refreshed validation records retain original behavioral tests and native
compiler results. The close and range tests now exercise their nonnull/nonempty
original paths through audited test-only import-slot bindings.
