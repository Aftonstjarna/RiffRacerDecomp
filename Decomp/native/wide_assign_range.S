# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original objdump listings and private Ghidra exports:
# /tmp/cloud-path-refresh/{exports,*.asm,pe.txt,ghidra.log}; no shared DB writes.
# Exact function bodies; following INT3 padding excluded; no inline data.
# VA [0x44f9b0,0x44faa6); Ghidra inclusive end 0x44faa5.
# ECX=destination; stack source WCHAR pointer,count; EAX=this; RET 8.
# EBX/ESI/EDI(on nonalias path)/EBP preserved. Detects nonnull source within
# current [data,data+length) and delegates to unresolved substring assignment
# 0x44fb30(this, offset_in_WCHARs, count), preserving overlapping-source behavior.
# Otherwise guards count<=0x7ffffffe, grows via unresolved 0x44fde0,
# copies count*2 bytes through 0x8f8d66 (jmp IAT 0x92d494, memcpy), sets length
# and trailing UTF-16 NUL. Empty inline/heap and post-growth arms retained.
# capacity<8 selects inline buffer; IAT 0x92d168 throws std::_Xlength_error
# with original message at 0x99994c. No local SEH/cookie; exceptions propagate.
.intel_syntax noprefix
.code32
.text
.global original_wide_assign_range
original_wide_assign_range:
.L44f9b0:
 push   ebp
.L44f9b1:
 {load} mov    ebp,esp
.L44f9b3:
 push   ebx
.L44f9b4:
 mov    ebx,DWORD PTR [ebp+0x8]
.L44f9b7:
 push   esi
.L44f9b8:
 {load} mov    esi,ecx
.L44f9ba:
 test   ebx,ebx
.L44f9bc:
 je .L44fa06
.L44f9be:
 mov    ecx,DWORD PTR [esi+0x14]
.L44f9c1:
 cmp    ecx,0x8
.L44f9c4:
 jb .L44f9ca
.L44f9c6:
 mov    eax,DWORD PTR [esi]
.L44f9c8:
 jmp .L44f9cc
.L44f9ca:
 {load} mov    eax,esi
.L44f9cc:
 {load} cmp    ebx,eax
.L44f9ce:
 jb .L44fa06
.L44f9d0:
 cmp    ecx,0x8
.L44f9d3:
 jb .L44f9d9
.L44f9d5:
 mov    edx,DWORD PTR [esi]
.L44f9d7:
 jmp .L44f9db
.L44f9d9:
 {load} mov    edx,esi
.L44f9db:
 mov    eax,DWORD PTR [esi+0x10]
.L44f9de:
 lea    eax,[edx+eax*2]
.L44f9e1:
 {load} cmp    eax,ebx
.L44f9e3:
 jbe .L44fa06
.L44f9e5:
 cmp    ecx,0x8
.L44f9e8:
 jb .L44f9ee
.L44f9ea:
 mov    eax,DWORD PTR [esi]
.L44f9ec:
 jmp .L44f9f0
.L44f9ee:
 {load} mov    eax,esi
.L44f9f0:
 push   DWORD PTR [ebp+0xc]
.L44f9f3:
 {load} sub    ebx,eax
.L44f9f5:
 {load} mov    ecx,esi
.L44f9f7:
 sar    ebx,1
.L44f9f9:
 push   ebx
.L44f9fa:
 push   esi
.L44f9fb:
 call target_44fb30
.L44fa00:
 pop    esi
.L44fa01:
 pop    ebx
.L44fa02:
 pop    ebp
.L44fa03:
 ret    0x8
.L44fa06:
 push   edi
.L44fa07:
 mov    edi,DWORD PTR [ebp+0xc]
.L44fa0a:
 cmp    edi,0x7ffffffe
.L44fa10:
 jbe .L44fa1d
.L44fa12:
 push   0x99994c
.L44fa17:
 call   DWORD PTR [0x92d168]
.L44fa1d:
 mov    eax,DWORD PTR [esi+0x14]
.L44fa20:
 {load} cmp    eax,edi
.L44fa22:
 jae .L44fa3d
.L44fa24:
 push   DWORD PTR [esi+0x10]
.L44fa27:
 {load} mov    ecx,esi
.L44fa29:
 push   edi
.L44fa2a:
 call target_44fde0
.L44fa2f:
 test   edi,edi
.L44fa31:
 je .L44fa9d
.L44fa33:
 cmp    DWORD PTR [esi+0x14],0x8
.L44fa37:
 jb .L44fa67
.L44fa39:
 mov    ecx,DWORD PTR [esi]
.L44fa3b:
 jmp .L44fa69
.L44fa3d:
 test   edi,edi
.L44fa3f:
 jne .L44fa33
.L44fa41:
 mov    DWORD PTR [esi+0x10],edi
.L44fa44:
 cmp    eax,0x8
.L44fa47:
 jb .L44fa59
.L44fa49:
 mov    eax,DWORD PTR [esi]
.L44fa4b:
 {load} xor    ecx,ecx
.L44fa4d:
 pop    edi
.L44fa4e:
 mov    WORD PTR [eax],cx
.L44fa51:
 {load} mov    eax,esi
.L44fa53:
 pop    esi
.L44fa54:
 pop    ebx
.L44fa55:
 pop    ebp
.L44fa56:
 ret    0x8
.L44fa59:
 {load} mov    eax,esi
.L44fa5b:
 {load} xor    ecx,ecx
.L44fa5d:
 pop    edi
.L44fa5e:
 pop    esi
.L44fa5f:
 pop    ebx
.L44fa60:
 mov    WORD PTR [eax],cx
.L44fa63:
 pop    ebp
.L44fa64:
 ret    0x8
.L44fa67:
 {load} mov    ecx,esi
.L44fa69:
 test   edi,edi
.L44fa6b:
 je .L44fa7b
.L44fa6d:
 lea    eax,[edi+edi*1]
.L44fa70:
 push   eax
.L44fa71:
 push   ebx
.L44fa72:
 push   ecx
.L44fa73:
 call target_8f8d66
.L44fa78:
 add    esp,0xc
.L44fa7b:
 cmp    DWORD PTR [esi+0x14],0x8
.L44fa7f:
 mov    DWORD PTR [esi+0x10],edi
.L44fa82:
 jb .L44fa95
.L44fa84:
 mov    eax,DWORD PTR [esi]
.L44fa86:
 {load} xor    ecx,ecx
.L44fa88:
 mov    WORD PTR [eax+edi*2],cx
.L44fa8c:
 {load} mov    eax,esi
.L44fa8e:
 pop    edi
.L44fa8f:
 pop    esi
.L44fa90:
 pop    ebx
.L44fa91:
 pop    ebp
.L44fa92:
 ret    0x8
.L44fa95:
 {load} mov    eax,esi
.L44fa97:
 {load} xor    ecx,ecx
.L44fa99:
 mov    WORD PTR [eax+edi*2],cx
.L44fa9d:
 pop    edi
.L44fa9e:
 {load} mov    eax,esi
.L44faa0:
 pop    esi
.L44faa1:
 pop    ebx
.L44faa2:
 pop    ebp
.L44faa3:
 ret    0x8
.equ target_44fb30,0x44fb30
.equ target_44fde0,0x44fde0
.equ target_8f8d66,0x8f8d66
