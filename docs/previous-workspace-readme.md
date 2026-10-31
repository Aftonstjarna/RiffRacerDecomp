# ReRiff

Riff Racer server restoration and native Linux reconstruction.

## Goals

1. Recover and document the client/server contract.
2. Restore persistent profiles, song records, scores, and ghost files.
3. Validate compatibility with the existing Windows client.
4. Reconstruct a native Linux client from documented behavior and recovered formats.

## Current evidence

The installed local Flask server returns canned responses, discards object writes,
and supplies a placeholder upload URL. ParseOctane.dll contains network operations
for account access, object commits, atomic increments, deletion, and file transfers.
Game.exe contains native x86 code and CLR metadata, and imports Direct3D 9,
XInput, X3DAudio, Windows APIs, and FFTW. A native Linux build requires recovered
source or a new implementation of these systems; the executable is not directly
portable source code.

## Analysis artifacts

`analysis/manifest.json` records input file hashes and sizes.
`analysis/assets.json` lists archive entries without extracting game assets.
`analysis/imports.txt` records executable imports.
The strings files contain ASCII and UTF-16 strings extracted from binaries.
These are investigation leads, not a verified protocol specification.

## Next investigation

Recover network call sites and query construction, then document class schemas,
file references, authentication behavior, and error handling before implementing
compatible persistence. Validate requests and responses against the original
client. Track generation and replay compatibility need separate investigation.

Original game files have not been changed. No game executables or assets are
included in this project. Extracted strings may contain proprietary material;
review artifacts before publishing them.
