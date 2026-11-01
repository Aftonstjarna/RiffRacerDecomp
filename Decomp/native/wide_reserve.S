# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Evidence: /tmp/reriff-recovery-resume/{exports,*.asm,ghidra.log}.
# Private copy of Strings Ghidra DB; existing research databases unchanged.
# Reviewed against Ghidra and original objdump: VA [0x44fc30,0x44fce6).
# ECX=wide-string object; stack count and trim flag; RET 8, boolean EAX.
# Length +0x10, capacity +0x14; inline WCHAR storage for capacity<8.
# Rejects count>0x7ffffffe via std::_Xlength_error. Calls recovered growth
# when capacity is insufficient. With trim and count<8, preserves min(length,
# count) characters, frees old heap storage and returns to inline capacity 7.
# Zero count clears length/NUL. External message/IAT remain original dependencies.
# Original VA range 0x44fc30..0x44fce6
.intel_syntax noprefix
.code32
.text
.global original_wide_reserve
original_wide_reserve:
.L44fc30:
 push   ebp
.L44fc31:
 {load} mov    ebp,esp
.L44fc33:
 push   esi
.L44fc34:
 push   edi
.L44fc35:
 mov    edi,DWORD PTR [ebp+0x8]
.L44fc38:
 {load} mov    esi,ecx
.L44fc3a:
 cmp    edi,0x7ffffffe
.L44fc40:
 jbe .L44fc4d
.L44fc42:
 push   0x99994c
.L44fc47:
 call   DWORD PTR [0x92d168]
.L44fc4d:
 mov    eax,DWORD PTR [esi+0x14]
.L44fc50:
 {load} cmp    eax,edi
.L44fc52:
 jae .L44fc6b
.L44fc54:
 push   DWORD PTR [esi+0x10]
.L44fc57:
 push   edi
.L44fc58:
 call target_44fde0
.L44fc5d:
 {load} xor    eax,eax
.L44fc5f:
 {load} cmp    eax,edi
.L44fc61:
 pop    edi
.L44fc62:
 {load} sbb    eax,eax
.L44fc64:
 neg    eax
.L44fc66:
 pop    esi
.L44fc67:
 pop    ebp
.L44fc68:
 ret    0x8
.L44fc6b:
 cmp    BYTE PTR [ebp+0xc],0x0
.L44fc6f:
 je .L44fcc5
.L44fc71:
 cmp    edi,0x8
.L44fc74:
 jae .L44fcc5
.L44fc76:
 push   ebx
.L44fc77:
 mov    ebx,DWORD PTR [esi+0x10]
.L44fc7a:
 {load} cmp    edi,ebx
.L44fc7c:
 cmovb  ebx,edi
.L44fc7f:
 cmp    eax,0x8
.L44fc82:
 jb .L44fca8
.L44fc84:
 mov    ecx,DWORD PTR [esi]
.L44fc86:
 mov    DWORD PTR [ebp+0xc],ecx
.L44fc89:
 test   ebx,ebx
.L44fc8b:
 je .L44fc9e
.L44fc8d:
 lea    eax,[ebx+ebx*1]
.L44fc90:
 push   eax
.L44fc91:
 push   ecx
.L44fc92:
 push   esi
.L44fc93:
 call target_8f8d66
.L44fc98:
 mov    ecx,DWORD PTR [ebp+0xc]
.L44fc9b:
 add    esp,0xc
.L44fc9e:
 push   ecx
.L44fc9f:
 call   DWORD PTR [0x92d4b0]
.L44fca5:
 add    esp,0x4
.L44fca8:
 {load} xor    eax,eax
.L44fcaa:
 mov    DWORD PTR [esi+0x10],ebx
.L44fcad:
 mov    DWORD PTR [esi+0x14],0x7
.L44fcb4:
 {load} cmp    eax,edi
.L44fcb6:
 mov    WORD PTR [esi+ebx*2],ax
.L44fcba:
 pop    ebx
.L44fcbb:
 {load} sbb    eax,eax
.L44fcbd:
 pop    edi
.L44fcbe:
 neg    eax
.L44fcc0:
 pop    esi
.L44fcc1:
 pop    ebp
.L44fcc2:
 ret    0x8
.L44fcc5:
 test   edi,edi
.L44fcc7:
 jne .L44fcd8
.L44fcc9:
 mov    DWORD PTR [esi+0x10],edi
.L44fccc:
 cmp    eax,0x8
.L44fccf:
 jb .L44fcd3
.L44fcd1:
 mov    esi,DWORD PTR [esi]
.L44fcd3:
 {load} xor    eax,eax
.L44fcd5:
 mov    WORD PTR [esi],ax
.L44fcd8:
 {load} xor    eax,eax
.L44fcda:
 {load} cmp    eax,edi
.L44fcdc:
 pop    edi
.L44fcdd:
 {load} sbb    eax,eax
.L44fcdf:
 neg    eax
.L44fce1:
 pop    esi
.L44fce2:
 pop    ebp
.L44fce3:
 ret    0x8
.equ target_44fde0,0x44fde0
.equ target_8f8d66,0x8f8d66
