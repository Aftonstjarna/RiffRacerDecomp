# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original objdump listings and private Ghidra exports:
# /tmp/cloud-path-refresh/{exports,*.asm,pe.txt,ghidra.log}; no shared DB writes.
# Exact function bodies; following INT3 padding excluded; no inline data.
# VA [0x535ec0,0x536023); Ghidra inclusive end 0x536022.
# ECX=this, no stack arguments, plain RET; ESI/EDI/EBP preserved; EAX unspecified.
# SHGetFolderPathW(0,0x1a,0,0,local WCHAR[260]) through IAT 0x92d510;
# negative HRESULT leaves path unchanged. Success assigns this+0x14, adds
# backslash, then this+0x2c when nonempty; otherwise adds UTF-16 Octane
# (0x9ffe00, six characters), backslash, and runtime-derived name; final slash.
# Raw instructions override Ghidra bogus extra API argument/fastcall inference.
# push ECX before append-char supplies its unused first stack slot, not a count.
# FS:[0] restored and cookie checked on normal exit. Temporary wide string
# at EBP-0x230 becomes live only at state 0 after 0x44f490 returns; normal
# cleanup resets state -1 before delete via IAT 0x92d4b0 (capacity>=8).
# Original handler 0x90633b validates two cookies then dispatches through
# 0x8f8968/__CxxFrameHandler3 with FuncInfo 0xb7dc44 (magic 0x19930522,
# one unwind state; map 0xb7dc68: state -1, action 0x906330). Unwind action
# tailcalls 0x44f760 on that temporary. Handler/metadata not reconstructed.
# Unresolved: runtime accessor 0x6d86bb, vtable+0xc slot(0), constructor
# 0x44f490, destructor 0x44f760, runtime EH/data; calls retain original VAs.
.intel_syntax noprefix
.code32
.text
.global original_save_device_refresh
original_save_device_refresh:
.L535ec0:
 push   ebp
.L535ec1:
 {load} mov    ebp,esp
.L535ec3:
 push   0xffffffff
.L535ec5:
 push   0x90633b
.L535eca:
 mov    eax,fs:0x0
.L535ed0:
 push   eax
.L535ed1:
 sub    esp,0x228
.L535ed7:
 mov    eax,[0xbaabc0]
.L535edc:
 {load} xor    eax,ebp
.L535ede:
 mov    DWORD PTR [ebp-0x10],eax
.L535ee1:
 push   esi
.L535ee2:
 push   edi
.L535ee3:
 push   eax
.L535ee4:
 lea    eax,[ebp-0xc]
.L535ee7:
 mov    fs:0x0,eax
.L535eed:
 {load} mov    edi,ecx
.L535eef:
 lea    eax,[ebp-0x218]
.L535ef5:
 push   eax
.L535ef6:
 push   0x0
.L535ef8:
 push   0x0
.L535efa:
 push   0x1a
.L535efc:
 push   0x0
.L535efe:
 call   DWORD PTR [0x92d510]
.L535f04:
 test   eax,eax
.L535f06:
 js .L536008
.L535f0c:
 cmp    WORD PTR [ebp-0x218],0x0
.L535f14:
 jne .L535f1a
.L535f16:
 {load} xor    eax,eax
.L535f18:
 jmp .L535f32
.L535f1a:
 lea    eax,[ebp-0x218]
.L535f20:
 lea    edx,[eax+0x2]
.L535f23:
 mov    cx,WORD PTR [eax]
.L535f26:
 add    eax,0x2
.L535f29:
 test   cx,cx
.L535f2c:
 jne .L535f23
.L535f2e:
 {load} sub    eax,edx
.L535f30:
 sar    eax,1
.L535f32:
 push   eax
.L535f33:
 lea    eax,[ebp-0x218]
.L535f39:
 push   eax
.L535f3a:
 lea    ecx,[edi+0x14]
.L535f3d:
 call target_44f9b0
.L535f42:
 push   0x5c
.L535f44:
 push   ecx
.L535f45:
 lea    ecx,[edi+0x14]
.L535f48:
 call target_44f8f0
.L535f4d:
 cmp    DWORD PTR [edi+0x3c],0x0
.L535f51:
 je .L535f68
.L535f53:
 push   0xffffffff
.L535f55:
 push   0x0
.L535f57:
 lea    eax,[edi+0x2c]
.L535f5a:
 push   eax
.L535f5b:
 lea    ecx,[edi+0x14]
.L535f5e:
 call target_5360b0
.L535f63:
 jmp .L535ffd
.L535f68:
 {load} xor    ecx,ecx
.L535f6a:
 mov    eax,0x6
.L535f6f:
 cmp    WORD PTR [0x9ffe00],cx
.L535f76:
 cmove  eax,ecx
.L535f79:
 lea    ecx,[edi+0x14]
.L535f7c:
 push   eax
.L535f7d:
 push   0x9ffe00
.L535f82:
 call target_536160
.L535f87:
 push   0x5c
.L535f89:
 push   ecx
.L535f8a:
 lea    ecx,[edi+0x14]
.L535f8d:
 call target_44f8f0
.L535f92:
 call target_6d86bb
.L535f97:
 push   0x0
.L535f99:
 {load} mov    ecx,eax
.L535f9b:
 mov    edx,DWORD PTR [eax]
.L535f9d:
 call   DWORD PTR [edx+0xc]
.L535fa0:
 {load} mov    edx,eax
.L535fa2:
 lea    ecx,[ebp-0x230]
.L535fa8:
 call target_44f490
.L535fad:
 push   0xffffffff
.L535faf:
 push   0x0
.L535fb1:
 push   eax
.L535fb2:
 lea    ecx,[edi+0x14]
.L535fb5:
 mov    DWORD PTR [ebp-0x4],0x0
.L535fbc:
 call target_5360b0
.L535fc1:
 mov    DWORD PTR [ebp-0x4],0xffffffff
.L535fc8:
 cmp    DWORD PTR [ebp-0x21c],0x8
.L535fcf:
 jb .L535fe0
.L535fd1:
 push   DWORD PTR [ebp-0x230]
.L535fd7:
 call   DWORD PTR [0x92d4b0]
.L535fdd:
 add    esp,0x4
.L535fe0:
 {load} xor    eax,eax
.L535fe2:
 mov    DWORD PTR [ebp-0x21c],0x7
.L535fec:
 mov    DWORD PTR [ebp-0x220],0x0
.L535ff6:
 mov    WORD PTR [ebp-0x230],ax
.L535ffd:
 push   0x5c
.L535fff:
 push   ecx
.L536000:
 lea    ecx,[edi+0x14]
.L536003:
 call target_44f8f0
.L536008:
 mov    ecx,DWORD PTR [ebp-0xc]
.L53600b:
 mov    DWORD PTR fs:0x0,ecx
.L536012:
 pop    ecx
.L536013:
 pop    edi
.L536014:
 pop    esi
.L536015:
 mov    ecx,DWORD PTR [ebp-0x10]
.L536018:
 {load} xor    ecx,ebp
.L53601a:
 call target_8f8958
.L53601f:
 {load} mov    esp,ebp
.L536021:
 pop    ebp
.L536022:
 ret
.equ target_44f490,0x44f490
.equ target_44f8f0,0x44f8f0
.equ target_44f9b0,0x44f9b0
.equ target_5360b0,0x5360b0
.equ target_536160,0x536160
.equ target_6d86bb,0x6d86bb
.equ target_8f8958,0x8f8958
