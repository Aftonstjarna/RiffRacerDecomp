# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x438560,0x4385e1). Construction record, including its matrix initializer call.
.intel_syntax noprefix
.code32
.text
.equ MATRIX64_INITIALIZE_BASIS,0x438480
.global original_body_construction_record_initialize
original_body_construction_record_initialize:
 push ebp
 {load} mov ebp,esp
 mov eax,DWORD PTR [ebp+8]
 push esi
 {load} mov esi,ecx
 mov DWORD PTR [esi+4],eax
 lea ecx,[esi+8]
 mov eax,DWORD PTR [ebp+12]
 mov DWORD PTR [esi+0x48],eax
 mov eax,DWORD PTR [ebp+16]
 movss DWORD PTR [esi],xmm1
 movdqu xmm0,XMMWORD PTR [eax]
 mov DWORD PTR [esi+0x5c],0
 mov DWORD PTR [esi+0x60],0
 movdqu XMMWORD PTR [esi+0x4c],xmm0
 mov DWORD PTR [esi+0x64],0x3f000000
 mov DWORD PTR [esi+0x68],0
 mov DWORD PTR [esi+0x6c],0x3f4ccccd
 mov DWORD PTR [esi+0x70],0x3f800000
 mov BYTE PTR [esi+0x74],0
 mov DWORD PTR [esi+0x78],0x3ba3d70a
 mov DWORD PTR [esi+0x7c],0x3c23d70a
 mov DWORD PTR [esi+0x80],0x3c23d70a
 mov DWORD PTR [esi+0x84],0x3c23d70a
 call MATRIX64_INITIALIZE_BASIS
 {load} mov eax,esi
 pop esi
 pop ebp
 ret 12
.section .note.GNU-stack,"",@progbits
