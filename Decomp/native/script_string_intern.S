# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f5e40,0x4f5fef); both returns included; trailing INT3 excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_string_intern
.equ runtime_error,0x486ab0
.equ resize_string_buckets,0x4f5d70
.equ script_reallocate,0x4f7d10
.equ memcpy_import,0x8f8d66
original_script_string_intern:
 push   ebp
 mov.s    ebp,esp
 and    esp,0xfffffff8
 sub    esp,0xc
 push   ebx
 push   esi
 push   edi
 mov    DWORD PTR [esp+0x10],edx
 mov    edx,DWORD PTR [ebp+0x8]
 mov.s    ebx,edx
 mov.s    edi,edx
 mov    DWORD PTR [esp+0xc],ecx
 shr    edi,0x5
 mov.s    esi,edx
 inc    edi
 cmp.s    edx,edi
 jb     hash_ready
 mov    edx,DWORD PTR [esp+0x10]
 {disp32} lea    esp,[esp+0x0]
# Sample hash at stride (length >> 5) + 1, from the end.
hash_sample:
 movzx  ecx,BYTE PTR [edx+esi*1-0x1]
 mov.s    eax,ebx
 shl    eax,0x5
 sub.s    esi,edi
 add.s    ecx,eax
 mov.s    eax,ebx
 shr    eax,0x2
 add.s    ecx,eax
 xor.s    ebx,ecx
 cmp.s    esi,edi
 jae    hash_sample
 mov    edx,DWORD PTR [ebp+0x8]
hash_ready:
 mov    esi,DWORD PTR [esp+0xc]
 mov    eax,DWORD PTR [esi+0x10]
 mov    DWORD PTR [esp+0x14],eax
 mov    ecx,DWORD PTR [eax+0x8]
 mov    eax,DWORD PTR [eax]
 dec    ecx
 and.s    ecx,ebx
 mov    edi,DWORD PTR [eax+ecx*4]
 test   edi,edi
 je     allocate_string
# Match stored length, then compare words and remaining bytes.
probe_node:
 cmp    DWORD PTR [edi+0xc],edx
 jne    next_node
 mov    esi,DWORD PTR [ebp+0x8]
 lea    eax,[edi+0x10]
 mov    edx,DWORD PTR [esp+0x10]
 sub    esi,0x4
 jb     compare_tail
 {disp8} lea    esp,[esp+0x0]
compare_words:
 mov    ecx,DWORD PTR [edx]
 cmp    ecx,DWORD PTR [eax]
 jne    compare_bytes
 add    edx,0x4
 add    eax,0x4
 sub    esi,0x4
 jae    compare_words
compare_tail:
 cmp    esi,0xfffffffc
 je     existing_string
compare_bytes:
 mov    cl,BYTE PTR [edx]
 cmp    cl,BYTE PTR [eax]
 jne    different_string
 cmp    esi,0xfffffffd
 je     existing_string
 mov    cl,BYTE PTR [edx+0x1]
 cmp    cl,BYTE PTR [eax+0x1]
 jne    different_string
 cmp    esi,0xfffffffe
 je     existing_string
 mov    cl,BYTE PTR [edx+0x2]
 cmp    cl,BYTE PTR [eax+0x2]
 jne    different_string
 cmp    esi,0xffffffff
 je     existing_string
 mov    cl,BYTE PTR [edx+0x3]
 cmp    cl,BYTE PTR [eax+0x3]
 je     existing_string
different_string:
 mov    edx,DWORD PTR [ebp+0x8]
next_node:
 mov    edi,DWORD PTR [edi]
 test   edi,edi
 jne    probe_node
 mov    esi,DWORD PTR [esp+0xc]
# Missing key: validate size, allocate header + bytes + terminator.
allocate_string:
 lea    eax,[edx+0x1]
 cmp    eax,0xffffffed
 jbe    allocation_size_ready
 push   0x9fdb34
 push   esi
 call   runtime_error
 mov    edx,DWORD PTR [ebp+0x8]
 add    esp,0x8
allocation_size_ready:
 lea    eax,[edx+0x11]
 mov.s    ecx,esi
 push   eax
 push   0x0
 xor.s    edx,edx
 call   script_reallocate
 mov    ecx,DWORD PTR [esp+0x14]
 mov.s    edi,eax
 mov    esi,DWORD PTR [ebp+0x8]
 push   esi
 push   DWORD PTR [esp+0x1c]
 mov    DWORD PTR [edi+0xc],esi
 lea    eax,[edi+0x10]
 mov    DWORD PTR [edi+0x8],ebx
 mov    ecx,DWORD PTR [ecx+0x10]
 push   eax
 mov    cl,BYTE PTR [ecx+0x14]
 and    cl,0x3
 mov    BYTE PTR [edi+0x4],0x4
 mov    BYTE PTR [edi+0x5],cl
 mov    BYTE PTR [edi+0x6],0x0
 call   memcpy_import
 mov    BYTE PTR [edi+esi*1+0x10],0x0
 add    esp,0x14
 mov    esi,DWORD PTR [esp+0xc]
 mov    edx,DWORD PTR [esi+0x10]
 mov    eax,DWORD PTR [edx+0x8]
 dec    eax
 and.s    eax,ebx
 {disp32} lea    ecx,[eax*4+0x0]
 mov    eax,DWORD PTR [edx]
 mov    eax,DWORD PTR [ecx+eax*1]
 mov    DWORD PTR [edi],eax
 mov    eax,DWORD PTR [edx]
 mov    DWORD PTR [ecx+eax*1],edi
 inc    DWORD PTR [edx+0x4]
 mov    eax,DWORD PTR [edx+0x8]
 cmp    DWORD PTR [edx+0x4],eax
 jbe    return_string
 cmp    eax,0x3ffffffe
 jg     return_string
 lea    edx,[eax+eax*1]
 mov.s    ecx,esi
 call   resize_string_buckets
return_string:
 mov.s    eax,edi
 pop    edi
 pop    esi
 pop    ebx
 mov.s    esp,ebp
 pop    ebp
 ret
# Existing key: reconcile white GC mark bits before returning.
existing_string:
 mov    ecx,DWORD PTR [esp+0x14]
 mov    al,BYTE PTR [edi+0x5]
 movzx  edx,al
 and    edx,0x3
 movzx  ecx,BYTE PTR [ecx+0x14]
 not    ecx
 test   cl,dl
 je     return_string
 xor    al,0x3
 mov    BYTE PTR [edi+0x5],al
 mov.s    eax,edi
 pop    edi
 pop    esi
 pop    ebx
 mov.s    esp,ebp
 pop    ebp
 ret
.section .note.GNU-stack,"",@progbits
