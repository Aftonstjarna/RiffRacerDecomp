.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x560230.
.equ index_lookup, 0x598d50
.global original_mounted_archive_search
original_mounted_archive_search:
 push ebp
 {load} mov ebp, esp
 push ebx
 push esi
 push edi
 {load} mov edi, ecx
 mov eax, 0x66666667
 {load} xor ebx, ebx
 mov edx, DWORD PTR [edi+0x4c]
 sub edx, DWORD PTR [edi+0x48]
 imul edx
 sar edx, 3
 {load} mov eax, edx
 shr eax, 31
 {load} add eax, edx
 je .Lfailure
 {load} xor esi, esi
.Lloop:
 mov ecx, DWORD PTR [edi+0x48]
 push DWORD PTR [ebp+8]
 mov ecx, DWORD PTR [ecx+esi+8]
 call index_lookup
 {load} mov ecx, eax
 test ecx, ecx
 jne .Lsuccess
 mov ecx, DWORD PTR [edi+0x4c]
 mov eax, 0x66666667
 sub ecx, DWORD PTR [edi+0x48]
 inc ebx
 imul ecx
 add esi, 0x14
 sar edx, 3
 {load} mov eax, edx
 shr eax, 31
 {load} add eax, edx
 {load} cmp ebx, eax
 jb .Lloop
.Lfailure:
 mov eax, DWORD PTR [ebp+0xc]
 pop edi
 pop esi
 pop ebx
 mov DWORD PTR [eax], 0
 {load} xor eax, eax
 pop ebp
 ret 8
.Lsuccess:
 mov eax, DWORD PTR [ebp+0xc]
 pop edi
 pop esi
 mov DWORD PTR [eax], ebx
 {load} mov eax, ecx
 pop ebx
 pop ebp
 ret 8
