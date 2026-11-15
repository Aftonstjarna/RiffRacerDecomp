# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x43e850,0x43e880). One conditional branch, one RET 4.
.intel_syntax noprefix
.code32
.text
.global original_u32_vector_cleanup_element
.equ SCALAR_DELETE_IAT,0x92d4b0
original_u32_vector_cleanup_element:
 push ebp
 mov.s ebp,esp
 push esi
 mov esi,DWORD PTR [ebp+8]
 mov eax,DWORD PTR [esi]
 test eax,eax
 je done
 push eax
 call DWORD PTR ds:SCALAR_DELETE_IAT
 add esp,4
 mov DWORD PTR [esi],0
 mov DWORD PTR [esi+4],0
 mov DWORD PTR [esi+8],0
done:
 pop esi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
