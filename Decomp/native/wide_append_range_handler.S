# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Evidence: /tmp/reriff-recovery-resume/{exports,*.asm,ghidra.log}.
# Private copy of Strings Ghidra DB; existing research databases unchanged.
# Reviewed original [0x8ffa20,0x8ffa3b), MSVC exception-dispatch ABI.
# Registration frame from [esp+8]; EAX=frame+0xc; cookie at frame-0x18
# XOR EAX into ECX. Calls recovered cookie check; passes FuncInfo 0xb77fd4
# in EAX and tail-jumps to recovered __CxxFrameHandler3 import thunk.
# FuncInfo and unwind/try maps remain external, not credited as source recovery.
# Original VA range 0x8ffa20..0x8ffa3b
.intel_syntax noprefix
.code32
.text
.global original_wide_append_range_handler
original_wide_append_range_handler:
.L8ffa20:
 mov    edx,DWORD PTR [esp+0x8]
.L8ffa24:
 lea    eax,[edx+0xc]
.L8ffa27:
 mov    ecx,DWORD PTR [edx-0x18]
.L8ffa2a:
 {load} xor    ecx,eax
.L8ffa2c:
 call target_8f8958
.L8ffa31:
 mov    eax,0xb77fd4
.L8ffa36:
 jmp target_8f8968
.equ target_8f8958,0x8f8958
.equ target_8f8968,0x8f8968
