.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x55ca20, size 145.
.global original_audio_configuration_select
original_audio_configuration_select:
.L55ca20:
push   ebp
.L55ca21:
mov.s    ebp,esp
.L55ca23:
push   ecx
.L55ca24:
push   ebx
.L55ca25:
mov.s    ebx,edx
.L55ca27:
mov    DWORD PTR [ebp-0x4],ecx
.L55ca2a:
push   esi
.L55ca2b:
push   edi
.L55ca2c:
add    ecx,0x6da8
.L55ca32:
mov    edi,DWORD PTR [ebx+0x8]
.L55ca35:
mov    eax,DWORD PTR [ebx+0xc]
.L55ca38:
dec    edi
.L55ca39:
xor.s    esi,esi
.L55ca3b:
jmp    .L55ca40
.L55ca3d:
{disp8} lea ecx,[ecx+0x0]
.L55ca40:
cmp    DWORD PTR [esi*4+0x9ee8f0],eax
.L55ca47:
je     .L55ca65
.L55ca49:
inc    esi
.L55ca4a:
cmp    esi,0x9
.L55ca4d:
jl     .L55ca40
.L55ca4f:
test   ecx,ecx
.L55ca51:
je     .L55ca93
.L55ca53:
mov    ecx,DWORD PTR [ecx+0x8]
.L55ca56:
test   ecx,ecx
.L55ca58:
je     .L55ca93
.L55ca5a:
cmp.s    ecx,eax
.L55ca5c:
jne    .L55ca93
.L55ca5e:
mov    esi,0x9
.L55ca63:
jmp    .L55ca69
.L55ca65:
test   esi,esi
.L55ca67:
js     .L55ca93
.L55ca69:
mov    eax,DWORD PTR [ebp+0x8]
.L55ca6c:
mov    edx,DWORD PTR [ebp+0xc]
.L55ca6f:
cmp.s    eax,edx
.L55ca71:
jge    .L55ca93
.L55ca73:
lea    ecx,[edi*4+0x493]
.L55ca7a:
add.s    ecx,edi
.L55ca7c:
lea    ecx,[esi+ecx*2]
.L55ca7f:
mov    esi,DWORD PTR [ebp-0x4]
.L55ca82:
lea    ecx,[ecx+ecx*2]
.L55ca85:
lea    ecx,[esi+ecx*4]
.L55ca88:
cmp    BYTE PTR [ecx+eax*1],0x0
.L55ca8c:
jne    .L55ca9c
.L55ca8e:
inc    eax
.L55ca8f:
cmp.s    eax,edx
.L55ca91:
jl     .L55ca88
.L55ca93:
pop    edi
.L55ca94:
pop    esi
.L55ca95:
xor.s    eax,eax
.L55ca97:
pop    ebx
.L55ca98:
mov.s    esp,ebp
.L55ca9a:
pop    ebp
.L55ca9b:
ret
.L55ca9c:
mov    eax,DWORD PTR [eax*4+0x9ee890]
.L55caa3:
pop    edi
.L55caa4:
mov    DWORD PTR [ebx],eax
.L55caa6:
mov    eax,0x1
.L55caab:
pop    esi
.L55caac:
pop    ebx
.L55caad:
mov.s    esp,ebp
.L55caaf:
pop    ebp
.L55cab0:
ret
.section .note.GNU-stack,"",@progbits
