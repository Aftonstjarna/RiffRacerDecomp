.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x443110, exclusive end 0x44313b; both returns included.
.global original_object_flags_channel_enabled
original_object_flags_channel_enabled:
 push esi
 {load} mov esi,ecx
 mov al,BYTE PTR [esi+0x174]
 test al,0x1
 je disabled
 test al,0x2
 je disabled
 test al,0x4
 je disabled
 mov eax,0x1
 {load} mov ecx,edx
 shl eax,cl
 test DWORD PTR [esi+0x4c],eax
 je disabled
 mov al,0x1
 pop esi
 ret
disabled:
 {load} xor al,al
 pop esi
 ret
