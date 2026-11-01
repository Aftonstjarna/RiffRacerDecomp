# Original-byte meanings learned through ReRiff

ReRiff's experimental client has newer reverse-engineering findings than this
repository's matching source. This ledger records leads and their provenance;
it grants no coverage credit. Original symbols/IL may already exist in ignored
analysis exports without the semantics, corrections or runtime observations
being incorporated into reconstructed source.

All current-build addresses below refer to the supported 8,635,392-byte Game.exe,
SHA256 `2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2`.
VAs assume image base 0x400000. Do not confuse a CLR import/fixup thunk with the
managed method it resolves to. Hash guards and successful mod behavior are useful
evidence, not a substitute for independently compiling and comparing each span.

## Menu fields, functions and input

Source: `/var/home/afton/.dev/ReRiff/ExperimentalMenu/ENGINE-MENU.md`,
`engine_menu.c`, `settings_scroll.h`, `test_engine.c`, and
`ClientConfig/NativeReelBridge.cs`.

- `gaOptionsMenu` vtable VA 0xBA5A7C. Documented callbacks include tick slot 3,
  initScreens 15, cleanup 16, input 24 and updateItemColour 26. ReRiff maps their
  native thunks, fixup slots and CLR metadata tokens separately.
- Options state +248; title +144; screen +184; main/audio groups +268/+332;
  original option text pointers start at +272.
- Text item position +32/+36; extents +48/+52; enabled mask +76; interaction
  latch +356; visibility bit 0 at +372. Re-enabling every frame clears the
  interaction latch, disrupting mouse press/release despite controller input
  still working. Preserve the original latch by enabling only when needed.
- Original direction handling at VA 0x44AA60 uses mode 1 at item +0x98 and
  Up/Down target IDs at +0x9C/+0xA0.
- Native reel methods are identified by tokens 0x06001138, 0x0600113B,
  0x0600113C, 0x0600113D, 0x0600113E, 0x06001140 and 0x06001142. These cover
  construction, adding options, scrolling limits, tick, movement, selection and
  scrollbar creation. ReRiff invokes the original methods rather than replacing
  native scrolling. Owning SSP arguments require their original ABI treatment.
- ReRiff also identified menu-group visibility, stale Audio input latches,
  screen cleanup and focus timing through native integration tests.

The recovery repository's older `0044b4a0.txt` export alone is not this full
knowledge: it lists a six-byte thunk, not the complete implementation/lifecycle.

## Renderer and UI scaling

Source: the same ENGINE-MENU document, `display_modes.h`, `antialiasing.h`,
`ui_scale.h`, `ui_scale_tables.h`, and their tests.

- The public `wsGraphicsDevice` singleton at RVA 0x80D408 is a command wrapper,
  with primary vtable RVA 0x5FBF44. Its PC interface at +0x18 forwards commands;
  it is not an embedded render backend.
- VA 0x497020 reads backend global VA 0xBFCC44. Lazy initialization at 0x5CFB60
  allocates 0xBBC bytes and calls 0x49FD30. The backend is non-polymorphic;
  D3D9 device pointers are +0x78 and optional Ex +0x7C. This corrects two
  earlier ReRiff interpretations; use the corrected layout.
- Original graphics confirmation is `gaGraphicsConfirm`, state 26, table RVA
  0x7A5918. Resolution application and rejection reuse this native lifecycle.
- Managed tokens 0x060010DC and 0x060012A5 identify
  `gaGame.onResolutionAdjusted` and `gaStateManager.rescaleMenus`.
- UI scaling research separates physical pointer/render coordinates, logical
  menu dimensions, font setup and the native background effect. ReRiff's new
  scaling behavior itself belongs to mod work, not matching reconstruction.

Some renderer meanings overlap the recovered FRAME.md/device source. The newer
wrapper/backend correction and UI integration evidence should be cross-checked
against that existing knowledge rather than counted as wholly new discovery.

## Song cache

Source: `/var/home/afton/.dev/ReRiff/NativeLauncher/song_sync.h`, derived from
original `gaSaveGame.writeSongCache` IL.

The v19 cache has a 16-byte header, then seven NUL-terminated UTF-8 strings and
29 scalar bytes per record. ReRiff identifies filename, song ID, title and artist
and validates the header and record bounds. This is useful data-format knowledge,
not evidence that the original serializer has been source-reconstructed.

## Audio: distinguish the two executable builds

Source: `/var/home/afton/.dev/ReRiff/reports/M4A-DECODER-COMPARISON.md` and its
private original-byte/Ghidra evidence. The older supplied executable has SHA256
`ba9913af9c788b68f30defd311edfa5b9c0dc07d19edf4b34c4123f23bdb98ce`.

- Decode-worker VA 0x48D9C0 exists in both builds. The older build's dispatch
  handles M4A; the supported newer build lacks that extension branch despite
  retaining M4A in the picker strings. Imports alone do not explain this loss.
- **Older build only:** wrapper VA 0x4F91F0 checks MP4 `ftyp`, selects an audio
  track and decodes packets. Loop 0x4F94B0 converts signed 16-bit samples from
  the first channel with stride equal to channel count. The float at 0xA23780
  is exactly 1/32768. It does not average stereo channels.
- Those old-build addresses must not be transplanted into the supported
  executable. An intentional M4A restoration belongs to ReRiff/redux; the
  differing original decoder behavior belongs in recovery provenance.

## How to promote a lead

Retain the original hash, VA/RVA or metadata token, caller/callee and object
layout evidence. Recheck original IL/native bytes, recover a source-built span,
and pass the strict comparator before adding coverage. Keep observed mod
behavior, inferred prototypes and independently verified original semantics
distinct. None of this ledger claims a complete matching executable.
