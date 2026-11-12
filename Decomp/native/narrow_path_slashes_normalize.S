.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x43fd50; complete span ends at 0x43fd88.
.global original_narrow_path_slashes_normalize
original_narrow_path_slashes_normalize:
    push ebp
    {load} mov ebp,esp
    mov ecx,DWORD PTR [ebp+8]
    cmp DWORD PTR [ecx+0x14],0x10
    jb initial_inline
    mov eax,DWORD PTR [ecx]
    jmp loop_start
initial_inline:
    {load} mov eax,ecx
loop_start:
    push esi
loop_reload:
    cmp DWORD PTR [ecx+0x14],0x10
    jb end_inline
    mov esi,DWORD PTR [ecx]
    jmp end_ready
end_inline:
    {load} mov esi,ecx
end_ready:
    mov edx,DWORD PTR [ecx+0x10]
    {load} add edx,esi
    {load} cmp eax,edx
    je done
    cmp BYTE PTR [eax],0x5c
    jne advance
    mov BYTE PTR [eax],0x2f
advance:
    inc eax
    jmp loop_reload
done:
    pop esi
    pop ebp
    ret 4
