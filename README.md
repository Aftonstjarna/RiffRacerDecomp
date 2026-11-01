# Riff Racer original EXE reconstruction

This repository tracks the original Windows Game.exe reconstruction separately
from port and server restoration work. The baseline objective
is a source-built executable matching all 8,635,392 original bytes.

Verified source-built fragment coverage: **68,751 / 8,635,392 bytes (0.79615%)**.

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

## Project goals

### Recover the original game

Reconstruct the original Windows executable from source and verify it byte for
byte, including code, metadata, resources and executable layout. This matching
baseline comes first: it establishes the original behavior before porting or
gameplay changes are introduced.

### Enable a faithful native Linux port

Use recovered code and original asset formats to reproduce track generation,
spline evaluation, road orientation, vehicle physics, rendering and music
synchronization on Linux. The goal is the original game's behavior on a native
runtime, grounded in its implementation rather than approximate replacements.
Port development remains separate from matching reconstruction; this repository
does not yet provide a complete matching executable or a playable native port.

### Build a foundation for modding

Make the game's systems and data formats understandable enough to support
deliberate changes to vehicles, tracks, visuals and gameplay. Keep modifications
separate from the verified baseline so their effects can be identified and
tested against original behavior. Modding tools and extension points are future
goals, not currently supported features.

Matching recovery belongs on `decomp`; intentional behavior changes belong on
`redux` or dedicated modification branches. The modified server, launcher and
current native-port work remain in [ReRiff](https://github.com/Aftonstjarna/ReRiff).
