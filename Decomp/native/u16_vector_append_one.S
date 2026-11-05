# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x41c290,0x41c2f8); excludes following INT3 padding.
# ECX: begin/end/capacity pointer triple; stack argument: pointer to uint16.
# Preserve aliased source index across growth; external sources retain pointer.
.intel_syntax noprefix
.code32
.text
.global original_u16_vector_append_one
original_u16_vector_append_one:
 push ebp
 {load} mov ebp,esp
 push esi
 {load} mov esi,ecx
 push edi
 mov edi,DWORD PTR [ebp+8]
 mov eax,DWORD PTR [esi+4]
 {load} cmp edi,eax
 jae .Lexternal
 mov ecx,DWORD PTR [esi]
 {load} cmp ecx,edi
 ja .Lexternal
 {load} sub edi,ecx
 sar edi,1
 cmp eax,DWORD PTR [esi+8]
 jne .Lalias_ready
 push 1
 {load} mov ecx,esi
 call grow_u16
.Lalias_ready:
 mov ecx,DWORD PTR [esi+4]
 test ecx,ecx
 je .Ladvance
 mov eax,DWORD PTR [esi]
 mov ax,WORD PTR [eax+edi*2]
 mov WORD PTR [ecx],ax
 add DWORD PTR [esi+4],2
 pop edi
 pop esi
 pop ebp
 ret 4
.Lexternal:
 cmp eax,DWORD PTR [esi+8]
 jne .Lexternal_ready
 push 1
 {load} mov ecx,esi
 call grow_u16
.Lexternal_ready:
 mov ecx,DWORD PTR [esi+4]
 test ecx,ecx
 je .Ladvance
 mov ax,WORD PTR [edi]
 mov WORD PTR [ecx],ax
.Ladvance:
 add DWORD PTR [esi+4],2
 pop edi
 pop esi
 pop ebp
 ret 4
.equ grow_u16,0x41c470
.section .note.GNU-stack,"",@progbits
