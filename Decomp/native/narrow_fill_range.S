.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x44fae0, exclusive end 0x44fb24.
.equ memset_import,0x8f8d7e
.global original_narrow_fill_range
original_narrow_fill_range:
 push ebp
 {load} mov ebp,esp
 mov eax,DWORD PTR [ebp+0xc]
 {load} mov edx,ecx
 cmp eax,1
 jne many
 cmp DWORD PTR [edx+0x14],0x10
 jb single_inline
 mov edx,DWORD PTR [edx]
single_inline:
 mov eax,DWORD PTR [ebp+8]
 mov cl,BYTE PTR [ebp+0x10]
 mov BYTE PTR [edx+eax],cl
 pop ebp
 ret 0xc
many:
 cmp DWORD PTR [edx+0x14],0x10
 jb many_inline
 mov edx,DWORD PTR [edx]
many_inline:
 push eax
 mov eax,DWORD PTR [ebp+0x10]
 movsx eax,al
 push eax
 mov eax,DWORD PTR [ebp+8]
 {load} add eax,edx
 push eax
 call memset_import
 add esp,0xc
 pop ebp
 ret 0xc
.section .note.GNU-stack,"",@progbits
