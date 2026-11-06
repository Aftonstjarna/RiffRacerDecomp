# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x4225c0,0x422630); all three returns and complete tail included.
# cdecl compare(left,right,unsigned byte_count), EAX=-1/0/+1.
.intel_syntax noprefix
.code32
.text
.global original_byte_range_compare
original_byte_range_compare:
 push ebp
 {load} mov ebp,esp
 mov ecx,DWORD PTR [ebp+16]
 test ecx,ecx
 jne .nonzero
 {load} xor eax,eax
 pop ebp
 ret
.nonzero:
 mov edx,DWORD PTR [ebp+8]
 push esi
 mov esi,DWORD PTR [ebp+12]
 sub ecx,4
 jb .tail
 {disp32} lea ebx,[ebx+0]
.words:
 mov eax,DWORD PTR [edx]
 cmp eax,DWORD PTR [esi]
 jne .bytes
 add edx,4
 add esi,4
 sub ecx,4
 jae .words
.tail:
 cmp ecx,-4
 je .equal
.bytes:
 mov al,BYTE PTR [edx]
 cmp al,BYTE PTR [esi]
 jne .different
 cmp ecx,-3
 je .equal
 mov al,BYTE PTR [edx+1]
 cmp al,BYTE PTR [esi+1]
 jne .different
 cmp ecx,-2
 je .equal
 mov al,BYTE PTR [edx+2]
 cmp al,BYTE PTR [esi+2]
 jne .different
 cmp ecx,-1
 je .equal
 mov al,BYTE PTR [edx+3]
 cmp al,BYTE PTR [esi+3]
 je .equal
.different:
 {load} sbb eax,eax
 or eax,1
 pop esi
 pop ebp
 ret
.equal:
 {load} xor eax,eax
 pop esi
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
