.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x457f70,0x457f93); ECX node, EAX terminal field address.
.global original_node_chain_terminal_vector
original_node_chain_terminal_vector:
 mov eax,DWORD PTR [ecx+0x1c0]
 test eax,eax
 je terminal
 {disp32} lea ebx,[ebx+0]
next_node:
 lea ecx,[eax]
 mov eax,DWORD PTR [ecx+0x1c0]
 test eax,eax
 jne next_node
terminal:
 lea eax,[ecx+0x1b0]
 ret
.section .note.GNU-stack,"",@progbits
