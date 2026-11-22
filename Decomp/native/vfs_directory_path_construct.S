# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x561d40,0x561e30); instruction-contiguous extent, padding excluded.
# VFS directory path construction used by discovery: SEH frame with cookie 0xBAABC0, string helpers
# 0x44FC30/0x5360B0/0x536160, original stack/cleanup order and both normal and unwind paths retained.
# Derived from original instructions; earns reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x561d40..0x561e30
.intel_syntax noprefix
.code32
.text
.global original_vfs_directory_path_construct
original_vfs_directory_path_construct:
.L561d40:
 push   ebp
.L561d41:
 {load} mov    ebp,esp
.L561d43:
 push   0xffffffff
.L561d45:
 push   0x8ff8f9
.L561d4a:
 mov    eax,fs:0x0
.L561d50:
 push   eax
.L561d51:
 sub    esp,0xc
.L561d54:
 push   ebx
.L561d55:
 push   esi
.L561d56:
 push   edi
.L561d57:
 mov    eax,[0xbaabc0]
.L561d5c:
 {load} xor    eax,ebp
.L561d5e:
 push   eax
.L561d5f:
 lea    eax,[ebp-0xc]
.L561d62:
 mov    fs:0x0,eax
.L561d68:
 {load} mov    eax,edx
.L561d6a:
 mov    DWORD PTR [ebp-0x14],eax
.L561d6d:
 {load} mov    esi,ecx
.L561d6f:
 mov    DWORD PTR [ebp-0x18],esi
.L561d72:
 mov    DWORD PTR [ebp-0x10],0x0
.L561d79:
 {load} xor    ecx,ecx
.L561d7b:
 mov    DWORD PTR [esi+0x14],0x7
.L561d82:
 mov    DWORD PTR [esi+0x10],0x0
.L561d89:
 mov    WORD PTR [esi],cx
.L561d8c:
 mov    edi,DWORD PTR [ebp+0x8]
.L561d8f:
 mov    DWORD PTR [ebp-0x4],ecx
.L561d92:
 mov    ebx,DWORD PTR [eax+0x10]
.L561d95:
 mov    DWORD PTR [ebp-0x10],0x1
.L561d9c:
 cmp    WORD PTR [edi],cx
.L561d9f:
 je .L561db5
.L561da1:
 {load} mov    ecx,edi
.L561da3:
 lea    edx,[ecx+0x2]
.L561da6:
 mov    ax,WORD PTR [ecx]
.L561da9:
 add    ecx,0x2
.L561dac:
 test   ax,ax
.L561daf:
 jne .L561da6
.L561db1:
 {load} sub    ecx,edx
.L561db3:
 sar    ecx,1
.L561db5:
 lea    eax,[ecx+ebx*1]
.L561db8:
 mov    ebx,DWORD PTR [esi+0x10]
.L561dbb:
 {load} cmp    ebx,eax
.L561dbd:
 ja .L561de7
.L561dbf:
 cmp    DWORD PTR [esi+0x14],eax
.L561dc2:
 je .L561de7
.L561dc4:
 push   0x1
.L561dc6:
 push   eax
.L561dc7:
 {load} mov    ecx,esi
.L561dc9:
 call target_44fc30
.L561dce:
 test   al,al
.L561dd0:
 je .L561de7
.L561dd2:
 cmp    DWORD PTR [esi+0x14],0x8
.L561dd6:
 mov    DWORD PTR [esi+0x10],ebx
.L561dd9:
 jb .L561ddf
.L561ddb:
 mov    eax,DWORD PTR [esi]
.L561ddd:
 jmp .L561de1
.L561ddf:
 {load} mov    eax,esi
.L561de1:
 {load} xor    ecx,ecx
.L561de3:
 mov    WORD PTR [eax+ebx*2],cx
.L561de7:
 push   0xffffffff
.L561de9:
 push   0x0
.L561deb:
 push   DWORD PTR [ebp-0x14]
.L561dee:
 {load} mov    ecx,esi
.L561df0:
 call target_5360b0
.L561df5:
 cmp    WORD PTR [edi],0x0
.L561df9:
 jne .L561dff
.L561dfb:
 {load} xor    ecx,ecx
.L561dfd:
 jmp .L561e13
.L561dff:
 {load} mov    ecx,edi
.L561e01:
 lea    edx,[ecx+0x2]
.L561e04:
 mov    ax,WORD PTR [ecx]
.L561e07:
 add    ecx,0x2
.L561e0a:
 test   ax,ax
.L561e0d:
 jne .L561e04
.L561e0f:
 {load} sub    ecx,edx
.L561e11:
 sar    ecx,1
.L561e13:
 push   ecx
.L561e14:
 push   edi
.L561e15:
 {load} mov    ecx,esi
.L561e17:
 call target_536160
.L561e1c:
 {load} mov    eax,esi
.L561e1e:
 mov    ecx,DWORD PTR [ebp-0xc]
.L561e21:
 mov    DWORD PTR fs:0x0,ecx
.L561e28:
 pop    ecx
.L561e29:
 pop    edi
.L561e2a:
 pop    esi
.L561e2b:
 pop    ebx
.L561e2c:
 {load} mov    esp,ebp
.L561e2e:
 pop    ebp
.L561e2f:
 ret
.equ target_44fc30,0x44fc30
.equ target_5360b0,0x5360b0
.equ target_536160,0x536160
