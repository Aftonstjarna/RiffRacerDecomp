# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f4fd0,0x4f501c); excludes following INT3 padding.
.intel_syntax noprefix
.code32
.text
.global original_script_callinfo_grow
.equ THROW_STATUS,0x4f4d80
.equ RESIZE_CALLINFO,0x4f4f50
.equ RUNTIME_ERROR,0x486ab0
.equ OVERFLOW_MESSAGE,0x9fd828
original_script_callinfo_grow:
 push esi
 mov.s esi,ecx
 mov edx,DWORD PTR [esi+0x30]
 cmp edx,0x4e20
 jle .Lresize
 mov edx,5
 call THROW_STATUS
 mov eax,DWORD PTR [esi+0x14]
 add eax,0x18
 mov DWORD PTR [esi+0x14],eax
 pop esi
 ret
.Lresize:
 add.s edx,edx
 call RESIZE_CALLINFO
 cmp DWORD PTR [esi+0x30],0x4e20
 jle .Ladvance
 push OVERFLOW_MESSAGE
 push esi
 call RUNTIME_ERROR
 add esp,8
.Ladvance:
 mov eax,DWORD PTR [esi+0x14]
 add eax,0x18
 mov DWORD PTR [esi+0x14],eax
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
