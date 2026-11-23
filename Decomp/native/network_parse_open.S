# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x56faa0,0x56fbb6); instruction-contiguous extent, INT3 padding excluded.
# Network stream open helper: references the networkParseOpen import and preserves the original SEH frame and cleanup. Called from the application worker.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x56faa0..0x56fbb6
.intel_syntax noprefix
.code32
.text
.global original_network_parse_open
original_network_parse_open:
.L56faa0:
 push   ebp
.L56faa1:
 {load} mov    ebp,esp
.L56faa3:
 push   0xffffffff
.L56faa5:
 push   0x907818
.L56faaa:
 mov    eax,fs:0x0
.L56fab0:
 push   eax
.L56fab1:
 push   ecx
.L56fab2:
 push   esi
.L56fab3:
 mov    eax,[0xbaabc0]
.L56fab8:
 {load} xor    eax,ebp
.L56faba:
 push   eax
.L56fabb:
 lea    eax,[ebp-0xc]
.L56fabe:
 mov    fs:0x0,eax
.L56fac4:
 cmp    DWORD PTR [0xbfcd38],0x0
.L56facb:
 mov    esi,DWORD PTR [0x92d4b4]
.L56fad1:
 jne .L56faf9
.L56fad3:
 push   0x8
.L56fad5:
 call   esi
.L56fad7:
 add    esp,0x4
.L56fada:
 test   eax,eax
.L56fadc:
 je .L56faf2
.L56fade:
 mov    [0xc0d57c],eax
.L56fae3:
 mov    DWORD PTR [eax],0xa00ffc
.L56fae9:
 mov    DWORD PTR [eax+0x4],0x0
.L56faf0:
 jmp .L56faf4
.L56faf2:
 {load} xor    eax,eax
.L56faf4:
 mov    [0xbfcd38],eax
.L56faf9:
 cmp    DWORD PTR [0xbfb610],0x0
.L56fb00:
 jne .L56fb31
.L56fb02:
 push   0x238
.L56fb07:
 call   esi
.L56fb09:
 add    esp,0x4
.L56fb0c:
 mov    DWORD PTR [ebp-0x10],eax
.L56fb0f:
 mov    DWORD PTR [ebp-0x4],0x0
.L56fb16:
 test   eax,eax
.L56fb18:
 je .L56fb23
.L56fb1a:
 {load} mov    ecx,eax
.L56fb1c:
 call target_414550
.L56fb21:
 jmp .L56fb25
.L56fb23:
 {load} xor    eax,eax
.L56fb25:
 mov    DWORD PTR [ebp-0x4],0xffffffff
.L56fb2c:
 mov    [0xbfb610],eax
.L56fb31:
 cmp    DWORD PTR [0xbfcd30],0x0
.L56fb38:
 jne .L56fb55
.L56fb3a:
 push   0x40
.L56fb3c:
 call   esi
.L56fb3e:
 add    esp,0x4
.L56fb41:
 test   eax,eax
.L56fb43:
 je .L56fb4e
.L56fb45:
 {load} mov    ecx,eax
.L56fb47:
 call target_56c910
.L56fb4c:
 jmp .L56fb50
.L56fb4e:
 {load} xor    eax,eax
.L56fb50:
 mov    [0xbfcd30],eax
.L56fb55:
 cmp    DWORD PTR [0xc0055c],0x0
.L56fb5c:
 jne .L56fb8a
.L56fb5e:
 push   0x10
.L56fb60:
 call   esi
.L56fb62:
 add    esp,0x4
.L56fb65:
 mov    DWORD PTR [ebp-0x10],eax
.L56fb68:
 mov    DWORD PTR [ebp-0x4],0x1
.L56fb6f:
 test   eax,eax
.L56fb71:
 je .L56fb7c
.L56fb73:
 {load} mov    ecx,eax
.L56fb75:
 call target_59ed70
.L56fb7a:
 jmp .L56fb7e
.L56fb7c:
 {load} xor    eax,eax
.L56fb7e:
 mov    DWORD PTR [ebp-0x4],0xffffffff
.L56fb85:
 mov    [0xc0055c],eax
.L56fb8a:
 call   DWORD PTR [0x92d500]
.L56fb90:
 mov    ecx,DWORD PTR [ebp-0xc]
.L56fb93:
 mov    DWORD PTR fs:0x0,ecx
.L56fb9a:
 pop    ecx
.L56fb9b:
 pop    esi
.L56fb9c:
 {load} mov    esp,ebp
.L56fb9e:
 pop    ebp
.L56fb9f:
 ret
.L56fba0:
 mov    eax,[0xbfb610]
.L56fba5:
 test   eax,eax
.L56fba7:
 je .L56fbad
.L56fba9:
 add    eax,0x4
.L56fbac:
 ret
.L56fbad:
 {load} xor    eax,eax
.L56fbaf:
 ret
.L56fbb0:
 mov    eax,[0xbfb610]
.L56fbb5:
 ret
.equ target_414550,0x414550
.equ target_56c910,0x56c910
.equ target_59ed70,0x59ed70
