# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x4242e0,0x424376); surrounding INT3 padding excluded.
# ECX=0x234-byte object, EAX=this, no stack arguments, plain RET.
# Twelve iterations initialize the entire 0x234-byte object; see reference.json.
.intel_syntax noprefix
.code32
.text
.global original_worker_state_construct
original_worker_state_construct:
 push ebx
 mov.s ebx,ecx
 mov ecx,0xc
 push esi
 push edi
 lea edi,[ebx+0x1ac]
 lea edx,[ebx+0x181]
 lea esi,[ebx+0x1a8]
 lea eax,[ebx+0xc0]
.Linitialize_pair:
 mov DWORD PTR [eax-0xc0],0x3f19999a
 lea eax,[eax+8]
 mov DWORD PTR [eax-0x68],0
 lea esi,[esi+0xc]
 mov DWORD PTR [eax-8],0
 lea edx,[edx+3]
 mov DWORD PTR [eax+0x58],2
 lea edi,[edi+0xc]
 mov BYTE PTR [edx-4],0
 mov DWORD PTR [esi-0x10],0
 mov DWORD PTR [eax-0xc4],0x3f19999a
 mov DWORD PTR [eax-0x64],0
 mov DWORD PTR [eax-4],0
 mov DWORD PTR [eax+0x5c],2
 mov BYTE PTR [edx-3],0
 mov DWORD PTR [esi-0xc],0
 mov BYTE PTR [edx-2],0
 mov DWORD PTR [edi-0xc],0
 dec ecx
 jne .Linitialize_pair
 pop edi
 pop esi
 mov.s eax,ebx
 pop ebx
 ret
.section .note.GNU-stack,"",@progbits
