# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original objdump and private Ghidra exports in
# /tmp/cloud-cleanup-review/exports; caller 0x44eb10 and ctor 0x48d6e0.
# Thiscall ECX=this, preserves EDI; plain ret, no stack arguments.
# Wait for +0x18, set stop +0x1c, reset +0x18, signal +0x14, join +8.
# Release heap string +0x20 iff unsigned capacity +0x34 >=16; reset to
# empty inline storage, restore base vtable, close thread +8. Events are
# not closed here. Win32 calls are stdcall; operator delete is cdecl.
# Vtables agree with constructor; class identity remains unproven.
# Exact function bounds end at ret; no embedded data, SEH registration or
# local EH cleanup. Dependency failures propagate; no invented cleanup.
# Adjacent functions and alignment padding excluded.
# Original VA range 0x48d800..0x48d86a
.intel_syntax noprefix
.code32
.text
.global original_member_cleanup
original_member_cleanup:
.L48d800:
 push   edi
.L48d801:
 {load} mov    edi,ecx
.L48d803:
 push   0xffffffff
.L48d805:
 push   DWORD PTR [edi+0x18]
.L48d808:
 mov    DWORD PTR [edi],offset member_vtable
.L48d80e:
 call   DWORD PTR [imported_WaitForSingleObject]
.L48d814:
 push   DWORD PTR [edi+0x18]
.L48d817:
 mov    BYTE PTR [edi+0x1c],0x1
.L48d81b:
 call   DWORD PTR [imported_ResetEvent]
.L48d821:
 push   DWORD PTR [edi+0x14]
.L48d824:
 call   DWORD PTR [imported_SetEvent]
.L48d82a:
 push   0xffffffff
.L48d82c:
 push   DWORD PTR [edi+0x8]
.L48d82f:
 call   DWORD PTR [imported_WaitForSingleObject]
.L48d835:
 cmp    DWORD PTR [edi+0x34],0x10
.L48d839:
 jb .L48d847
.L48d83b:
 push   DWORD PTR [edi+0x20]
.L48d83e:
 call   DWORD PTR [imported_operator_delete]
.L48d844:
 add    esp,0x4
.L48d847:
 mov    DWORD PTR [edi+0x34],0xf
.L48d84e:
 mov    DWORD PTR [edi+0x30],0x0
.L48d855:
 mov    BYTE PTR [edi+0x20],0x0
.L48d859:
 push   DWORD PTR [edi+0x8]
.L48d85c:
 mov    DWORD PTR [edi],offset base_vtable
.L48d862:
 call   DWORD PTR [imported_CloseHandle]
.L48d868:
 pop    edi
.L48d869:
 ret

.equ member_vtable,0x9fbdf0
.equ base_vtable,0x9fbe20
.equ imported_WaitForSingleObject,0x92d124
.equ imported_ResetEvent,0x92d104
.equ imported_SetEvent,0x92d120
.equ imported_operator_delete,0x92d4b0
.equ imported_CloseHandle,0x92d0d4
