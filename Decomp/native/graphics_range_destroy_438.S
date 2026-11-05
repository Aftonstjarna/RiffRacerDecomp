# Mechanically transcribed reference evidence; NOT high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x49d6b0..0x49d820 exclusive. All branches included; adjacent functions excluded.
.intel_syntax noprefix
.code32
.text
.global original_graphics_range_destroy_438
original_graphics_range_destroy_438:
# ECX=begin, EDX=end for 12-byte entries; caller cleans forwarded stack words.
# Preserve EBX/ESI/EDI/EBP and install the original Windows SEH frame.
.L49d6b0:
 push   ebp
.L49d6b1:
 {load} mov    ebp,esp
.L49d6b3:
 push   0xffffffff
.L49d6b5:
 push   0x902413
.L49d6ba:
 mov    eax,fs:0x0
.L49d6c0:
 push   eax
.L49d6c1:
 sub    esp,0x8
.L49d6c4:
 push   ebx
.L49d6c5:
 push   esi
.L49d6c6:
 push   edi
.L49d6c7:
 mov    eax,[0xbaabc0]
.L49d6cc:
 {load} xor    eax,ebp
.L49d6ce:
 push   eax
.L49d6cf:
 lea    eax,[ebp-0xc]
.L49d6d2:
 mov    fs:0x0,eax
.L49d6d8:
 {load} mov    eax,edx
.L49d6da:
 mov    DWORD PTR [ebp-0x10],eax
.L49d6dd:
 {load} mov    edi,ecx
.L49d6df:
 mov    DWORD PTR [ebp-0x14],edi
.L49d6e2:
 {load} cmp    edi,eax
.L49d6e4:
 je .L49d80e
.L49d6ea:
 {disp32} lea    ebx,[ebx+0x0]
# Release entry+8 through its adjusted reference-counted base and virtual destructor.
.L49d6f0:
 mov    DWORD PTR [ebp-0x4],0x0
.L49d6f7:
 mov    ecx,DWORD PTR [edi+0x8]
.L49d6fa:
 test   ecx,ecx
.L49d6fc:
 je .L49d717
.L49d6fe:
 mov    eax,DWORD PTR [ecx+0x4]
.L49d701:
 add    ecx,0x4
.L49d704:
 mov    eax,DWORD PTR [eax+0x4]
.L49d707:
 {load} add    ecx,eax
.L49d709:
 dec    DWORD PTR [ecx+0x4]
.L49d70c:
 jne .L49d714
.L49d70e:
 mov    eax,DWORD PTR [ecx]
.L49d710:
 push   0x1
.L49d712:
 call   DWORD PTR [eax]
.L49d714:
 mov    eax,DWORD PTR [ebp-0x10]
.L49d717:
 mov    DWORD PTR [ebp-0x4],0xffffffff
# A negative entry+4 skips texture-manager release. Otherwise use manager 0xc0d3f0.
.L49d71e:
 mov    ebx,DWORD PTR [edi+0x4]
.L49d721:
 test   ebx,ebx
.L49d723:
 js .L49d800
.L49d729:
 mov    esi,DWORD PTR [0xc0d3f0]
.L49d72f:
 test   esi,esi
.L49d731:
 jne .L49d77f
# Lazy 0x58-byte manager construction with elTextureResource metadata.
.L49d733:
 push   0x58
.L49d735:
 call   DWORD PTR [0x92d4b4]
.L49d73b:
 {load} mov    esi,eax
.L49d73d:
 add    esp,0x4
.L49d740:
 mov    DWORD PTR [ebp-0x14],esi
.L49d743:
 mov    DWORD PTR [ebp-0x4],0x1
.L49d74a:
 test   esi,esi
.L49d74c:
 je .L49d770
.L49d74e:
 push   0xbaac54
.L49d753:
 lea    ecx,[esi+0x4]
.L49d756:
 mov    WORD PTR [esi],0x100
.L49d75b:
 mov    BYTE PTR [esi+0x2],0x5c
.L49d75f:
 call target_417810
.L49d764:
 mov    WORD PTR [esi+0x54],0x100
.L49d76a:
 mov    BYTE PTR [esi+0x56],0x5c
.L49d76e:
 jmp .L49d772
.L49d770:
 {load} xor    esi,esi
.L49d772:
 mov    DWORD PTR [ebp-0x4],0xffffffff
.L49d779:
 mov    DWORD PTR [0xc0d3f0],esi
# Signed 16-bit handle map indexes 8-byte resource records; release on zero count.
.L49d77f:
 mov    eax,DWORD PTR [esi+0x4]
.L49d782:
 movsx  ecx,WORD PTR [eax+ebx*2]
.L49d786:
 mov    eax,DWORD PTR [esi+0x28]
.L49d789:
 dec    DWORD PTR [eax+ecx*8+0x4]
.L49d78d:
 cmp    DWORD PTR [eax+ecx*8+0x4],0x0
.L49d792:
 jne .L49d7f6
.L49d794:
 mov    esi,DWORD PTR [0xc0d3f0]
.L49d79a:
 mov    ebx,DWORD PTR [edi+0x4]
.L49d79d:
 test   esi,esi
.L49d79f:
 jne .L49d7ed
# The original repeats the lazy manager construction on the zero-count path.
.L49d7a1:
 push   0x58
.L49d7a3:
 call   DWORD PTR [0x92d4b4]
.L49d7a9:
 {load} mov    esi,eax
.L49d7ab:
 add    esp,0x4
.L49d7ae:
 mov    DWORD PTR [ebp-0x14],esi
.L49d7b1:
 mov    DWORD PTR [ebp-0x4],0x2
.L49d7b8:
 test   esi,esi
.L49d7ba:
 je .L49d7de
.L49d7bc:
 push   0xbaac54
.L49d7c1:
 lea    ecx,[esi+0x4]
.L49d7c4:
 mov    WORD PTR [esi],0x100
.L49d7c9:
 mov    BYTE PTR [esi+0x2],0x5c
.L49d7cd:
 call target_417810
.L49d7d2:
 mov    WORD PTR [esi+0x54],0x100
.L49d7d8:
 mov    BYTE PTR [esi+0x56],0x5c
.L49d7dc:
 jmp .L49d7e0
.L49d7de:
 {load} xor    esi,esi
.L49d7e0:
 mov    DWORD PTR [ebp-0x4],0xffffffff
.L49d7e7:
 mov    DWORD PTR [0xc0d3f0],esi
# Remove the zero-count handle, invalidate entry+4, then advance one 12-byte entry.
.L49d7ed:
 push   ebx
.L49d7ee:
 lea    ecx,[esi+0x4]
.L49d7f1:
 call target_41c090
.L49d7f6:
 mov    eax,DWORD PTR [ebp-0x10]
.L49d7f9:
 mov    DWORD PTR [edi+0x4],0xffffffff
.L49d800:
 add    edi,0xc
.L49d803:
 mov    DWORD PTR [ebp-0x14],edi
.L49d806:
 {load} cmp    edi,eax
.L49d808:
 jne .L49d6f0
# Restore the exception chain and saved registers. Handler 0x902413 is external.
.L49d80e:
 mov    ecx,DWORD PTR [ebp-0xc]
.L49d811:
 mov    DWORD PTR fs:0x0,ecx
.L49d818:
 pop    ecx
.L49d819:
 pop    edi
.L49d81a:
 pop    esi
.L49d81b:
 pop    ebx
.L49d81c:
 {load} mov    esp,ebp
.L49d81e:
 pop    ebp
.L49d81f:
 ret
.equ target_417810,0x417810
.equ target_41c090,0x41c090
.section .note.GNU-stack,"",@progbits
