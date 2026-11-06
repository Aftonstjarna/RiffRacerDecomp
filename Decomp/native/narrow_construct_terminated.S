# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x415b00,0x415b51); both returns included; following INT3 excluded.
.intel_syntax noprefix
.code32
.text
.equ narrow_assign_range,0x416520
.global original_narrow_construct_terminated
original_narrow_construct_terminated:
 push ebp
 {load} mov ebp,esp
 push esi
 {load} mov esi,ecx
 mov ecx,DWORD PTR [ebp+8]
 mov DWORD PTR [esi+20],15
 mov DWORD PTR [esi+16],0
 mov BYTE PTR [esi],0
 cmp BYTE PTR [ecx],0
 jne .nonempty
 {load} xor edx,edx
 push edx
 push ecx
 {load} mov ecx,esi
 call narrow_assign_range
 {load} mov eax,esi
 pop esi
 pop ebp
 ret 4
.nonempty:
 {load} mov edx,ecx
 push edi
 lea edi,[edx+1]
.scan:
 mov al,BYTE PTR [edx]
 inc edx
 test al,al
 jne .scan
 {load} sub edx,edi
 pop edi
 push edx
 push ecx
 {load} mov ecx,esi
 call narrow_assign_range
 {load} mov eax,esi
 pop esi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
