# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x43e7a0,0x43e7cb); padding excluded.
# ECX=source begin, EDX=source end, [ESP+4]=destination, EAX=destination end.
.intel_syntax noprefix
.code32
.text
.global original_record12_copy_assign_range
original_record12_copy_assign_range:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+8]
 push esi
 mov.s esi,edx
 cmp.s ecx,esi
 je done
 {disp8} lea ecx,[ecx+0]
copy_record:
 movq xmm0,QWORD PTR [ecx]
 movq QWORD PTR [eax],xmm0
 mov edx,DWORD PTR [ecx+8]
 add ecx,12
 mov DWORD PTR [eax+8],edx
 add eax,12
 cmp.s ecx,esi
 jne copy_record
done:
 pop esi
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
