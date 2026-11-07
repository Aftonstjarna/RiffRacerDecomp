# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4a4d80.
.intel_syntax noprefix
.code32
.text
.global original_device_pending_targets_prepare
original_device_pending_targets_prepare:
.equ pending_cleanup,0x4a4ea0
L_4a4d80:
    push   ebx
L_4a4d81:
    push   esi
L_4a4d82:
    push   edi
L_4a4d83:
    {load} mov    esi,ecx
L_4a4d85:
    mov    edi,0x2000
L_4a4d8a:
    push   0x0
L_4a4d8c:
    mov    eax,DWORD PTR [esi+0xd8]
L_4a4d92:
    lea    edx,[esi+0x4]
L_4a4d95:
    mov    ecx,DWORD PTR [esi+0x78]
L_4a4d98:
    {load} cmp    eax,edi
L_4a4d9a:
    push   edx
L_4a4d9b:
    push   0x0
L_4a4d9d:
    push   DWORD PTR [esi+0x1f8]
L_4a4da3:
    cmovb  edi,eax
L_4a4da6:
    mov    eax,DWORD PTR [ecx]
L_4a4da8:
    push   0x1
L_4a4daa:
    push   0x1
L_4a4dac:
    lea    ebx,[edi+edi*8]
L_4a4daf:
    shr    ebx,0x4
L_4a4db2:
    push   ebx
L_4a4db3:
    push   edi
L_4a4db4:
    push   ecx
L_4a4db5:
    call   DWORD PTR [eax+0x5c]
L_4a4db8:
    test   eax,eax
L_4a4dba:
    js     L_4a4e91
L_4a4dc0:
    cmp    BYTE PTR [esi+0x2],0x0
L_4a4dc4:
    je     L_4a4deb
L_4a4dc6:
    mov    ecx,DWORD PTR [esi+0x78]
L_4a4dc9:
    lea    eax,[esi+0x8]
L_4a4dcc:
    push   0x0
L_4a4dce:
    push   eax
L_4a4dcf:
    push   0x0
L_4a4dd1:
    push   DWORD PTR [esi+0x1f8]
L_4a4dd7:
    mov    edx,DWORD PTR [ecx]
L_4a4dd9:
    push   0x1
L_4a4ddb:
    push   0x1
L_4a4ddd:
    push   ebx
L_4a4dde:
    push   edi
L_4a4ddf:
    push   ecx
L_4a4de0:
    call   DWORD PTR [edx+0x5c]
L_4a4de3:
    test   eax,eax
L_4a4de5:
    js     L_4a4e91
L_4a4deb:
    mov    ecx,DWORD PTR [esi+0x4]
L_4a4dee:
    lea    eax,[esi+0xc]
L_4a4df1:
    push   eax
L_4a4df2:
    push   0x0
L_4a4df4:
    push   ecx
L_4a4df5:
    mov    edx,DWORD PTR [ecx]
L_4a4df7:
    call   DWORD PTR [edx+0x48]
L_4a4dfa:
    test   eax,eax
L_4a4dfc:
    js     L_4a4e91
L_4a4e02:
    cmp    BYTE PTR [esi+0x2],0x0
L_4a4e06:
    je     L_4a4e1b
L_4a4e08:
    mov    ecx,DWORD PTR [esi+0x8]
L_4a4e0b:
    lea    eax,[esi+0x10]
L_4a4e0e:
    push   eax
L_4a4e0f:
    push   0x0
L_4a4e11:
    push   ecx
L_4a4e12:
    mov    edx,DWORD PTR [ecx]
L_4a4e14:
    call   DWORD PTR [edx+0x48]
L_4a4e17:
    test   eax,eax
L_4a4e19:
    js     L_4a4e91
L_4a4e1b:
    mov    ecx,DWORD PTR [esi+0x78]
L_4a4e1e:
    lea    eax,[esi+0x14]
L_4a4e21:
    push   0x0
L_4a4e23:
    push   eax
L_4a4e24:
    push   0x1
L_4a4e26:
    mov    edx,DWORD PTR [ecx]
L_4a4e28:
    push   0x0
L_4a4e2a:
    push   0x0
L_4a4e2c:
    push   DWORD PTR [esi+0x1e0]
L_4a4e32:
    push   ebx
L_4a4e33:
    push   edi
L_4a4e34:
    push   ecx
L_4a4e35:
    call   DWORD PTR [edx+0x74]
L_4a4e38:
    test   eax,eax
L_4a4e3a:
    js     L_4a4e91
L_4a4e3c:
    mov    ecx,DWORD PTR [esi+0x78]
L_4a4e3f:
    lea    eax,[esi+0x18]
L_4a4e42:
    push   0x0
L_4a4e44:
    push   eax
L_4a4e45:
    push   0x2
L_4a4e47:
    push   DWORD PTR [esi+0x1f8]
L_4a4e4d:
    mov    edx,DWORD PTR [ecx]
L_4a4e4f:
    push   ebx
L_4a4e50:
    push   edi
L_4a4e51:
    push   ecx
L_4a4e52:
    call   DWORD PTR [edx+0x90]
L_4a4e58:
    test   eax,eax
L_4a4e5a:
    js     L_4a4e91
L_4a4e5c:
    xorps  xmm0,xmm0
L_4a4e5f:
    mov    al,0x1
L_4a4e61:
    movdqu XMMWORD PTR [esi+0x1c],xmm0
L_4a4e66:
    movq   QWORD PTR [esi+0x2c],xmm0
L_4a4e6b:
    mov    DWORD PTR [esi+0x24],edi
L_4a4e6e:
    pop    edi
L_4a4e6f:
    mov    DWORD PTR [esi+0x28],ebx
L_4a4e72:
    mov    DWORD PTR [esi+0x1c],0x0
L_4a4e79:
    mov    DWORD PTR [esi+0x20],0x0
L_4a4e80:
    mov    DWORD PTR [esi+0x2c],0x0
L_4a4e87:
    mov    DWORD PTR [esi+0x30],0x3f800000
L_4a4e8e:
    pop    esi
L_4a4e8f:
    pop    ebx
L_4a4e90:
    ret
L_4a4e91:
    {load} mov    ecx,esi
L_4a4e93:
    call   pending_cleanup
L_4a4e98:
    pop    edi
L_4a4e99:
    pop    esi
L_4a4e9a:
    {load} xor    al,al
L_4a4e9c:
    pop    ebx
L_4a4e9d:
    ret
