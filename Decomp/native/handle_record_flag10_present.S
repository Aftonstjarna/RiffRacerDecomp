# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x499e40,0x499e52). Both returns included; INT3 padding excluded.
# ECX points to a handle whose first word points to a record; AL is the boolean result.
.intel_syntax noprefix
.code32
.text
.global original_handle_record_flag10_present
original_handle_record_flag10_present:
    mov eax, DWORD PTR [ecx]
    test eax, eax
    je flag_absent
    cmp BYTE PTR [eax+0x10], 0
    je flag_absent
    mov al, 1
    ret
flag_absent:
    {load} xor al, al
    ret
