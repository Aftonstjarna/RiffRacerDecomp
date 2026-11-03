
Game.exe:     file format pei-i386


Disassembly of section .text:

0048d9c0 <.text+0x8c9c0>:
  48d9c0:	55                   	push   ebp
  48d9c1:	8b ec                	mov    ebp,esp
  48d9c3:	83 e4 f8             	and    esp,0xfffffff8
  48d9c6:	83 ec 0c             	sub    esp,0xc
  48d9c9:	53                   	push   ebx
  48d9ca:	56                   	push   esi
  48d9cb:	57                   	push   edi
  48d9cc:	8b f9                	mov    edi,ecx
  48d9ce:	6a ff                	push   0xffffffff
  48d9d0:	ff 77 14             	push   DWORD PTR [edi+0x14]
  48d9d3:	ff 15 24 d1 92 00    	call   DWORD PTR ds:0x92d124
  48d9d9:	80 7f 1c 00          	cmp    BYTE PTR [edi+0x1c],0x0
  48d9dd:	0f 85 90 01 00 00    	jne    0x48db73
  48d9e3:	c6 44 24 14 2e       	mov    BYTE PTR [esp+0x14],0x2e
  48d9e8:	83 c9 ff             	or     ecx,0xffffffff
  48d9eb:	eb 03                	jmp    0x48d9f0
  48d9ed:	8d 49 00             	lea    ecx,[ecx+0x0]
  48d9f0:	8b 47 30             	mov    eax,DWORD PTR [edi+0x30]
  48d9f3:	83 f8 01             	cmp    eax,0x1
  48d9f6:	0f 82 54 01 00 00    	jb     0x48db50
  48d9fc:	48                   	dec    eax
  48d9fd:	83 f8 ff             	cmp    eax,0xffffffff
  48da00:	0f 47 c1             	cmova  eax,ecx
  48da03:	83 7f 34 10          	cmp    DWORD PTR [edi+0x34],0x10
  48da07:	72 05                	jb     0x48da0e
  48da09:	8b 4f 20             	mov    ecx,DWORD PTR [edi+0x20]
  48da0c:	eb 03                	jmp    0x48da11
  48da0e:	8d 4f 20             	lea    ecx,[edi+0x20]
  48da11:	8d 34 01             	lea    esi,[ecx+eax*1]
  48da14:	80 3e 2e             	cmp    BYTE PTR [esi],0x2e
  48da17:	75 0a                	jne    0x48da23
  48da19:	8a 06                	mov    al,BYTE PTR [esi]
  48da1b:	8d 4c 24 14          	lea    ecx,[esp+0x14]
  48da1f:	3a 01                	cmp    al,BYTE PTR [ecx]
  48da21:	74 13                	je     0x48da36
  48da23:	8d 4f 20             	lea    ecx,[edi+0x20]
  48da26:	e8 35 87 f8 ff       	call   0x416160
  48da2b:	3b f0                	cmp    esi,eax
  48da2d:	0f 84 1d 01 00 00    	je     0x48db50
  48da33:	4e                   	dec    esi
  48da34:	eb de                	jmp    0x48da14
  48da36:	83 7f 34 10          	cmp    DWORD PTR [edi+0x34],0x10
  48da3a:	72 05                	jb     0x48da41
  48da3c:	8b 47 20             	mov    eax,DWORD PTR [edi+0x20]
  48da3f:	eb 03                	jmp    0x48da44
  48da41:	8d 47 20             	lea    eax,[edi+0x20]
  48da44:	2b f0                	sub    esi,eax
  48da46:	83 fe ff             	cmp    esi,0xffffffff
  48da49:	0f 84 01 01 00 00    	je     0x48db50
  48da4f:	83 7f 34 10          	cmp    DWORD PTR [edi+0x34],0x10
  48da53:	72 05                	jb     0x48da5a
  48da55:	8b 47 20             	mov    eax,DWORD PTR [edi+0x20]
  48da58:	eb 03                	jmp    0x48da5d
  48da5a:	8d 47 20             	lea    eax,[edi+0x20]
  48da5d:	03 f0                	add    esi,eax
  48da5f:	68 0c be 9f 00       	push   0x9fbe0c
  48da64:	56                   	push   esi
  48da65:	ff 15 d8 d3 92 00    	call   DWORD PTR ds:0x92d3d8
  48da6b:	83 c4 08             	add    esp,0x8
  48da6e:	85 c0                	test   eax,eax
  48da70:	74 7d                	je     0x48daef
  48da72:	68 14 be 9f 00       	push   0x9fbe14
  48da77:	56                   	push   esi
  48da78:	ff 15 d8 d3 92 00    	call   DWORD PTR ds:0x92d3d8
  48da7e:	83 c4 08             	add    esp,0x8
  48da81:	85 c0                	test   eax,eax
  48da83:	74 6a                	je     0x48daef
  48da85:	68 fc bd 9f 00       	push   0x9fbdfc
  48da8a:	56                   	push   esi
  48da8b:	ff 15 d8 d3 92 00    	call   DWORD PTR ds:0x92d3d8
  48da91:	83 c4 08             	add    esp,0x8
  48da94:	85 c0                	test   eax,eax
  48da96:	74 32                	je     0x48daca
  48da98:	68 04 be 9f 00       	push   0x9fbe04
  48da9d:	56                   	push   esi
  48da9e:	ff 15 d8 d3 92 00    	call   DWORD PTR ds:0x92d3d8
  48daa4:	83 c4 08             	add    esp,0x8
  48daa7:	85 c0                	test   eax,eax
  48daa9:	0f 85 a1 00 00 00    	jne    0x48db50
  48daaf:	8b 57 48             	mov    edx,DWORD PTR [edi+0x48]
  48dab2:	8d 47 40             	lea    eax,[edi+0x40]
  48dab5:	8b 4f 44             	mov    ecx,DWORD PTR [edi+0x44]
  48dab8:	8d 77 3c             	lea    esi,[edi+0x3c]
  48dabb:	50                   	push   eax
  48dabc:	56                   	push   esi
  48dabd:	ff 77 38             	push   DWORD PTR [edi+0x38]
  48dac0:	e8 cb af 06 00       	call   0x4f8a90
  48dac5:	83 c4 0c             	add    esp,0xc
  48dac8:	eb 49                	jmp    0x48db13
  48daca:	8b 57 48             	mov    edx,DWORD PTR [edi+0x48]
  48dacd:	8d 4f 40             	lea    ecx,[edi+0x40]
  48dad0:	51                   	push   ecx
  48dad1:	8d 87 4c 01 00 00    	lea    eax,[edi+0x14c]
  48dad7:	50                   	push   eax
  48dad8:	51                   	push   ecx
  48dad9:	8d 47 4c             	lea    eax,[edi+0x4c]
  48dadc:	50                   	push   eax
  48dadd:	51                   	push   ecx
  48dade:	8b 4f 44             	mov    ecx,DWORD PTR [edi+0x44]
  48dae1:	8d 77 3c             	lea    esi,[edi+0x3c]
  48dae4:	56                   	push   esi
  48dae5:	ff 77 38             	push   DWORD PTR [edi+0x38]
  48dae8:	e8 f3 ac 06 00       	call   0x4f87e0
  48daed:	eb 21                	jmp    0x48db10
  48daef:	8b 57 48             	mov    edx,DWORD PTR [edi+0x48]
  48daf2:	8d 4f 40             	lea    ecx,[edi+0x40]
  48daf5:	51                   	push   ecx
  48daf6:	8d 87 4c 01 00 00    	lea    eax,[edi+0x14c]
  48dafc:	50                   	push   eax
  48dafd:	51                   	push   ecx
  48dafe:	8d 47 4c             	lea    eax,[edi+0x4c]
  48db01:	50                   	push   eax
  48db02:	51                   	push   ecx
  48db03:	8d 77 3c             	lea    esi,[edi+0x3c]
  48db06:	56                   	push   esi
  48db07:	51                   	push   ecx
  48db08:	8b 4f 44             	mov    ecx,DWORD PTR [edi+0x44]
  48db0b:	e8 70 b5 06 00       	call   0x4f9080
  48db10:	83 c4 1c             	add    esp,0x1c
  48db13:	ff 77 44             	push   DWORD PTR [edi+0x44]
  48db16:	88 44 24 17          	mov    BYTE PTR [esp+0x17],al
  48db1a:	ff 15 a0 d4 92 00    	call   DWORD PTR ds:0x92d4a0
  48db20:	83 c4 04             	add    esp,0x4
  48db23:	c7 47 44 00 00 00 00 	mov    DWORD PTR [edi+0x44],0x0
  48db2a:	80 7c 24 13 00       	cmp    BYTE PTR [esp+0x13],0x0
  48db2f:	c7                   	.byte 0xc7
