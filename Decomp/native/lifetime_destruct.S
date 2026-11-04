# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original objdump and private Ghidra exception-exports in
# /tmp/reriff-recovery-resume; fresh instructions/imports/vtables/caller in
# /tmp/reriff-lifetime-review. Address names deliberately do not assert a class.
# Thiscall body preserves EDI. Constructor 0x44e5d0 sets the same three
# vtables and singleton 0xc0d40c; its +0x130 member ctor is 0x48d6e0.
# Wait +0x380 indefinitely, set stop byte +0x38c, reset event +0x380,
# signal +0x37c, join thread +0x1c, destroy member +0x130, close thread.
# Restore base vtables; destroy [this+4,this+8) 24-byte narrow strings via
# 0x4268f0, free backing storage, zero three pointers and clear singleton.
# Keep original uninitialized allocator/tag stack operands [ebp-5], &[ebp-1];
# 0x4268f0 reads only its first two arguments. Do not invent initialization.
# No local SEH/EH registration, landing pad or embedded data in this extent;
# dependency exceptions propagate, with no synthesized cleanup. Padding excluded.
# Original VA range 0x44eb10..0x44ebda
.intel_syntax noprefix
.code32
.text
.global original_lifetime_destruct
original_lifetime_destruct:
.L44eb10:
 push   ebp
.L44eb11:
 {load} mov    ebp,esp
.L44eb13:
 sub    esp,0x8
.L44eb16:
 push   edi
.L44eb17:
 {load} mov    edi,ecx
.L44eb19:
 push   0xffffffff
.L44eb1b:
 push   DWORD PTR [edi+0x380]
.L44eb21:
 mov    DWORD PTR [edi],offset lifetime_primary_vtable
.L44eb27:
 mov    DWORD PTR [edi+0x10],offset lifetime_secondary16_vtable
.L44eb2e:
 mov    DWORD PTR [edi+0x14],offset lifetime_secondary20_vtable
.L44eb35:
 call   DWORD PTR [imported_WaitForSingleObject]
.L44eb3b:
 push   DWORD PTR [edi+0x380]
.L44eb41:
 mov    BYTE PTR [edi+0x38c],0x1
.L44eb48:
 call   DWORD PTR [imported_ResetEvent]
.L44eb4e:
 push   DWORD PTR [edi+0x37c]
.L44eb54:
 call   DWORD PTR [imported_SetEvent]
.L44eb5a:
 push   0xffffffff
.L44eb5c:
 push   DWORD PTR [edi+0x1c]
.L44eb5f:
 call   DWORD PTR [imported_WaitForSingleObject]
.L44eb65:
 lea    ecx,[edi+0x130]
.L44eb6b:
 call target_48d800
.L44eb70:
 push   DWORD PTR [edi+0x1c]
.L44eb73:
 mov    DWORD PTR [edi+0x14],offset base20_vtable
.L44eb7a:
 call   DWORD PTR [imported_CloseHandle]
.L44eb80:
 mov    DWORD PTR [edi+0x10],offset base16_vtable
.L44eb87:
 mov    DWORD PTR [edi],offset storage_base_vtable
.L44eb8d:
 mov    eax,DWORD PTR [edi+0x4]
.L44eb90:
 test   eax,eax
.L44eb92:
 je .L44ebc5
.L44eb94:
 push   DWORD PTR [ebp-0x5]
.L44eb97:
 lea    ecx,[ebp-0x1]
.L44eb9a:
 push   ecx
.L44eb9b:
 push   DWORD PTR [edi+0x8]
.L44eb9e:
 push   eax
.L44eb9f:
 call target_4268f0
.L44eba4:
 push   DWORD PTR [edi+0x4]
.L44eba7:
 call   DWORD PTR [imported_operator_delete]
.L44ebad:
 add    esp,0x14
.L44ebb0:
 mov    DWORD PTR [edi+0x4],0x0
.L44ebb7:
 mov    DWORD PTR [edi+0x8],0x0
.L44ebbe:
 mov    DWORD PTR [edi+0xc],0x0
.L44ebc5:
 mov    DWORD PTR [edi],offset final_base_vtable
.L44ebcb:
 mov    DWORD PTR [lifetime_singleton],0x0
.L44ebd5:
 pop    edi
.L44ebd6:
 {load} mov    esp,ebp
.L44ebd8:
 pop    ebp
.L44ebd9:
 ret
.equ target_4268f0,0x4268f0
.equ target_48d800,0x48d800
.equ imported_operator_delete,0x92d4b0
.equ imported_WaitForSingleObject,0x92d124
.equ imported_ResetEvent,0x92d104
.equ imported_SetEvent,0x92d120
.equ imported_CloseHandle,0x92d0d4
.equ lifetime_singleton,0xc0d40c
.equ lifetime_primary_vtable,0x9fa118
.equ lifetime_secondary16_vtable,0x9fa1a8
.equ lifetime_secondary20_vtable,0x9fa1e4
.equ base20_vtable,0x9fbe20
.equ base16_vtable,0x9fa16c
.equ storage_base_vtable,0x9fbe38
.equ final_base_vtable,0x9fbe30
