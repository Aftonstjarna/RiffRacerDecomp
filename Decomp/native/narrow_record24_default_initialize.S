# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4268c0,0x4268ed); excludes INT3 padding.
.intel_syntax noprefix
.code32
.text
.global original_narrow_record24_default_initialize
original_narrow_record24_default_initialize:
 push ebp
 mov.s ebp,esp
 mov ecx,DWORD PTR [ebp+12]
 test ecx,ecx
 je done
 mov eax,DWORD PTR [ebp+8]
 {disp8} lea ecx,[ecx+0x00]
loop_record:
 test eax,eax
 je advance
 mov DWORD PTR [eax+20],15
 mov DWORD PTR [eax+16],0
 mov BYTE PTR [eax],0
advance:
 add eax,24
 dec ecx
 jne loop_record
done:
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
