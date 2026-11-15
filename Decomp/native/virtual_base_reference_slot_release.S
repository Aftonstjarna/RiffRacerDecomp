# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x41d590,0x41d5ad). Two conditional branches, one return.
.intel_syntax noprefix
.code32
.text
.global original_virtual_base_reference_slot_release
original_virtual_base_reference_slot_release:
 mov ecx,DWORD PTR [ecx]
 test ecx,ecx
 je done
 mov eax,DWORD PTR [ecx+4]
 add ecx,4
 mov eax,DWORD PTR [eax+4]
 add.s ecx,eax
 dec DWORD PTR [ecx+4]
 jne done
 mov eax,DWORD PTR [ecx]
 push 1
 call DWORD PTR [eax]
done:
 ret
.section .note.GNU-stack,"",@progbits
