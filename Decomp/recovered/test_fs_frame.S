# Synthetic normal-path registration probe; no recovered-byte credit.
.intel_syntax noprefix
.code32
.text
.global exercise_frame
exercise_frame:
 push DWORD PTR fs:[0]
 mov DWORD PTR fs:[0], esp
 mov eax, DWORD PTR fs:[0]
 cmp eax, esp
 jne .failed
 pop eax
 mov DWORD PTR fs:[0], eax
 ret
.failed:
 pop eax
 mov DWORD PTR fs:[0], eax
 xor eax, eax
 ret
.section .note.GNU-stack,"",@progbits
