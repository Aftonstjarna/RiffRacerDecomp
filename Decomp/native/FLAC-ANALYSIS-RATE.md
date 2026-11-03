# FLAC analysis time base and original resampler ABI

Supported Game.exe SHA-256:
`2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2`
(8,635,392 bytes; Steam depot 351991, build 1687655). References were checked
against `packaging/vanilla-reference.json` and the preserved original copy.
Addresses below are original VAs at image base `0x00400000`.

* Managed token `0x060014DB`, `gaNewTrackScreen.startDecodeForEssentia`, requests
  44,100 Hz at IL `0051`. Token `0x060014DD`, `essentiaJob`, supplies 44,100 Hz
  at IL `0059` to `gaAudioAnalysis.analyse` (call at `006a`).
* `gaAudioAnalysis.analyse` (`0x06000EC9`) calculates duration from samples/rate.
  Section and volume stages (`0x06000EAE`, `0x06000EB2`) use the original
  `s_requiredSampleRate` global. Merely relabeling 96 kHz samples is incorrect.
* Worker `0x0048D9C0` calls FLAC decoder `0x004F9080` at `0x0048DB0B`.
  Guard bytes are `e8 70 b5 06 00 83 c4 1c`; decoder prefix `55 8b ec 6a ff`.
  Input pointer/size arrive in ECX/EDX; seven stack arguments are caller-popped.
  This is not ordinary Microsoft `__fastcall`. Preserve all seven arguments,
  metadata and the original decoder's PCM conversion/channel behavior.
* Original Ogg resampler constructor: `0x005623E0`, prefix
  `55 8b ec 83 ec 18 66 0f 28 c1`. Ratio arrives in XMM1/XMM2; plain return.
  Processing: `0x00562630`, prefix `55 8b ec 83 ec 28 f2 0f 10 4d 1c`.
  ECX = state, EDX = input; caller-popped stack = input frames, EOF, consumed
  pointer, output, capacity, double ratio. Return = produced frames.
* Preserve the original float target/source division before converting to double.
  Ogg cleanup at `0x004F8D65` frees state pointers at offsets `0x2c`, `0x40`,
  `0`, `4`, then state. Original new[] entry is `0x008F87C8`; delete[] IAT
  is `0x0092D4A0`, CRT free IAT `0x0092D3A4`.

Evidence: original managed IL, original instruction disassembly and Ghidra
read-only exports retained in [flac-evidence](flac-evidence/).
The targeted export at `0x005624B0` is an interior constructor address, not a
separate function. No compiler-built matching-byte credit is claimed.

## Previously reported ReRiff behavioral checks

Original FLAC decoding of the 96 kHz / 24-bit FLOW — GET BACK source produces
18,757,120 mono frames. Passing those frames through the original Ogg resampler
at 44,100 / 96,000 produces 8,616,553 frames (195.386689 seconds). The source
duration is 195.386667 seconds. Standalone native execution preserves decoder
metadata. The 44.1 kHz version produces 8,616,552 frames; bypassing resampling
is byte-for-byte identical to the original decoder output. Two-second tones
at 32/48/96/192 kHz produce 88,202/88,201/88,201/88,201 output frames, with
finite PCM and preserved 1 kHz pitch. These are original-DSP behavioral tests,
not byte-matching reconstructed source or a completed in-game race test.

The intentional CALL redirection and ABI adapters live separately in ReRiff
ExperimentalMenu/flac_sample_rate.h on codex/flac-sample-rate. That initial
investigation changed no original reconstruction functions, recovery totals,
or active recovery Ghidra project.

## Recovered original PCM conversion

The original FLAC wrapper's loop at VA `0x4F91F0..0x4F9212` reads every
second signed 16-bit word from its decoded PCM scratch block and multiplies
it by `1/32768`. It retains channel zero rather than averaging stereo channels.
The byte count is shifted right once at `0x4F91CD`; an odd trailing byte is
ignored. An odd word count still emits its final channel-zero sample.

[Readable C++ and reproducible tests](../recovered/flac-pcm/) recover this
algorithm slice. The interface returns the number of samples written; this is
a testable extraction, not the complete wrapper's original ABI. The surrounding
wrapper increments its output position by `1 + ((words - 1) >> 1)` when words
are positive. Neither the decoder, metadata handling, allocation/error paths,
nor the full resampling DSP has been source-reconstructed here.

The comparison first verifies the supported EXE hash, the exact 34-byte loop
and the float constant at `0xA06428`. It then executes that loop through a
test-only ABI adapter and compares the C++ results, counts, preserved input and
output guards. All 65,536 signed sample values and byte lengths 0 through 4,096
passed. MSVC 18.00.40629 on native Windows compiled the implementation with
`/O1`, `/O2`, and `/O2 /Oy-`. Windows compilation alone is not a runtime check
or a byte match. This is behavior-validated, unmatched high-level source and
adds zero certified matching-source bytes. The assembly is a transcribed test
oracle with zero coverage credit.

From the repository root, with an independently preserved original:

```sh
distrobox enter development -- make -C Decomp/recovered/flac-pcm \
  GAME=/absolute/path/to/original/Game.exe test
```

## Provenance and limits

The pre-patch ReRiff baseline is commit
`53d35aa031f9db10a9499df78d391e786ae8a728`. Its
`ExperimentalMenu/engine_menu.c` has no FLAC hook. The subsequent working-tree
patch adds `flac_sample_rate.h` and calls `install_flac_sample_rate` after the
existing executable checks and DLL lifetime pin. That patch redirects the
original worker CALL and adds resampling; those intentional changes are not
part of this reconstruction. Exact before-file and patch-source hashes are in
[provenance.json](../recovered/flac-pcm/provenance.json).

The original worker/wrapper disassembly was freshly extracted from the
hash-checked EXE. Ghidra exports are retained as research leads, not accepted
source: their inferred prototypes and unassigned register parameters require
review. The retained `analyse` IL confirms its duration calculation converts
each integer operand to float and then double, divides, and converts the result
to float. Do not replace that sequence with an assumed direct float division.

The earlier sample-rate and full-DSP results above are retained from ReRiff's
FLAC investigation, not rerun or certified by this integration. Only the PCM
conversion checks described here were rerun. The other managed tokens and
resampler ABI remain separately recorded research; this partial recovery does
not validate every earlier claim or establish completed in-game behavior.
