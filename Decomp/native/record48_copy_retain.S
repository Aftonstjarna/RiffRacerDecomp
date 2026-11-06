# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x004b4310,0x004b437e); adjacent INT3 padding excluded.
# ECX=destination, [entry ESP+4]=source; EAX=destination; RET 4.
# Four nullable pointers retain by non-atomic INC [pointer+4]; eight plain DWORDs follow.
.intel_syntax noprefix
.code32
.text
.global original_record48_copy_retain
original_record48_copy_retain:
 push ebp
 mov.s ebp,esp
 mov edx,DWORD PTR [ebp+8]
 mov eax,DWORD PTR [edx]
 mov DWORD PTR [ecx],eax
 test eax,eax
 je .Lnext0
 inc DWORD PTR [eax+4]
.Lnext0:
 mov eax,DWORD PTR [edx+0x4]
 mov DWORD PTR [ecx+0x4],eax
 test eax,eax
 je .Lnext1
 inc DWORD PTR [eax+4]
.Lnext1:
 mov eax,DWORD PTR [edx+0x8]
 mov DWORD PTR [ecx+0x8],eax
 test eax,eax
 je .Lnext2
 inc DWORD PTR [eax+4]
.Lnext2:
 mov eax,DWORD PTR [edx+0xc]
 mov DWORD PTR [ecx+0xc],eax
 test eax,eax
 je .Lnext3
 inc DWORD PTR [eax+4]
.Lnext3:
 mov eax,DWORD PTR [edx+0x10]
 mov DWORD PTR [ecx+0x10],eax
 mov eax,DWORD PTR [edx+0x14]
 mov DWORD PTR [ecx+0x14],eax
 mov eax,DWORD PTR [edx+0x18]
 mov DWORD PTR [ecx+0x18],eax
 mov eax,DWORD PTR [edx+0x1c]
 mov DWORD PTR [ecx+0x1c],eax
 mov eax,DWORD PTR [edx+0x20]
 mov DWORD PTR [ecx+0x20],eax
 mov eax,DWORD PTR [edx+0x24]
 mov DWORD PTR [ecx+0x24],eax
 mov eax,DWORD PTR [edx+0x28]
 mov DWORD PTR [ecx+0x28],eax
 mov eax,DWORD PTR [edx+0x2c]
 mov DWORD PTR [ecx+0x2c],eax
 mov.s eax,ecx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
