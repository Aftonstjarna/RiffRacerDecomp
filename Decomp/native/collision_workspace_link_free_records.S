.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x5497b0; exclusive end 0x549811.
.global original_collision_workspace_link_free_records
original_collision_workspace_link_free_records:
mov.s edx,ecx
xorps xmm0,xmm0
push esi
mov esi,0x80
mov DWORD PTR [edx],0x9
lea ecx,[edx+0x2600]
movdqu XMMWORD PTR [edx+0x28],xmm0
mov DWORD PTR [edx+0x38],0
mov DWORD PTR [edx+0x263c],0
{disp8} lea ecx,[ecx+0]
.Lrecord:
mov DWORD PTR [ecx+0x30],0
mov eax,DWORD PTR [edx+0x2648]
mov DWORD PTR [ecx+0x34],eax
mov eax,DWORD PTR [edx+0x2648]
test eax,eax
je .Lno_head
mov DWORD PTR [eax+0x30],ecx
.Lno_head:
inc DWORD PTR [edx+0x264c]
mov DWORD PTR [edx+0x2648],ecx
sub ecx,0x3c
dec esi
jne .Lrecord
pop esi
ret
