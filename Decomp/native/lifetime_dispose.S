# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original objdump and private Ghidra exception-exports in
# /tmp/reriff-recovery-resume; fresh instructions/imports/vtables/caller in
# /tmp/reriff-lifetime-review. Address names deliberately do not assert a class.
# ECX=complete object; preserve ESI, call body, delete iff stack flag bit 0.
# Return complete this in EAX, RET 4. Vtable 0x9fa118 first slot points here.
# Body exception propagates before deletion: no local EH registration/data.
# Original VA range 0x44eae0..0x44eb02
.intel_syntax noprefix
.code32
.text
.global original_lifetime_dispose
original_lifetime_dispose:
.L44eae0:
 push   ebp
.L44eae1:
 {load} mov    ebp,esp
.L44eae3:
 push   esi
.L44eae4:
 {load} mov    esi,ecx
.L44eae6:
 call target_44eb10
.L44eaeb:
 test   BYTE PTR [ebp+0x8],0x1
.L44eaef:
 je .L44eafb
.L44eaf1:
 push   esi
.L44eaf2:
 call   DWORD PTR [imported_operator_delete]
.L44eaf8:
 add    esp,0x4
.L44eafb:
 {load} mov    eax,esi
.L44eafd:
 pop    esi
.L44eafe:
 pop    ebp
.L44eaff:
 ret    0x4
.equ target_44eb10,0x44eb10
.equ imported_operator_delete,0x92d4b0
