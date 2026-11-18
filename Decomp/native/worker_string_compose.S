# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x5c21d0.
.intel_syntax noprefix
.code32
.text
.global original_worker_string_compose
.equ append_range,0x4420b0
.equ move_construct,0x416af0
original_worker_string_compose:
 push ebp
 mov.s ebp,esp
 push ecx
 mov ecx,[ebp+0xc]
 push -1
 push 0
 push DWORD PTR [ebp+0x10]
 mov DWORD PTR [ebp-4],0
 call append_range
 mov ecx,[ebp+8]
 push eax
 call move_construct
 mov eax,[ebp+8]
 mov.s esp,ebp
 pop ebp
 ret
