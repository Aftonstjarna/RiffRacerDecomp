# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x5c2380.
.intel_syntax noprefix
.code32
.text
.global original_unicode_scalar_cp1252_map
original_unicode_scalar_cp1252_map:
    cmp ecx,0x20ac
    jne L_5c238e
    mov eax,0x80
    ret
L_5c238e:
    cmp ecx,0x201a
    jne L_5c239c
    mov eax,0x82
    ret
L_5c239c:
    cmp ecx,0x192
    jne L_5c23aa
    mov eax,0x83
    ret
L_5c23aa:
    cmp ecx,0x201e
    jne L_5c23b8
    mov eax,0x84
    ret
L_5c23b8:
    cmp ecx,0x2026
    jne L_5c23c6
    mov eax,0x85
    ret
L_5c23c6:
    cmp ecx,0x2020
    jne L_5c23d4
    mov eax,0x86
    ret
L_5c23d4:
    cmp ecx,0x2021
    jne L_5c23e2
    mov eax,0x87
    ret
L_5c23e2:
    cmp ecx,0x2c6
    jne L_5c23f0
    mov eax,0x88
    ret
L_5c23f0:
    cmp ecx,0x2030
    jne L_5c23fe
    mov eax,0x89
    ret
L_5c23fe:
    cmp ecx,0x160
    jne L_5c240c
    mov eax,0x8a
    ret
L_5c240c:
    cmp ecx,0x2039
    jne L_5c241a
    mov eax,0x8b
    ret
L_5c241a:
    cmp ecx,0x152
    jne L_5c2428
    mov eax,0x8c
    ret
L_5c2428:
    cmp ecx,0x17d
    jne L_5c2436
    mov eax,0x8e
    ret
L_5c2436:
    cmp ecx,0x2018
    jne L_5c2444
    mov eax,0x91
    ret
L_5c2444:
    cmp ecx,0x2019
    jne L_5c2452
    mov eax,0x92
    ret
L_5c2452:
    cmp ecx,0x201c
    jne L_5c2460
    mov eax,0x93
    ret
L_5c2460:
    cmp ecx,0x201d
    jne L_5c246e
    mov eax,0x94
    ret
L_5c246e:
    cmp ecx,0x2022
    jne L_5c247c
    mov eax,0x95
    ret
L_5c247c:
    cmp ecx,0x2013
    jne L_5c248a
    mov eax,0x96
    ret
L_5c248a:
    cmp ecx,0x2014
    jne L_5c2498
    mov eax,0x97
    ret
L_5c2498:
    cmp ecx,0x2dc
    jne L_5c24a6
    mov eax,0x98
    ret
L_5c24a6:
    cmp ecx,0x2122
    jne L_5c24b4
    mov eax,0x99
    ret
L_5c24b4:
    cmp ecx,0x161
    jne L_5c24c2
    mov eax,0x9a
    ret
L_5c24c2:
    cmp ecx,0x203a
    jne L_5c24d0
    mov eax,0x9b
    ret
L_5c24d0:
    cmp ecx,0x153
    jne L_5c24de
    mov eax,0x9c
    ret
L_5c24de:
    cmp ecx,0x17e
    jne L_5c24ec
    mov eax,0x9e
    ret
L_5c24ec:
    mov eax,0x9f
    cmp ecx,0x178
    cmove ecx,eax
    {load} mov eax,ecx
    ret
