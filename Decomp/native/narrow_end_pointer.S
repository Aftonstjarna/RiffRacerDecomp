# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x440a60,0x440a89); both returns included; INT3 padding excluded.
# ECX = narrow string; stack argument = writable pointer-result slot.
# Capacity >=16 selects heap; otherwise storage is inline. Returns slot in EAX.
.intel_syntax noprefix
.code32
.text
.global original_narrow_end_pointer
original_narrow_end_pointer:
 push ebp
 {load} mov ebp,esp
 cmp DWORD PTR [ecx+0x14],0x10
 jb .Linline
 mov eax,DWORD PTR [ecx]
 mov ecx,DWORD PTR [ecx+0x10]
 {load} add ecx,eax
 mov eax,DWORD PTR [ebp+0x8]
 mov DWORD PTR [eax],ecx
 pop ebp
 ret 4
.Linline:
 {load} mov eax,ecx
 mov ecx,DWORD PTR [ecx+0x10]
 {load} add ecx,eax
 mov eax,DWORD PTR [ebp+0x8]
 mov DWORD PTR [eax],ecx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
