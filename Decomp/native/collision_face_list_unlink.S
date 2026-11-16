.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x549780,0x5497a9); excludes INT3 padding.
.global original_collision_face_list_unlink
original_collision_face_list_unlink:
push esi
mov esi,DWORD PTR [edx+0x34]
test esi,esi
je .Lnext_done
mov eax,DWORD PTR [edx+0x30]
mov DWORD PTR [esi+0x30],eax
.Lnext_done:
mov esi,DWORD PTR [edx+0x30]
test esi,esi
je .Lprev_done
mov eax,DWORD PTR [edx+0x34]
mov DWORD PTR [esi+0x34],eax
.Lprev_done:
pop esi
cmp edx,DWORD PTR [ecx]
jne .Lhead_done
mov eax,DWORD PTR [edx+0x34]
mov DWORD PTR [ecx],eax
.Lhead_done:
dec DWORD PTR [ecx+0x4]
ret
.section .note.GNU-stack,"",@progbits
