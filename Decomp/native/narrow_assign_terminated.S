# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x415b90, exclusive end 0x415bc6; both returns included.
.intel_syntax noprefix
.code32
.text
.global original_narrow_assign_terminated
original_narrow_assign_terminated:
 push ebp
 {load} mov ebp,esp
 push esi
 mov esi,DWORD PTR [ebp+8]
 cmp BYTE PTR [esi],0
 jne nonempty
 {load} xor edx,edx
 push edx
 push esi
 call assign_range
 pop esi
 pop ebp
 ret 4
nonempty:
 {load} mov edx,esi
 push edi
 lea edi,[edx+1]
scan:
 mov al,BYTE PTR [edx]
 inc edx
 test al,al
 jne scan
 {load} sub edx,edi
 pop edi
 push edx
 push esi
 call assign_range
 pop esi
 pop ebp
 ret 4
.equ assign_range,0x416520
.section .note.GNU-stack,"",@progbits
