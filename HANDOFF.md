# Bounded recovery: shader constructor 0x005788C0

Completed only the assigned Drift constructor. Added reviewed mnemonic source
`Decomp/native/shader_drift_ctor.S`, fixed-address build/test target
`test-shader-drift`, and registry span RVA `0x1788C0`, length 149. Detailed
provenance, ABI and exception review are in `Decomp/native/SHADERS.md`.

Evidence: existing Ghidra export `analysis/ghidra/recovery/005788c0.txt`,
original Game.exe instructions through RET 4 at 0x00578952, original finalizer
call site, and original driftIconParams string at 0x00A0178C. Supported original
SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
Ghidra's inferred signature misses the unused stack argument. Preserved ECX
object/EAX return, RET 4, ESI/EBP, FS:[0], cookie setup and state -1 to 0.

Validation ran inside a development Distrobox, from the recovery worktree root:

```
make -C Decomp OUT=../build/decomp-container coverage test-draft -j2
```

All registered comparisons, matching/IL regression tests, and assembly drafter
roundtrip/rejection tests passed. New fragment: 149/149 equal, zero differences,
zero masks; SHA-256 c1b508dc554c24ef34d5af2f78dfb5ce55edb9510da403bd16ba72212fe98950.
Local outputs: `build/decomp-container/shader-drift-ctor-comparison.json`,
`coverage.json`, and `cloud-validation.log`. Updated tracked coverage snapshot
and README only after successful comparison. Total: 62,317 / 8,635,392 bytes
(0.72164645%), all 82 fragments exact. Full executable rebuild remains unverified.

Unresolved dependencies outside this function: original vtable 0x00A01734,
string/data placement, memset 0x008F8D7E, runtime handler dispatch 0x008F8968
and unwind metadata 0x00B7D1E0. Basic2d constructor and handler thunk are already
registered; this change does not count them twice. Metadata cleanup semantics
are not inferred or replaced. Driving remains disabled.

Exact next action: coordinator reviews the 149-byte source and comparison
report, then preserves these uncommitted changes. For subsequent independently
scoped recovery, inspect original unwind metadata at 0x00B7D1E0 and dispatch
0x008F8968 before claiming recovered exception cleanup semantics. No changes
to verifier implementation, original game, shared Ghidra database, canonical
workspace, branches or commits were made.
