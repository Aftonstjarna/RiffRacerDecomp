# Reviewed against pinned depot SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Evidence: /tmp/cloud-narrow-dependencies/{exports/00901740.txt,unwind-context.asm,unwind-data.txt}.
# EH funclet: inherited EBP locates temporary at -0x2c; tail-jumps to
# destructor 415b60 with ECX=this, preserving caller return address. Exactly
# eight bytes before handler 901748. Ghidra includes noncontiguous destructor
# tail in its body; that separate span is registered once as narrow-destroy.
# FuncInfo b799a8 / unwind map b799cc references this helper. Metadata remains
# external, unreconstructed; no embedded data or independent stack frame.
# Original VA range 0x901740..0x901748
.intel_syntax noprefix
.code32
.text
.global original_narrow_reset_unwind
original_narrow_reset_unwind:
.L901740:
 lea    ecx,[ebp-0x2c]
.L901743:
 jmp target_415b60
.equ target_415b60,0x415b60
