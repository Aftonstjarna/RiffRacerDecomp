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
# Test-only, single-threaded i386 TLS backing for normal-path FS:[0] access.
# int test_install_fs(void *storage): 0 on success, negative Linux errno on
# failure. Caller owns valid writable storage and must initialize its head.
# Reuse the allocated descriptor when rebinding so repeated tests do not
# consume TLS entries. This does NOT implement Windows dispatch/unwinding.
.global test_install_fs, test_get_fs_head
test_install_fs:
 mov eax, [esp+4]
 test eax, eax
 jz .invalid_fs_storage
 push ebx
 mov [test_fs_descriptor+4], eax
 lea ebx, [test_fs_descriptor]
 mov eax, 243 # Linux i386 __NR_set_thread_area
 int 0x80
 test eax, eax
 js .fs_done
 mov eax, [test_fs_descriptor]
 shl eax, 3
 or eax, 3
 mov fs, ax
 xor eax, eax
.fs_done:
 pop ebx
 ret
.invalid_fs_storage:
 mov eax, -22 # EINVAL; existing FS remains unchanged
 ret
test_get_fs_head:
 mov eax, DWORD PTR fs:[0]
 ret
.data
.align 4
test_fs_descriptor:
 .long -1, 0, 0xfffff, 0x51 # user_desc: allocated entry, base, 4GiB limit, writable 32-bit data
.section .note.GNU-stack,"",@progbits
