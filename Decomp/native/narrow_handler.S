# Reviewed pinned depot SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Evidence /tmp/cloud-string-growth/{handler.asm,exports/008fd780.txt,eh-data.txt}.
# Growth's EH thunk: stack+8 is registration frame; recover EBP via +12,
# validate cookie from frame-28 XOR recovered EBP through 8f8958, load EAX
# with FuncInfo b75d80, tail-jump 8f8968 (__CxxFrameHandler3 import thunk).
# Runtime ABI, no ordinary ret or embedded data. Extent ends 8fd79b before int3.
# FuncInfo and shared runtime remain external and earn no coverage here.
# Original VA range 0x8fd780..0x8fd79b
.intel_syntax noprefix
.code32
.text
.global original_narrow_handler
original_narrow_handler:
.L8fd780:
 mov    edx,DWORD PTR [esp+0x8]
.L8fd784:
 lea    eax,[edx+0xc]
.L8fd787:
 mov    ecx,DWORD PTR [edx-0x1c]
.L8fd78a:
 {load} xor    ecx,eax
.L8fd78c:
 call target_8f8958
.L8fd791:
 mov    eax,0xb75d80
.L8fd796:
 jmp target_8f8968
.equ target_8f8958,0x8f8958
.equ target_8f8968,0x8f8968
