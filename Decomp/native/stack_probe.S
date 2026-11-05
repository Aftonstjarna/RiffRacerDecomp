# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256:
# 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f9800,0x8f982b); INT3 padding excluded.
# EAX=requested stack bytes; ECX preserved. No calls or external data.
# Includes page-touch loop after RET. Windows guard-page behavior remains external.
.intel_syntax noprefix
.code32
.text
.global original_stack_probe
original_stack_probe:
 push ecx
 lea ecx,[esp+4]
 {load} sub ecx,eax
 {load} sbb eax,eax
 not eax
 {load} and ecx,eax
 {load} mov eax,esp
 and eax,0xfffff000
.Lcompare:
 {load} cmp ecx,eax
 jb .Lprobe
 {load} mov eax,ecx
 pop ecx
 xchg esp,eax
 mov eax,DWORD PTR [eax]
 mov DWORD PTR [esp],eax
 ret
.Lprobe:
 sub eax,0x1000
 test DWORD PTR [eax],eax
 jmp .Lcompare
.section .note.GNU-stack,"",@progbits
