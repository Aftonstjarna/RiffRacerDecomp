# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x58b3c0; complete span [0x58b3c0,0x58b460).
.intel_syntax noprefix
.code32
.text
.global original_audio_record32_array_clear
original_audio_record32_array_clear:
    push   ebp
    {load} mov ebp,esp
    sub    esp,0x8
    push   esi
    {load} mov eax,edx
    {load} mov esi,ecx
    mov    ecx,DWORD PTR [0x92d3a4]
    push   edi
    {load} xor edi,edi
    mov    DWORD PTR [ebp-0x8],eax
    mov    DWORD PTR [ebp-0x4],esi
    cmp    DWORD PTR [eax],edi
    jbe L_58b444
    push   ebx
    {load} xor ebx,ebx
L_58b3e1:
    mov    esi,DWORD PTR [esi]
    {load} add esi,ebx
    mov    eax,DWORD PTR [esi+0x14]
    test   eax,eax
    je L_58b3f8
    push   eax
    call   ecx
    mov    ecx,DWORD PTR [0x92d3a4]
    add    esp,0x4
L_58b3f8:
    mov    DWORD PTR [esi+0x14],0x0
    mov    DWORD PTR [esi+0x18],0x0
    mov    DWORD PTR [esi+0x1c],0x0
    mov    eax,DWORD PTR [esi+0x8]
    test   eax,eax
    je L_58b41a
    push   eax
    call   ecx
    add    esp,0x4
L_58b41a:
    mov    eax,DWORD PTR [ebp-0x8]
    inc    edi
    mov    ecx,DWORD PTR [0x92d3a4]
    add    ebx,0x20
    mov    DWORD PTR [esi+0x8],0x0
    mov    DWORD PTR [esi+0xc],0x0
    mov    DWORD PTR [esi+0x10],0x0
    mov    esi,DWORD PTR [ebp-0x4]
    cmp    edi,DWORD PTR [eax]
    jb L_58b3e1
    pop    ebx
L_58b444:
    push   DWORD PTR [esi]
    call   ecx
    mov    eax,DWORD PTR [ebp-0x8]
    add    esp,0x4
    mov    DWORD PTR [esi],0x0
    pop    edi
    mov    DWORD PTR [eax],0x0
    pop    esi
    {load} mov esp,ebp
    pop    ebp
    ret
