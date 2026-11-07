# Riff Racer decompilation and recovery

Recover and document the original Riff Racer implementation to support a
faithful native Linux port and deliberate modding. Useful results include
buildable source, understood algorithms, documented asset formats and tested
behavior, even when a new compiler produces different machine code.

**A 100% byte-identical executable is an optional research target, not a
prerequisite for recovery, porting or modding.** Exact matching remains valuable
evidence where practical; it is not the sole measure of progress.

## Project goals

- **Recover original behavior.** Explain the game's systems using its original
  code, data and execution evidence. Produce maintainable source and record
  uncertain details rather than inventing replacement behavior.
- **Enable a native Linux port.** Recover the track generation, splines, road
  orientation, vehicle physics, rendering and music synchronization needed to
  reproduce the original experience on a native runtime.
- **Support modding.** Make vehicles, tracks, visuals and gameplay understandable
  and extensible. Keep intentional changes distinguishable from faithful
  reconstruction so their effects can be tested against the original.

## How recovery is validated

**Behavior-validated source** is useful recovery even without byte equality.
Document the original function or format, its inputs, outputs and side effects,
and compare representative cases against the original game or preserved
reference evidence. Record the tested cases, differences and unresolved paths;
sampled tests do not establish equivalence for every possible input.

**Compiler-built matching source** additionally produces exactly matching bytes
for the declared span, with reproducible source, toolchain and build provenance.
Keep this stronger byte claim separate from behavioral validation. Reproducing
the original compiler is useful for this work, but is not required before
recovering portable source or validating its behavior.

**Matching assembly** is a separate reference tier. Distinguish instruction
transcription from assembly with reviewed semantic evidence. Dense labels,
renaming symbols or successful reassembly do not themselves demonstrate source
recovery. Preserve provenance and unresolved dependencies in either case.

Copied instruction bytes, embedded original code blobs and unreviewed decompiler
output do not earn source-recovery credit. Intentional behavior changes belong
to modding work and must be identified as such.

## Current status

This repository does not yet provide a complete rebuilt game or a playable
native Linux port. A systematic count of behavior-validated source and working
port features has not yet been established; no overall port-completion
percentage is claimed.

The first [readable render-helper batch](Decomp/recovered/README.md) adds three
unmatched C++ routines for matrix scaling, shader initialization and binding
callbacks. Sampled tests compare their results and side effects to byte-checked
original assembly. The documented GCC configuration passes; an optimized-build
NaN difference and remaining ABI/platform limitations are recorded explicitly.

Four [original-ABI C++ functions](Decomp/recovered/README.md#native-windows-compiler-candidates)
now contribute 345 certified matching-source bytes. Native Windows MSVC2013 and
an independent source-only sandbox rebuild reproduce their complete fragments;
the actual native fragments pass differential behavior tests and controller
source review. The [source ledger](verification/source-coverage.json) and
[certification evidence](verification/source-certifications/msvc-render-helpers-v1/) record that scope.
The [UTF-16 length setter](Decomp/recovered/msvc/wide_length.cpp) adds another
37 certified source bytes, bringing the total to 1379. Its separate
[certification](verification/source-certifications/msvc-wide-length-v1/) includes
native Windows and isolated MSVC rebuilds plus 1,256 comparisons of the actual
compiled function with the original, covering inline/heap storage and guards.
Three existing portable routines also pass native compiler compatibility checks;
their original-behavior tests have been rerun with audited callback bindings.

The [original FLAC PCM conversion](Decomp/native/FLAC-ANALYSIS-RATE.md) is also
recovered as a small, behavior-validated C++ slice. It retains channel zero,
passes exhaustive signed-16-bit value and block-length checks, and compiles
with native MSVC2013. Full decoder and resampler source remain unrecovered;
this slice earns no matching-source credit.

The [reviewed C++ batches](Decomp/recovered/batches/) also recover string
operations, buffer allocation, resource cleanup, window-frame handling and
shader management. Recent additions include
[wide-string character append](Decomp/recovered/batches/source-81/) and
[shader-pair creation](Decomp/recovered/batches/source-86/), including partial
failure cleanup. Each batch records its original reference, tests, review and
remaining dependencies. These implementations remain unmatched source and add
no certified matching bytes; sampled behavior tests do not prove full-game
equivalence or portable Windows dependency replacements.

The following are **byte-comparison metrics**, not overall recovery or port
completion. They describe the accepted recovery on the
[`decomp` branch](https://github.com/Aftonstjarna/RiffRacerDecomp/tree/decomp):

| Evidence | Whole executable | `.text` section |
|---|---:|---:|
| Compiler-built matching high-level source | 1,379 / 8,635,392 bytes (0.01597%) | 1,379 / 5,421,056 bytes (0.02544%) |
| Existing assembly-level byte matches | 82,772 / 8,635,392 bytes (0.95852%) | 82,744 / 5,421,056 bytes (1.52634%) |

The [legacy assembly byte-comparison ledger](verification/coverage.json)
contains 278 matching spans. Their provenance is assembly
sources, including mechanical transcription. Assembly alone earns no high-level
source credit. The separate source ledger admits only reviewed, independently
rebuilt C++ function spans. Its certified ranges overlap existing assembly evidence;
the two rows must not be added together. Stricter assembly qualification remains
pending, so the assembly row is reference evidence, not certified semantic recovery.

Five UTF-16 string helpers add 338 bytes of mechanically transcribed reference
assembly: move construction, storage transfer, destruction, terminated-pointer
assignment and length/terminator updates. Original instructions and targeted
Ghidra exports establish their boundaries and dependencies; complete rebuilt
spans are compared without masking. In particular, the storage helper at
`0x44F890` empties its source after transferring ownership, correcting an earlier
copy-helper description. These references support further path and save-device
recovery; assembly evidence itself adds no certified high-level-source credit
or behavioral claim. The length setter now also has the separate C++
certification described above; the other four helpers remain reference-only.

The 28 bytes outside `.text` are exception metadata in `.rdata`. The `.text`
denominator includes padding and is not a proven instruction-only total.
The source ledger verifies its admitted spans only. The legacy assembly ledger's
`source_rebuild_verified` remains false, and `whole_executable_compared` is false
for both tiers: no complete source-built executable has been compared
successfully to the original.

## Repository scope

Faithful recovery belongs on `decomp`, including useful non-byte-matching source
backed by original evidence and behavioral checks. Reserve `redux` or dedicated
modification branches for intentional behavior changes.

The modified server, launcher and current native-port work remain in
[ReRiff](https://github.com/Aftonstjarna/ReRiff). This repository supplies recovery
findings and reference implementations; full-game playability and supported
modding tools remain goals rather than released features here.

## Verify the existing byte matches

From the `decomp` checkout, build and compare the existing fragments inside a
development Distrobox, using an unmodified, preserved copy of the game:

```sh
distrobox enter development -- make -C "$PWD/Decomp" \
  OUT=../build/decomp-container GAME="/path/to/unmodified/Game.exe" \
  coverage test-draft -j2
```

Replace `development` with your container name and provide the actual reference
path. The supported executable is 8,635,392 bytes with SHA-256
`2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2`.
Keep original executables and assets outside Git; record hashes and provenance.

See the [recovery and comparison guide](Decomp/README.md),
[startup reference](Decomp/native/STARTUP.md) and
[findings carried over from ReRiff](Decomp/RERIFF-EVIDENCE.md).
