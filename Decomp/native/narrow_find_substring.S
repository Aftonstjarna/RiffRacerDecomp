# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x440b90..0x440c2e exclusive; all three returns and loop included.
# Narrow substring search used by graphics-options; external memchr and byte-range-compare.
.intel_syntax noprefix
.code32
.text
.equ target_4225c0,0x4225c0
.equ target_92d474,0x92d474
.global original_narrow_find_substring
original_narrow_find_substring:
.L440b90:
 push   ebp
.L440b91:
 {load} mov    ebp,esp
.L440b93:
 mov    edx,DWORD PTR [ebp+0x10]
.L440b96:
 push   ebx
.L440b97:
 {load} mov    ebx,ecx
.L440b99:
 mov    ecx,DWORD PTR [ebp+0xc]
.L440b9c:
 test   edx,edx
.L440b9e:
 jne    .L440bac
.L440ba0:
 cmp    ecx,DWORD PTR [ebx+0x10]
.L440ba3:
 ja     .L440bac
.L440ba5:
 {load} mov    eax,ecx
.L440ba7:
 pop    ebx
.L440ba8:
 pop    ebp
.L440ba9:
 ret    0xc
.L440bac:
 push   esi
.L440bad:
 mov    esi,DWORD PTR [ebx+0x10]
.L440bb0:
 push   edi
.L440bb1:
 {load} cmp    ecx,esi
.L440bb3:
 jae    .L440c24
.L440bb5:
 {load} sub    esi,ecx
.L440bb7:
 {load} cmp    edx,esi
.L440bb9:
 ja     .L440c24
.L440bbb:
 mov    eax,0x1
.L440bc0:
 {load} sub    eax,edx
.L440bc2:
 {load} add    esi,eax
.L440bc4:
 cmp    DWORD PTR [ebx+0x14],0x10
.L440bc8:
 jb     .L440bce
.L440bca:
 mov    eax,DWORD PTR [ebx]
.L440bcc:
 jmp    .L440bd0
.L440bce:
 {load} mov    eax,ebx
.L440bd0:
 {load} add    ecx,eax
.L440bd2:
 mov    DWORD PTR [ebp+0xc],ecx
.L440bd5:
 test   esi,esi
.L440bd7:
 je     .L440c24
.L440bd9:
 mov    eax,DWORD PTR [ebp+0x8]
.L440bdc:
 push   esi
.L440bdd:
 movsx  eax,BYTE PTR [eax]
.L440be0:
 push   eax
.L440be1:
 push   ecx
.L440be2:
 call   DWORD PTR ds:target_92d474
.L440be8:
 {load} mov    edi,eax
.L440bea:
 add    esp,0xc
.L440bed:
 test   edi,edi
.L440bef:
 je     .L440c24
.L440bf1:
 push   DWORD PTR [ebp+0x10]
.L440bf4:
 push   DWORD PTR [ebp+0x8]
.L440bf7:
 push   edi
.L440bf8:
 call   target_4225c0
.L440bfd:
 add    esp,0xc
.L440c00:
 test   eax,eax
.L440c02:
 je     .L440c11
.L440c04:
 mov    ecx,DWORD PTR [ebp+0xc]
.L440c07:
 {load} sub    ecx,edi
.L440c09:
 dec    ecx
.L440c0a:
 {load} add    esi,ecx
.L440c0c:
 lea    ecx,[edi+0x1]
.L440c0f:
 jmp    .L440bd2
.L440c11:
 cmp    DWORD PTR [ebx+0x14],0x10
.L440c15:
 jb     .L440c19
.L440c17:
 mov    ebx,DWORD PTR [ebx]
.L440c19:
 {load} sub    edi,ebx
.L440c1b:
 {load} mov    eax,edi
.L440c1d:
 pop    edi
.L440c1e:
 pop    esi
.L440c1f:
 pop    ebx
.L440c20:
 pop    ebp
.L440c21:
 ret    0xc
.L440c24:
 pop    edi
.L440c25:
 pop    esi
.L440c26:
 or     eax,0xffffffff
.L440c29:
 pop    ebx
.L440c2a:
 pop    ebp
.L440c2b:
 ret    0xc
.section .note.GNU-stack,"",@progbits
