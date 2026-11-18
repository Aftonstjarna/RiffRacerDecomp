# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4f2190.
.intel_syntax noprefix
.code32
.text
.global original_script_gc_finish_mark
.equ scan_linked,0x4f2150
.equ propagate,0x4f17e0
.equ mark_object,0x4f0ef0
.equ scan_roots,0x4f1fe0
.equ helper_1090,0x4f1090
.equ helper_0fc0,0x4f0fc0
.equ helper_1900,0x4f1900
original_script_gc_finish_mark:
 push esi
 mov.s esi,ecx
 push edi
 mov edi,[esi+0x10]
 mov.s ecx,edi
 call scan_linked
 mov.s ecx,edi
 call propagate
 mov eax,[edi+0x2c]
 mov [edi+0x24],eax
 mov DWORD PTR [edi+0x2c],0
 test BYTE PTR [esi+5],3
 je .Lskip
 mov.s edx,esi
 mov.s ecx,edi
 call mark_object
.Lskip:
 mov.s ecx,edi
 call scan_roots
 mov.s ecx,edi
 call propagate
 mov eax,[edi+0x28]
 mov.s ecx,edi
 mov [edi+0x24],eax
 mov DWORD PTR [edi+0x28],0
 call propagate
 xor.s edx,edx
 mov.s ecx,esi
 call helper_1090
 mov.s ecx,edi
 mov.s esi,eax
 call helper_0fc0
 mov.s ecx,edi
 call propagate
 mov ecx,[edi+0x2c]
 add.s esi,eax
 call helper_1900
 xor BYTE PTR [edi+0x14],3
 lea eax,[edi+0x1c]
 mov [edi+0x20],eax
 mov eax,[edi+0x44]
 sub.s eax,esi
 mov DWORD PTR [edi+0x18],0
 mov BYTE PTR [edi+0x15],2
 mov [edi+0x48],eax
 pop edi
 pop esi
 ret
