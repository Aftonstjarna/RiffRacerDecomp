# Supported Game.exe SHA256:
# 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original objdump boundaries, PE imports and private Ghidra exports:
# development:/tmp/cloud-growth-runtime/{handlers.asm,frame-boundaries.asm,
# import-boundaries.asm,pe.txt,eh-data.txt,exports,ghidra.log,original.sha256}.
# Private Strings DB copied from prior private growth DB; shared DB untouched.
# Four uncovered code routines supporting wide_grow's copy/retry/rethrow paths.
# No embedded data or padding; all boundaries agree with Ghidra and objdump.
# External IAT contents and EH metadata are dependencies, not rebuilt here.
.intel_syntax noprefix
.code32

.section .wide_grow_handler,"ax"
.global original_wide_grow_handler
original_wide_grow_handler:
# VA [0x8ffa00,0x8ffa1b). MSVC EH dispatcher, not an ordinary C function.
# [esp+8] is the registration frame (grow EBP-0xc); EAX=frame+0xc.
# Decode saved cookie [frame-0x1c] with EAX into ECX; existing checker
# 0x8f8958 preserves EDX/EAX on success, tail-fails on cookie mismatch.
# EAX then carries FuncInfo VA into the tail-dispatched frame handler.
# No local return/stack cleanup: original exception-dispatch ABI is retained.
    mov edx,DWORD PTR [esp+8]
    lea eax,[edx+0xc]
    mov ecx,DWORD PTR [edx-0x1c]
    {load} xor ecx,eax
    call original_cookie_check_va
    mov eax,OFFSET FLAT:wide_grow_funcinfo_va
    jmp original_cxx_frame_handler_va
# FuncInfo at 0xb77f48: magic 0x19930522, maxState=4, unwind=0xb77f6c,
# tryCount=2, tryMap=0xb77f8c, flags=1. Four unwind entries:
# (-1,0),(-1,0),(1,0),(1,0). Try ranges [2,2,3] and [0,0,3],
# each one catch-all (adjectives=0x40,type=0,object=0), handlers
# 0x44feba and 0x44fe80 respectively. Tables remain external: this code
# match does not reconstruct EH metadata, imports, or CRT implementation.
.equ original_cookie_check_va,0x8f8958
.equ wide_grow_funcinfo_va,0xb77f48
.equ original_cxx_frame_handler_va,0x8f8968

.section .cxx_frame_handler_import,"ax"
.global original_cxx_frame_handler_import
original_cxx_frame_handler_import:
# VA [0x8f8968,0x8f896e). Tail jump preserves dispatcher registers,
# arguments and return address. IAT 0x92d4c4 = __CxxFrameHandler3.
    jmp DWORD PTR [0x92d4c4]

.section .cxx_throw_import,"ax"
.global original_cxx_throw_import
original_cxx_throw_import:
# VA [0x8f8d5a,0x8f8d60). IAT 0x92d49c = _CxxThrowException.
# No wrapper prologue/cleanup. Growth's failure funclet passes (0,0)
# to rethrow the active exception; the imported runtime does not return.
    jmp DWORD PTR [0x92d49c]

.section .memcpy_import,"ax"
.global original_memcpy_import
original_memcpy_import:
# VA [0x8f8d66,0x8f8d6c). IAT 0x92d494 = memcpy; cdecl stack
# (destination,source,byte_count), EAX=result, caller removes arguments.
# Pure tail jump retains all ABI effects in the external CRT. Growth uses
# preserved_length*2 bytes; substring/range assignment share this thunk.
    jmp DWORD PTR [0x92d494]
