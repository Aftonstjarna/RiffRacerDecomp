# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x5a1850,0x5a1942); instruction-contiguous extent, INT3 padding excluded.
# Secondary worker thread setup. The "-b" suffix is intentional: it shares the thread-creation call pattern with 0x528120 but its higher-level owner is not yet distinguished.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x5a1850..0x5a1942
.intel_syntax noprefix
.code32
.text
.global original_worker_thread_create_b
original_worker_thread_create_b:
.L5a1850:
 push   ebx
.L5a1851:
 {load} mov    ebx,ecx
.L5a1853:
 push   edi
.L5a1854:
 push   0x80001000
.L5a1859:
 lea    edi,[ebx+0xc]
.L5a185c:
 lea    eax,[ebx+0x10]
.L5a185f:
 mov    DWORD PTR [edi],0x0
.L5a1865:
 push   eax
.L5a1866:
 mov    DWORD PTR [ebx+0x4],0x0
.L5a186d:
 mov    DWORD PTR [ebx+0x8],0x0
.L5a1874:
 mov    DWORD PTR [ebx],0xa05a8c
.L5a187a:
 call   DWORD PTR [0x92d07c]
.L5a1880:
 mov    DWORD PTR [ebx+0x30],0xffffffff
.L5a1887:
 mov    DWORD PTR [ebx+0x34],0xffffffff
.L5a188e:
 push   0x0
.L5a1890:
 mov    DWORD PTR [ebx+0x38],0x0
.L5a1897:
 push   0x0
.L5a1899:
 mov    DWORD PTR [ebx+0x3c],0x0
.L5a18a0:
 mov    DWORD PTR [ebx+0x40],0x0
.L5a18a7:
 mov    DWORD PTR [ebx+0x44],0x0
.L5a18ae:
 mov    DWORD PTR [ebx+0x1048],0x0
.L5a18b8:
 push   0x0
.L5a18ba:
 mov    BYTE PTR [ebx+0x104c],0x0
.L5a18c1:
 push   0x0
.L5a18c3:
 mov    BYTE PTR [ebx+0x104d],0x0
.L5a18ca:
 call   DWORD PTR [0x92d114]
.L5a18d0:
 push   0x0
.L5a18d2:
 push   0x0
.L5a18d4:
 push   0x0
.L5a18d6:
 push   0x0
.L5a18d8:
 mov    DWORD PTR [ebx+0x28],eax
.L5a18db:
 call   DWORD PTR [0x92d114]
.L5a18e1:
 push   edi
.L5a18e2:
 push   0x0
.L5a18e4:
 push   ebx
.L5a18e5:
 push   0x48dc50
.L5a18ea:
 push   0x0
.L5a18ec:
 push   0x0
.L5a18ee:
 mov    DWORD PTR [ebx+0x2c],eax
.L5a18f1:
 call   DWORD PTR [0x92d37c]
.L5a18f7:
 add    esp,0x18
.L5a18fa:
 mov    DWORD PTR [ebx+0x8],eax
.L5a18fd:
 cmp    eax,0xffffffff
.L5a1900:
 je .L5a193d
.L5a1902:
 mov    ecx,DWORD PTR [ebx+0x4]
.L5a1905:
 {load} xor    edx,edx
.L5a1907:
 {load} sub    ecx,edx
.L5a1909:
 je .L5a1932
.L5a190b:
 dec    ecx
.L5a190c:
 je .L5a1923
.L5a190e:
 dec    ecx
.L5a190f:
 jne .L5a1935
.L5a1911:
 mov    edx,0x1
.L5a1916:
 push   edx
.L5a1917:
 push   eax
.L5a1918:
 call   DWORD PTR [0x92d0d8]
.L5a191e:
 pop    edi
.L5a191f:
 {load} mov    eax,ebx
.L5a1921:
 pop    ebx
.L5a1922:
 ret
.L5a1923:
 {load} xor    edx,edx
.L5a1925:
 push   edx
.L5a1926:
 push   eax
.L5a1927:
 call   DWORD PTR [0x92d0d8]
.L5a192d:
 pop    edi
.L5a192e:
 {load} mov    eax,ebx
.L5a1930:
 pop    ebx
.L5a1931:
 ret
.L5a1932:
 or     edx,0xffffffff
.L5a1935:
 push   edx
.L5a1936:
 push   eax
.L5a1937:
 call   DWORD PTR [0x92d0d8]
.L5a193d:
 pop    edi
.L5a193e:
 {load} mov    eax,ebx
.L5a1940:
 pop    ebx
.L5a1941:
 ret
