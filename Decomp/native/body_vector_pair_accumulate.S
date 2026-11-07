# Mechanically transcribed reference evidence; NOT high-level source recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4386f0, complete span [0x4386f0,0x438820).
.intel_syntax noprefix
.code32
.text
.equ scaled_vector_accumulate,0x4385f0
.global original_body_vector_pair_accumulate
original_body_vector_pair_accumulate:
  push   ebp
  {load} mov    ebp,esp
  movss  xmm1,DWORD PTR [ecx+0x150]
  sub    esp,0x10
  xorps  xmm0,xmm0
  ucomiss xmm1,xmm0
  lahf
  test   ah,0x44
  jnp    done
  mov    edx,DWORD PTR [ebp+0x8]
  lea    eax,[ecx+0x218]
  movss  xmm0,DWORD PTR [ecx+0x15c]
  movss  xmm4,xmm1
  movss  xmm3,DWORD PTR [ecx+0x158]
  movaps xmm1,xmm4
  mulss  xmm0,DWORD PTR [edx+0x8]
  movss  xmm2,DWORD PTR [edx]
  mulss  xmm2,DWORD PTR [ecx+0x154]
  mulss  xmm3,DWORD PTR [edx+0x4]
  mulss  xmm1,xmm2
  movaps xmm2,xmm4
  mulss  xmm4,xmm0
  movss  xmm0,DWORD PTR [ecx+0x130]
  mulss  xmm2,xmm3
  addss  xmm0,xmm1
  movss  DWORD PTR [ecx+0x130],xmm0
  movss  xmm0,DWORD PTR [ecx+0x134]
  addss  xmm0,xmm2
  movss  DWORD PTR [ecx+0x134],xmm0
  movss  xmm0,DWORD PTR [ecx+0x138]
  addss  xmm0,xmm4
  movss  DWORD PTR [ecx+0x138],xmm0
  test   eax,eax
  je     done
  mov    eax,DWORD PTR [ebp+0xc]
  movss  xmm5,DWORD PTR [ecx+0x158]
  movss  xmm3,DWORD PTR [ecx+0x15c]
  mulss  xmm5,DWORD PTR [edx+0x4]
  mov    DWORD PTR [ebp-0x4],0x0
  mulss  xmm3,DWORD PTR [edx+0x8]
  movss  xmm4,DWORD PTR [eax+0x4]
  movss  xmm2,DWORD PTR [eax+0x8]
  movaps xmm1,xmm4
  movss  xmm6,DWORD PTR [edx]
  movaps xmm0,xmm2
  mulss  xmm6,DWORD PTR [ecx+0x154]
  mulss  xmm1,xmm3
  mulss  xmm0,xmm5
  mulss  xmm2,xmm6
  subss  xmm1,xmm0
  mulss  xmm4,xmm6
  movss  DWORD PTR [ebp-0x10],xmm1
  movss  xmm1,DWORD PTR [eax]
  lea    eax,[ebp-0x10]
  movaps xmm0,xmm1
  mulss  xmm1,xmm5
  push   eax
  mulss  xmm0,xmm3
  subss  xmm1,xmm4
  subss  xmm2,xmm0
  movss  DWORD PTR [ebp-0x8],xmm1
  movss  DWORD PTR [ebp-0xc],xmm2
  call   scaled_vector_accumulate
done:
  {load} mov    esp,ebp
  pop    ebp
  ret    0x8
