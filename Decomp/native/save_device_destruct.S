.intel_syntax noprefix
.code32
# Provenance: supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Original objdump instructions and private Ghidra exports 00535770/005357a0.
.equ imported_operator_delete,0x92d4b0
.equ ws_save_device_primary_vtable,0x9ffe2c
.equ ws_save_device_secondary_vtable,0x9ffe6c
.equ el_save_device_vtable,0x9f99d8
# ECX=this; scalar deleting wrapper takes a stack flag and returns this in EAX.
# Callee preserves ESI; wrapper pops its flag. No local EH registration or data.
.section .save_device_dispose,"ax"
.global original_save_device_dispose
original_save_device_dispose:
 push ebp
 {load} mov ebp,esp
 push esi
 {load} mov esi,ecx
 call original_save_device_destruct
 test BYTE PTR [ebp+8],1
 je .dispose_return
 push esi
 call DWORD PTR [imported_operator_delete]
 add esp,4
.dispose_return:
 {load} mov eax,esi
 pop esi
 pop ebp
 ret 4

.section .save_device_destruct,"ax"
.global original_save_device_destruct
# Ordinary thiscall destructor: destroy wide-string storage at +2c then +14.
# Capacity >=8 selects heap ownership; reset capacity=7, length=0, first WCHAR=0.
# Vtables and imported deallocator remain symbolic-address dependencies. Calls
# propagate any exception directly; no synthesized cleanup or file-close call.
original_save_device_destruct:
 push esi
 {load} mov esi,ecx
 mov DWORD PTR [esi],offset ws_save_device_primary_vtable
 mov DWORD PTR [esi+8],offset ws_save_device_secondary_vtable
 cmp DWORD PTR [esi+0x40],8
 jb .second_inline
 push DWORD PTR [esi+0x2c]
 call DWORD PTR [imported_operator_delete]
 add esp,4
.second_inline:
 {load} xor eax,eax
 mov DWORD PTR [esi+0x40],7
 mov DWORD PTR [esi+0x3c],0
 mov WORD PTR [esi+0x2c],ax
 cmp DWORD PTR [esi+0x28],8
 jb .first_inline
 push DWORD PTR [esi+0x14]
 call DWORD PTR [imported_operator_delete]
 add esp,4
.first_inline:
 mov DWORD PTR [esi+0x28],7
 {load} xor eax,eax
 mov DWORD PTR [esi+0x24],0
 mov WORD PTR [esi+0x14],ax
 mov DWORD PTR [esi],offset el_save_device_vtable
 pop esi
 ret
