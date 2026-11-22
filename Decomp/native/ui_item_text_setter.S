# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x450930,0x4509d0); instruction-contiguous extent, padding excluded.
# UI item text setter wrapper: ECX is the item and [EBP+8] the text string; forwards the item field block
# (+0x1C8..+0x1E0, including the 0x1D8/0x1E0 floats and 0x1DC/0x1DE bytes) through 0x416520 and
# the narrow-string assignment at 0x455520. No literal text is introduced.
# Derived from original instructions; earns reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x450930..0x4509d0
.intel_syntax noprefix
.code32
.text
.global original_ui_item_text_setter
original_ui_item_text_setter:
.L450930:
 push   ebp
.L450931:
 {load} mov    ebp,esp
.L450933:
 and    esp,0xfffffff8
.L450936:
 sub    esp,0x8
.L450939:
 push   esi
.L45093a:
 {load} mov    esi,ecx
.L45093c:
 push   edi
.L45093d:
 mov    edi,DWORD PTR [ebp+0x8]
.L450940:
 movzx  eax,BYTE PTR [esi+0x1de]
.L450947:
 movss  xmm0,DWORD PTR [esi+0x1e0]
.L45094f:
 push   eax
.L450950:
 movzx  eax,BYTE PTR [esi+0x1dc]
.L450957:
 push   ecx
.L450958:
 movss  DWORD PTR [esp],xmm0
.L45095d:
 movss  xmm0,DWORD PTR [esi+0x1d8]
.L450965:
 push   eax
.L450966:
 push   ecx
.L450967:
 mov    ecx,DWORD PTR [esi+0x1cc]
.L45096d:
 lea    eax,[esi+0x28]
.L450970:
 movss  DWORD PTR [esp],xmm0
.L450975:
 push   DWORD PTR [esi+0x1d4]
.L45097b:
 push   DWORD PTR [esi+0x1d0]
.L450981:
 push   eax
.L450982:
 push   DWORD PTR [esi+0x1c8]
.L450988:
 lea    eax,[esp+0x28]
.L45098c:
 push   DWORD PTR [esi+0x1c4]
.L450992:
 push   edi
.L450993:
 push   eax
.L450994:
 call target_455520
.L450999:
 mov    ecx,DWORD PTR [eax]
.L45099b:
 mov    DWORD PTR [esi+0x30],ecx
.L45099e:
 mov    eax,DWORD PTR [eax+0x4]
.L4509a1:
 mov    DWORD PTR [esi+0x34],eax
.L4509a4:
 cmp    BYTE PTR [edi],0x0
.L4509a7:
 jne .L4509ad
.L4509a9:
 {load} xor    ecx,ecx
.L4509ab:
 jmp .L4509bb
.L4509ad:
 {load} mov    ecx,edi
.L4509af:
 lea    edx,[ecx+0x1]
.L4509b2:
 mov    al,BYTE PTR [ecx]
.L4509b4:
 inc    ecx
.L4509b5:
 test   al,al
.L4509b7:
 jne .L4509b2
.L4509b9:
 {load} sub    ecx,edx
.L4509bb:
 push   ecx
.L4509bc:
 push   edi
.L4509bd:
 lea    ecx,[esi+0x194]
.L4509c3:
 call target_416520
.L4509c8:
 pop    edi
.L4509c9:
 pop    esi
.L4509ca:
 {load} mov    esp,ebp
.L4509cc:
 pop    ebp
.L4509cd:
 ret    0x4
.equ target_416520,0x416520
.equ target_455520,0x455520
