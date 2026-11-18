# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4f20e0.
.intel_syntax noprefix
.code32
.text
.global original_script_gc_begin_mark
.equ mark_object,0x4f0ef0
.equ mark_roots,0x4f1fe0
original_script_gc_begin_mark:
 push esi
 push edi
 mov.s edi,ecx
 mov esi,DWORD PTR [edi+0x10]
 mov edx,DWORD PTR [esi+0x64]
 mov DWORD PTR [esi+0x24],0
 mov DWORD PTR [esi+0x28],0
 mov DWORD PTR [esi+0x2c],0
 test BYTE PTR [edx+0x5],3
 je .Lfirst_done
 mov.s ecx,esi
 call mark_object
.Lfirst_done:
 mov eax,DWORD PTR [esi+0x64]
 cmp DWORD PTR [eax+0x4c],4
 jl .Lsecond_done
 mov edx,DWORD PTR [eax+0x48]
 test BYTE PTR [edx+0x5],3
 je .Lsecond_done
 mov.s ecx,esi
 call mark_object
.Lsecond_done:
 mov eax,DWORD PTR [edi+0x10]
 cmp DWORD PTR [eax+0x60],4
 jl .Lthird_done
 mov edx,DWORD PTR [eax+0x5c]
 test BYTE PTR [edx+0x5],3
 je .Lthird_done
 mov.s ecx,esi
 call mark_object
.Lthird_done:
 mov.s ecx,esi
 call mark_roots
 pop edi
 mov BYTE PTR [esi+0x15],1
 pop esi
 ret
