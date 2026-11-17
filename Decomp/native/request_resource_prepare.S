# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA [0x528d10,0x528e3a).
.intel_syntax noprefix
.code32
.text
.global original_request_resource_prepare
.L528d10:
original_request_resource_prepare:
 push ebp
.L528d11:
 mov.s ebp,esp
.L528d13:
 sub esp,0x18
.L528d16:
 push ebx
.L528d17:
 push esi
.L528d18:
 mov esi,DWORD PTR [ebp+0x8]
.L528d1b:
 mov.s ebx,ecx
.L528d1d:
 mov DWORD PTR [ebp-0x4],ebx
.L528d20:
 test esi,esi
.L528d22:
 jle .L528e32
.L528d28:
 mov edx,DWORD PTR [ebx+0x14]
.L528d2b:
 lea ecx,[ebx+0xc]
.L528d2e:
 sub edx,DWORD PTR [ecx]
.L528d30:
 mov eax,0x66666667
.L528d35:
 imul edx
.L528d37:
 sar edx,0x3
.L528d3a:
 mov.s eax,edx
.L528d3c:
 shr eax,0x1f
.L528d3f:
 add.s eax,edx
.L528d41:
 cmp.s eax,esi
.L528d43:
 jae .L528d5e
.L528d45:
 cmp esi,0xccccccc
.L528d4b:
 jbe .L528d58
.L528d4d:
 push 0x999938
.L528d52:
 call DWORD PTR [0x92d168]
.L528d58:
 push esi
.L528d59:
 call target_52c750
.L528d5e:
 mov ecx,DWORD PTR [ebx+0x20]
.L528d61:
 mov eax,0x66666667
.L528d66:
 sub ecx,DWORD PTR [ebx+0x18]
.L528d69:
 imul ecx
.L528d6b:
 push edi
.L528d6c:
 sar edx,0x4
.L528d6f:
 mov.s eax,edx
.L528d71:
 shr eax,0x1f
.L528d74:
 add.s eax,edx
.L528d76:
 cmp eax,0x4000
.L528d7b:
 jae .L528d8a
.L528d7d:
 push 0x4000
.L528d82:
 lea ecx,[ebx+0x18]
.L528d85:
 call target_429850
.L528d8a:
 mov eax,DWORD PTR [ebx+0x2c]
.L528d8d:
 lea ecx,[ebx+0x24]
.L528d90:
 sub eax,DWORD PTR [ecx]
.L528d92:
 sar eax,0x2
.L528d95:
 cmp eax,0x4000
.L528d9a:
 jae .L528da6
.L528d9c:
 push 0x4000
.L528da1:
 call target_426800
.L528da6:
 mov ecx,DWORD PTR [ebx+0x38]
.L528da9:
 mov eax,0x66666667
.L528dae:
 sub ecx,DWORD PTR [ebx+0x30]
.L528db1:
 imul ecx
.L528db3:
 sar edx,0x4
.L528db6:
 mov.s eax,edx
.L528db8:
 shr eax,0x1f
.L528dbb:
 add.s eax,edx
.L528dbd:
 cmp eax,0x40
.L528dc0:
 jae .L528dcc
.L528dc2:
 push 0x40
.L528dc4:
 lea ecx,[ebx+0x30]
.L528dc7:
 call target_52c880
.L528dcc:
 movss xmm0,DWORD PTR [ebx+0x40]
.L528dd1:
 mov eax,[0xbfcc44]
.L528dd6:
 mulss xmm0,DWORD PTR [0xa06800]
.L528dde:
 mov BYTE PTR [ebx+0x44],0x0
.L528de2:
 mov edi,DWORD PTR [eax+0x78]
.L528de5:
 call target_8f8f50
.L528dea:
 mov.s ebx,eax
.L528dec:
 test esi,esi
.L528dee:
 jle .L528e31
.L528df0:
 mov eax,DWORD PTR [edi]
.L528df2:
 lea ecx,[ebp-0x18]
.L528df5:
 push 0x0
.L528df7:
 push ecx
.L528df8:
 push 0x0
.L528dfa:
 push 0x15
.L528dfc:
 push 0x1
.L528dfe:
 push 0x1
.L528e00:
 push ebx
.L528e01:
 push ebx
.L528e02:
 push edi
.L528e03:
 call DWORD PTR [eax+0x5c]
.L528e06:
 test eax,eax
.L528e08:
 js .L528e2e
.L528e0a:
 mov ecx,DWORD PTR [ebp-0x4]
.L528e0d:
 lea eax,[ebp-0x18]
.L528e10:
 push eax
.L528e11:
 mov DWORD PTR [ebp-0x14],0x0
.L528e18:
 mov DWORD PTR [ebp-0x10],0x0
.L528e1f:
 lea ecx,[ecx+0xc]
.L528e22:
 mov DWORD PTR [ebp-0x8],0xffffffff
.L528e29:
 call target_52c610
.L528e2e:
 dec esi
.L528e2f:
 jne .L528df0
.L528e31:
 pop edi
.L528e32:
 pop esi
.L528e33:
 pop ebx
.L528e34:
 mov.s esp,ebp
.L528e36:
 pop ebp
.L528e37:
 ret 0x4
.equ target_52c750,0x52c750
.equ target_429850,0x429850
.equ target_426800,0x426800
.equ target_52c880,0x52c880
.equ target_8f8f50,0x8f8f50
.equ target_52c610,0x52c610
.section .note.GNU-stack,"",@progbits
