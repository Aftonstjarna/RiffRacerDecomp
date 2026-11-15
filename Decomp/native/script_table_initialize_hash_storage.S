.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f0580,0x4f0657); INT3 padding excluded.
.global original_script_table_initialize_hash_storage
.equ dep_486ab0,0x486ab0
.equ dep_4f7d10,0x4f7d10
.equ dep_4f7cf0,0x4f7cf0
original_script_table_initialize_hash_storage:
    push ebp
    mov.s ebp,esp
    push ecx
    push ebx
    push esi
    mov esi,DWORD PTR [ebp+0x8]
    push edi
    mov.s edi,edx
    mov.s edx,ecx
    mov DWORD PTR [ebp-0x4],edx
    test esi,esi
    jne L_4f05a3
    mov DWORD PTR [edi+0x10],0x99a424
    xor.s ebx,ebx
    jmp L_4f0641
L_4f05a3:
    lea eax,[esi-0x1]
    or ecx,0xffffffff
    cmp eax,0x100
    jb L_4f05bd
L_4f05b0:
    shr eax,0x8
    add ecx,0x8
    cmp eax,0x100
    jae L_4f05b0
L_4f05bd:
    movzx eax,BYTE PTR [eax+0x99a438]
    lea ebx,[ecx+0x1]
    add.s ebx,eax
    cmp ebx,0x1a
    jle L_4f05df
    push 0x9fd740
    push edx
    call dep_486ab0
    mov edx,DWORD PTR [ebp-0x4]
    add esp,0x8
L_4f05df:
    mov esi,0x1
    mov.s ecx,ebx
    shl esi,cl
    lea eax,[esi+0x1]
    cmp eax,0xccccccc
    ja L_4f060a
    mov ecx,DWORD PTR [ebp-0x4]
    lea eax,[esi+esi*4]
    shl eax,0x2
    xor.s edx,edx
    push eax
    push 0x0
    call dep_4f7d10
    add esp,0x8
    jmp L_4f0611
L_4f060a:
    mov.s ecx,edx
    call dep_4f7cf0
L_4f0611:
    mov DWORD PTR [edi+0x10],eax
    test esi,esi
    jle L_4f0641
    xor.s ecx,ecx
    mov.s edx,esi
    {disp8} lea esp,[esp+0x0]
L_4f0620:
    mov eax,DWORD PTR [edi+0x10]
    lea ecx,[ecx+0x14]
    mov DWORD PTR [eax+ecx*1-0x4],0x0
    mov DWORD PTR [eax+ecx*1-0x8],0x0
    mov DWORD PTR [eax+ecx*1-0x10],0x0
    dec edx
    jne L_4f0620
L_4f0641:
    mov eax,DWORD PTR [edi+0x10]
    lea ecx,[esi+esi*4]
    mov BYTE PTR [edi+0x7],bl
    lea eax,[eax+ecx*4]
    mov DWORD PTR [edi+0x14],eax
    pop edi
    pop esi
    pop ebx
    mov.s esp,ebp
    pop ebp
    ret 
.section .note.GNU-stack,"",@progbits
