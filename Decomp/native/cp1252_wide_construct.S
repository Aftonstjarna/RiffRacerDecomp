# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x44f3e0,0x44f486); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_cp1252_wide_construct
.equ MULTIBYTE_TO_WIDE_CHAR,0x92d10c
.equ ARRAY_NEW,0x8f87c8
.equ WIDE_RANGE_CONSTRUCT,0x44ff80
.equ ARRAY_DELETE_SLOT,0x92d4a0
original_cp1252_wide_construct:
 push ebp
 mov.s ebp,esp
 sub esp,0xc
 push ebx
 push esi
 push 0
 push 0
 push -1
 mov.s ebx,edx
 mov DWORD PTR [ebp-8],ecx
 push ebx
 push 0
 push 0x4e4
 mov DWORD PTR [ebp-0xc],0
 call DWORD PTR [MULTIBYTE_TO_WIDE_CHAR]
 xor.s ecx,ecx
 mov.s esi,eax
 mov edx,2
 mul edx
 seto cl
 neg ecx
 or.s ecx,eax
 push ecx
 call ARRAY_NEW
 add esp,4
 push esi
 mov.s esi,eax
 push esi
 push -1
 push ebx
 push 0
 push 0x4e4
 call DWORD PTR [MULTIBYTE_TO_WIDE_CHAR]
 mov.s ecx,esi
 lea edx,[ecx+2]
 {disp8} lea esp,[esp+0]
.scan:
 mov ax,WORD PTR [ecx]
 add ecx,2
 test ax,ax
 jne .scan
 mov ebx,DWORD PTR [ebp-8]
 sub.s ecx,edx
 push DWORD PTR [ebp-8]
 sar ecx,1
 xor.s eax,eax
 mov DWORD PTR [ebx+0x14],7
 mov DWORD PTR [ebx+0x10],0
 mov WORD PTR [ebx],ax
 lea eax,[esi+ecx*2]
 push eax
 push esi
 mov.s ecx,ebx
 call WIDE_RANGE_CONSTRUCT
 push esi
 call DWORD PTR [ARRAY_DELETE_SLOT]
 add esp,4
 mov.s eax,ebx
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
