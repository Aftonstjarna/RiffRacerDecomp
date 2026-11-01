# Reviewed symbolic recovery from supported Game.exe SHA256
# 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Evidence: /tmp/cloud-request-review/{request.asm,exports/0048d870.txt,
# imports.txt,original.sha256}; private Ghidra Request project, read-only export.
# thiscall: ECX=worker, stack=(narrow-string reference, request value), AL=bool;
# RET 8, EBX/EDI/EBP preserved. Exact body ends at 48d9b3; INT3 excluded.
# Reset string via unresolved 48d630, delete[] old +3c/+44 buffers; zero
# +3c/+40/+44/+48 and flags +4c/+14c. Assign string via unresolved 415fe0
# unless aliased (after reset, as in original); store second argument at +38.
# String uses inline bytes below capacity 16, otherwise indirect storage.
# Manager c0d414 vslot +4 writes a resource reference to EBP-10, mode=1.
# Null or false resource vslot +4 returns false, releasing any reference.
# Otherwise vslot +18 supplies size, new[] 8f87c8 allocates +44, vslot +8
# reads (buffer,size); release reference, ResetEvent(+18), SetEvent(+14).
# Read/event return values are deliberately ignored, matching instructions.
# EH state becomes 0 only after manager call; allocation/read exceptions
# release EBP-10 via 901770. Success clears that local before event calls.
# Handler 901778 verifies cookie and uses FuncInfo b799dc; state-0 unwind
# map b79a00 is (-1,901770). Metadata remains external, not recovered here.
# No embedded data or format dispatch in this body; MP3/OGG/FLAC dispatch
# at already-covered 48d9c0 remains untouched. External targets remain gaps.
# Original VA range 0x48d870..0x48d9b3
.intel_syntax noprefix
.code32
.text
.global original_decode_request_prepare
original_decode_request_prepare:
.L48d870:
 push   ebp
.L48d871:
 {load} mov    ebp,esp
.L48d873:
 push   0xffffffff
.L48d875:
 push   0x901778
.L48d87a:
 mov    eax,fs:0x0
.L48d880:
 push   eax
.L48d881:
 push   ecx
.L48d882:
 push   ebx
.L48d883:
 push   edi
.L48d884:
 mov    eax,[0xbaabc0]
.L48d889:
 {load} xor    eax,ebp
.L48d88b:
 push   eax
.L48d88c:
 lea    eax,[ebp-0xc]
.L48d88f:
 mov    fs:0x0,eax
.L48d895:
 {load} mov    edi,ecx
.L48d897:
 lea    ebx,[edi+0x20]
.L48d89a:
 {load} mov    ecx,ebx
.L48d89c:
 call target_48d630
.L48d8a1:
 push   DWORD PTR [edi+0x3c]
.L48d8a4:
 call   DWORD PTR [0x92d4a0]
.L48d8aa:
 push   DWORD PTR [edi+0x44]
.L48d8ad:
 call   DWORD PTR [0x92d4a0]
.L48d8b3:
 mov    eax,DWORD PTR [ebp+0x8]
.L48d8b6:
 add    esp,0x8
.L48d8b9:
 mov    DWORD PTR [edi+0x3c],0x0
.L48d8c0:
 mov    DWORD PTR [edi+0x40],0x0
.L48d8c7:
 mov    DWORD PTR [edi+0x44],0x0
.L48d8ce:
 mov    DWORD PTR [edi+0x48],0x0
.L48d8d5:
 mov    BYTE PTR [edi+0x4c],0x0
.L48d8d9:
 mov    BYTE PTR [edi+0x14c],0x0
.L48d8e0:
 {load} cmp    ebx,eax
.L48d8e2:
 je .L48d8f0
.L48d8e4:
 push   0xffffffff
.L48d8e6:
 push   0x0
.L48d8e8:
 push   eax
.L48d8e9:
 {load} mov    ecx,ebx
.L48d8eb:
 call target_415fe0
.L48d8f0:
 mov    eax,DWORD PTR [ebp+0xc]
.L48d8f3:
 mov    DWORD PTR [edi+0x38],eax
.L48d8f6:
 cmp    DWORD PTR [ebx+0x14],0x10
.L48d8fa:
 mov    ecx,DWORD PTR [0xc0d414]
.L48d900:
 jb .L48d904
.L48d902:
 mov    ebx,DWORD PTR [ebx]
.L48d904:
 mov    eax,DWORD PTR [ecx]
.L48d906:
 lea    edx,[ebp-0x10]
.L48d909:
 push   0x1
.L48d90b:
 push   ebx
.L48d90c:
 push   edx
.L48d90d:
 call   DWORD PTR [eax+0x4]
.L48d910:
 mov    DWORD PTR [ebp-0x4],0x0
.L48d917:
 mov    ecx,DWORD PTR [ebp-0x10]
.L48d91a:
 test   ecx,ecx
.L48d91c:
 je .L48d982
.L48d91e:
 mov    eax,DWORD PTR [ecx]
.L48d920:
 mov    eax,DWORD PTR [eax+0x4]
.L48d923:
 call   eax
.L48d925:
 mov    ecx,DWORD PTR [ebp-0x10]
.L48d928:
 test   al,al
.L48d92a:
 je .L48d982
.L48d92c:
 mov    eax,DWORD PTR [ecx]
.L48d92e:
 call   DWORD PTR [eax+0x18]
.L48d931:
 push   eax
.L48d932:
 mov    DWORD PTR [edi+0x48],eax
.L48d935:
 call target_8f87c8
.L48d93a:
 mov    ecx,DWORD PTR [ebp-0x10]
.L48d93d:
 add    esp,0x4
.L48d940:
 mov    DWORD PTR [edi+0x44],eax
.L48d943:
 push   DWORD PTR [edi+0x48]
.L48d946:
 mov    edx,DWORD PTR [ecx]
.L48d948:
 push   eax
.L48d949:
 call   DWORD PTR [edx+0x8]
.L48d94c:
 mov    ecx,DWORD PTR [ebp-0x10]
.L48d94f:
 test   ecx,ecx
.L48d951:
 je .L48d969
.L48d953:
 dec    DWORD PTR [ecx+0x4]
.L48d956:
 cmp    DWORD PTR [ecx+0x4],0x0
.L48d95a:
 jne .L48d962
.L48d95c:
 mov    eax,DWORD PTR [ecx]
.L48d95e:
 push   0x1
.L48d960:
 call   DWORD PTR [eax]
.L48d962:
 mov    DWORD PTR [ebp-0x10],0x0
.L48d969:
 push   DWORD PTR [edi+0x18]
.L48d96c:
 call   DWORD PTR [0x92d104]
.L48d972:
 push   DWORD PTR [edi+0x14]
.L48d975:
 call   DWORD PTR [0x92d120]
.L48d97b:
 mov    ecx,DWORD PTR [ebp-0x10]
.L48d97e:
 mov    bl,0x1
.L48d980:
 jmp .L48d984
.L48d982:
 {load} xor    bl,bl
.L48d984:
 mov    DWORD PTR [ebp-0x4],0xffffffff
.L48d98b:
 test   ecx,ecx
.L48d98d:
 je .L48d99e
.L48d98f:
 dec    DWORD PTR [ecx+0x4]
.L48d992:
 cmp    DWORD PTR [ecx+0x4],0x0
.L48d996:
 jne .L48d99e
.L48d998:
 mov    edx,DWORD PTR [ecx]
.L48d99a:
 push   0x1
.L48d99c:
 call   DWORD PTR [edx]
.L48d99e:
 {load} mov    al,bl
.L48d9a0:
 mov    ecx,DWORD PTR [ebp-0xc]
.L48d9a3:
 mov    DWORD PTR fs:0x0,ecx
.L48d9aa:
 pop    ecx
.L48d9ab:
 pop    edi
.L48d9ac:
 pop    ebx
.L48d9ad:
 {load} mov    esp,ebp
.L48d9af:
 pop    ebp
.L48d9b0:
 ret    0x8
.equ target_415fe0,0x415fe0
.equ target_48d630,0x48d630
.equ target_8f87c8,0x8f87c8
