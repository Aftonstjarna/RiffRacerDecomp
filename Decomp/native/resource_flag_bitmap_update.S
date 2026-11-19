.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x41f500.
.global original_resource_flag_bitmap_update
original_resource_flag_bitmap_update:
 push ebp
 {load} mov ebp,esp
 push ebx
 mov bl,BYTE PTR [ebp+8]
 mov BYTE PTR [ecx+0x14],bl
 sub ecx,DWORD PTR [0xbfcc0c]
 shr ecx,5
 lea ecx,[ecx*2+1]
 cmp ecx,DWORD PTR [0xc007b4]
 jae .Ldone
 {load} mov edx,ecx
 shr edx,5
 {load} mov eax,edx
 shl eax,5
 {load} sub ecx,eax
 mov eax,DWORD PTR [0xc007b0]
 push esi
 mov esi,1
 shl esi,cl
 lea ecx,[eax+edx*4]
 {load} mov eax,esi
 not eax
 and DWORD PTR [ecx],eax
 test bl,bl
 je .Lpop
 mov eax,DWORD PTR [0xc007b0]
 or DWORD PTR [eax+edx*4],esi
.Lpop:
 pop esi
.Ldone:
 pop ebx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
