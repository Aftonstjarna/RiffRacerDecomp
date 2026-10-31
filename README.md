# Riff Racer original EXE reconstruction

This repository tracks the original Windows Game.exe reconstruction separately
from the ReRiff Linux port and server restoration work. The baseline objective
is a source-built executable matching all 8,635,392 original bytes.

The authoritative verified source-built fragment coverage is recorded in
[verification/coverage.json](verification/coverage.json). No complete matching
EXE has been produced. Extracted bytes and analysis output receive no reconstruction credit.

Build and verify using the existing development Distrobox:

```sh
distrobox enter development -- bash -lc 'cd /home/afton/.dev/RiffRacer && make -C Decomp OUT=../build/decomp-container coverage test-draft -j2'
```

The original executable is read from the default Steam installation; override
`GAME` in make if needed. Its required SHA-256 is
`2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2`.
See [reconstruction instructions](Decomp/README.md) and
[recovered spans](Decomp/native/STARTUP.md).

## Repository separation

The initial source snapshot comes from `/var/home/afton/.dev/ReRiff/Decomp`.
That workspace is preserved. Continue EXE recovery in this repository.
`Decomp/support` contains the existing verifier's shared header dependencies,
including the MIT-licensed nlohmann JSON header. These are tool support, not
recovered game code, and earn no byte credit. No Linux viewer is included.

Existing local analysis files are preserved and ignored by Git. Ghidra research
exports were copied locally for continuity; they are not matching source.
The existing Ghidra database remains `/tmp/reriff-ghidra/ReRiffNative` inside
development, and the export script now resolves this repository's paths.
The previous workspace README is retained in `docs/previous-workspace-readme.md`.
The canonical remote is https://github.com/Aftonstjarna/RiffRacerDecomp,
with matching reconstruction on `decomp`. ReRiff server, launcher and native-port
work remains in https://github.com/Aftonstjarna/ReRiff.
The local repository and queue worktree paths remain unchanged.
