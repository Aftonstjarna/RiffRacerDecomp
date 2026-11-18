# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x41f480.
.intel_syntax noprefix
.code32
.text
.global original_pointer_slot_release
original_pointer_slot_release:
 mov edx,DWORD PTR [ecx]
 test edx,edx
 je done
 mov eax,DWORD PTR [edx]
 mov ecx,DWORD PTR [eax+0x4]
 add.s ecx,edx
 dec DWORD PTR [ecx+0x4]
 jne done
 mov eax,DWORD PTR [ecx]
 push 0x1
 call DWORD PTR [eax]
done:
 ret
.section .note.GNU-stack,"",@progbits
