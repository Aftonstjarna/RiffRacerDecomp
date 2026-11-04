# Reviewed against pinned depot SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Evidence: /tmp/cloud-narrow-dependencies/{exports/00415b60.txt,narrow_destroy.asm}.
# ECX=this, preserves ESI, no stack arguments. Capacity >=16 releases heap
# through scalar delete IAT 0x92d4b0; then restores capacity=15, length=0,
# inline NUL. No local EH frame or embedded data; ret ends at 415b87,
# excluding following int3 alignment. Delete exceptions propagate unchanged.
# Original VA range 0x415b60..0x415b87
.intel_syntax noprefix
.code32
.text
.global original_narrow_destroy
original_narrow_destroy:
.L415b60:
 push   esi
.L415b61:
 {load} mov    esi,ecx
.L415b63:
 cmp    DWORD PTR [esi+0x14],0x10
.L415b67:
 jb .L415b74
.L415b69:
 push   DWORD PTR [esi]
.L415b6b:
 call   DWORD PTR [0x92d4b0]
.L415b71:
 add    esp,0x4
.L415b74:
 mov    DWORD PTR [esi+0x14],0xf
.L415b7b:
 mov    DWORD PTR [esi+0x10],0x0
.L415b82:
 mov    BYTE PTR [esi],0x0
.L415b85:
 pop    esi
.L415b86:
 ret
