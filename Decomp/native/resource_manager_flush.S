# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x542f80..0x5431ba exclusive.
.intel_syntax noprefix
.code32
.text
.global original_resource_manager_flush
original_resource_manager_flush:
.L542f80:
 push   ebp
.L542f81:
 {load} mov    ebp,esp
.L542f83:
 sub    esp,0x1c
.L542f86:
 mov    eax,[0xbaabc0]
.L542f8b:
 {load} xor    eax,ebp
.L542f8d:
 mov    DWORD PTR [ebp-0x4],eax
.L542f90:
 push   ebx
.L542f91:
 push   esi
.L542f92:
 mov    esi,DWORD PTR [0x92d024]
.L542f98:
 push   edi
.L542f99:
 {load} mov    edi,ecx
# Enter outer queue lock and inner producer lock.
.L542f9b:
 lea    eax,[edi+0x20]
.L542f9e:
 push   eax
.L542f9f:
 mov    DWORD PTR [ebp-0x14],eax
.L542fa2:
 call   esi
.L542fa4:
 lea    ebx,[edi+0x8]
.L542fa7:
 push   ebx
.L542fa8:
 call   esi
# Swap pending record and COM-release vectors, each three pointers.
.L542faa:
 lea    esi,[edi+0x50]
.L542fad:
 lea    edx,[edi+0x38]
.L542fb0:
 mov    DWORD PTR [ebp-0x18],esi
.L542fb3:
 {load} cmp    esi,edx
.L542fb5:
 je .L542fd7
.L542fb7:
 {load} mov    ecx,DWORD PTR [esi]
.L542fb9:
 {load} mov    eax,DWORD PTR [edx]
.L542fbb:
 mov    DWORD PTR [esi],eax
.L542fbd:
 mov    DWORD PTR [edx],ecx
.L542fbf:
 mov    ecx,DWORD PTR [esi+0x4]
.L542fc2:
 mov    eax,DWORD PTR [edx+0x4]
.L542fc5:
 mov    DWORD PTR [esi+0x4],eax
.L542fc8:
 mov    DWORD PTR [edx+0x4],ecx
.L542fcb:
 mov    ecx,DWORD PTR [esi+0x8]
.L542fce:
 mov    eax,DWORD PTR [edx+0x8]
.L542fd1:
 mov    DWORD PTR [esi+0x8],eax
.L542fd4:
 mov    DWORD PTR [edx+0x8],ecx
.L542fd7:
 lea    edx,[edi+0x44]
.L542fda:
 lea    eax,[edi+0x5c]
.L542fdd:
 {load} cmp    eax,edx
.L542fdf:
 je .L543002
.L542fe1:
 {load} mov    ecx,DWORD PTR [eax]
.L542fe3:
 {load} mov    eax,DWORD PTR [edx]
.L542fe5:
 mov    DWORD PTR [edi+0x5c],eax
.L542fe8:
 mov    DWORD PTR [edx],ecx
.L542fea:
 mov    ecx,DWORD PTR [edi+0x60]
.L542fed:
 mov    eax,DWORD PTR [edx+0x4]
.L542ff0:
 mov    DWORD PTR [edi+0x60],eax
.L542ff3:
 mov    DWORD PTR [edx+0x4],ecx
.L542ff6:
 mov    ecx,DWORD PTR [edi+0x64]
.L542ff9:
 mov    eax,DWORD PTR [edx+0x8]
.L542ffc:
 mov    DWORD PTR [edi+0x64],eax
.L542fff:
 mov    DWORD PTR [edx+0x8],ecx
.L543002:
 push   ebx
.L543003:
 call   DWORD PTR [0x92d028]
# Remove duplicate payload ownership from retained records.
.L543009:
 {load} mov    ecx,DWORD PTR [esi]
.L54300b:
 cmp    ecx,DWORD PTR [edi+0x54]
.L54300e:
 je .L54303c
.L543010:
 mov    eax,DWORD PTR [edi+0x68]
.L543013:
 cmp    eax,DWORD PTR [edi+0x6c]
.L543016:
 je .L543034
.L543018:
 {load} mov    edx,DWORD PTR [eax]
.L54301a:
 {load} cmp    edx,DWORD PTR [ecx]
.L54301c:
 jne .L54302c
.L54301e:
 mov    DWORD PTR [eax+0x8],0x0
.L543025:
 mov    DWORD PTR [eax+0x10],0x0
.L54302c:
 add    eax,0x18
.L54302f:
 cmp    eax,DWORD PTR [edi+0x6c]
.L543032:
 jne .L543018
.L543034:
 add    ecx,0x18
.L543037:
 cmp    ecx,DWORD PTR [edi+0x54]
.L54303a:
 jne .L543010
# Merge 24-byte records, then empty retained queue.
.L54303c:
 push   DWORD PTR [ebp-0x14]
.L54303f:
 lea    ebx,[edi+0x68]
.L543042:
 {load} mov    ecx,esi
.L543044:
 push   DWORD PTR [edi+0x6c]
.L543047:
 push   DWORD PTR [ebx]
.L543049:
 push   DWORD PTR [edi+0x54]
.L54304c:
 call target_5433a0
.L543051:
 {load} mov    eax,DWORD PTR [ebx]
.L543053:
 mov    DWORD PTR [ebx+0x4],eax
.L543056:
 {load} mov    esi,DWORD PTR [esi]
.L543058:
 cmp    esi,DWORD PTR [edi+0x54]
.L54305b:
 je .L54317a
# Process pending records: retry count, decode payload or release COM.
.L543061:
 mov    ecx,0x1
.L543066:
 mov    eax,DWORD PTR [esi+0x10]
.L543069:
 test   eax,eax
.L54306b:
 je .L54307e
.L54306d:
 dec    eax
.L54306e:
 {load} mov    ecx,ebx
.L543070:
 push   esi
.L543071:
 mov    DWORD PTR [esi+0x10],eax
.L543074:
 call target_4b2500
.L543079:
 jmp .L543169
.L54307e:
 mov    edx,DWORD PTR [esi+0x8]
.L543081:
 test   edx,edx
.L543083:
 je .L543155
.L543089:
 cmp    DWORD PTR [esi+0x4],0x0
.L54308d:
 jne .L543151
.L543093:
 cmp    BYTE PTR [edi+0x74],0x0
.L543097:
 jne .L543151
# Classify DDS / PNG; immediates are signature constants.
.L54309d:
 cmp    DWORD PTR [edx],0x20534444
.L5430a3:
 jne .L5430ac
.L5430a5:
 mov    eax,0x4
.L5430aa:
 jmp .L5430da
.L5430ac:
 {load} mov    eax,DWORD PTR [edx]
.L5430ae:
 lea    ecx,[ebp-0xc]
.L5430b1:
 mov    DWORD PTR [ebp-0xc],0x474e5089
.L5430b8:
 mov    DWORD PTR [ebp-0x8],0xa1a0a0d
.L5430bf:
 {load} cmp    eax,DWORD PTR [ecx]
.L5430c1:
 jne .L5430d0
.L5430c3:
 mov    eax,DWORD PTR [edx+0x4]
.L5430c6:
 cmp    eax,DWORD PTR [ecx+0x4]
.L5430c9:
 mov    eax,0x3
.L5430ce:
 je .L5430d5
.L5430d0:
 mov    eax,0x2
.L5430d5:
 mov    ecx,0x1
# DDS mip count and cube flag select D3DX upload path.
.L5430da:
 mov    ebx,0x1
.L5430df:
 cmp    eax,0x4
.L5430e2:
 jne .L543119
.L5430e4:
 mov    ebx,DWORD PTR [edx+0x1c]
.L5430e7:
 test   ebx,ebx
.L5430e9:
 cmove  ebx,ecx
.L5430ec:
 test   DWORD PTR [edx+0x70],0x200
.L5430f3:
 je .L543119
.L5430f5:
 lea    eax,[ebp-0x10]
.L5430f8:
 mov    DWORD PTR [ebp-0x10],0x0
.L5430ff:
 push   eax
.L543100:
 push   DWORD PTR [esi+0xc]
.L543103:
 push   edx
.L543104:
 push   DWORD PTR [edi]
.L543106:
 call   DWORD PTR [0x92d660]
.L54310c:
 {load} mov    ecx,DWORD PTR [esi]
.L54310e:
 lea    ebx,[edi+0x68]
.L543111:
 mov    eax,DWORD PTR [ebp-0x10]
.L543114:
 mov    DWORD PTR [ecx+0x8],eax
.L543117:
 jmp .L543169
.L543119:
 {load} mov    eax,DWORD PTR [esi]
.L54311b:
 {load} xor    ecx,ecx
.L54311d:
 add    eax,0x8
.L543120:
 push   eax
.L543121:
 mov    eax,[0xbfcc44]
.L543126:
 push   0x0
.L543128:
 push   0x0
.L54312a:
 push   0x0
.L54312c:
 cmp    DWORD PTR [eax+0x7c],ecx
.L54312f:
 push   0xffffffff
.L543131:
 push   0xffffffff
.L543133:
 sete   cl
.L543136:
 push   ecx
.L543137:
 push   0x0
.L543139:
 push   0x0
.L54313b:
 push   ebx
.L54313c:
 push   0xfffffffe
.L54313e:
 push   0xfffffffe
.L543140:
 push   DWORD PTR [esi+0xc]
.L543143:
 push   edx
.L543144:
 push   DWORD PTR [edi]
.L543146:
 call   DWORD PTR [0x92d668]
.L54314c:
 lea    ebx,[edi+0x68]
.L54314f:
 jmp .L543169
# Release obsolete COM handle when no payload is present.
.L543151:
 test   edx,edx
.L543153:
 jne .L54316e
.L543155:
 mov    ecx,DWORD PTR [esi+0x4]
.L543158:
 test   ecx,ecx
.L54315a:
 je .L543169
.L54315c:
 {load} mov    eax,DWORD PTR [ecx]
.L54315e:
 push   ecx
.L54315f:
 call   DWORD PTR [eax+0x8]
.L543162:
 mov    DWORD PTR [esi+0x4],0x0
.L543169:
 mov    ecx,0x1
.L54316e:
 add    esi,0x18
.L543171:
 cmp    esi,DWORD PTR [edi+0x54]
.L543174:
 jne .L543066
# Release queued COM pointers and reset consumed queue ends.
.L54317a:
 mov    esi,DWORD PTR [edi+0x5c]
.L54317d:
 cmp    esi,DWORD PTR [edi+0x60]
.L543180:
 je .L543192
.L543182:
 {load} mov    eax,DWORD PTR [esi]
.L543184:
 push   eax
.L543185:
 {load} mov    ecx,DWORD PTR [eax]
.L543187:
 call   DWORD PTR [ecx+0x8]
.L54318a:
 add    esi,0x4
.L54318d:
 cmp    esi,DWORD PTR [edi+0x60]
.L543190:
 jne .L543182
.L543192:
 mov    ecx,DWORD PTR [ebp-0x18]
.L543195:
 push   DWORD PTR [ebp-0x14]
.L543198:
 {load} mov    eax,DWORD PTR [ecx]
.L54319a:
 mov    DWORD PTR [ecx+0x4],eax
.L54319d:
 mov    eax,DWORD PTR [edi+0x5c]
.L5431a0:
 mov    DWORD PTR [edi+0x60],eax
.L5431a3:
 call   DWORD PTR [0x92d028]
# Original stack-cookie verification and complete epilogue.
.L5431a9:
 mov    ecx,DWORD PTR [ebp-0x4]
.L5431ac:
 pop    edi
.L5431ad:
 pop    esi
.L5431ae:
 {load} xor    ecx,ebp
.L5431b0:
 pop    ebx
.L5431b1:
 call target_8f8958
.L5431b6:
 {load} mov    esp,ebp
.L5431b8:
 pop    ebp
.L5431b9:
 ret
.equ target_4b2500,0x4b2500
.equ target_5433a0,0x5433a0
.equ target_8f8958,0x8f8958
.section .note.GNU-stack,"",@progbits
