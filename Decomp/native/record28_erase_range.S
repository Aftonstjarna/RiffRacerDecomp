# Mechanically transcribed reference evidence; not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4b2480..0x4b24f4 (exclusive). Both returns included.
# ECX=vector triple; stack args: output iterator pointer, first, last.
# 28-byte records, forward compaction; no calls, imports or globals.
.intel_syntax noprefix
.code32
.text
.global original_record28_erase_range
original_record28_erase_range:
 push ebp
 {load} mov ebp,esp
 mov edx,DWORD PTR [ebp+12]
 push esi
 mov esi,DWORD PTR [ebp+16]
 push edi
 {load} mov edi,ecx
 mov eax,DWORD PTR [edi]
 {load} cmp edx,eax
 jne .Lpartial
 cmp esi,DWORD PTR [edi+4]
 jne .Lpartial
 # Whole-range erase: clear logical end, return original first iterator.
 mov DWORD PTR [edi+4],eax
 mov eax,DWORD PTR [ebp+8]
 pop edi
 pop esi
 mov DWORD PTR [eax],edx
 pop ebp
 ret 12
.Lpartial:
 {load} cmp edx,esi
 je .Lresult
 push ebx
 mov ebx,DWORD PTR [edi+4]
 {load} mov ecx,edx
 {load} cmp esi,ebx
 je .Lupdate_end
 jmp .Lcopy
 # Original unreachable instruction padding retained as mnemonics.
 {disp32} lea esp,[esp+0]
 {disp8} lea ecx,[ecx+0]
.Lcopy:
 movdqu xmm0,XMMWORD PTR [esi]
 movdqu XMMWORD PTR [ecx],xmm0
 movq xmm0,QWORD PTR [esi+16]
 movq QWORD PTR [ecx+16],xmm0
 mov eax,DWORD PTR [esi+24]
 add esi,28
 mov DWORD PTR [ecx+24],eax
 add ecx,28
 {load} cmp esi,ebx
 jne .Lcopy
 mov edx,DWORD PTR [ebp+12]
.Lupdate_end:
 mov DWORD PTR [edi+4],ecx
 pop ebx
.Lresult:
 mov eax,DWORD PTR [ebp+8]
 pop edi
 pop esi
 mov DWORD PTR [eax],edx
 pop ebp
 ret 12
.section .note.GNU-stack,"",@progbits
