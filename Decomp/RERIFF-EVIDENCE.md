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


## November 1 UI research: verified facts and remaining gaps

- Native UI dimensions come from `elUI.getResolution`, VA 0x0041FA50, including
  ratio floats at RVAs 0x7AACAC/0x7AACB0. These are distinct from the public
  graphics device resolution. ReRiff Auto mode retains the original behavior.
- Original `gaMenu.setupStandardBackground` (IL RVA 0x2DD3C0) centers its visual
  during creation. `gaMenu.applyBackgroundEffect` (token 0x0600112F, IL RVA
  0x2E1FF8) recomputes cover scale and animated zoom; it does not recenter the
  existing visual. These distinct responsibilities matter when a mod changes
  logical UI dimensions. The mod itself is not matching reconstruction.
- Native Settings uses menu transition state 0 when ready for input; state 1
  must not be substituted as an idle guard. The original Audio tick remains
  the authority for its repeat masks, mouse drag and slider artwork.
- `elUIScreen.getRenderGroup` (token 0x060010FA) reads screen +8. That group is
  optional: the native add routine at VA 0x0048E8D0 checks for null before
  assigning it to an item through vtable slot 18. A mod may not assume all PC
  menu screens already have a group. Rendering semantics and a correct manual
  UI-scaling integration remain unresolved; failed experiments receive no credit.
- `elMatrix.scaleBy` is now an exact separately source-built 146-byte fragment;
  see `native/UI-MATRIX.md`. This does not validate a ReRiff manual UI transform.

## Graphics selector and scrolling visibility

Checked against the original supported executable's CLI MethodDef table and IL:

- `gaGraphicsOptions.showResolutionText`: token 0x06001177, IL RVA 0x2EC76C,
  code size 186 bytes. Selection lives at menu +300; text-vector begin/end at
  +280/+284. It wraps indices using the display-mode vector at +268/+272,
  returns without changing visibility when the selected index is unchanged,
  otherwise hides all text entries and shows the selected entry. Therefore a
  scrolling mod must restore the selected label after hiding it; an unchanged
  call to this function will not restore visibility.
- `elUI.createButtonSprite`: token 0x060016E5, native RVA 0x222C0. Original
  `gaGraphicsOptions.initScreens` creates resolution buttons with sprites 59/60,
  IDs 1/2, shortcut mask 0, and origins 3/5. ReRiff's fullscreen selector extends
  this original factory/artwork/input instead of creating another repeat system.

These are verified original semantics and mod-integration evidence, not new
source-built reconstruction. Verified coverage remains 67,275 / 8,635,392 bytes
(0.77906133%); this documentation adds no matching-byte credit.

## Native Apply selection and reusable save-prompt evidence

Checked against supported original Game.exe metadata, IL and native instructions:

- `gaGraphicsOptions.initScreens` (IL RVA 0x2EDD4C), IL offsets
  0x0ABD..0x0AD4, clears bit 1 at Apply item +372 using AND 253. Apply is
  the existing sprite-35 button with ID 3; disabling directional selection
  is deliberate original behavior, not evidence of a missing sprite.
- `elUIItem.setAsMenuItem`, token 0x060016AA, native VA 0x44B530, sets
  both flag bits 1 and 2 at item +372 from its boolean argument. The original
  instructions at 0x44B56F..0x44B592 establish these writes. The routine also
  assigns the native menu material; it is not merely a raw bit-1 setter.
  Input masks at +76 remain a separate concern. ReRiff's test doubles were
  extended to check focus/highlight and screen-mask integration; actual
  controller/hover behavior remains a live mod-validation question.
- `gaQuitConfirmMenu` is overlay state 9, established by its original ctor
  (IL RVA 0x3607F8). Its original input handler (IL RVA 0x360B14) uses selection
  2 for quit and otherwise pops the overlay except for -1. Its original Back
  handling (IL RVA 0x360B6C) pops the overlay directly. A save/discard adaptation
  must intercept the quit action and distinguish Back from an explicit choice.
- `gaStateManager.setOverlayState` / `popOverlayState` are tokens
  0x0600129B/0x0600129C, IL RVAs 0x2FE0A0/0x2FDFC4. The manager singleton is
  RVA 0x7EEFE0; its current overlay pointer is +44. ReRiff reuses these methods
  and the original dialog art/lifecycle, deferring callbacks until removal.

These are original-function findings and intentional mod integration, not
additional reconstructed spans. This ledger claims no new matching-byte credit.

## Original Graphics toggle and Audio slider input (2026-11-01)

Reference: DepotDownloader depot 351991, build 1687655, manifest
8951408038967536554; Game.exe SHA-256
`2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2`.

- `gaGraphicsOptions.setTogglebarVars`, token `0x0600117D`, chooses thumb
  sprite 75/74 and origin 3/5 from the fullscreen byte at menu +305. It copies
  the bar position, subtracts bar width times menu +60 scale only when Off, and
  adds +25 or -25 times that scale for Off or On. ReRiff's alignment regression
  came from subsequently restoring an old thumb position in its added scrolling
  layout; that is an intentional mod integration error, not original behaviour.
- `gaOptionsMenu.tick`, token `0x0600119A`, polls native Left/Right masks
  256/512 through pressed and held-repeat methods. The UI Scale adaptation must
  retain one input owner rather than also activating button shortcuts.
- Native direction handler VA `0x44AA60` uses +0x98 navigation mode; mode 1
  selects +0x9C/+0xA0 for Up/Down and +0xA4/+0xA8 for Left/Right. At VA
  `0x44AAF3`, bytes `83 F8 FF 74 66` compare the target to -1 and branch to
  VA `0x44AB5E` without changing focus. Verified from original objdump output.

This is original metadata/instruction evidence and mod integration guidance.
No reconstructed source span or additional matching-byte credit is claimed.
