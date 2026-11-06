# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4b2d20,0x4b2d66): complete 70-byte function.
# Caller-cleaned stack: output, terminated prefix, mutable narrow string.
# Prepend prefix through 0x47ab30, then move-construct output via 0x416af0.
.intel_syntax noprefix
.code32
.text
.global original_narrow_prefix_move_construct
.equ narrow_insert_pointer,0x47ab30
.equ narrow_move_construct,0x416af0
original_narrow_prefix_move_construct:
 push ebp
 {load} mov ebp,esp
 push ecx
 mov edx,DWORD PTR [ebp+0xc]
 push esi
 mov DWORD PTR [ebp-4],0
 cmp BYTE PTR [edx],0
 jne scan_prefix
 {load} xor eax,eax
 jmp insert_prefix
scan_prefix:
 {load} mov eax,edx
 lea esi,[eax+1]
 {disp8} lea ecx,[ecx+0]
scan_byte:
 mov cl,BYTE PTR [eax]
 inc eax
 test cl,cl
 jne scan_byte
 {load} sub eax,esi
insert_prefix:
 mov ecx,DWORD PTR [ebp+0x10]
 push eax
 push edx
 push 0
 call narrow_insert_pointer
 mov ecx,DWORD PTR [ebp+8]
 push eax
 call narrow_move_construct
 mov eax,DWORD PTR [ebp+8]
 pop esi
 {load} mov esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
