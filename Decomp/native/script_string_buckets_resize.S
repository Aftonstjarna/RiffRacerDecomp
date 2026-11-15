# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x4f5d70,0x4f5e40); complete function, no embedded data.
.intel_syntax noprefix
.code32
.text
.global original_script_string_buckets_resize
.equ script_reallocate,0x4f7d10
.equ allocation_too_large,0x4f7cf0
original_script_string_buckets_resize:
# ECX = script state, EDX = new bucket count; no stack arguments.
 push   ebp
 mov.s    ebp,esp
 sub    esp,0x14
 push   ebx
 mov.s    ebx,ecx
 mov    DWORD PTR [ebp-0x4],edx
 mov    DWORD PTR [ebp-0x14],ebx
# Suppress resizing while the global GC-state byte is 2.
 mov    eax,DWORD PTR [ebx+0x10]
 cmp    BYTE PTR [eax+0x15],0x2
 je     L_4f5e3b
# Check allocation size, preserving the original error-return continuation.
 lea    eax,[edx+0x1]
 push   esi
 push   edi
 cmp    eax,0x3fffffff
 ja     L_4f5db3
 lea    eax,[edx*4+0x0]
 xor.s    edx,edx
 push   eax
 push   0x0
 call   script_reallocate
 mov.s    esi,eax
 add    esp,0x8
 mov    DWORD PTR [ebp-0x8],esi
 jmp    L_4f5dbd
L_4f5db3:
 call   allocation_too_large
 mov.s    esi,eax
 mov    DWORD PTR [ebp-0x8],eax
# Fetch global state after allocation; zero the new bucket array.
L_4f5dbd:
 mov    ecx,DWORD PTR [ebp-0x4]
 mov    ebx,DWORD PTR [ebx+0x10]
 mov    DWORD PTR [ebp-0x10],ebx
 test   ecx,ecx
 jle    L_4f5dd3
 xor.s    eax,eax
 mov.s    edi,esi
 rep stos DWORD PTR es:[edi],eax
 mov    ecx,DWORD PTR [ebp-0x4]
# Walk all old buckets, including empty ones.
L_4f5dd3:
 xor.s    edi,edi
 mov    DWORD PTR [ebp-0xc],edi
 cmp    DWORD PTR [ebx+0x8],edi
 jle    L_4f5e1b
 {disp8} lea    ecx,[ecx+0x0]
L_4f5de0:
 mov    eax,DWORD PTR [ebx]
 mov    eax,DWORD PTR [eax+edi*4]
 test   eax,eax
 je     L_4f5e0c
# Relink each chain by stored hash & (new_count - 1).
 mov    edi,DWORD PTR [ebp-0x8]
 lea    ebx,[ecx-0x1]
 nop
L_4f5df0:
 mov    ecx,DWORD PTR [eax+0x8]
 mov    esi,DWORD PTR [eax]
 and.s    ecx,ebx
 lea    edx,[edi+ecx*4]
 mov    ecx,DWORD PTR [edx]
 mov    DWORD PTR [eax],ecx
 mov    DWORD PTR [edx],eax
 mov.s    eax,esi
 test   esi,esi
 jne    L_4f5df0
 mov    edi,DWORD PTR [ebp-0xc]
 mov    ebx,DWORD PTR [ebp-0x10]
L_4f5e0c:
 mov    ecx,DWORD PTR [ebp-0x4]
 inc    edi
 mov    DWORD PTR [ebp-0xc],edi
 cmp    edi,DWORD PTR [ebx+0x8]
 jl     L_4f5de0
 mov    esi,DWORD PTR [ebp-0x8]
# Free old buckets, then install the new pointer and count.
L_4f5e1b:
 mov    eax,DWORD PTR [ebx+0x8]
 mov    edx,DWORD PTR [ebx]
 mov    ecx,DWORD PTR [ebp-0x14]
 shl    eax,0x2
 push   0x0
 push   eax
 call   script_reallocate
 mov    edx,DWORD PTR [ebp-0x4]
 add    esp,0x8
 mov    DWORD PTR [ebx],esi
 mov    DWORD PTR [ebx+0x8],edx
 pop    edi
 pop    esi
# Shared epilogue also serves the GC-state early exit.
L_4f5e3b:
 pop    ebx
 mov.s    esp,ebp
 pop    ebp
 ret
.section .note.GNU-stack,"",@progbits
