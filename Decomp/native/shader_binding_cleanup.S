# Reviewed original instructions and Ghidra control flow; see SHADERS.md.
# Original VA range 0x52f5b0..0x52f5f3
.intel_syntax noprefix
.code32
.text
.global original_shader_binding_cleanup
original_shader_binding_cleanup:
.L52f5b0:
 push   ebp
.L52f5b1:
 {load} mov    ebp,esp
.L52f5b3:
 push   ecx
.L52f5b4:
 push   ebx
.L52f5b5:
 push   esi
.L52f5b6:
 push   edi
.L52f5b7:
 lea    ebx,[ecx+0xe1c]
.L52f5bd:
 mov    DWORD PTR [ebp-0x4],0x118
.L52f5c4:
 {load} mov    esi,ebx
.L52f5c6:
 mov    edi,0x6
.L52f5cb:
 jmp .L52f5d0
.L52f5cd:
 {disp8} lea    ecx,[ecx+0x0]
.L52f5d0:
 mov    ecx,DWORD PTR [esi]
.L52f5d2:
 test   ecx,ecx
.L52f5d4:
 je .L52f5db
.L52f5d6:
 mov    eax,DWORD PTR [ecx]
.L52f5d8:
 call   DWORD PTR [eax+0x10]
.L52f5db:
 add    esi,0x460
.L52f5e1:
 dec    edi
.L52f5e2:
 jne .L52f5d0
.L52f5e4:
 add    ebx,0x4
.L52f5e7:
 dec    DWORD PTR [ebp-0x4]
.L52f5ea:
 jne .L52f5c4
.L52f5ec:
 pop    edi
.L52f5ed:
 pop    esi
.L52f5ee:
 pop    ebx
.L52f5ef:
 {load} mov    esp,ebp
.L52f5f1:
 pop    ebp
.L52f5f2:
 ret
