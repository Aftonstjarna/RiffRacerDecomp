# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f5830,0x4f58b4); all branches included, INT3 excluded.
# ECX=script state, EDX=function slot, [entry ESP+4]=result count;
# caller pops stack argument. ESI/EDI/EBP restored; stack aligned to 8.
# Nested calls and nonlocal error exits retain their original dependencies.
.intel_syntax noprefix
.code32
.text
.global original_script_call_with_depth_guard
.equ RUNTIME_ERROR,0x486ab0
.equ THROW_STATUS,0x4f4d80
.equ PRECALL,0x4f54a0
.equ EXECUTE,0x4f33c0
.equ GC_STEP,0x4f2330
.equ STACK_OVERFLOW_MESSAGE,0x9fd840
original_script_call_with_depth_guard:
 push ebp
 mov.s ebp,esp
 and esp,0xfffffff8
 push esi
 mov.s esi,ecx
 mov ecx,0xc8
 push edi
 mov.s edi,edx
 inc WORD PTR [esi+0x34]
 mov ax,WORD PTR [esi+0x34]
 cmp.s ax,cx
 jb .Linvoke
 jne .Loverflow_limit
 push STACK_OVERFLOW_MESSAGE
 push esi
 call RUNTIME_ERROR
 add esp,8
 jmp .Linvoke
.Loverflow_limit:
 mov ecx,0xe1
 cmp.s ax,cx
 jb .Linvoke
 mov edx,5
 mov.s ecx,esi
 call THROW_STATUS
.Linvoke:
 push DWORD PTR [ebp+8]
 mov.s edx,edi
 mov.s ecx,esi
 call PRECALL
 add esp,4
 test eax,eax
 jne .Lfinish
 lea edx,[eax+1]
 mov.s ecx,esi
 call EXECUTE
.Lfinish:
 mov ecx,DWORD PTR [esi+0x10]
 mov eax,0xffff
 add WORD PTR [esi+0x34],ax
 mov eax,DWORD PTR [ecx+0x44]
 cmp eax,DWORD PTR [ecx+0x40]
 jb .Lreturn
 mov.s ecx,esi
 call GC_STEP
.Lreturn:
 pop edi
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
