# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8fc990,0x8fc9a1). Padding and preceding jump thunk excluded.
.intel_syntax noprefix
.code32
.text
.global original_sse_raise_invalid
original_sse_raise_invalid:
    pcmpeqd xmm3,xmm3
    pslld xmm3,0x1f
    xorps xmm2,xmm2
    divss xmm3,xmm2
    ret
.section .note.GNU-stack,"",@progbits
