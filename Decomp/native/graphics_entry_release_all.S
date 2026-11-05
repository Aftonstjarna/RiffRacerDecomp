# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256:
# 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x4b2400..0x4b2476 (exclusive). Error tail follows normal ret.
.intel_syntax noprefix
.code32
.text
.global original_graphics_entry_release_all
original_graphics_entry_release_all:
 push ebp
 {load} mov ebp,esp
 # ECX is the table object; snapshot (end-begin)/12.
 sub esp,0x8
 mov edx,DWORD PTR [ecx+0x4]
 mov eax,0x2aaaaaab
 sub edx,DWORD PTR [ecx]
 imul edx
 push esi
 sar edx,1
 mov esi,0x0
 {load} mov eax,edx
 mov DWORD PTR [ebp-0x8],ecx
 shr eax,0x1f
 {load} add eax,edx
 mov DWORD PTR [ebp-0x4],eax
 je .Ldone
 push ebx
 push edi
 {load} xor edi,edi
 {disp8} lea ecx,[ecx+0x0]
.Lloop:
 # Recheck the current table size before each entry release.
 mov ebx,DWORD PTR [ecx]
 mov eax,0x2aaaaaab
 mov ecx,DWORD PTR [ecx+0x4]
 {load} sub ecx,ebx
 imul ecx
 sar edx,1
 {load} mov eax,edx
 shr eax,0x1f
 {load} add eax,edx
 {load} cmp eax,esi
 jbe .Lrange_error
 push 0x1
 lea ecx,[edi+ebx*1]
 call target_release_entry
 mov ecx,DWORD PTR [ebp-0x8]
 inc esi
 add edi,0xc
 cmp esi,DWORD PTR [ebp-0x4]
 jb .Lloop
 pop edi
 pop ebx
.Ldone:
 pop esi
 {load} mov esp,ebp
 pop ebp
 # One stack slot is unused by this body but is callee-popped.
 ret 0x4
.Lrange_error:
 # Original diagnostic string and MSVCP120 std::_Xout_of_range IAT.
 push 0x999ec8
 call DWORD PTR [0x92d16c]
 int3
.equ target_release_entry,0x49ca20
.section .note.GNU-stack,"",@progbits
