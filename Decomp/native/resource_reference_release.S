# Reviewed against /tmp/cloud-request-review/release.asm and Ghidra
# exports/0041cd10.txt; supported original SHA256 in original.sha256.
# ECX points to reference slot. Null is a no-op; non-null decrements signed
# storage at object+4 without atomic operations; zero calls vslot 0 with
# deleting flag 1, object in ECX. Plain RET, no stack arguments to helper.
# Does not clear slot, check underflow, or impose alternate ownership rules.
# Shared tail of request unwind funclet 901770. Ends 41cd22 before padding.
# Original VA range 0x41cd10..0x41cd22
.intel_syntax noprefix
.code32
.text
.global original_resource_reference_release
original_resource_reference_release:
.L41cd10:
 mov    ecx,DWORD PTR [ecx]
.L41cd12:
 test   ecx,ecx
.L41cd14:
 je .L41cd21
.L41cd16:
 dec    DWORD PTR [ecx+0x4]
.L41cd19:
 jne .L41cd21
.L41cd1b:
 mov    eax,DWORD PTR [ecx]
.L41cd1d:
 push   0x1
.L41cd1f:
 call   DWORD PTR [eax]
.L41cd21:
 ret
