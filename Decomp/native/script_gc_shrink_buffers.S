# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f1b50,0x4f1bbc), including both returns.
.intel_syntax noprefix
.code32
.text
.global original_script_gc_shrink_buffers
.equ RESIZE_BUCKETS,0x4f5d70
.equ REALLOCATE,0x4f7d10
.equ TOO_LARGE,0x4f7cf0
original_script_gc_shrink_buffers:
 push ebx
 mov.s ebx,ecx
 push esi
 push edi
 mov esi,DWORD PTR [ebx+0x10]
 mov edi,DWORD PTR [esi+0x8]
 mov.s eax,edi
 cdq
 and edx,3
 add.s eax,edx
 sar eax,2
 cmp DWORD PTR [esi+4],eax
 jae .Lbuckets_done
 cmp edi,0x40
 jle .Lbuckets_done
 mov.s eax,edi
 cdq
 sub.s eax,edx
 sar eax,1
 mov.s edx,eax
 call RESIZE_BUCKETS
.Lbuckets_done:
 mov ecx,DWORD PTR [esi+0x3c]
 cmp ecx,0x40
 jbe .Ldone
 mov.s edi,ecx
 shr edi,1
 lea eax,[edi+1]
 cmp eax,0xfffffffd
 ja .Ltoo_large
 mov edx,DWORD PTR [esi+0x34]
 push edi
 push ecx
 mov.s ecx,ebx
 call REALLOCATE
 add esp,8
 mov DWORD PTR [esi+0x3c],edi
 mov DWORD PTR [esi+0x34],eax
 pop edi
 pop esi
 pop ebx
 ret
.Ltoo_large:
 mov.s ecx,ebx
 call TOO_LARGE
 mov DWORD PTR [esi+0x34],eax
 mov DWORD PTR [esi+0x3c],edi
.Ldone:
 pop edi
 pop esi
 pop ebx
 ret
.section .note.GNU-stack,"",@progbits
