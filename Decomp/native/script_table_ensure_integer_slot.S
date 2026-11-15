# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f0cc0,0x4f0d0d); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_table_ensure_integer_slot
.equ GET_INTEGER,0x4f0ae0
.equ NEW_KEY,0x4f09e0
.equ NIL_VALUE,0x99a41c
original_script_table_ensure_integer_slot:
 push ebp
 mov.s ebp,esp
 and esp,-8
 sub esp,8
 push ebx
 push esi
 mov.s esi,edx
 mov.s ebx,ecx
 mov edx,DWORD PTR [ebp+8]
 mov.s ecx,esi
 call GET_INTEGER
 cmp eax,NIL_VALUE
 jne .Lreturn
 # Missing integer key: construct an eight-byte numeric tagged value.
 movd xmm0,DWORD PTR [ebp+8]
 lea eax,[esp+8]
 cvtdq2ps xmm0,xmm0
 push eax
 mov.s edx,esi
 mov DWORD PTR [esp+0x10],3
 mov.s ecx,ebx
 movss DWORD PTR [esp+0xc],xmm0
 call NEW_KEY
 add esp,4
.Lreturn:
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
