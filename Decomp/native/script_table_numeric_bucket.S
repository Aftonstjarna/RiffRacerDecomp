.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f00c0,0x4f0106); both returns included, INT3 padding excluded.
.global original_script_table_numeric_bucket
.equ FLOAT_ZERO,0xa063ec
original_script_table_numeric_bucket:
 push ebp
 mov.s ebp,esp
 push ecx
 ucomiss xmm1,DWORD PTR [FLOAT_ZERO]
 push edi
 mov.s edi,ecx
 movss DWORD PTR [ebp-4],xmm1
 lahf
 test ah,0x44
 jp .Lhash
 mov eax,DWORD PTR [edi+0x10]
 pop edi
 mov.s esp,ebp
 pop ebp
 ret
.Lhash:
 mov cl,BYTE PTR [edi+7]
 xor.s edx,edx
 mov eax,DWORD PTR [ebp-4]
 push esi
 mov esi,1
 shl esi,cl
 dec esi
 or esi,1
 div esi
 mov eax,DWORD PTR [edi+0x10]
 pop esi
 pop edi
 lea ecx,[edx+edx*4]
 lea eax,[eax+ecx*4]
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
