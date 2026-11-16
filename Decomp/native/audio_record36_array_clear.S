.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x58b460; end 0x58b50a, exclusive.
.equ CRT_FREE_IAT,0x92d3a4
.global original_audio_record36_array_clear
original_audio_record36_array_clear:
 push   ebp
 {load} mov    ebp,esp
 sub    esp,0xc
 push   ebx
 mov    ebx,DWORD PTR [CRT_FREE_IAT]
 {load} mov    eax,edx
 push   esi
 push   edi
 {load} xor    edi,edi
 mov    DWORD PTR [ebp-0xc],eax
 {load} mov    esi,ecx
 mov    DWORD PTR [ebp-0x8],esi
 cmp    DWORD PTR [eax],edi
 jbe L_58b4ed
 {load} xor    eax,eax
 mov    DWORD PTR [ebp-0x4],eax
L_58b484:
 mov    esi,DWORD PTR [esi]
 {load} add    esi,eax
 mov    eax,DWORD PTR [esi+0x10]
 test   eax,eax
 je L_58b495
 push   eax
 call   ebx
 add    esp,0x4
L_58b495:
 mov    DWORD PTR [esi+0x10],0x0
 mov    DWORD PTR [esi+0x14],0x0
 mov    DWORD PTR [esi+0x18],0x0
 mov    eax,DWORD PTR [esi+0x4]
 test   eax,eax
 je L_58b4b7
 push   eax
 call   ebx
 add    esp,0x4
L_58b4b7:
 mov    DWORD PTR [esi+0x4],0x0
 mov    DWORD PTR [esi+0x8],0x0
 mov    DWORD PTR [esi+0xc],0x0
 mov    eax,DWORD PTR [esi+0x20]
 test   eax,eax
 je L_58b4d9
 push   eax
 call   ebx
 add    esp,0x4
L_58b4d9:
 mov    ecx,DWORD PTR [ebp-0xc]
 inc    edi
 mov    eax,DWORD PTR [ebp-0x4]
 mov    esi,DWORD PTR [ebp-0x8]
 add    eax,0x24
 mov    DWORD PTR [ebp-0x4],eax
 cmp    edi,DWORD PTR [ecx]
 jb L_58b484
L_58b4ed:
 push   DWORD PTR [esi]
 call   ebx
 mov    eax,DWORD PTR [ebp-0xc]
 add    esp,0x4
 mov    DWORD PTR [esi],0x0
 pop    edi
 pop    esi
 mov    DWORD PTR [eax],0x0
 pop    ebx
 {load} mov    esp,ebp
 pop    ebp
 ret
.section .note.GNU-stack,"",@progbits
