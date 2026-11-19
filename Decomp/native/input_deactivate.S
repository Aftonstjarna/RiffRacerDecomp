.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x48d240.
.equ xinput_slot,0x92d61c
.equ memset_thunk,0x8f8d7e
.global original_input_deactivate
original_input_deactivate:
 push esi
 {load} mov esi,ecx
 push 0
 mov byte ptr [esi+0x140],0
 call dword ptr [xinput_slot]
 push 0x100
 mov dword ptr [esi+0x18],0
 lea eax,[esi+0x40]
 mov dword ptr [esi+0x1c],0
 mov dword ptr [esi+0x20],0
 mov dword ptr [esi+0x24],0
 mov dword ptr [esi+0x28],0
 push 0
 push eax
 mov dword ptr [esi+0x2c],0
 mov dword ptr [esi+0x34],0
 mov dword ptr [esi+0x30],0
 mov dword ptr [esi+0x38],0
 call memset_thunk
 add esp,0xc
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
