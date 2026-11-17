.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x8f9131..0x8f925e.
.equ target_8f8f93,0x8f8f93
.equ target_8f9019,0x8f9019
.equ target_8f90db,0x8f90db
.equ target_8f90ed,0x8f90ed
.global original_sse_double_to_integer_dispatch
original_sse_double_to_integer_dispatch:
L_8f9131:
 mov    ecx,0x1
L_8f9136:
 movsd  xmm5,QWORD PTR [0x982518]
L_8f913e:
 jmp L_8f915c
L_8f9140:
 mov    ecx,0x4
L_8f9145:
 movsd  xmm5,QWORD PTR [0x982520]
L_8f914d:
 jmp L_8f915c
L_8f914f:
 mov    ecx,0x5
L_8f9154:
 movsd  xmm5,QWORD PTR [0x982518]
L_8f915c:
 movdqa xmm1,xmm0
L_8f9160:
 psrldq xmm1,0x4
L_8f9165:
 movd   eax,xmm1
L_8f9169:
 and    eax,0x7fffffff
L_8f916e:
 cmp    eax,0x7ff00000
L_8f9173:
 jae target_8f90db
L_8f9179:
 cmp    ecx,0x1
L_8f917c:
 je target_8f8f93
L_8f9182:
 movdqa xmm1,xmm0
L_8f9186:
 psllq  xmm1,0x1
L_8f918b:
 psrlq  xmm1,0x1
L_8f9190:
 movsd  xmm2,QWORD PTR [0x982528]
L_8f9198:
 comisd xmm1,xmm2
L_8f919c:
 jbe L_8f91cd
L_8f919e:
 cmp    ecx,0x4
L_8f91a1:
 je L_8f91b9
L_8f91a3:
 mov    edx,0x1
L_8f91a8:
 call target_8f90ed
L_8f91ad:
 mov    edx,0x10
L_8f91b2:
 call target_8f90ed
L_8f91b7:
 jmp L_8f91cd
L_8f91b9:
 mov    edx,0x10
L_8f91be:
 call target_8f90ed
L_8f91c3:
 mov    edx,0x1
L_8f91c8:
 call target_8f90ed
L_8f91cd:
 movsd  xmm2,QWORD PTR [0x982530]
L_8f91d5:
 comisd xmm1,xmm2
L_8f91d9:
 jae L_8f9202
L_8f91db:
 xorpd  xmm2,xmm2
L_8f91df:
 comisd xmm1,xmm2
L_8f91e3:
 je target_8f9019
L_8f91e9:
 mov    edx,0x2
L_8f91ee:
 call target_8f90ed
L_8f91f3:
 mov    edx,0x10
L_8f91f8:
 call target_8f90ed
L_8f91fd:
 jmp target_8f9019
L_8f9202:
 movdqa xmm3,xmm0
L_8f9206:
 cmp    ecx,0x4
L_8f9209:
 jne L_8f921d
L_8f920b:
 movsd  xmm2,QWORD PTR [0x982518]
L_8f9213:
 comisd xmm3,xmm2
L_8f9217:
 jb L_8f921d
L_8f9219:
 subpd  xmm3,xmm2
L_8f921d:
 movdqa xmm4,xmm3
L_8f9221:
 psllq  xmm4,0x23
L_8f9226:
 psrlq  xmm4,0x23
L_8f922b:
 movd   eax,xmm4
L_8f922f:
 {load} or eax,eax
L_8f9231:
 je L_8f923d
L_8f9233:
 mov    edx,0x10
L_8f9238:
 call target_8f90ed
L_8f923d:
 comisd xmm0,xmm5
L_8f9241:
 jae target_8f90db
L_8f9247:
 movsd  xmm2,QWORD PTR [0x982510]
L_8f924f:
 comisd xmm0,xmm2
L_8f9253:
 jb target_8f90db
L_8f9259:
 jmp target_8f9019
