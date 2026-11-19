.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x447e90.
.global original_screen_find_focused_item
original_screen_find_focused_item:
 push   ebp
 {load} mov    ebp,esp
 push   0xffffffff
 push   0x8ff549
 mov    eax,fs:0
 push   eax
 sub    esp,0xc
 push   ebx
 push   esi
 push   edi
 mov    eax,DWORD PTR [0xbaabc0]
 {load} xor    eax,ebp
 push   eax
 lea    eax,[ebp-0xc]
 mov    fs:0,eax
 {load} mov    ebx,ecx
 mov    DWORD PTR [ebp-0x18],0x0
 mov    al,BYTE PTR [ebx+0x174]
 mov    ecx,DWORD PTR [ebx+0x10]
 shr    al,0x2
 and    al,0x1
 cmp    ecx,0x1
 je L447f80
 cmp    ecx,0x2
 jne L447ee5
 test   al,al
 jne L447f80
L447ee5:
 {load} xor    esi,esi
 mov    DWORD PTR [ebp-0x10],esi
 mov    DWORD PTR [ebp-0x4],0x1
 mov    edi,DWORD PTR [ebx+0x178]
 cmp    edi,DWORD PTR [ebx+0x17c]
 je L447f42
 nop
L447f00:
 mov    ecx,DWORD PTR [edi]
 lea    eax,[ebp-0x14]
 push   eax
 call original_screen_find_focused_item
 mov    eax,DWORD PTR [eax]
 test   eax,eax
 je L447f19
 {load} mov    esi,eax
 mov    DWORD PTR [ebp-0x10],esi
 inc    DWORD PTR [esi+0x4]
L447f19:
 mov    BYTE PTR [ebp-0x4],0x1
 mov    ecx,DWORD PTR [ebp-0x14]
 test   ecx,ecx
 je L447f33
 dec    DWORD PTR [ecx+0x4]
 cmp    DWORD PTR [ecx+0x4],0x0
 jne L447f33
 mov    eax,DWORD PTR [ecx]
 push   0x1
 call   DWORD PTR [eax]
L447f33:
 test   esi,esi
 jne L447f42
 add    edi,0x4
 cmp    edi,DWORD PTR [ebx+0x17c]
 jne L447f00
L447f42:
 mov    edi,DWORD PTR [ebp+0x8]
 mov    DWORD PTR [edi],esi
 test   esi,esi
 je L447f4e
 inc    DWORD PTR [esi+0x4]
L447f4e:
 mov    DWORD PTR [ebp-0x18],0x1
 mov    BYTE PTR [ebp-0x4],0x0
 test   esi,esi
 je L447f6a
 dec    DWORD PTR [esi+0x4]
 jne L447f6a
 mov    edx,DWORD PTR [esi]
 {load} mov    ecx,esi
 push   0x1
 call   DWORD PTR [edx]
L447f6a:
 {load} mov    eax,edi
 mov    ecx,DWORD PTR [ebp-0xc]
 mov    DWORD PTR fs:0,ecx
 pop    ecx
 pop    edi
 pop    esi
 pop    ebx
 {load} mov    esp,ebp
 pop    ebp
 ret    0x4
L447f80:
 mov    eax,DWORD PTR [ebp+0x8]
 mov    DWORD PTR [eax],ebx
 inc    DWORD PTR [ebx+0x4]
 mov    ecx,DWORD PTR [ebp-0xc]
 mov    DWORD PTR fs:0,ecx
 pop    ecx
 pop    edi
 pop    esi
 pop    ebx
 {load} mov    esp,ebp
 pop    ebp
 ret    0x4
