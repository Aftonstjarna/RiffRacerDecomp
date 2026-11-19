.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x48f580.
.equ select_item,0x448180
.equ find_focus,0x447e90
.global original_screen_set_focus_id
original_screen_set_focus_id:
 push ebp
 {load} mov ebp,esp
 push -1
 push 0x8ff408
 mov eax,fs:0
 push eax
 push esi
 push edi
 mov eax,DWORD PTR [0xbaabc0]
 {load} xor eax,ebp
 push eax
 lea eax,[ebp-0xc]
 mov fs:0,eax
 {load} mov esi,ecx
 push DWORD PTR [ebp+8]
 mov ecx,DWORD PTR [esi+0xc]
 call select_item
 mov ecx,DWORD PTR [esi+0xc]
 lea eax,[ebp+8]
 push eax
 call find_focus
 {load} mov edi,eax
 mov DWORD PTR [ebp-4],0
 mov ecx,DWORD PTR [esi+0x14]
 cmp ecx,DWORD PTR [edi]
 je same
 test ecx,ecx
 je replace
 dec DWORD PTR [ecx+4]
 jne replace
 mov eax,DWORD PTR [ecx]
 push 1
 call DWORD PTR [eax]
replace:
 mov eax,DWORD PTR [edi]
 mov DWORD PTR [esi+0x14],eax
 test eax,eax
 je same
 inc DWORD PTR [eax+4]
same:
 mov DWORD PTR [ebp-4],-1
 mov ecx,DWORD PTR [ebp+8]
 test ecx,ecx
 je done
 dec DWORD PTR [ecx+4]
 cmp DWORD PTR [ecx+4],0
 jne done
 mov eax,DWORD PTR [ecx]
 push 1
 call DWORD PTR [eax]
done:
 mov ecx,DWORD PTR [ebp-0xc]
 mov DWORD PTR fs:0,ecx
 pop ecx
 pop edi
 pop esi
 {load} mov esp,ebp
 pop ebp
 ret 4
