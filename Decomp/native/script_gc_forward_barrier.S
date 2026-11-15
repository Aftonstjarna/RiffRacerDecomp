# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f2560,0x4f2589); following INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_gc_forward_barrier
.equ MARK_OBJECT,0x4f0ef0
original_script_gc_forward_barrier:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ecx+0x10]
 cmp BYTE PTR [eax+0x15],1
 jne .Lrewhite
 mov edx,DWORD PTR [ebp+8]
 mov.s ecx,eax
 pop ebp
 jmp MARK_OBJECT
.Lrewhite:
 mov cl,BYTE PTR [eax+0x14]
 mov al,BYTE PTR [edx+5]
 and cl,3
 and al,0xf8
 or.s cl,al
 mov BYTE PTR [edx+5],cl
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
