# Mechanically transcribed reference evidence; not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x41cd30,0x41cd5f); following INT3 excluded.
.intel_syntax noprefix
.code32
.text
.global original_pool32_table_initialize
original_pool32_table_initialize:
 mov BYTE PTR [0xbfcb30],0
 mov eax,0xbfbab4
 mov ecx,0x160
.Lclear_record:
 mov DWORD PTR [eax+4],0
 lea eax,[eax+0xc]
 mov DWORD PTR [eax-0xc],0
 mov DWORD PTR [eax-0x10],0
 dec ecx
 jne .Lclear_record
 ret 4
.section .note.GNU-stack,"",@progbits
