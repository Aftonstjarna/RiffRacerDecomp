.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x41a050.
.equ alloc_helper, 0x8f87c8
.equ clear_helper, 0x8f8d7e
.equ temp_construct, 0x426a30
.equ manager_get, 0x417270
.equ manager_insert, 0x41bf60
.equ temp_destroy, 0x426be0
.global original_resource_name_insert
original_resource_name_insert:
 push ebp
 {load} mov ebp, esp
 push -1
 push 0x8fd8c8
 mov eax, fs:[0]
 push eax
 sub esp, 0xc
 push esi
 mov eax, DWORD PTR [0xbaabc0]
 {load} xor eax, ebp
 push eax
 lea eax, [ebp-0xc]
 mov fs:[0], eax
 {load} mov esi, ecx
 cmp DWORD PTR [0xbfcb38], 0
 mov DWORD PTR [ebp-0x14], 0
 jne initialized
 push 0x20000
 call alloc_helper
 push 0x20000
 push 0
 push eax
 mov DWORD PTR [0xbfcb38], eax
 call clear_helper
 mov eax, DWORD PTR [0xbfcb38]
 add esp, 0x10
 mov DWORD PTR [eax], 0x80000001
 mov eax, DWORD PTR [0xbfcb38]
 mov DWORD PTR [eax+8], 0x4000bfff
initialized:
 mov DWORD PTR [ebp-0x10], 0
 push esi
 lea ecx, [ebp-0x14]
 mov DWORD PTR [ebp-4], 0
 call temp_construct
 call manager_get
 lea ecx, [ebp-0x14]
 push ecx
 lea ecx, [eax+4]
 call manager_insert
 lea ecx, [ebp-0x14]
 {load} mov esi, eax
 call temp_destroy
 {load} mov eax, esi
 mov ecx, DWORD PTR [ebp-0xc]
 mov DWORD PTR fs:[0], ecx
 pop ecx
 pop esi
 {load} mov esp, ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
