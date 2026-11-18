# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4f1900.
.intel_syntax noprefix
.code32
.text
.global original_script_gc_clear_weak_entries
original_script_gc_clear_weak_entries:
 push ebx
 mov.s ebx,ecx
 test ebx,ebx
 je .Lexit
 push esi
 push edi
 {disp8} lea ecx,[ecx+0]
.Lobject:
 test BYTE PTR [ebx+5],0x10
 mov edx,[ebx+0x1c]
 je .Lhash_init
 test edx,edx
 je .Lhash_init
 {disp8} lea ecx,[ecx+0]
.Larray:
 mov eax,[ebx+0xc]
 dec edx
 mov esi,[eax+edx*8+4]
 lea ecx,[eax+edx*8]
 cmp esi,4
 jl .Larray_next
 mov eax,[ecx]
 jne .Larray_other
 and BYTE PTR [eax+5],0xfc
 jmp .Larray_next
.Larray_other:
 mov al,[eax+5]
 test al,3
 jne .Larray_clear
 cmp esi,7
 jne .Larray_next
 test al,8
 je .Larray_next
.Larray_clear:
 mov DWORD PTR [ecx+4],0
.Larray_next:
 test edx,edx
 jne .Larray
.Lhash_init:
 mov cl,[ebx+7]
 mov esi,1
 shl esi,cl
 test esi,esi
 je .Lnext_object
 lea edi,[esi+esi*4]
 shl edi,2
 {disp32} lea esp,[esp+0]
.Lhash:
 mov eax,[ebx+0x10]
 sub edi,0x14
 add.s eax,edi
 dec esi
 cmp DWORD PTR [eax+4],0
 je .Lhash_next
 mov ecx,[eax+0xc]
 cmp ecx,4
 jl .Lvalue
 mov ecx,[eax+8]
 jne .Lkey_other
 and BYTE PTR [ecx+5],0xfc
 jmp .Lvalue
.Lkey_other:
 test BYTE PTR [ecx+5],3
 jne .Lclear
.Lvalue:
 mov edx,[eax+4]
 cmp edx,4
 jl .Lhash_next
 jne .Lvalue_other
 mov eax,[eax]
 and BYTE PTR [eax+5],0xfc
 jmp .Lhash_next
.Lvalue_other:
 mov ecx,[eax]
 mov cl,[ecx+5]
 test cl,3
 jne .Lclear
 cmp edx,7
 jne .Lhash_next
 test cl,8
 je .Lhash_next
.Lclear:
 cmp DWORD PTR [eax+0xc],4
 mov DWORD PTR [eax+4],0
 jl .Lhash_next
 mov DWORD PTR [eax+0xc],0xb
.Lhash_next:
 test esi,esi
 jne .Lhash
.Lnext_object:
 mov ebx,[ebx+0x18]
 test ebx,ebx
 jne .Lobject
 pop edi
 pop esi
.Lexit:
 pop ebx
 ret
