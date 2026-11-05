# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x416160,0x41616c); both RET paths included, INT3 padding excluded.
# ECX = narrow-string object; EAX = inline buffer or heap pointer.
.intel_syntax noprefix
.code32
.text
.global original_narrow_storage_pointer
original_narrow_storage_pointer:
 cmp DWORD PTR [ecx+0x14],0x10
 jb .Linline
 mov eax,DWORD PTR [ecx]
 ret
.Linline:
 mov.s eax,ecx
 ret
