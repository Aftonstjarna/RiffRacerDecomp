# Test-only Linux i386 entry/syscall/MXCSR helpers. Never recovery-byte credit.
.intel_syntax noprefix
.code32
.text
.global _start, test_write, test_get_mxcsr, test_set_mxcsr
_start:
 call test_main
 mov ebx, eax
 mov eax, 1
 int 0x80
test_write:
 push ebx
 mov eax, 4
 mov ebx, 1
 mov ecx, [esp+8]
 mov edx, [esp+12]
 int 0x80
 pop ebx
 ret
test_get_mxcsr:
 sub esp, 4
 stmxcsr [esp]
 mov eax, [esp]
 add esp, 4
 ret
test_set_mxcsr:
 ldmxcsr [esp+4]
 ret
.section .note.GNU-stack,"",@progbits
