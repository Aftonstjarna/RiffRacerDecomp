# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x416700,0x416721); both RET 4 paths included, INT3 padding excluded.
# ECX=string object; stack argument=new length; unsigned capacity threshold 16.
.intel_syntax noprefix
.code32
.text
.global original_narrow_set_length
original_narrow_set_length:
 push ebp
 mov.s ebp,esp
 cmp DWORD PTR [ecx+0x14],0x10
 mov edx,DWORD PTR [ebp+8]
 mov DWORD PTR [ecx+0x10],edx
 jb .Linline
 mov eax,DWORD PTR [ecx]
 mov BYTE PTR [eax+edx],0
 pop ebp
 ret 4
.Linline:
 mov BYTE PTR [ecx+edx],0
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
