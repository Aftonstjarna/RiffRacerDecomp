# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x434320,0x434366); INT3 padding excluded.
# ECX destination, stack source; ten ordered DWORD loads/stores, EAX=destination.
# Direct caller 0x432d69 selects a 40-byte record before vector arithmetic.
.intel_syntax noprefix
.code32
.text
.global original_record40_copy_assign
original_record40_copy_assign:
 push ebp
 mov.s ebp,esp
 mov edx,DWORD PTR [ebp+8]
 mov eax,DWORD PTR [edx]
 mov DWORD PTR [ecx],eax
 mov eax,DWORD PTR [edx+0x4]
 mov DWORD PTR [ecx+0x4],eax
 mov eax,DWORD PTR [edx+0x8]
 mov DWORD PTR [ecx+0x8],eax
 mov eax,DWORD PTR [edx+0xc]
 mov DWORD PTR [ecx+0xc],eax
 mov eax,DWORD PTR [edx+0x10]
 mov DWORD PTR [ecx+0x10],eax
 mov eax,DWORD PTR [edx+0x14]
 mov DWORD PTR [ecx+0x14],eax
 mov eax,DWORD PTR [edx+0x18]
 mov DWORD PTR [ecx+0x18],eax
 mov eax,DWORD PTR [edx+0x1c]
 mov DWORD PTR [ecx+0x1c],eax
 mov eax,DWORD PTR [edx+0x20]
 mov DWORD PTR [ecx+0x20],eax
 mov eax,DWORD PTR [edx+0x24]
 mov DWORD PTR [ecx+0x24],eax
 mov.s eax,ecx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
