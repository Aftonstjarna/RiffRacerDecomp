# Provenance: supported Game.exe SHA256
# 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed objdump VA [008f9320,008f93cb), existing Ghidra export 008f9320,
# and 008f933c export from private /tmp/cloud-conversion-ghidra database.
# Two runtime ST(0)-to-integer entries share the x87 fallback at 008f9356;
# register the contiguous union once, excluding the following INT3 at 008f93cb.
# Ghidra's inferred fastcall parameters are not the ABI: input is x87 ST(0).
# SSE2 path consumes ST(0), returns int32 EAX and leaves EDX unchanged. Checked
# entry additionally requires x87 control-word low seven bits all set before
# branching backward into the first entry's SSE2 path. Otherwise FISTP/FILD
# builds EDX:EAX and sign-dependent ADC/SBB corrects rounding toward zero.
# Zero/integer-indefinite path pops both temporaries without the correction.
# Both paths preserve EBP and restore ESP after dynamic alignment; ECX/EDX
# are volatile. RET has no stack arguments. No SEH frame or embedded data;
# floating exceptions retain the original control-word and instruction behavior.
# Runtime feature flag initialization at 00bfb160 remains an external dependency;
# no claim of a uniform 64-bit result on the SSE2 path or C++ cast equivalence.
.equ runtime_sse2_available,0x00bfb160
.intel_syntax noprefix
.code32
.text
.global original_runtime_fp_convert
original_runtime_fp_convert:
.L8f9320:
 cmp    DWORD PTR [runtime_sse2_available],0x0
.L8f9327:
 je .L8f9356
.L8f9329:
 push   ebp
.L8f932a:
 {load} mov    ebp,esp
.L8f932c:
 sub    esp,0x8
.L8f932f:
 and    esp,0xfffffff8
.L8f9332:
 fstp   QWORD PTR [esp]
.L8f9335:
 cvttsd2si eax,QWORD PTR [esp]
.L8f933a:
 leave
.L8f933b:
 ret
.global original_runtime_fp_convert_checked
original_runtime_fp_convert_checked:
.L8f933c:
 cmp    DWORD PTR [runtime_sse2_available],0x0
.L8f9343:
 je .L8f9356
.L8f9345:
 sub    esp,0x4
.L8f9348:
 fnstcw WORD PTR [esp]
.L8f934b:
 pop    eax
.L8f934c:
 and    ax,0x7f
.L8f9350:
 cmp    ax,0x7f
.L8f9354:
 je .L8f9329
.L8f9356:
 push   ebp
.L8f9357:
 {load} mov    ebp,esp
.L8f9359:
 sub    esp,0x20
.L8f935c:
 and    esp,0xfffffff0
.L8f935f:
 fld    st(0)
.L8f9361:
 fst    DWORD PTR [esp+0x18]
.L8f9365:
 fistp  QWORD PTR [esp+0x10]
.L8f9369:
 fild   QWORD PTR [esp+0x10]
.L8f936d:
 mov    edx,DWORD PTR [esp+0x18]
.L8f9371:
 mov    eax,DWORD PTR [esp+0x10]
.L8f9375:
 test   eax,eax
.L8f9377:
 je .L8f93b5
.L8f9379:
 fsubp  st(1),st
.L8f937b:
 test   edx,edx
.L8f937d:
 jns .L8f939d
.L8f937f:
 fstp   DWORD PTR [esp]
.L8f9382:
 mov    ecx,DWORD PTR [esp]
.L8f9385:
 xor    ecx,0x80000000
.L8f938b:
 add    ecx,0x7fffffff
.L8f9391:
 adc    eax,0x0
.L8f9394:
 mov    edx,DWORD PTR [esp+0x14]
.L8f9398:
 adc    edx,0x0
.L8f939b:
 jmp .L8f93c9
.L8f939d:
 fstp   DWORD PTR [esp]
.L8f93a0:
 mov    ecx,DWORD PTR [esp]
.L8f93a3:
 add    ecx,0x7fffffff
.L8f93a9:
 sbb    eax,0x0
.L8f93ac:
 mov    edx,DWORD PTR [esp+0x14]
.L8f93b0:
 sbb    edx,0x0
.L8f93b3:
 jmp .L8f93c9
.L8f93b5:
 mov    edx,DWORD PTR [esp+0x14]
.L8f93b9:
 test   edx,0x7fffffff
.L8f93bf:
 jne .L8f9379
.L8f93c1:
 fstp   DWORD PTR [esp+0x18]
.L8f93c5:
 fstp   DWORD PTR [esp+0x18]
.L8f93c9:
 leave
.L8f93ca:
 ret
