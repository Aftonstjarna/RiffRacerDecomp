# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original instructions and private Ghidra exports in development:
# /tmp/cloud-string-growth/{*.asm,exports,eh-data.txt,messages.txt,pe.txt,ghidra.log}.
# Private Strings DB copied from /tmp/cloud-path-refresh; no shared DB writes.
# Exact instruction bodies; following INT3 padding excluded; no inline data.
# String layout: +0 inline WCHAR[8]/pointer, +0x10 length, +0x14 capacity;
# capacity<8 selects inline storage. External CRT/EH/data keep original VAs.
# VA [0x44fde0,0x44ff39); ECX=this; stack requested capacity,preserved length.
# RET 8; normal EAX=0; EBX/ESI/EDI/EBP preserved. Round request|7 unless
# beyond 0x7ffffffe. If old_capacity/2 > rounded_capacity/3, choose
# old_capacity+old_capacity/2 capped at 0x7ffffffe. Allocate (capacity+1)*2
# via operator new (0x92d4b4), memcpy preserved_length*2 through 0x8f8d66,
# delete old heap (0x92d4b0), publish pointer/capacity/length and WCHAR NUL.
# MSVC EH frame: saved ESP EBP-0x10, this -0x18, allocation -0x14, state -4,
# cookie -0x28. Normal exit restores FS:[0]; no normal cookie-check call.
# Handler 0x8ffa00 checks cookie then dispatches FuncInfo 0xb77f48 through
# 0x8f8968/__CxxFrameHandler3. FuncInfo magic=0x19930522, maxState=4;
# unwind map 0xb77f6c: (-1,0),(-1,0),(1,0),(1,0). Two try blocks at
# 0xb77f8c: [2,2],catchHigh=3,catch-all 0xb77fb4 -> 0x44feba;
# [0,0],catchHigh=3,catch-all 0xb77fc4 -> 0x44fe80 (adjectives=0x40).
# First allocation failure retries exact requested+1 WCHARs via 0x44ff40;
# catch funclet returns continuation VA 0x44fe9d in EAX, not a public return.
# Retry failure at 0x44feba frees old heap, resets inline capacity=7/length=0,
# writes NUL, then rethrows through 0x8f8d5a -> IAT 0x92d49c with (0,0).
# Ghidra omits continuation [0x44fe9d,0x44fea9) and catch [0x44feba,0x44fee8)
# from primary body. Original instructions and EH tables establish both as code
# in this span; all retained. Handler/FuncInfo/tables/CRT thunks/imports/cookie
# remain unreconstructed external dependencies, not evidence of a linked EXE.
.intel_syntax noprefix
.code32
.text
.global original_wide_grow
original_wide_grow:
.L44fde0:
 push   ebp
.L44fde1:
 {load} mov    ebp,esp
.L44fde3:
 push   0xffffffff
.L44fde5:
 push   0x8ffa00
.L44fdea:
 mov    eax,fs:0x0
.L44fdf0:
 push   eax
.L44fdf1:
 sub    esp,0xc
.L44fdf4:
 push   ebx
.L44fdf5:
 push   esi
.L44fdf6:
 push   edi
.L44fdf7:
 mov    eax,[0xbaabc0]
.L44fdfc:
 {load} xor    eax,ebp
.L44fdfe:
 push   eax
.L44fdff:
 lea    eax,[ebp-0xc]
.L44fe02:
 mov    fs:0x0,eax
.L44fe08:
 mov    DWORD PTR [ebp-0x10],esp
.L44fe0b:
 {load} mov    esi,ecx
.L44fe0d:
 mov    DWORD PTR [ebp-0x18],esi
.L44fe10:
 mov    eax,DWORD PTR [ebp+0x8]
.L44fe13:
 {load} mov    edi,eax
.L44fe15:
 or     edi,0x7
.L44fe18:
 cmp    edi,0x7ffffffe
.L44fe1e:
 jbe .L44fe24
.L44fe20:
 {load} mov    edi,eax
.L44fe22:
 jmp .L44fe4b
.L44fe24:
 mov    ebx,DWORD PTR [esi+0x14]
.L44fe27:
 mov    eax,0xaaaaaaab
.L44fe2c:
 mul    edi
.L44fe2e:
 {load} mov    ecx,ebx
.L44fe30:
 shr    ecx,1
.L44fe32:
 shr    edx,1
.L44fe34:
 {load} cmp    ecx,edx
.L44fe36:
 jbe .L44fe4b
.L44fe38:
 mov    eax,0x7ffffffe
.L44fe3d:
 lea    edi,[ecx+ebx*1]
.L44fe40:
 {load} sub    eax,ecx
.L44fe42:
 {load} cmp    ebx,eax
.L44fe44:
 jbe .L44fe4b
.L44fe46:
 mov    edi,0x7ffffffe
.L44fe4b:
 lea    eax,[edi+0x1]
.L44fe4e:
 mov    DWORD PTR [ebp-0x4],0x0
.L44fe55:
 {load} xor    ecx,ecx
.L44fe57:
 mov    DWORD PTR [ebp-0x14],ecx
.L44fe5a:
 test   eax,eax
.L44fe5c:
 je .L44fea9
.L44fe5e:
 cmp    eax,0x7fffffff
.L44fe63:
 ja .L44fe7a
.L44fe65:
 {load} add    eax,eax
.L44fe67:
 push   eax
.L44fe68:
 call   DWORD PTR [0x92d4b4]
.L44fe6e:
 {load} mov    ecx,eax
.L44fe70:
 add    esp,0x4
.L44fe73:
 mov    DWORD PTR [ebp-0x14],ecx
.L44fe76:
 test   ecx,ecx
.L44fe78:
 jne .L44fea9
.L44fe7a:
 call   DWORD PTR [0x92d164]
.L44fe80:
 mov    eax,DWORD PTR [ebp+0x8]
.L44fe83:
 mov    DWORD PTR [ebp+0x8],eax
.L44fe86:
 inc    eax
.L44fe87:
 mov    DWORD PTR [ebp-0x10],esp
.L44fe8a:
 push   eax
.L44fe8b:
 mov    BYTE PTR [ebp-0x4],0x2
.L44fe8f:
 call target_44ff40
.L44fe94:
 mov    DWORD PTR [ebp-0x14],eax
.L44fe97:
 mov    eax,0x44fe9d
.L44fe9c:
 ret
.L44fe9d:
 mov    ecx,DWORD PTR [ebp-0x14]
.L44fea0:
 mov    esi,DWORD PTR [ebp-0x18]
.L44fea3:
 mov    edi,DWORD PTR [ebp+0x8]
.L44fea6:
 mov    DWORD PTR [ebp-0x14],ecx
.L44fea9:
 mov    ebx,DWORD PTR [ebp+0xc]
.L44feac:
 test   ebx,ebx
.L44feae:
 je .L44fefc
.L44feb0:
 cmp    DWORD PTR [esi+0x14],0x8
.L44feb4:
 jb .L44fee8
.L44feb6:
 mov    edx,DWORD PTR [esi]
.L44feb8:
 jmp .L44feea
.L44feba:
 mov    esi,DWORD PTR [ebp-0x18]
.L44febd:
 cmp    DWORD PTR [esi+0x14],0x8
.L44fec1:
 jb .L44fece
.L44fec3:
 push   DWORD PTR [esi]
.L44fec5:
 call   DWORD PTR [0x92d4b0]
.L44fecb:
 add    esp,0x4
.L44fece:
 {load} xor    eax,eax
.L44fed0:
 mov    DWORD PTR [esi+0x14],0x7
.L44fed7:
 push   eax
.L44fed8:
 mov    DWORD PTR [esi+0x10],0x0
.L44fedf:
 push   eax
.L44fee0:
 mov    WORD PTR [esi],ax
.L44fee3:
 call target_8f8d5a
.L44fee8:
 {load} mov    edx,esi
.L44feea:
 test   ebx,ebx
.L44feec:
 je .L44fefc
.L44feee:
 lea    eax,[ebx+ebx*1]
.L44fef1:
 push   eax
.L44fef2:
 push   edx
.L44fef3:
 push   ecx
.L44fef4:
 call target_8f8d66
.L44fef9:
 add    esp,0xc
.L44fefc:
 cmp    DWORD PTR [esi+0x14],0x8
.L44ff00:
 jb .L44ff0d
.L44ff02:
 push   DWORD PTR [esi]
.L44ff04:
 call   DWORD PTR [0x92d4b0]
.L44ff0a:
 add    esp,0x4
.L44ff0d:
 mov    eax,DWORD PTR [ebp-0x14]
.L44ff10:
 mov    DWORD PTR [esi],eax
.L44ff12:
 mov    DWORD PTR [esi+0x14],edi
.L44ff15:
 mov    DWORD PTR [esi+0x10],ebx
.L44ff18:
 cmp    edi,0x8
.L44ff1b:
 jb .L44ff1f
.L44ff1d:
 {load} mov    esi,eax
.L44ff1f:
 {load} xor    eax,eax
.L44ff21:
 mov    WORD PTR [esi+ebx*2],ax
.L44ff25:
 mov    ecx,DWORD PTR [ebp-0xc]
.L44ff28:
 mov    DWORD PTR fs:0x0,ecx
.L44ff2f:
 pop    ecx
.L44ff30:
 pop    edi
.L44ff31:
 pop    esi
.L44ff32:
 pop    ebx
.L44ff33:
 {load} mov    esp,ebp
.L44ff35:
 pop    ebp
.L44ff36:
 ret    0x8
.equ target_44ff40,0x44ff40
.equ target_8f8d5a,0x8f8d5a
.equ target_8f8d66,0x8f8d66
