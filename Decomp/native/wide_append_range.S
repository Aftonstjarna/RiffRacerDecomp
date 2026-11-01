# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Evidence: /tmp/reriff-recovery-resume/{exports,*.asm,ghidra.log}.
# Private copy of Strings Ghidra DB; existing research databases unchanged.
# Reviewed original [0x44ff80,0x45004f), including EH-only landing pad
# 0x45000d..0x45003b omitted from Ghidra's normal-flow function extent.
# ECX=wide-string object; stack first/end WCHAR pointers and unused tag; RET 12.
# Optionally reserves (end-first)/2 capacity, restores previous length/NUL,
# then appends each WCHAR using 0x44f8f0. No invented interpretation of ECX
# after helper calls: its unused stack argument is preserved as emitted.
# On exception: free heap when capacity>=8, reset to empty inline string,
# rethrow via _CxxThrowException(0,0). Retains fs:[0] registration and cookie.
# The following adjustor thunks at 0x45004f and 0x450057 are excluded.
# Original VA range 0x44ff80..0x45004f
.intel_syntax noprefix
.code32
.text
.global original_wide_append_range
original_wide_append_range:
.L44ff80:
 push   ebp
.L44ff81:
 {load} mov    ebp,esp
.L44ff83:
 push   0xffffffff
.L44ff85:
 push   0x8ffa20
.L44ff8a:
 mov    eax,fs:0x0
.L44ff90:
 push   eax
.L44ff91:
 sub    esp,0x8
.L44ff94:
 push   ebx
.L44ff95:
 push   esi
.L44ff96:
 push   edi
.L44ff97:
 mov    eax,[0xbaabc0]
.L44ff9c:
 {load} xor    eax,ebp
.L44ff9e:
 push   eax
.L44ff9f:
 lea    eax,[ebp-0xc]
.L44ffa2:
 mov    fs:0x0,eax
.L44ffa8:
 mov    DWORD PTR [ebp-0x10],esp
.L44ffab:
 {load} mov    edi,ecx
.L44ffad:
 mov    DWORD PTR [ebp-0x14],edi
.L44ffb0:
 mov    ebx,DWORD PTR [ebp+0xc]
.L44ffb3:
 {load} mov    eax,ebx
.L44ffb5:
 mov    esi,DWORD PTR [ebp+0x8]
.L44ffb8:
 {load} sub    eax,esi
.L44ffba:
 mov    ecx,DWORD PTR [edi+0x10]
.L44ffbd:
 sar    eax,1
.L44ffbf:
 mov    DWORD PTR [ebp+0xc],ecx
.L44ffc2:
 {load} cmp    ecx,eax
.L44ffc4:
 ja .L44fff1
.L44ffc6:
 cmp    DWORD PTR [edi+0x14],eax
.L44ffc9:
 je .L44fff1
.L44ffcb:
 push   0x1
.L44ffcd:
 push   eax
.L44ffce:
 {load} mov    ecx,edi
.L44ffd0:
 call target_44fc30
.L44ffd5:
 test   al,al
.L44ffd7:
 je .L44fff1
.L44ffd9:
 cmp    DWORD PTR [edi+0x14],0x8
.L44ffdd:
 mov    ecx,DWORD PTR [ebp+0xc]
.L44ffe0:
 mov    DWORD PTR [edi+0x10],ecx
.L44ffe3:
 jb .L44ffe9
.L44ffe5:
 mov    eax,DWORD PTR [edi]
.L44ffe7:
 jmp .L44ffeb
.L44ffe9:
 {load} mov    eax,edi
.L44ffeb:
 {load} xor    edx,edx
.L44ffed:
 mov    WORD PTR [eax+ecx*2],dx
.L44fff1:
 mov    DWORD PTR [ebp-0x4],0x0
.L44fff8:
 {load} cmp    esi,ebx
.L44fffa:
 je .L45003b
.L44fffc:
 movzx  eax,WORD PTR [esi]
.L44ffff:
 push   eax
.L450000:
 push   ecx
.L450001:
 {load} mov    ecx,edi
.L450003:
 call target_44f8f0
.L450008:
 add    esi,0x2
.L45000b:
 jmp .L44fff8
.L45000d:
 mov    esi,DWORD PTR [ebp-0x14]
.L450010:
 cmp    DWORD PTR [esi+0x14],0x8
.L450014:
 jb .L450021
.L450016:
 push   DWORD PTR [esi]
.L450018:
 call   DWORD PTR [0x92d4b0]
.L45001e:
 add    esp,0x4
.L450021:
 {load} xor    eax,eax
.L450023:
 mov    DWORD PTR [esi+0x14],0x7
.L45002a:
 push   eax
.L45002b:
 mov    DWORD PTR [esi+0x10],0x0
.L450032:
 push   eax
.L450033:
 mov    WORD PTR [esi],ax
.L450036:
 call target_8f8d5a
.L45003b:
 mov    ecx,DWORD PTR [ebp-0xc]
.L45003e:
 mov    DWORD PTR fs:0x0,ecx
.L450045:
 pop    ecx
.L450046:
 pop    edi
.L450047:
 pop    esi
.L450048:
 pop    ebx
.L450049:
 {load} mov    esp,ebp
.L45004b:
 pop    ebp
.L45004c:
 ret    0xc
.equ target_44f8f0,0x44f8f0
.equ target_44fc30,0x44fc30
.equ target_8f8d5a,0x8f8d5a
