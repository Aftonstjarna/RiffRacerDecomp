# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original span: VA 0x511e90 through 0x511ebe exclusive.
# thiscall: ECX object, stack uint32 index; EAX result; RET 4 on both paths.
.intel_syntax noprefix
.code32
.text
.global original_resource_index_acquire
original_resource_index_acquire:
    push ebp
    {load} mov ebp,esp
    {load} mov edx,ecx
    push esi
    mov esi,DWORD PTR [ebp+8]
    mov eax,DWORD PTR [edx+0x38]
    sub eax,DWORD PTR [edx+0x34]
    sar eax,2
    {load} cmp esi,eax
    jb acquire
    {load} xor eax,eax
    pop esi
    pop ebp
    ret 4
acquire:
    mov ecx,DWORD PTR [edx+0x40]
    inc DWORD PTR [ecx+esi*4]
    mov eax,DWORD PTR [edx+0x34]
    mov eax,DWORD PTR [eax+esi*4]
    pop esi
    pop ebp
    ret 4
.section .note.GNU-stack,"",@progbits
