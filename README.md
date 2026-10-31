# Riff Racer original EXE reconstruction

This repository tracks the original Windows Game.exe reconstruction separately
from the ReRiff Linux port and server restoration work. The baseline objective
is a source-built executable matching all 8,635,392 original bytes.

The authoritative verified source-built fragment coverage is recorded in
[verification/coverage.json](verification/coverage.json). No complete matching
EXE has been produced. Extracted bytes and analysis output receive no reconstruction credit.

From the repository root, build and verify inside a development Distrobox:

```sh
distrobox enter development -- make -C "$PWD/Decomp" OUT=../build/decomp-container coverage test-draft -j2
```

Replace `development` with your container name. The original executable is read
from `$HOME/.local/share/Steam/steamapps/common/Riff Racer/Game.exe` by default;
pass `GAME="/path/to/Riff Racer/Game.exe"` to make for another installation.
Its required SHA-256 is
`2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2`.
See [reconstruction instructions](Decomp/README.md) and
[recovered spans](Decomp/native/STARTUP.md).

## Repository separation

The initial source snapshot comes from ReRiff's `Decomp` directory.
Continue EXE recovery in this repository.
`Decomp/support` contains the existing verifier's shared header dependencies,
including the MIT-licensed nlohmann JSON header. These are tool support, not
recovered game code, and earn no byte credit. No Linux viewer is included.

Local analysis files and Ghidra research exports are ignored by Git; they are
not matching source. See [Ghidra instructions](Decomp/GHIDRA.md) for analysis setup.
The previous workspace README is retained in `docs/previous-workspace-readme.md`.
The canonical repository is [RiffRacerDecomp](https://github.com/Aftonstjarna/RiffRacerDecomp),
with matching reconstruction on `decomp`. Server, launcher and native-port
work remains in [ReRiff](https://github.com/Aftonstjarna/ReRiff).
