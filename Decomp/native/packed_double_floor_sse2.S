.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x008fc3c0, exclusive end 0x008fc40a.
.equ TWO52,0x00c0f600
.equ SIGN_BITS,0x00c0f610
.equ ONES,0x00c0f620
.global original_packed_double_floor_sse2
original_packed_double_floor_sse2:
    movaps xmm3,xmm0
    movaps xmm2,XMMWORD PTR [TWO52]
    movaps xmm4,xmm0
    movaps xmm1,XMMWORD PTR [SIGN_BITS]
    movaps xmm5,xmm2
    andps xmm3,xmm1
    andnps xmm1,xmm0
    cmpltpd xmm5,xmm1
    addpd xmm1,xmm2
    subpd xmm1,xmm2
    orps xmm1,xmm3
    movaps xmm6,xmm5
    cmpltpd xmm4,xmm1
    andps xmm4,XMMWORD PTR [ONES]
    andps xmm0,xmm5
    subpd xmm1,xmm4
    andnps xmm6,xmm1
    orps xmm0,xmm6
    ret
.section .note.GNU-stack,"",@progbits
