# Test oracle only: reviewed symbolic transcription of [0x4f91f0,0x4f9212).
# Supported original SHA256 is recorded in provenance.json. No coverage credit.
.intel_syntax noprefix
.code32
.section .flac_channel0_loop,"ax"
.global original_flac_channel0_loop
original_flac_channel0_loop:
    movsx eax,WORD PTR [ebp+ecx*2-0x1010]
    lea edx,[edx+4]
    add ecx,2
    movd xmm0,eax
    cvtdq2ps xmm0,xmm0
    mulss xmm0,xmm1
    movss DWORD PTR [edx-4],xmm0
    {load} cmp ecx,esi
    jl original_flac_channel0_loop

# Test-only fallthrough after the exact original loop. This return is never
# included in the compared reference span and is not an original instruction.
.section .test_loop_return,"ax"
    ret
.text
.global original_flac_channel_zero
original_flac_channel_zero:
    push ebp
    push esi
    mov esi,DWORD PTR [esp+16]
    shr esi,1
    xor eax,eax
    test esi,esi
    jz .done
    mov eax,DWORD PTR [esp+12]
    lea ebp,[eax+0x1010]
    mov edx,DWORD PTR [esp+20]
    xor ecx,ecx
    movss xmm1,DWORD PTR [.scale]
    call original_flac_channel0_loop
    mov eax,ecx
    shr eax,1
.done:
    pop esi
    pop ebp
    ret
.section .rodata
.scale:
    .long 0x38000000 # Genuine float data: verified at original VA 0xa06428.
.section .note.GNU-stack,"",@progbits
