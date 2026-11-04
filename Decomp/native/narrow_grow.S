# Reviewed pinned depot SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Evidence /tmp/cloud-string-growth/{grow.asm,exports/00416890.txt,eh-data.txt}.
# thiscall ECX=string, stack requested capacity/preserved length; ret 8.
# Preserves EBP/EBX/ESI/EDI, restores FS exception chain. Capacity rounds by
# OR 15, prefers old+old/2 when larger, saturates at fffffffe. Allocate cap+1,
# copy preserved bytes via 8f8d66, free old heap via IAT 92d4b0, install/NUL.
# Original instruction cmp ecx,ffffffff / ja retained although branch impossible.
# EH metadata b75d80 has four unwind states and two try blocks; handlers b75dfc
# and b75dec target 416927 (retry requested+1 via 4169f0) and 416964
# (free/reset inline then rethrow via 8f8d5a). 416947 resumes after retry.
# These disjoint funclets are omitted from Ghidra function extent; original
# instructions and metadata establish ownership. 416941 returns continuation
# address in EAX to runtime, not normal caller. No embedded data in code span.
# External allocator, copy/rethrow, cookie helper and EH metadata unresolved.
# Final ret ends 4169e1; exclude int3 alignment. No copied machine-code source.
# Original VA range 0x416890..0x4169e1
.intel_syntax noprefix
.code32
.text
.global original_narrow_grow
original_narrow_grow:
.L416890:
 push   ebp
.L416891:
 {load} mov    ebp,esp
.L416893:
 push   0xffffffff
.L416895:
 push   0x8fd780
.L41689a:
 mov    eax,fs:0x0
.L4168a0:
 push   eax
.L4168a1:
 sub    esp,0xc
.L4168a4:
 push   ebx
.L4168a5:
 push   esi
.L4168a6:
 push   edi
.L4168a7:
 mov    eax,[0xbaabc0]
.L4168ac:
 {load} xor    eax,ebp
.L4168ae:
 push   eax
.L4168af:
 lea    eax,[ebp-0xc]
.L4168b2:
 mov    fs:0x0,eax
.L4168b8:
 mov    DWORD PTR [ebp-0x10],esp
.L4168bb:
 {load} mov    esi,ecx
.L4168bd:
 mov    DWORD PTR [ebp-0x18],esi
.L4168c0:
 mov    eax,DWORD PTR [ebp+0x8]
.L4168c3:
 {load} mov    edi,eax
.L4168c5:
 or     edi,0xf
.L4168c8:
 cmp    edi,0xfffffffe
.L4168cb:
 jbe .L4168d1
.L4168cd:
 {load} mov    edi,eax
.L4168cf:
 jmp .L4168f8
.L4168d1:
 mov    ebx,DWORD PTR [esi+0x14]
.L4168d4:
 mov    eax,0xaaaaaaab
.L4168d9:
 mul    edi
.L4168db:
 {load} mov    ecx,ebx
.L4168dd:
 shr    ecx,1
.L4168df:
 shr    edx,1
.L4168e1:
 {load} cmp    ecx,edx
.L4168e3:
 jbe .L4168f8
.L4168e5:
 mov    eax,0xfffffffe
.L4168ea:
 lea    edi,[ecx+ebx*1]
.L4168ed:
 {load} sub    eax,ecx
.L4168ef:
 {load} cmp    ebx,eax
.L4168f1:
 jbe .L4168f8
.L4168f3:
 mov    edi,0xfffffffe
.L4168f8:
 lea    ecx,[edi+0x1]
.L4168fb:
 mov    DWORD PTR [ebp-0x4],0x0
.L416902:
 {load} xor    eax,eax
.L416904:
 mov    DWORD PTR [ebp-0x14],eax
.L416907:
 test   ecx,ecx
.L416909:
 je .L416953
.L41690b:
 cmp    ecx,0xffffffff
.L41690e:
 ja .L416921
.L416910:
 push   ecx
.L416911:
 call   DWORD PTR [0x92d4b4]
.L416917:
 add    esp,0x4
.L41691a:
 mov    DWORD PTR [ebp-0x14],eax
.L41691d:
 test   eax,eax
.L41691f:
 jne .L416953
.L416921:
 call   DWORD PTR [0x92d164]
.L416927:
 mov    eax,DWORD PTR [ebp+0x8]
.L41692a:
 lea    ecx,[ebp+0xb]
.L41692d:
 mov    DWORD PTR [ebp-0x14],eax
.L416930:
 inc    eax
.L416931:
 mov    DWORD PTR [ebp-0x10],esp
.L416934:
 push   eax
.L416935:
 mov    BYTE PTR [ebp-0x4],0x2
.L416939:
 call target_4169f0
.L41693e:
 mov    DWORD PTR [ebp+0x8],eax
.L416941:
 mov    eax,0x416947
.L416946:
 ret
.L416947:
 mov    edi,DWORD PTR [ebp-0x14]
.L41694a:
 mov    eax,DWORD PTR [ebp+0x8]
.L41694d:
 mov    esi,DWORD PTR [ebp-0x18]
.L416950:
 mov    DWORD PTR [ebp-0x14],eax
.L416953:
 mov    ebx,DWORD PTR [ebp+0xc]
.L416956:
 test   ebx,ebx
.L416958:
 je .L4169a3
.L41695a:
 cmp    DWORD PTR [esi+0x14],0x10
.L41695e:
 jb .L416992
.L416960:
 mov    ecx,DWORD PTR [esi]
.L416962:
 jmp .L416994
.L416964:
 mov    esi,DWORD PTR [ebp-0x18]
.L416967:
 cmp    DWORD PTR [esi+0x14],0x10
.L41696b:
 jb .L416978
.L41696d:
 push   DWORD PTR [esi]
.L41696f:
 call   DWORD PTR [0x92d4b0]
.L416975:
 add    esp,0x4
.L416978:
 push   0x0
.L41697a:
 mov    DWORD PTR [esi+0x14],0xf
.L416981:
 mov    DWORD PTR [esi+0x10],0x0
.L416988:
 push   0x0
.L41698a:
 mov    BYTE PTR [esi],0x0
.L41698d:
 call target_8f8d5a
.L416992:
 {load} mov    ecx,esi
.L416994:
 test   ebx,ebx
.L416996:
 je .L4169a3
.L416998:
 push   ebx
.L416999:
 push   ecx
.L41699a:
 push   eax
.L41699b:
 call target_8f8d66
.L4169a0:
 add    esp,0xc
.L4169a3:
 cmp    DWORD PTR [esi+0x14],0x10
.L4169a7:
 jb .L4169b4
.L4169a9:
 push   DWORD PTR [esi]
.L4169ab:
 call   DWORD PTR [0x92d4b0]
.L4169b1:
 add    esp,0x4
.L4169b4:
 mov    eax,DWORD PTR [ebp-0x14]
.L4169b7:
 mov    BYTE PTR [esi],0x0
.L4169ba:
 mov    DWORD PTR [esi],eax
.L4169bc:
 mov    DWORD PTR [esi+0x14],edi
.L4169bf:
 mov    DWORD PTR [esi+0x10],ebx
.L4169c2:
 cmp    edi,0x10
.L4169c5:
 jb .L4169c9
.L4169c7:
 {load} mov    esi,eax
.L4169c9:
 mov    BYTE PTR [esi+ebx*1],0x0
.L4169cd:
 mov    ecx,DWORD PTR [ebp-0xc]
.L4169d0:
 mov    DWORD PTR fs:0x0,ecx
.L4169d7:
 pop    ecx
.L4169d8:
 pop    edi
.L4169d9:
 pop    esi
.L4169da:
 pop    ebx
.L4169db:
 {load} mov    esp,ebp
.L4169dd:
 pop    ebp
.L4169de:
 ret    0x8
.equ target_4169f0,0x4169f0
.equ target_8f8d5a,0x8f8d5a
.equ target_8f8d66,0x8f8d66
