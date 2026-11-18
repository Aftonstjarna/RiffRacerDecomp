# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x57ffe0.
.intel_syntax noprefix
.code32
.text
.global original_shader_global_resource_construct
.equ base_construct,0x5421b0
.equ finish_construct,0x542230
original_shader_global_resource_construct:
 push ebp
 mov.s ebp,esp
 push -1
 push 0x907fe8
 mov eax,fs:0
 push eax
 push ecx
 push esi
 mov eax,DWORD PTR [0xbaabc0]
 xor.s eax,ebp
 push eax
 lea eax,[ebp-0xc]
 mov fs:0,eax
 mov.s esi,ecx
 mov DWORD PTR [ebp-0x10],esi
 call base_construct
 mov DWORD PTR [ebp-4],0
 mov edx,DWORD PTR [0xbfcd04]
 mov DWORD PTR [esi],0xa02270
 push 0x9fe740
 push 0
 mov eax,DWORD PTR [edx+0x808]
 mov DWORD PTR [esi+4],eax
 mov eax,DWORD PTR [edx+0x810]
 mov DWORD PTR [esi+8],eax
 mov eax,DWORD PTR [edx+0x80c]
 mov DWORD PTR [esi+0x10],eax
 mov eax,DWORD PTR [edx+0x814]
 mov DWORD PTR [esi+0x14],eax
 mov eax,DWORD PTR [esi+0x10]
 push eax
 mov ecx,DWORD PTR [eax]
 call DWORD PTR [ecx+0x24]
 mov.s ecx,esi
 mov DWORD PTR [esi+0x58],eax
 call finish_construct
 mov.s eax,esi
 mov ecx,DWORD PTR [ebp-0xc]
 mov DWORD PTR fs:0,ecx
 pop ecx
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
