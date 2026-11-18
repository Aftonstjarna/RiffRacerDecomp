.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x486180.
.global original_script_operand_validate
original_script_operand_validate:
 push ebp
 {load} mov ebp,esp
 mov eax,DWORD PTR [ebp+0x8]
 push esi
 {load} mov esi,ecx
 sub eax,0x0
 je .Lzero
 sub eax,0x2
 je .Ltwo
 dec eax
 jne .Lyes
 {load} xor ecx,ecx
 test edx,0x100
 je .Lregister
 and edx,0xfffffeff
 cmp edx,DWORD PTR [esi+0x28]
 jmp .Lset
.Lregister:
 movzx eax,BYTE PTR [esi+0x4b]
 {load} cmp edx,eax
.Lset:
 setl cl
 test ecx,ecx
 jne .Lyes
 {load} xor eax,eax
 pop esi
 pop ebp
 ret
.Ltwo:
 movzx eax,BYTE PTR [esi+0x4b]
 {load} cmp edx,eax
 jl .Lyes
.Lno:
 {load} xor eax,eax
 pop esi
 pop ebp
 ret
.Lzero:
 test edx,edx
 jne .Lno
.Lyes:
 mov eax,0x1
 pop esi
 pop ebp
 ret
