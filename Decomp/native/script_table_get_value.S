# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f0bb0,0x4f0c36). External jump table and padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_table_get_value
.equ GET_STRING,0x4f0b70
.equ GET_INTEGER,0x4f0ae0
.equ MAIN_BUCKET,0x4f0110
.equ DISPATCH,0x4f0c38
.equ NIL_VALUE,0x99a41c
original_script_table_get_value:
 push esi
 mov.s esi,edx
 push edi
 mov edi,DWORD PTR [esi+4]
 mov.s eax,edi
 sub eax,0
 je .Lnil
 sub eax,3
 je .Lnumber
 dec eax
 jne .Lgeneric
 mov edx,DWORD PTR [esi]
 pop edi
 pop esi
 jmp GET_STRING
.Lnumber:
 cvttss2si edx,DWORD PTR [esi]
 movd xmm0,edx
 cvtdq2ps xmm0,xmm0
 ucomiss xmm0,DWORD PTR [esi]
 lahf
 test ah,0x44
 jp .Lgeneric
 pop edi
 pop esi
 jmp GET_INTEGER
.Lgeneric:
 mov.s edx,esi
 call MAIN_BUCKET
 mov.s ecx,eax
.Lprobe:
 mov eax,DWORD PTR [ecx+0xc]
 cmp.s eax,edi
 jne .Lnext
 cmp eax,3
 ja .Lidentity
 jmp DWORD PTR [eax*4+DISPATCH]
.Lfloat:
 movss xmm0,DWORD PTR [ecx+8]
 ucomiss xmm0,DWORD PTR [esi]
 lahf
 test ah,0x44
 jp .Lnext
.Lfound:
 pop edi
 mov.s eax,ecx
 pop esi
 ret
.Lidentity:
 mov eax,DWORD PTR [ecx+8]
 xor.s edx,edx
 cmp eax,DWORD PTR [esi]
 sete dl
 test edx,edx
 jne .Lfound
.Lnext:
 mov ecx,DWORD PTR [ecx+0x10]
 test ecx,ecx
 jne .Lprobe
.Lnil:
 pop edi
 mov eax,NIL_VALUE
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
