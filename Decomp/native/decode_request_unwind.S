# Reviewed against /tmp/cloud-request-review/exception.asm and Ghidra
# exports/00901770.txt, supported original SHA256 recorded in original.sha256.
# EH funclet: inherited EBP, ECX=&local resource reference at EBP-10;
# tail-jump to 41cd10. Ghidra includes that shared tail in its function body;
# register only these 8 distinct bytes, with the tail registered separately.
# FuncInfo b799dc -> unwind map b79a00 -> (-1,901770), checked in .rdata.
# Original VA range 0x901770..0x901778
.intel_syntax noprefix
.code32
.text
.global original_decode_request_unwind
original_decode_request_unwind:
.L901770:
 lea    ecx,[ebp-0x10]
.L901773:
 jmp target_41cd10
.equ target_41cd10,0x41cd10
