# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x43e800,0x43e842); three conditional branches, one RET.
# Stack arguments: begin, end, followed by two unused caller-supplied arguments.
# Caller cleanup; EBP/ESI/EDI/EBX preserved. CRT delete is an external dependency.
.intel_syntax noprefix
.code32
.text
.global original_u32_vector_range_cleanup
.equ SCALAR_DELETE_IAT,0x92d4b0
original_u32_vector_range_cleanup:
 push ebp
 mov.s ebp,esp
 push esi
 mov esi,DWORD PTR [ebp+8]
 push edi
 mov edi,DWORD PTR [ebp+12]
 cmp.s esi,edi
 je done
 push ebx
 mov ebx,DWORD PTR ds:SCALAR_DELETE_IAT
loop_record:
 mov eax,DWORD PTR [esi]
 test eax,eax
 je next_record
 push eax
 call ebx
 add esp,4
 mov DWORD PTR [esi],0
 mov DWORD PTR [esi+4],0
 mov DWORD PTR [esi+8],0
next_record:
 add esi,12
 cmp.s esi,edi
 jne loop_record
 pop ebx
done:
 pop edi
 pop esi
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
