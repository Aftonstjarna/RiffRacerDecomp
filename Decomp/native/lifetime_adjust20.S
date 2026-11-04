# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original objdump and private Ghidra exception-exports in
# /tmp/reriff-recovery-resume; fresh instructions/imports/vtables/caller in
# /tmp/reriff-lifetime-review. Address names deliberately do not assert a class.
# ECX points to subobject +0x14; preserve stack flag and tail-dispatch.
# Original vtable 0x9fa1e4 first slot points here. No local EH/data.
# Original VA range 0x450057..0x45005f
.intel_syntax noprefix
.code32
.text
.global original_lifetime_adjust20
original_lifetime_adjust20:
.L450057:
 sub    ecx,0x14
.L45005a:
 jmp target_44eae0
.equ target_44eae0,0x44eae0
