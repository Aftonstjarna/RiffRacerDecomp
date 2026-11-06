# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x490e70,0x490eaf); trailing INT3 excluded.
.intel_syntax noprefix
.code32
.text
.global original_nested_record_pair_copy
original_nested_record_pair_copy:
 push ebp
 mov.s ebp,esp
 mov.s edx,ecx
 mov eax,DWORD PTR [edx+0x44]
 test eax,eax
 je .Labsent
 # Preserve original 8+4 byte copy order and reload of the nested pointer.
 movq xmm0,QWORD PTR [eax+0x70]
 mov ecx,DWORD PTR [ebp+0x8]
 movq QWORD PTR [ecx],xmm0
 mov eax,DWORD PTR [eax+0x78]
 mov DWORD PTR [ecx+0x8],eax
 mov eax,DWORD PTR [edx+0x44]
 mov ecx,DWORD PTR [ebp+0xc]
 movq xmm0,QWORD PTR [eax+0x64]
 movq QWORD PTR [ecx],xmm0
 mov eax,DWORD PTR [eax+0x6c]
 mov DWORD PTR [ecx+0x8],eax
 mov al,0x1
 pop ebp
 ret 0x8
.Labsent:
 xor.s al,al
 pop ebp
 ret 0x8
.section .note.GNU-stack,"",@progbits
