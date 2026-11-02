/* Provenance: depot SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
 * Evidence: /tmp/cloud-string-reset/{exports,narrow_reset_handler.asm}.
 * Exception entry uses establisher frame at [esp+8], validates both aligned-frame cookies then tail-jumps to 0x8f8968 with metadata 0xb799a8. No return or inline data; ends at next unwind helper. External FuncInfo has magic 0x19930522, maxState 2 and unwind map 0xb799cc; map references 0x901740. Reset itself keeps state -1; metadata and inactive unwind helper remain unreconstructed.
 */
# Reviewed symbolic reconstruction; instruction encodings checked by native-check.
# Original VA range 0x901748..0x901770
.intel_syntax noprefix
.code32
.text
.global original_narrow_reset_handler
original_narrow_reset_handler:
.L901748:
 mov    edx,DWORD PTR [esp+0x8]
.L90174c:
 lea    eax,[edx-0x24]
.L90174f:
 mov    ecx,DWORD PTR [edx-0x28]
.L901752:
 {load} xor    ecx,eax
.L901754:
 call target_8f8958
.L901759:
 add    eax,0x4
.L90175c:
 mov    ecx,DWORD PTR [edx-0x8]
.L90175f:
 {load} xor    ecx,eax
.L901761:
 call target_8f8958
.L901766:
 mov    eax,0xb799a8
.L90176b:
 jmp target_8f8968
.equ target_8f8958,0x8f8958
.equ target_8f8968,0x8f8968
