.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x456e60.
.global original_font_glyph_lookup
original_font_glyph_lookup:
 push ebp
 {load} mov ebp, esp
 push esi
 push edi
 mov edi, DWORD PTR [ebp+0xc]
 {load} mov esi, ecx
 test edi, edi
 je .Lchar
 mov BYTE PTR [edi], 0
.Lchar:
 mov dx, WORD PTR [ebp+8]
 cmp dx, 0xd
 je .Lspecial
 cmp dx, 0xa
 je .Lspecial
 mov eax, DWORD PTR [esi+0x28]
 mov ecx, DWORD PTR [esi+0x2c]
 {load} cmp eax, ecx
 je .Lalternate
 jmp .Lprimary
 {disp8} lea ecx, [ecx+0]
.Lprimary:
 cmp WORD PTR [eax], dx
 je .Lreturn
 add eax, 0x2c
 {load} cmp eax, ecx
 jne .Lprimary
.Lalternate:
 test edi, edi
 je .Ldefault
 mov ecx, DWORD PTR [esi+0x68]
 test ecx, ecx
 je .Ldefault
 mov eax, DWORD PTR [ecx+0x28]
 mov ecx, DWORD PTR [ecx+0x2c]
 {load} cmp eax, ecx
 je .Ldefault
.Lalt_loop:
 cmp WORD PTR [eax], dx
 je .Lalt_hit
 add eax, 0x2c
 {load} cmp eax, ecx
 jne .Lalt_loop
.Ldefault:
 mov eax, DWORD PTR [esi+0x34]
 pop edi
 pop esi
 pop ebp
 ret 8
.Lalt_hit:
 mov BYTE PTR [edi], 1
 pop edi
 pop esi
 pop ebp
 ret 8
.Lspecial:
 lea eax, [esi+0x38]
.Lreturn:
 pop edi
 pop esi
 pop ebp
 ret 8
