# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x421dc0,0x421ddb); complete leaf; trailing INT3 excluded.
.intel_syntax noprefix
.code32
.text
.global original_resource_table_acquire
original_resource_table_acquire:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+0xc]
 mov ecx,DWORD PTR [ecx]
 mov ecx,DWORD PTR [ecx+eax*4]
 mov eax,DWORD PTR [ebp+8]
 mov DWORD PTR [eax],ecx
 test ecx,ecx
 je .Ldone
 inc DWORD PTR [ecx+4]
.Ldone:
 pop ebp
 ret 8
.section .note.GNU-stack,"",@progbits
