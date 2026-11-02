/* Provenance: depot SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
 * Evidence: /tmp/cloud-string-reset/{exports,narrow_string_reset.asm}.
 * ECX is the string object; no stack arguments. Aligned stack, dual GS cookies and FS exception registration retained. Empty SSO temporary swaps storage then length/capacity; former heap storage freed at capacity >=16. State remains -1; no active unwind action. No embedded data; excludes INT3 padding. Handler metadata at 0xb799a8 remains external.
 */
# Reviewed symbolic reconstruction; instruction encodings checked by native-check.
# Original VA range 0x48d630..0x48d6d6
.intel_syntax noprefix
.code32
.text
.global original_narrow_string_reset
original_narrow_string_reset:
.L48d630:
 push   ebp
.L48d631:
 {load} mov    ebp,esp
.L48d633:
 and    esp,0xfffffff8
.L48d636:
 push   0xffffffff
.L48d638:
 push   0x901748
.L48d63d:
 mov    eax,fs:0x0
.L48d643:
 push   eax
.L48d644:
 sub    esp,0x20
.L48d647:
 mov    eax,[0xbaabc0]
.L48d64c:
 {load} xor    eax,esp
.L48d64e:
 mov    DWORD PTR [esp+0x18],eax
.L48d652:
 push   esi
.L48d653:
 mov    eax,[0xbaabc0]
.L48d658:
 {load} xor    eax,esp
.L48d65a:
 push   eax
.L48d65b:
 lea    eax,[esp+0x28]
.L48d65f:
 mov    fs:0x0,eax
.L48d665:
 {load} mov    esi,ecx
.L48d667:
 mov    DWORD PTR [esp+0x1c],0xf
.L48d66f:
 mov    DWORD PTR [esp+0x18],0x0
.L48d677:
 mov    BYTE PTR [esp+0x8],0x0
.L48d67c:
 lea    eax,[esp+0x8]
.L48d680:
 {load} cmp    eax,esi
.L48d682:
 je .L48d6ba
.L48d684:
 push   esi
.L48d685:
 {load} mov    ecx,eax
.L48d687:
 call target_451b60
.L48d68c:
 mov    eax,DWORD PTR [esi+0x10]
.L48d68f:
 mov    ecx,DWORD PTR [esp+0x18]
.L48d693:
 mov    DWORD PTR [esi+0x10],ecx
.L48d696:
 mov    ecx,DWORD PTR [esi+0x14]
.L48d699:
 mov    DWORD PTR [esp+0x18],eax
.L48d69d:
 mov    eax,DWORD PTR [esp+0x1c]
.L48d6a1:
 mov    DWORD PTR [esp+0x1c],ecx
.L48d6a5:
 mov    DWORD PTR [esi+0x14],eax
.L48d6a8:
 cmp    ecx,0x10
.L48d6ab:
 jb .L48d6ba
.L48d6ad:
 push   DWORD PTR [esp+0x8]
.L48d6b1:
 call   DWORD PTR [0x92d4b0]
.L48d6b7:
 add    esp,0x4
.L48d6ba:
 mov    ecx,DWORD PTR [esp+0x28]
.L48d6be:
 mov    DWORD PTR fs:0x0,ecx
.L48d6c5:
 pop    ecx
.L48d6c6:
 pop    esi
.L48d6c7:
 mov    ecx,DWORD PTR [esp+0x18]
.L48d6cb:
 {load} xor    ecx,esp
.L48d6cd:
 call target_8f8958
.L48d6d2:
 {load} mov    esp,ebp
.L48d6d4:
 pop    ebp
.L48d6d5:
 ret
.equ target_451b60,0x451b60
.equ target_8f8958,0x8f8958
