.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f0b70,0x4f0ba8). String-key table lookup, complete leaf.
.global original_script_table_get_string
.equ NIL_VALUE,0x99a41c
original_script_table_get_string:
 push esi
 push edi
 mov.s edi,ecx
 mov eax,1
 mov cl,BYTE PTR [edi+7]
 shl eax,cl
 dec eax
 and eax,DWORD PTR [edx+8]
 lea esi,[eax+eax*4]
 mov eax,DWORD PTR [edi+0x10]
 pop edi
 lea eax,[eax+esi*4]
 pop esi
 {disp8} lea ecx,[ecx+0]
.Lprobe:
 cmp DWORD PTR [eax+0xc],4
 jne .Lnext
 cmp DWORD PTR [eax+8],edx
 je .Ldone
.Lnext:
 mov eax,DWORD PTR [eax+0x10]
 test eax,eax
 jne .Lprobe
 mov eax,NIL_VALUE
.Ldone:
 ret
.section .note.GNU-stack,"",@progbits
