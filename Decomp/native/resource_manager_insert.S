# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x41bf60,0x41c08b); instruction-contiguous extent, padding excluded.
# Resource manager insertion: increments the 16-bit count at +0x30, grows capacity at +0x32, reserves
# the pointer vector at +0x24 and copies the pooled string via 0x41C300/0x41C3A0/0x426A30/0x426BE0.
# Returns the new index in EAX through RET 4.
# Derived from original instructions; earns reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x41bf60..0x41c08b
.intel_syntax noprefix
.code32
.text
.global original_resource_manager_insert
original_resource_manager_insert:
.L41bf60:
 push   ebp
.L41bf61:
 {load} mov    ebp,esp
.L41bf63:
 push   ecx
.L41bf64:
 push   ebx
.L41bf65:
 push   esi
.L41bf66:
 push   edi
.L41bf67:
 {load} mov    edi,ecx
.L41bf69:
 movzx  eax,WORD PTR [edi+0x30]
.L41bf6d:
 movsx  ebx,ax
.L41bf70:
 inc    eax
.L41bf71:
 mov    WORD PTR [edi+0x30],ax
.L41bf75:
 cmp    ax,WORD PTR [edi+0x32]
.L41bf79:
 jle .L41bf7f
.L41bf7b:
 mov    WORD PTR [edi+0x32],ax
.L41bf7f:
 mov    eax,DWORD PTR [edi+0x28]
.L41bf82:
 lea    ecx,[edi+0x24]
.L41bf85:
 sub    eax,DWORD PTR [ecx]
.L41bf87:
 sar    eax,0x3
.L41bf8a:
 {load} cmp    ebx,eax
.L41bf8c:
 jl .L41bfb1
.L41bf8e:
 lea    esi,[ebx+0x8]
.L41bf91:
 and    esi,0xfffffff8
.L41bf94:
 push   esi
.L41bf95:
 call target_41c3a0
.L41bf9a:
 lea    eax,[ebp-0x4]
.L41bf9d:
 mov    DWORD PTR [ebp-0x4],0xffffffff
.L41bfa4:
 push   eax
.L41bfa5:
 push   esi
.L41bfa6:
 lea    ecx,[edi+0xc]
.L41bfa9:
 call target_41c300
.L41bfae:
 lea    ecx,[edi+0x24]
.L41bfb1:
 mov    eax,DWORD PTR [ecx+0x4]
.L41bfb4:
 mov    edx,DWORD PTR [ecx]
.L41bfb6:
 {load} sub    eax,edx
.L41bfb8:
 sar    eax,0x3
.L41bfbb:
 {load} cmp    eax,ebx
.L41bfbd:
 ja .L41bfca
.L41bfbf:
 push   0x999ec8
.L41bfc4:
 call   DWORD PTR [0x92d16c]
.L41bfca:
 mov    eax,DWORD PTR [ebp+0x8]
.L41bfcd:
 lea    esi,[edx+ebx*8]
.L41bfd0:
 {load} cmp    eax,esi
.L41bfd2:
 je .L41bffa
.L41bfd4:
 cmp    DWORD PTR [esi],0x0
.L41bfd7:
 je .L41bfe3
.L41bfd9:
 {load} mov    ecx,esi
.L41bfdb:
 call target_426be0
.L41bfe0:
 mov    eax,DWORD PTR [ebp+0x8]
.L41bfe3:
 mov    ecx,DWORD PTR [eax]
.L41bfe5:
 mov    eax,[0xbfcb38]
.L41bfea:
 add    eax,0x4
.L41bfed:
 {load} add    eax,ecx
.L41bfef:
 {load} mov    ecx,esi
.L41bff1:
 push   eax
.L41bff2:
 call target_426a30
.L41bff7:
 mov    eax,DWORD PTR [ebp+0x8]
.L41bffa:
 mov    eax,DWORD PTR [eax+0x4]
.L41bffd:
 mov    DWORD PTR [esi+0x4],eax
.L41c000:
 mov    eax,DWORD PTR [edi+0x1c]
.L41c003:
 sub    eax,DWORD PTR [edi+0x18]
.L41c006:
 sar    eax,1
.L41c008:
 je .L41c017
.L41c00a:
 mov    eax,DWORD PTR [edi+0x1c]
.L41c00d:
 movsx  esi,WORD PTR [eax-0x2]
.L41c011:
 add    DWORD PTR [edi+0x1c],0xfffffffe
.L41c015:
 jmp .L41c047
.L41c017:
 movzx  eax,WORD PTR [edi+0x34]
.L41c01b:
 movsx  esi,ax
.L41c01e:
 inc    eax
.L41c01f:
 mov    WORD PTR [edi+0x34],ax
.L41c023:
 mov    eax,DWORD PTR [edi+0x4]
.L41c026:
 sub    eax,DWORD PTR [edi]
.L41c028:
 sar    eax,1
.L41c02a:
 {load} cmp    esi,eax
.L41c02c:
 jl .L41c047
.L41c02e:
 lea    eax,[ebp+0x8]
.L41c031:
 mov    DWORD PTR [ebp+0x8],0xffffffff
.L41c038:
 push   eax
.L41c039:
 lea    eax,[esi+0x8]
.L41c03c:
 {load} mov    ecx,edi
.L41c03e:
 and    eax,0xfffffff8
.L41c041:
 push   eax
.L41c042:
 call target_41c300
.L41c047:
 mov    eax,DWORD PTR [edi+0x4]
.L41c04a:
 mov    ecx,DWORD PTR [edi]
.L41c04c:
 {load} sub    eax,ecx
.L41c04e:
 sar    eax,1
.L41c050:
 {load} cmp    eax,esi
.L41c052:
 ja .L41c05f
.L41c054:
 push   0x999ec8
.L41c059:
 call   DWORD PTR [0x92d16c]
.L41c05f:
 mov    WORD PTR [ecx+esi*2],bx
.L41c063:
 mov    eax,DWORD PTR [edi+0x10]
.L41c066:
 mov    ecx,DWORD PTR [edi+0xc]
.L41c069:
 {load} sub    eax,ecx
.L41c06b:
 sar    eax,1
.L41c06d:
 {load} cmp    eax,ebx
.L41c06f:
 ja .L41c07c
.L41c071:
 push   0x999ec8
.L41c076:
 call   DWORD PTR [0x92d16c]
.L41c07c:
 pop    edi
.L41c07d:
 mov    WORD PTR [ecx+ebx*2],si
.L41c081:
 {load} mov    eax,esi
.L41c083:
 pop    esi
.L41c084:
 pop    ebx
.L41c085:
 {load} mov    esp,ebp
.L41c087:
 pop    ebp
.L41c088:
 ret    0x4
.equ target_41c300,0x41c300
.equ target_41c3a0,0x41c3a0
.equ target_426a30,0x426a30
.equ target_426be0,0x426be0
