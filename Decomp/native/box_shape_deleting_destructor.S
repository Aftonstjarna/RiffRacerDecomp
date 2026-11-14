# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x439180,0x4391a9); surrounding INT3 padding excluded.
# ECX=this; stack flags; EAX=this; callee pops 4 bytes.
.intel_syntax noprefix
.code32
.text
.equ BASE_VTABLE,0x9fb0b8
.equ FREE_COUNT,0xbfcc18
.equ FREE_CALLBACK,0x99a0bc
.global original_box_shape_deleting_destructor
original_box_shape_deleting_destructor:
 push ebp
 mov.s ebp,esp
 test BYTE PTR [ebp+8],1
 push esi
 mov.s esi,ecx
 mov DWORD PTR [esi],BASE_VTABLE
 je done
 inc DWORD PTR [FREE_COUNT]
 push esi
 call DWORD PTR [FREE_CALLBACK]
 add esp,4
done:
 mov.s eax,esi
 pop esi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
