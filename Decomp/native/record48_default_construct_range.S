.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x541f40, exclusive end 0x541f9e.
.global original_record48_default_construct_range
original_record48_default_construct_range:
test edx,edx
je .Ldone
add ecx,0x14
.Lloop:
lea eax,[ecx-0x14]
test eax,eax
je .Lnext
mov DWORD PTR [ecx-0x14],0
mov DWORD PTR [ecx-0x10],0
mov DWORD PTR [ecx-0xc],0
mov DWORD PTR [ecx-0x8],0
mov DWORD PTR [ecx-0x4],0
mov DWORD PTR [ecx],0
mov DWORD PTR [ecx+4],0
mov DWORD PTR [ecx+8],0
mov DWORD PTR [ecx+0xc],0
mov DWORD PTR [ecx+0x14],0
mov BYTE PTR [ecx+0x18],0
.Lnext:
add ecx,0x30
dec edx
jne .Lloop
.Ldone:
ret
.section .note.GNU-stack,"",@progbits
