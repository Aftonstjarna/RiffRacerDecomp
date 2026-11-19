.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x418010 through 0x4180e2 inclusive.
.global original_worker_resource_name_handle_construct
original_worker_resource_name_handle_construct:
 push ebp
 {load} mov ebp,esp
 and esp,0xfffffff8
 push -1
 push 0x8fd828
 mov eax,fs:0
 push eax
 sub esp,0x24
 mov eax,ds:0xbaabc0
 {load} xor eax,esp
 mov [esp+0x1c],eax
 push esi
 push edi
 mov eax,ds:0xbaabc0
 {load} xor eax,esp
 push eax
 lea eax,[esp+0x30]
 mov fs:0,eax
 {load} mov edi,ecx
 mov edx,[ebp+8]
 mov dword ptr [edi],-1
 test edx,edx
 je .Ldone
 cmp byte ptr [edx],0
 je .Ldone
 lea ecx,[esp+0x10]
 call helper_41a110
 mov dword ptr [esp+0x38],0
 lea ecx,[esp+0x10]
 cmp dword ptr [esp+0x24],0x10
 cmovae ecx,[esp+0x10]
 call helper_419ec0
 test eax,eax
 jns .Lfound
 cmp dword ptr [esp+0x24],0x10
 lea ecx,[esp+0x10]
 cmovae ecx,[esp+0x10]
 call helper_41a050
.Lfound:
 mov [edi],eax
 {load} mov esi,eax
 call helper_417270
 {load} mov edx,eax
 mov eax,[edx+4]
 movsx ecx,word ptr [eax+esi*2]
 mov eax,[edx+0x28]
 inc dword ptr [eax+ecx*8+4]
 cmp dword ptr [esp+0x24],0x10
 jb .Ldone
 push dword ptr [esp+0x10]
 call dword ptr ds:0x92d4b0
 add esp,4
.Ldone:
 {load} mov eax,edi
 mov ecx,[esp+0x30]
 mov fs:0,ecx
 pop ecx
 pop edi
 pop esi
 mov ecx,[esp+0x1c]
 {load} xor ecx,esp
 call helper_8f8958
 {load} mov esp,ebp
 pop ebp
 ret 4
.equ helper_41a110,0x41a110
.equ helper_419ec0,0x419ec0
.equ helper_41a050,0x41a050
.equ helper_417270,0x417270
.equ helper_8f8958,0x8f8958
