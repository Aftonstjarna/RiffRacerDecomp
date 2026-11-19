.intel_syntax noprefix
.code32
.text
.global original_vfs_directory_record_construct
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x561e30.
original_vfs_directory_record_construct:
    push ebp
    {load} mov ebp,esp
    mov eax,DWORD PTR [edx]
    push esi
    push DWORD PTR [ebp+0x8]
    {load} mov esi,ecx
    lea ecx,[esi+0x4]
    mov DWORD PTR [esi],eax
    call wide_move_construct
    {load} mov eax,esi
    pop esi
    pop ebp
    ret
.equ wide_move_construct,0x44f6f0
.section .note.GNU-stack,"",@progbits
