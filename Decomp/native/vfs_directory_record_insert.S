# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x561ff0,0x562076); instruction-contiguous extent, padding excluded.
# VFS directory record insertion: 28-byte records (0x92492493 divide), capacity check and growth via
# 0x561B80, element move via 0x44F6F0 and post-insert update at 0x562120. Returns through RET 0xC.
# Derived from original instructions; earns reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x561ff0..0x562076
.intel_syntax noprefix
.code32
.text
.global original_vfs_directory_record_insert
original_vfs_directory_record_insert:
.L561ff0:
 push   ebp
.L561ff1:
 {load} mov    ebp,esp
.L561ff3:
 push   ebx
.L561ff4:
 push   esi
.L561ff5:
 mov    esi,DWORD PTR [ebp+0xc]
.L561ff8:
 mov    eax,0x92492493
.L561ffd:
 push   edi
.L561ffe:
 {load} mov    edi,ecx
.L562000:
 sub    esi,DWORD PTR [edi]
.L562002:
 imul   esi
.L562004:
 mov    eax,DWORD PTR [edi+0x4]
.L562007:
 {load} add    edx,esi
.L562009:
 sar    edx,0x4
.L56200c:
 {load} mov    ebx,edx
.L56200e:
 shr    ebx,0x1f
.L562011:
 {load} add    ebx,edx
.L562013:
 cmp    eax,DWORD PTR [edi+0x8]
.L562016:
 jne .L56201e
.L562018:
 push   ecx
.L562019:
 call target_561b80
.L56201e:
 mov    edx,DWORD PTR [edi+0x4]
.L562021:
 test   edx,edx
.L562023:
 je .L562038
.L562025:
 mov    ecx,DWORD PTR [ebp+0x10]
.L562028:
 mov    eax,DWORD PTR [ecx]
.L56202a:
 mov    DWORD PTR [edx],eax
.L56202c:
 lea    eax,[ecx+0x4]
.L56202f:
 push   eax
.L562030:
 lea    ecx,[edx+0x4]
.L562033:
 call target_44f6f0
.L562038:
 add    DWORD PTR [edi+0x4],0x1c
.L56203c:
 lea    esi,[ebx*8+0x0]
.L562043:
 mov    eax,DWORD PTR [edi+0x4]
.L562046:
 {load} sub    esi,ebx
.L562048:
 mov    ecx,DWORD PTR [edi]
.L56204a:
 shl    esi,0x2
.L56204d:
 {load} add    ecx,esi
.L56204f:
 lea    edx,[eax-0x1c]
.L562052:
 {load} cmp    ecx,edx
.L562054:
 je .L562066
.L562056:
 {load} cmp    edx,eax
.L562058:
 je .L562066
.L56205a:
 sub    esp,0x8
.L56205d:
 push   eax
.L56205e:
 call target_562120
.L562063:
 add    esp,0xc
.L562066:
 mov    ecx,DWORD PTR [edi]
.L562068:
 mov    eax,DWORD PTR [ebp+0x8]
.L56206b:
 {load} add    ecx,esi
.L56206d:
 pop    edi
.L56206e:
 pop    esi
.L56206f:
 pop    ebx
.L562070:
 mov    DWORD PTR [eax],ecx
.L562072:
 pop    ebp
.L562073:
 ret    0xc
.equ target_44f6f0,0x44f6f0
.equ target_561b80,0x561b80
.equ target_562120,0x562120
