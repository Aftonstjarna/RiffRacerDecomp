# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4ef9a0,0x4ef9da); external dispatch table at 0x4ef9dc.
.intel_syntax noprefix
.code32
.text
.global original_script_value_raw_equal
.equ DISPATCH,0x4ef9dc
original_script_value_raw_equal:
 mov eax,DWORD PTR [ecx+4]
 cmp eax,DWORD PTR [edx+4]
 je .Lsame_tag
.Lfalse:
 xor.s eax,eax
 ret
.Lsame_tag:
 cmp eax,3
 ja .Lidentity
 jmp DWORD PTR [eax*4+DISPATCH]
.Lnil:
 mov eax,1
 ret
.Lnumber:
 movss xmm0,DWORD PTR [ecx]
 ucomiss xmm0,DWORD PTR [edx]
 lahf
 test ah,0x44
 jp .Lfalse
 mov eax,1
 ret
.Lidentity:
 mov ecx,DWORD PTR [ecx]
 xor.s eax,eax
 cmp ecx,DWORD PTR [edx]
 sete al
 ret
.section .note.GNU-stack,"",@progbits
