# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f2150,0x4f2189); caller at 0x4f2199.
.intel_syntax noprefix
.code32
.text
.global original_script_gc_scan_linked_values
.equ MARK_OBJECT,0x4f0ef0
original_script_gc_scan_linked_values:
 push ebx
 mov.s ebx,ecx
 push esi
 push edi
 mov esi,DWORD PTR [ebx+0x78]
 lea edi,[ebx+0x68]
 cmp.s esi,edi
 je .Ldone
 nop
.Lloop:
 test BYTE PTR [esi+0x5],0x7
 jne .Lnext
 mov eax,DWORD PTR [esi+0x8]
 cmp DWORD PTR [eax+0x4],0x4
 jl .Lnext
 mov edx,DWORD PTR [eax]
 test BYTE PTR [edx+0x5],0x3
 je .Lnext
 mov.s ecx,ebx
 call MARK_OBJECT
.Lnext:
 mov esi,DWORD PTR [esi+0x10]
 cmp.s esi,edi
 jne .Lloop
.Ldone:
 pop edi
 pop esi
 pop ebx
 ret
.section .note.GNU-stack,"",@progbits
