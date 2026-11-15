.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4384f0, complete 7-byte btMotionState base destructor.
.equ MOTION_STATE_VTABLE,0x9f981c
.global original_motion_state_base_destruct
original_motion_state_base_destruct:
    mov DWORD PTR [ecx], MOTION_STATE_VTABLE
    ret
