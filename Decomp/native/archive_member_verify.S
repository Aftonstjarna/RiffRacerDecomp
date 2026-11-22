# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x560cb0,0x561162); instruction-contiguous extent, padding excluded.
# Archive/member validation state machine: one stack record pointer, AL result and RET 4; walks the
# linked member records, sums decoded DWORDs modulo 2^32, compares against the stored value and
# uses the original synchronization/allocation import slots. Multi-return extent; no inline data.
# Derived from original instructions; earns reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x560cb0..0x561162
.intel_syntax noprefix
.code32
.text
.global original_archive_member_verify
original_archive_member_verify:
.L560cb0:
 push   ebp
.L560cb1:
 {load} mov    ebp,esp
.L560cb3:
 push   ebx
.L560cb4:
 push   esi
.L560cb5:
 push   edi
.L560cb6:
 mov    edi,DWORD PTR [ebp+0x8]
.L560cb9:
 {load} xor    ebx,ebx
.L560cbb:
 mov    esi,DWORD PTR [edi]
.L560cbd:
 test   esi,esi
.L560cbf:
 je .L560d86
.L560cc5:
 mov    eax,DWORD PTR [esi+0x3c]
.L560cc8:
 lea    edx,[esi+0x40]
.L560ccb:
 sub    esp,0x18
.L560cce:
 mov    DWORD PTR [esi+0x20],eax
.L560cd1:
 lea    eax,[esi+0x54]
.L560cd4:
 mov    DWORD PTR [esi+0x24],ebx
.L560cd7:
 {load} mov    ecx,esi
.L560cd9:
 mov    DWORD PTR [esi+0x18],ebx
.L560cdc:
 push   eax
.L560cdd:
 call target_5987c0
.L560ce2:
 {load} xor    ecx,ecx
.L560ce4:
 {load} mov    edx,eax
.L560ce6:
 add    esp,0x1c
.L560ce9:
 test   edx,edx
.L560ceb:
 sete   cl
.L560cee:
 mov    DWORD PTR [esi+0x28],ecx
.L560cf1:
 test   edx,edx
.L560cf3:
 jne .L560d74
.L560cf5:
 mov    ecx,DWORD PTR [edi]
.L560cf7:
 {load} xor    eax,eax
.L560cf9:
 mov    DWORD PTR [ebp+0x8],eax
.L560cfc:
 test   ecx,ecx
.L560cfe:
 je .L560d29
.L560d00:
 cmp    DWORD PTR [ecx+0x28],eax
.L560d03:
 je .L560d29
.L560d05:
 mov    esi,DWORD PTR [ecx+0x20]
.L560d08:
 add    esi,DWORD PTR [ecx+0x10]
.L560d0b:
 mov    edx,DWORD PTR [ecx+0x24]
.L560d0e:
 adc    edx,DWORD PTR [ecx+0x14]
.L560d11:
 add    esi,0x10
.L560d14:
 {load} adc    edx,eax
.L560d16:
 mov    eax,DWORD PTR [ecx]
.L560d18:
 mov    DWORD PTR [eax+0x30],esi
.L560d1b:
 mov    DWORD PTR [eax+0x34],edx
.L560d1e:
 lea    edx,[ebp+0x8]
.L560d21:
 call target_5981c0
.L560d26:
 mov    eax,DWORD PTR [ebp+0x8]
.L560d29:
 mov    esi,DWORD PTR [edi]
.L560d2b:
 {load} add    ebx,eax
.L560d2d:
 test   esi,esi
.L560d2f:
 je .L560d86
.L560d31:
 cmp    DWORD PTR [esi+0x28],0x0
.L560d35:
 je .L560d79
.L560d37:
 mov    ecx,DWORD PTR [esi+0x18]
.L560d3a:
 inc    ecx
.L560d3b:
 cmp    ecx,DWORD PTR [esi+0x8]
.L560d3e:
 je .L560d79
.L560d40:
 mov    eax,DWORD PTR [esi+0x50]
.L560d43:
 lea    edx,[esi+0x40]
.L560d46:
 add    eax,0x2e
.L560d49:
 mov    DWORD PTR [esi+0x18],ecx
.L560d4c:
 add    DWORD PTR [esi+0x20],eax
.L560d4f:
 {load} mov    ecx,esi
.L560d51:
 lea    eax,[esi+0x54]
.L560d54:
 adc    DWORD PTR [esi+0x24],0x0
.L560d58:
 sub    esp,0x18
.L560d5b:
 push   eax
.L560d5c:
 call target_5987c0
.L560d61:
 {load} mov    edx,eax
.L560d63:
 add    esp,0x1c
.L560d66:
 {load} xor    eax,eax
.L560d68:
 test   edx,edx
.L560d6a:
 sete   al
.L560d6d:
 mov    DWORD PTR [esi+0x28],eax
.L560d70:
 test   edx,edx
.L560d72:
 je .L560cf5
.L560d74:
 cmp    edx,0xffffff9c
.L560d77:
 jne .L560d86
.L560d79:
 cmp    ebx,DWORD PTR [edi+0x10]
.L560d7c:
 sete   al
.L560d7f:
 pop    edi
.L560d80:
 pop    esi
.L560d81:
 pop    ebx
.L560d82:
 pop    ebp
.L560d83:
 ret    0x4
.L560d86:
 pop    edi
.L560d87:
 pop    esi
.L560d88:
 {load} xor    al,al
.L560d8a:
 pop    ebx
.L560d8b:
 pop    ebp
.L560d8c:
 ret    0x4
.L560d8f:
 int3
.L560d90:
 push   ebp
.L560d91:
 {load} mov    ebp,esp
.L560d93:
 and    esp,0xfffffff8
.L560d96:
 sub    esp,0x1c
.L560d99:
 push   ebx
.L560d9a:
 push   esi
.L560d9b:
 push   edi
.L560d9c:
 {load} mov    edi,ecx
.L560d9e:
 push   0xffffffff
.L560da0:
 mov    DWORD PTR [esp+0x20],edi
.L560da4:
 push   DWORD PTR [edi+0xdc]
.L560daa:
 call   DWORD PTR [0x92d124]
.L560db0:
 cmp    BYTE PTR [edi+0xed],0x0
.L560db7:
 jne .L561019
.L560dbd:
 lea    ebx,[edi+0x70]
.L560dc0:
 lea    ecx,[edi+0xac]
.L560dc6:
 push   ecx
.L560dc7:
 lea    esi,[edi+0x64]
.L560dca:
 call   DWORD PTR [0x92d024]
.L560dd0:
 mov    eax,DWORD PTR [ebx]
.L560dd2:
 mov    DWORD PTR [ebx+0x4],eax
.L560dd5:
 {load} cmp    ebx,esi
.L560dd7:
 je .L560df9
.L560dd9:
 {load} mov    ecx,eax
.L560ddb:
 mov    eax,DWORD PTR [esi]
.L560ddd:
 mov    DWORD PTR [ebx],eax
.L560ddf:
 mov    DWORD PTR [esi],ecx
.L560de1:
 mov    ecx,DWORD PTR [ebx+0x4]
.L560de4:
 mov    eax,DWORD PTR [esi+0x4]
.L560de7:
 mov    DWORD PTR [ebx+0x4],eax
.L560dea:
 mov    DWORD PTR [esi+0x4],ecx
.L560ded:
 mov    ecx,DWORD PTR [ebx+0x8]
.L560df0:
 mov    eax,DWORD PTR [esi+0x8]
.L560df3:
 mov    DWORD PTR [ebx+0x8],eax
.L560df6:
 mov    DWORD PTR [esi+0x8],ecx
.L560df9:
 lea    eax,[edi+0xac]
.L560dff:
 push   eax
.L560e00:
 call   DWORD PTR [0x92d028]
.L560e06:
 mov    esi,DWORD PTR [ebx]
.L560e08:
 cmp    esi,DWORD PTR [edi+0x74]
.L560e0b:
 je .L560ffe
.L560e11:
 lea    eax,[edi+0xc4]
.L560e17:
 lea    ebx,[edi+0x7c]
.L560e1a:
 mov    DWORD PTR [esp+0x18],eax
.L560e1e:
 {load} mov    edi,edi
.L560e20:
 mov    ecx,DWORD PTR [esi]
.L560e22:
 mov    edx,DWORD PTR [esi+0x10]
.L560e25:
 mov    DWORD PTR [esp+0x10],edx
.L560e29:
 test   ecx,ecx
.L560e2b:
 je .L560e83
.L560e2d:
 cmp    BYTE PTR [esi+0x14],0x0
.L560e31:
 je .L560e74
.L560e33:
 mov    DWORD PTR [esp+0x14],0x0
.L560e3b:
 {load} mov    edi,edx
.L560e3d:
 test   edx,edx
.L560e3f:
 je .L560eae
.L560e41:
 cmp    BYTE PTR [esi+0x15],0x0
.L560e45:
 jne .L560eaa
.L560e47:
 mov    ecx,DWORD PTR [esi]
.L560e49:
 cmp    edi,0x10000
.L560e4f:
 mov    eax,0x10000
.L560e54:
 {load} mov    edx,edi
.L560e56:
 cmova  edx,eax
.L560e59:
 push   edx
.L560e5a:
 mov    eax,DWORD PTR [ecx]
.L560e5c:
 push   DWORD PTR [esi+0xc]
.L560e5f:
 call   DWORD PTR [eax+0x8]
.L560e62:
 cmp    eax,0xffffffff
.L560e65:
 je .L560eaa
.L560e67:
 add    DWORD PTR [esp+0x14],eax
.L560e6b:
 add    DWORD PTR [esi+0xc],eax
.L560e6e:
 {load} sub    edi,eax
.L560e70:
 jne .L560e41
.L560e72:
 jmp .L560eaa
.L560e74:
 mov    eax,DWORD PTR [ecx]
.L560e76:
 push   edx
.L560e77:
 push   DWORD PTR [esi+0xc]
.L560e7a:
 call   DWORD PTR [eax+0x8]
.L560e7d:
 mov    DWORD PTR [esp+0x14],eax
.L560e81:
 jmp .L560eaa
.L560e83:
 push   0x0
.L560e85:
 push   0x0
.L560e87:
 push   DWORD PTR [esi+0x8]
.L560e8a:
 push   DWORD PTR [esi+0x4]
.L560e8d:
 call   DWORD PTR [0x92d0b4]
.L560e93:
 push   0x0
.L560e95:
 lea    eax,[esp+0x18]
.L560e99:
 push   eax
.L560e9a:
 push   DWORD PTR [esp+0x18]
.L560e9e:
 push   DWORD PTR [esi+0xc]
.L560ea1:
 push   DWORD PTR [esi+0x4]
.L560ea4:
 call   DWORD PTR [0x92d098]
.L560eaa:
 mov    edx,DWORD PTR [esp+0x10]
.L560eae:
 cmp    BYTE PTR [esi+0x15],0x0
.L560eb2:
 mov    eax,DWORD PTR [esi+0x1c]
.L560eb5:
 mov    DWORD PTR [esp+0x20],eax
.L560eb9:
 je .L560ec6
.L560ebb:
 mov    edi,0x5
.L560ec0:
 mov    DWORD PTR [esp+0x24],edi
.L560ec4:
 jmp .L560edc
.L560ec6:
 {load} xor    eax,eax
.L560ec8:
 cmp    DWORD PTR [esp+0x14],edx
.L560ecc:
 setne  al
.L560ecf:
 add    eax,0x3
.L560ed2:
 mov    DWORD PTR [esp+0x10],eax
.L560ed6:
 {load} mov    edi,eax
.L560ed8:
 mov    DWORD PTR [esp+0x24],eax
.L560edc:
 push   DWORD PTR [esp+0x18]
.L560ee0:
 call   DWORD PTR [0x92d024]
.L560ee6:
 mov    ecx,DWORD PTR [ebx+0x4]
.L560ee9:
 lea    eax,[esp+0x20]
.L560eed:
 {load} cmp    eax,ecx
.L560eef:
 jae .L560f75
.L560ef5:
 mov    eax,DWORD PTR [ebx]
.L560ef7:
 lea    edx,[esp+0x20]
.L560efb:
 {load} cmp    eax,edx
.L560efd:
 ja .L560f75
.L560eff:
 {load} mov    edi,edx
.L560f01:
 mov    edx,DWORD PTR [ebx+0x8]
.L560f04:
 {load} sub    edi,eax
.L560f06:
 sar    edi,0x3
.L560f09:
 {load} cmp    ecx,edx
.L560f0b:
 jne .L560f5e
.L560f0d:
 {load} mov    eax,edx
.L560f0f:
 {load} sub    eax,ecx
.L560f11:
 sar    eax,0x3
.L560f14:
 cmp    eax,0x1
.L560f17:
 jae .L560f5e
.L560f19:
 sub    ecx,DWORD PTR [ebx]
.L560f1b:
 mov    eax,0x1fffffff
.L560f20:
 sar    ecx,0x3
.L560f23:
 {load} sub    eax,ecx
.L560f25:
 cmp    eax,0x1
.L560f28:
 jb .L561022
.L560f2e:
 sub    edx,DWORD PTR [ebx]
.L560f30:
 inc    ecx
.L560f31:
 sar    edx,0x3
.L560f34:
 mov    eax,0x1fffffff
.L560f39:
 mov    DWORD PTR [esp+0x10],ecx
.L560f3d:
 {load} mov    ecx,edx
.L560f3f:
 shr    ecx,1
.L560f41:
 {load} sub    eax,ecx
.L560f43:
 {load} cmp    eax,edx
.L560f45:
 jae .L560f4b
.L560f47:
 {load} xor    edx,edx
.L560f49:
 jmp .L560f4d
.L560f4b:
 {load} add    edx,ecx
.L560f4d:
 cmp    edx,DWORD PTR [esp+0x10]
.L560f51:
 {load} mov    ecx,ebx
.L560f53:
 cmovb  edx,DWORD PTR [esp+0x10]
.L560f58:
 push   edx
.L560f59:
 call target_48a260
.L560f5e:
 mov    edx,DWORD PTR [ebx+0x4]
.L560f61:
 test   edx,edx
.L560f63:
 je .L560fdd
.L560f65:
 mov    ecx,DWORD PTR [ebx]
.L560f67:
 mov    eax,DWORD PTR [ecx+edi*8]
.L560f6a:
 mov    DWORD PTR [edx],eax
.L560f6c:
 mov    eax,DWORD PTR [ecx+edi*8+0x4]
.L560f70:
 mov    DWORD PTR [edx+0x4],eax
.L560f73:
 jmp .L560fdd
.L560f75:
 mov    edx,DWORD PTR [ebx+0x8]
.L560f78:
 {load} cmp    ecx,edx
.L560f7a:
 jne .L560fcd
.L560f7c:
 {load} mov    eax,edx
.L560f7e:
 {load} sub    eax,ecx
.L560f80:
 sar    eax,0x3
.L560f83:
 cmp    eax,0x1
.L560f86:
 jae .L560fcd
.L560f88:
 sub    ecx,DWORD PTR [ebx]
.L560f8a:
 mov    eax,0x1fffffff
.L560f8f:
 sar    ecx,0x3
.L560f92:
 {load} sub    eax,ecx
.L560f94:
 cmp    eax,0x1
.L560f97:
 jb .L561022
.L560f9d:
 sub    edx,DWORD PTR [ebx]
.L560f9f:
 inc    ecx
.L560fa0:
 sar    edx,0x3
.L560fa3:
 mov    eax,0x1fffffff
.L560fa8:
 mov    DWORD PTR [esp+0x10],ecx
.L560fac:
 {load} mov    ecx,edx
.L560fae:
 shr    ecx,1
.L560fb0:
 {load} sub    eax,ecx
.L560fb2:
 {load} cmp    eax,edx
.L560fb4:
 jae .L560fba
.L560fb6:
 {load} xor    edx,edx
.L560fb8:
 jmp .L560fbc
.L560fba:
 {load} add    edx,ecx
.L560fbc:
 cmp    edx,DWORD PTR [esp+0x10]
.L560fc0:
 {load} mov    ecx,ebx
.L560fc2:
 cmovb  edx,DWORD PTR [esp+0x10]
.L560fc7:
 push   edx
.L560fc8:
 call target_48a260
.L560fcd:
 mov    ecx,DWORD PTR [ebx+0x4]
.L560fd0:
 test   ecx,ecx
.L560fd2:
 je .L560fdd
.L560fd4:
 mov    eax,DWORD PTR [esp+0x20]
.L560fd8:
 mov    DWORD PTR [ecx],eax
.L560fda:
 mov    DWORD PTR [ecx+0x4],edi
.L560fdd:
 push   DWORD PTR [esp+0x18]
.L560fe1:
 add    DWORD PTR [ebx+0x4],0x8
.L560fe5:
 call   DWORD PTR [0x92d028]
.L560feb:
 mov    edi,DWORD PTR [esp+0x1c]
.L560fef:
 add    esi,0x24
.L560ff2:
 cmp    esi,DWORD PTR [edi+0x74]
.L560ff5:
 jne .L560e20
.L560ffb:
 lea    ebx,[edi+0x70]
.L560ffe:
 push   0xffffffff
.L561000:
 push   DWORD PTR [edi+0xdc]
.L561006:
 call   DWORD PTR [0x92d124]
.L56100c:
 cmp    BYTE PTR [edi+0xed],0x0
.L561013:
 je .L560dc0
.L561019:
 pop    edi
.L56101a:
 pop    esi
.L56101b:
 {load} xor    eax,eax
.L56101d:
 pop    ebx
.L56101e:
 {load} mov    esp,ebp
.L561020:
 pop    ebp
.L561021:
 ret
.L561022:
 push   0x9fdf88
.L561027:
 call   DWORD PTR [0x92d168]
.L56102d:
 int3
.L56102e:
 int3
.L56102f:
 int3
.L561030:
 push   ebp
.L561031:
 {load} mov    ebp,esp
.L561033:
 push   esi
.L561034:
 {load} mov    esi,ecx
.L561036:
 push   edi
.L561037:
 mov    edi,DWORD PTR [ebp+0x8]
.L56103a:
 cmp    DWORD PTR [esi+0xe4],edi
.L561040:
 jne .L56104c
.L561042:
 mov    DWORD PTR [esi+0xe4],0x0
.L56104c:
 cmp    DWORD PTR [esi+0xe8],edi
.L561052:
 jne .L56105e
.L561054:
 mov    DWORD PTR [esi+0xe8],0x0
.L56105e:
 mov    eax,DWORD PTR [esi+0x8c]
.L561064:
 mov    ecx,DWORD PTR [esi+0x90]
.L56106a:
 {load} cmp    eax,ecx
.L56106c:
 je .L56107b
.L56106e:
 {load} mov    edi,edi
.L561070:
 cmp    DWORD PTR [eax],edi
.L561072:
 je .L5610a7
.L561074:
 add    eax,0x4
.L561077:
 {load} cmp    eax,ecx
.L561079:
 jne .L561070
.L56107b:
 mov    eax,DWORD PTR [esi+0xa4]
.L561081:
 mov    ecx,DWORD PTR [esi+0xa8]
.L561087:
 {load} cmp    eax,ecx
.L561089:
 je .L56109f
.L56108b:
 jmp .L561090
.L56108d:
 {disp8} lea    ecx,[ecx+0x0]
.L561090:
 cmp    DWORD PTR [eax],edi
.L561092:
 je .L56113f
.L561098:
 add    eax,0x4
.L56109b:
 {load} cmp    eax,ecx
.L56109d:
 jne .L561090
.L56109f:
 pop    edi
.L5610a0:
 {load} xor    al,al
.L5610a2:
 pop    esi
.L5610a3:
 pop    ebp
.L5610a4:
 ret    0x4
.L5610a7:
 cmp    BYTE PTR [esi+0xf0],0x0
.L5610ae:
 je .L56111c
.L5610b0:
 mov    eax,DWORD PTR [esi+0x9c]
.L5610b6:
 lea    ecx,[ebp+0x8]
.L5610b9:
 add    esi,0x98
.L5610bf:
 {load} cmp    ecx,eax
.L5610c1:
 jae .L5610fa
.L5610c3:
 mov    ecx,DWORD PTR [esi]
.L5610c5:
 lea    edx,[ebp+0x8]
.L5610c8:
 {load} cmp    ecx,edx
.L5610ca:
 ja .L5610fa
.L5610cc:
 {load} mov    edi,edx
.L5610ce:
 {load} sub    edi,ecx
.L5610d0:
 sar    edi,0x2
.L5610d3:
 cmp    eax,DWORD PTR [esi+0x8]
.L5610d6:
 jne .L5610e0
.L5610d8:
 push   ecx
.L5610d9:
 {load} mov    ecx,esi
.L5610db:
 call target_561740
.L5610e0:
 mov    ecx,DWORD PTR [esi+0x4]
.L5610e3:
 test   ecx,ecx
.L5610e5:
 je .L5610ee
.L5610e7:
 mov    eax,DWORD PTR [esi]
.L5610e9:
 mov    eax,DWORD PTR [eax+edi*4]
.L5610ec:
 mov    DWORD PTR [ecx],eax
.L5610ee:
 add    DWORD PTR [esi+0x4],0x4
.L5610f2:
 mov    al,0x1
.L5610f4:
 pop    edi
.L5610f5:
 pop    esi
.L5610f6:
 pop    ebp
.L5610f7:
 ret    0x4
.L5610fa:
 cmp    eax,DWORD PTR [esi+0x8]
.L5610fd:
 jne .L561107
.L5610ff:
 push   ecx
.L561100:
 {load} mov    ecx,esi
.L561102:
 call target_561740
.L561107:
 mov    eax,DWORD PTR [esi+0x4]
.L56110a:
 test   eax,eax
.L56110c:
 je .L561110
.L56110e:
 mov    DWORD PTR [eax],edi
.L561110:
 add    DWORD PTR [esi+0x4],0x4
.L561114:
 mov    al,0x1
.L561116:
 pop    edi
.L561117:
 pop    esi
.L561118:
 pop    ebp
.L561119:
 ret    0x4
.L56111c:
 lea    edx,[eax+0x4]
.L56111f:
 {load} sub    ecx,edx
.L561121:
 and    ecx,0xfffffffc
.L561124:
 push   ecx
.L561125:
 push   edx
.L561126:
 push   eax
.L561127:
 call   DWORD PTR [0x92d4a4]
.L56112d:
 add    esp,0xc
.L561130:
 mov    al,0x1
.L561132:
 add    DWORD PTR [esi+0x90],0xfffffffc
.L561139:
 pop    edi
.L56113a:
 pop    esi
.L56113b:
 pop    ebp
.L56113c:
 ret    0x4
.L56113f:
 lea    edx,[eax+0x4]
.L561142:
 {load} sub    ecx,edx
.L561144:
 and    ecx,0xfffffffc
.L561147:
 push   ecx
.L561148:
 push   edx
.L561149:
 push   eax
.L56114a:
 call   DWORD PTR [0x92d4a4]
.L561150:
 add    esp,0xc
.L561153:
 mov    al,0x1
.L561155:
 add    DWORD PTR [esi+0xa8],0xfffffffc
.L56115c:
 pop    edi
.L56115d:
 pop    esi
.L56115e:
 pop    ebp
.L56115f:
 ret    0x4
.equ target_48a260,0x48a260
.equ target_561740,0x561740
.equ target_5981c0,0x5981c0
.equ target_5987c0,0x5987c0
