# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original objdump and private Ghidra exception-exports in
# /tmp/reriff-recovery-resume; fresh instructions/imports/vtables/caller in
# /tmp/reriff-lifetime-review. Address names deliberately do not assert a class.
# ECX points to subobject +0x10; preserve stack flag and tail-dispatch.
# Original vtable 0x9fa1a8 slot at 0x9fa1dc points here. Shared target
# is registered separately; no duplicate extent, local EH or embedded data.
# Original VA range 0x45004f..0x450057
.intel_syntax noprefix
.code32
.text
.global original_lifetime_adjust16
original_lifetime_adjust16:
.L45004f:
 sub    ecx,0x10
.L450052:
 jmp target_44eae0
.equ target_44eae0,0x44eae0
