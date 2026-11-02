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

The following are **byte-comparison metrics**, not overall recovery or port
completion. They describe the accepted recovery on the
[`decomp` branch](https://github.com/Aftonstjarna/RiffRacerDecomp/tree/decomp):

| Evidence | Whole executable | `.text` section |
|---|---:|---:|
| Compiler-built matching high-level source | 0 / 8,635,392 bytes (0.00000%) | 0 / 5,421,056 bytes (0.00000%) |
| Existing assembly-level byte matches | 69,983 / 8,635,392 bytes (0.81042%) | 69,955 / 5,421,056 bytes (1.29043%) |

The [byte-comparison ledger](https://github.com/Aftonstjarna/RiffRacerDecomp/blob/decomp/verification/coverage.json)
contains 133 accepted spans. The provenance audit maps all of them to assembly
sources, including mechanical transcription; none currently contributes to the
high-level matching row. Stricter assembly qualification remains pending, so the
assembly row is reference evidence, not certified semantic recovery. The ledger
does not yet encode those provenance classes.

The 28 bytes outside `.text` are exception metadata in `.rdata`. The `.text`
denominator includes padding and is not a proven instruction-only total.
`source_rebuild_verified` and `whole_executable_compared` remain false: no
complete source-built executable has been compared successfully to the original.

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
