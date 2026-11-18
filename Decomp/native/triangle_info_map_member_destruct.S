# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x439290.
.intel_syntax noprefix
.code32
.text
.global original_triangle_info_map_member_destruct
original_triangle_info_map_member_destruct:
 push ebp
 mov.s ebp,esp
 push -1
 push 0x8feabe
 mov eax,fs:0
 push eax
 push ecx
 push esi
 mov eax,ds:0xbaabc0
 xor.s eax,ebp
 push eax
 lea eax,[ebp-0xc]
 mov fs:0,eax
 mov.s esi,ecx
 mov [ebp-0x10],esi
 mov DWORD PTR [ebp-4],2
 mov eax,[esi+0x48]
 test.s eax,eax
 je L1
 cmp BYTE PTR [esi+0x4c],0
 je L0
 inc DWORD PTR ds:0xbfcc18
 push eax
 call DWORD PTR ds:0x99a0bc
 add esp,4
L0:
 mov DWORD PTR [esi+0x48],0
L1:
 mov BYTE PTR [esi+0x4c],1
 mov DWORD PTR [esi+0x48],0
 mov DWORD PTR [esi+0x40],0
 mov DWORD PTR [esi+0x44],0
 mov BYTE PTR [ebp-4],1
 mov eax,[esi+0x34]
 test.s eax,eax
 je L3
 cmp BYTE PTR [esi+0x38],0
 je L2
 inc DWORD PTR ds:0xbfcc18
 push eax
 call DWORD PTR ds:0x99a0bc
 add esp,4
L2:
 mov DWORD PTR [esi+0x34],0
L3:
 mov BYTE PTR [esi+0x38],1
 mov DWORD PTR [esi+0x34],0
 mov DWORD PTR [esi+0x2c],0
 mov DWORD PTR [esi+0x30],0
 mov BYTE PTR [ebp-4],0
 mov eax,[esi+0x20]
 test.s eax,eax
 je L5
 cmp BYTE PTR [esi+0x24],0
 je L4
 inc DWORD PTR ds:0xbfcc18
 push eax
 call DWORD PTR ds:0x99a0bc
 add esp,4
L4:
 mov DWORD PTR [esi+0x20],0
L5:
 mov BYTE PTR [esi+0x24],1
 mov DWORD PTR [esi+0x20],0
 mov DWORD PTR [esi+0x18],0
 mov DWORD PTR [esi+0x1c],0
 mov DWORD PTR [ebp-4],-1
 mov eax,[esi+0xc]
 test.s eax,eax
 je L7
 cmp BYTE PTR [esi+0x10],0
 je L6
 inc DWORD PTR ds:0xbfcc18
 push eax
 call DWORD PTR ds:0x99a0bc
 add esp,4
L6:
 mov DWORD PTR [esi+0xc],0
L7:
 mov BYTE PTR [esi+0x10],1
 mov DWORD PTR [esi+0xc],0
 mov DWORD PTR [esi+4],0
 mov DWORD PTR [esi+8],0
 mov ecx,[ebp-0xc]
 mov DWORD PTR fs:0,ecx
 pop ecx
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
