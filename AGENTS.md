# Original-game recovery
- Faithful Game.exe recovery belongs on branch `decomp`, including useful
  non-byte-matching source backed by original evidence and behavioral checks.
  Reserve `redux` for intentional behavior changes.

- Use suitable tools from the explicitly supplied project/tool directories to
  accelerate recovery. Use Ghidra for native analysis and ILSpy for managed IL;
  validate recovered behavior against original code, data and execution evidence.
  Claims of exact matching additionally require an actual byte comparison.
- Report byte progress when committing or when requested, with whole-file and
  `.text` fractions and percentages for each tier. Separate compiler-built
  matching source, assembly reference evidence and behavior-validated source.
  Do not call assembly totals overall recovery/port completion or invent a
  behavioral-completion percentage without a defined, audited denominator.

- Continue recovery unattended within the authorized scope. Do not stop for
  routine confirmations or small progress checkpoints; ask the user only for
  an unresolved error, missing input, or a decision that genuinely needs them.

- Use a Distrobox development container for commands and builds, working
  from the repository root. Examples use `distrobox enter development -- ...`;
  substitute your container name. Install needed build packages inside the
  container rather than on the host. Container verification outputs currently
  use `build/decomp-container`.

- Prioritize understandable, maintainable recovery that helps faithful native
  porting and modding. A 100% byte-identical EXE is an optional research target,
  not a prerequisite; lack of the original compiler must not block useful
  source recovery and behavioral validation with other toolchains.
- Continue recovering Game.exe behavior. Leave the user's working DLL changes
  for track generation/sync-server support alone; they are intentional patches.
- Keep original reconstruction and the native Linux C++ port distinct. Numerical
  parity on sampled inputs does not establish a matching decompilation.
- Do not claim a matching rebuild without compiling recovered source and comparing
  the entire resulting executable against the supported original, including
  headers, metadata, native code, resources, padding and trailing data. Do not mask
  differences or count copied original bytes as reconstructed source.
- Preserve exact original IL, tokens, native disassembly, data and provenance.
  Record unresolved reconstruction/build/toolchain gaps explicitly.
- For nonmatching source, record original addresses/tokens, ABI/data layouts,
  tested inputs/outputs and side effects, known differences and untested paths.
  Keep transcribed assembly's origin distinct from semantic review; byte
  equality, renamed labels or comments alone do not certify source recovery.
- Use original code and assets, not invented substitute gameplay or physics.
  Substantive new implementation must be C++/C or Rust; Python only for simple tools.
- Continue to keep driving disabled until the original force/contact integration
  is recovered. Preserve existing uncommitted work.
