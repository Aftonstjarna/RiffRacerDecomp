# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA [0x4a5b00,0x4a5c35).
.intel_syntax noprefix
.code32
.text
.global original_graphics_frame_interval
.equ cookie_check,0x8f8958
.equ convert_double,0x8f9131
original_graphics_frame_interval:
L4a5b00:
 push ebp
L4a5b01:
 mov.s ebp,esp
L4a5b03:
 sub esp,0x28
L4a5b06:
 mov eax,DWORD PTR [0xbaabc0]
L4a5b0b:
 xor.s eax,ebp
L4a5b0d:
 mov DWORD PTR [ebp-0x4],eax
L4a5b10:
 push esi
L4a5b11:
 mov.s esi,ecx
L4a5b13:
 lea ecx,[ebp-0x14]
L4a5b16:
 push edi
L4a5b17:
 push ecx
L4a5b18:
 mov eax,DWORD PTR [esi+0x70]
L4a5b1b:
 push DWORD PTR [esi+0x6c]
L4a5b1e:
 push eax
L4a5b1f:
 mov edx,DWORD PTR [eax]
L4a5b21:
 call DWORD PTR [edx+0x20]
L4a5b24:
 test eax,eax
L4a5b26:
 js L4a5b6b
L4a5b28:
 mov eax,DWORD PTR [ebp-0xc]
L4a5b2b:
 test eax,eax
L4a5b2d:
 je L4a5b6b
L4a5b2f:
 movss xmm1,DWORD PTR [0xa0680c]
L4a5b37:
 movd xmm0,eax
L4a5b3b:
 cvtdq2pd xmm0,xmm0
L4a5b3f:
 shr eax,0x1f
L4a5b42:
 addsd xmm0,QWORD PTR [eax*8+0xa071b0]
L4a5b4b:
 cvtpd2ps xmm0,xmm0
L4a5b4f:
 divss xmm1,xmm0
L4a5b53:
 movss DWORD PTR [esi+0x4b4],xmm1
L4a5b5b:
 pop edi
L4a5b5c:
 pop esi
L4a5b5d:
 mov ecx,DWORD PTR [ebp-0x4]
L4a5b60:
 xor.s ecx,ebp
L4a5b62:
 call cookie_check
L4a5b67:
 mov.s esp,ebp
L4a5b69:
 pop ebp
L4a5b6a:
 ret
L4a5b6b:
 mov eax,DWORD PTR [esi+0x78]
L4a5b6e:
 push 0x0
L4a5b70:
 push 0x0
L4a5b72:
 push 0x0
L4a5b74:
 mov ecx,DWORD PTR [eax]
L4a5b76:
 push 0x0
L4a5b78:
 push eax
L4a5b79:
 call DWORD PTR [ecx+0x44]
L4a5b7c:
 mov eax,DWORD PTR [esi+0x78]
L4a5b7f:
 push 0x0
L4a5b81:
 push 0x0
L4a5b83:
 push 0x0
L4a5b85:
 mov ecx,DWORD PTR [eax]
L4a5b87:
 push 0x0
L4a5b89:
 push eax
L4a5b8a:
 call DWORD PTR [ecx+0x44]
L4a5b8d:
 mov eax,DWORD PTR [esi+0x78]
L4a5b90:
 push 0x0
L4a5b92:
 push 0x0
L4a5b94:
 push 0x0
L4a5b96:
 mov ecx,DWORD PTR [eax]
L4a5b98:
 push 0x0
L4a5b9a:
 push eax
L4a5b9b:
 call DWORD PTR [ecx+0x44]
L4a5b9e:
 lea eax,[ebp-0x20]
L4a5ba1:
 push eax
L4a5ba2:
 call DWORD PTR [0x92d0f4]
L4a5ba8:
 mov edi,0xa
L4a5bad:
 {disp8} lea ecx,[ecx]
L4a5bb0:
 mov eax,DWORD PTR [esi+0x78]
L4a5bb3:
 push 0x0
L4a5bb5:
 push 0x0
L4a5bb7:
 push 0x0
L4a5bb9:
 mov ecx,DWORD PTR [eax]
L4a5bbb:
 push 0x0
L4a5bbd:
 push eax
L4a5bbe:
 call DWORD PTR [ecx+0x44]
L4a5bc1:
 dec edi
L4a5bc2:
 jne L4a5bb0
L4a5bc4:
 lea eax,[ebp-0x28]
L4a5bc7:
 push eax
L4a5bc8:
 call DWORD PTR [0x92d0f4]
L4a5bce:
 mov eax,DWORD PTR [ebp-0x28]
L4a5bd1:
 sub eax,DWORD PTR [ebp-0x20]
L4a5bd4:
 movd xmm0,eax
L4a5bd8:
 cvtdq2pd xmm0,xmm0
L4a5bdc:
 shr eax,0x1f
L4a5bdf:
 addsd xmm0,QWORD PTR [eax*8+0xa071b0]
L4a5be8:
 divsd xmm0,QWORD PTR [0xc00b50]
L4a5bf0:
 call convert_double
L4a5bf5:
 pop edi
L4a5bf6:
 movd xmm0,eax
L4a5bfa:
 cvtdq2pd xmm0,xmm0
L4a5bfe:
 shr eax,0x1f
L4a5c01:
 addsd xmm0,QWORD PTR [eax*8+0xa071b0]
L4a5c0a:
 cvtpd2ps xmm0,xmm0
L4a5c0e:
 divss xmm0,DWORD PTR [0xa0680c]
L4a5c16:
 divss xmm0,DWORD PTR [0xa0675c]
L4a5c1e:
 movss DWORD PTR [esi+0x4b4],xmm0
L4a5c26:
 mov ecx,DWORD PTR [ebp-0x4]
L4a5c29:
 xor.s ecx,ebp
L4a5c2b:
 pop esi
L4a5c2c:
 call cookie_check
L4a5c31:
 mov.s esp,ebp
L4a5c33:
 pop ebp
L4a5c34:
 ret
.section .note.GNU-stack,"",@progbits
