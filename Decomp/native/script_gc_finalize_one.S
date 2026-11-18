# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4f1bc0.
.intel_syntax noprefix
.code32
.text
.global original_script_gc_finalize_one
.equ lookup_method,0x4f5ca0
.equ invoke_method,0x4f5830
original_script_gc_finalize_one:
 push ebp
 mov.s ebp,esp
 sub esp,0xc
 mov.s edx,ecx
 push esi
 push edi
 mov [ebp-8],edx
 mov esi,[edx+0x10]
 mov [ebp-0xc],esi
 mov ecx,[esi+0x30]
 mov edi,[ecx]
 cmp.s edi,ecx
 jne .Lunlink
 mov DWORD PTR [esi+0x30],0
 jmp .Lrelink
.Lunlink:
 mov eax,[edi]
 mov [ecx],eax
.Lrelink:
 mov eax,[esi+0x64]
 mov eax,[eax]
 mov [edi],eax
 mov eax,[esi+0x64]
 mov [eax],edi
 mov cl,[esi+0x14]
 mov al,[edi+5]
 and cl,3
 and al,0xf8
 or.s cl,al
 mov [edi+5],cl
 mov ecx,[edi+8]
 test ecx,ecx
 je .Ldone
 test BYTE PTR [ecx+6],4
 jne .Ldone
 mov eax,[edx+0x10]
 mov edx,2
 push DWORD PTR [eax+0xa8]
 call lookup_method
 add esp,4
 mov [ebp-4],eax
 test eax,eax
 je .Ldone
 mov edx,[ebp-8]
 mov esi,[esi+0x40]
 mov eax,[ebp-0xc]
 push ebx
 mov bl,[edx+0x39]
 mov BYTE PTR [edx+0x39],0
 mov ecx,[eax+0x44]
 add.s ecx,ecx
 mov [eax+0x40],ecx
 mov ecx,[edx+8]
 mov eax,[ebp-4]
 push 0
 mov eax,[eax]
 mov [ecx],eax
 mov eax,[ebp-4]
 mov eax,[eax+4]
 mov [ecx+4],eax
 mov eax,[edx+8]
 mov [eax+8],edi
 mov edi,[ebp-8]
 mov.s ecx,edi
 mov DWORD PTR [eax+0xc],7
 add DWORD PTR [edx+8],0x10
 mov edx,[edx+8]
 add edx,-0x10
 call invoke_method
 mov eax,[ebp-0xc]
 add esp,4
 mov [edi+0x39],bl
 mov [eax+0x40],esi
 pop ebx
.Ldone:
 pop edi
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
