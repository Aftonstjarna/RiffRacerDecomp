
Game.exe:     file format pei-i386


Disassembly of section .text:

004f9080 <.text+0xf8080>:
  4f9080:	55                   	push   ebp
  4f9081:	8b ec                	mov    ebp,esp
  4f9083:	6a ff                	push   0xffffffff
  4f9085:	68 4f 3c 90 00       	push   0x903c4f
  4f908a:	64 a1 00 00 00 00    	mov    eax,fs:0x0
  4f9090:	50                   	push   eax
  4f9091:	b8 18 10 00 00       	mov    eax,0x1018
  4f9096:	e8 65 07 40 00       	call   0x8f9800
  4f909b:	a1 c0 ab ba 00       	mov    eax,ds:0xbaabc0
  4f90a0:	33 c5                	xor    eax,ebp
  4f90a2:	89 45 f0             	mov    DWORD PTR [ebp-0x10],eax
  4f90a5:	53                   	push   ebx
  4f90a6:	56                   	push   esi
  4f90a7:	57                   	push   edi
  4f90a8:	50                   	push   eax
  4f90a9:	8d 45 f4             	lea    eax,[ebp-0xc]
  4f90ac:	64 a3 00 00 00 00    	mov    fs:0x0,eax
  4f90b2:	8b f2                	mov    esi,edx
  4f90b4:	8b d9                	mov    ebx,ecx
  4f90b6:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
  4f90b9:	89 85 e4 ef ff ff    	mov    DWORD PTR [ebp-0x101c],eax
  4f90bf:	8b 45 10             	mov    eax,DWORD PTR [ebp+0x10]
  4f90c2:	89 85 ec ef ff ff    	mov    DWORD PTR [ebp-0x1014],eax
  4f90c8:	8b 45 14             	mov    eax,DWORD PTR [ebp+0x14]
  4f90cb:	89 85 dc ef ff ff    	mov    DWORD PTR [ebp-0x1024],eax
  4f90d1:	8b 45 1c             	mov    eax,DWORD PTR [ebp+0x1c]
  4f90d4:	68 90 04 00 00       	push   0x490
  4f90d9:	89 85 e0 ef ff ff    	mov    DWORD PTR [ebp-0x1020],eax
  4f90df:	ff 15 b4 d4 92 00    	call   DWORD PTR ds:0x92d4b4
  4f90e5:	83 c4 04             	add    esp,0x4
  4f90e8:	89 85 e8 ef ff ff    	mov    DWORD PTR [ebp-0x1018],eax
  4f90ee:	c7 45 fc 00 00 00 00 	mov    DWORD PTR [ebp-0x4],0x0
  4f90f5:	85 c0                	test   eax,eax
  4f90f7:	74 0b                	je     0x4f9104
  4f90f9:	8b c8                	mov    ecx,eax
  4f90fb:	e8 f0 d1 06 00       	call   0x5662f0
  4f9100:	8b f8                	mov    edi,eax
  4f9102:	eb 02                	jmp    0x4f9106
  4f9104:	33 ff                	xor    edi,edi
  4f9106:	c7 45 fc ff ff ff ff 	mov    DWORD PTR [ebp-0x4],0xffffffff
  4f910d:	8b cf                	mov    ecx,edi
  4f910f:	89 b7 34 04 00 00    	mov    DWORD PTR [edi+0x434],esi
  4f9115:	89 9f 30 04 00 00    	mov    DWORD PTR [edi+0x430],ebx
  4f911b:	c7 87 38 04 00 00 00 	mov    DWORD PTR [edi+0x438],0x0
  4f9122:	00 00 00 
  4f9125:	c6 87 89 04 00 00 00 	mov    BYTE PTR [edi+0x489],0x0
  4f912c:	e8 7f d7 06 00       	call   0x5668b0
  4f9131:	84 c0                	test   al,al
  4f9133:	0f 84 23 01 00 00    	je     0x4f925c
  4f9139:	8b 07                	mov    eax,DWORD PTR [edi]
  4f913b:	8b cf                	mov    ecx,edi
  4f913d:	8b 40 1c             	mov    eax,DWORD PTR [eax+0x1c]
  4f9140:	ff d0                	call   eax
  4f9142:	0b c2                	or     eax,edx
  4f9144:	0f 84 12 01 00 00    	je     0x4f925c
  4f914a:	8b 07                	mov    eax,DWORD PTR [edi]
  4f914c:	8b cf                	mov    ecx,edi
  4f914e:	8b 40 1c             	mov    eax,DWORD PTR [eax+0x1c]
  4f9151:	ff d0                	call   eax
  4f9153:	8b b5 ec ef ff ff    	mov    esi,DWORD PTR [ebp-0x1014]
  4f9159:	8b cf                	mov    ecx,edi
  4f915b:	89 06                	mov    DWORD PTR [esi],eax
  4f915d:	8b 07                	mov    eax,DWORD PTR [edi]
  4f915f:	8b 40 1c             	mov    eax,DWORD PTR [eax+0x1c]
  4f9162:	ff d0                	call   eax
  4f9164:	33 c9                	xor    ecx,ecx
  4f9166:	ba 04 00 00 00       	mov    edx,0x4
  4f916b:	f7 e2                	mul    edx
  4f916d:	0f 90 c1             	seto   cl
  4f9170:	f7 d9                	neg    ecx
  4f9172:	0b c8                	or     ecx,eax
  4f9174:	51                   	push   ecx
  4f9175:	e8 4e f6 3f 00       	call   0x8f87c8
  4f917a:	8b 8d e4 ef ff ff    	mov    ecx,DWORD PTR [ebp-0x101c]
  4f9180:	83 c4 04             	add    esp,0x4
  4f9183:	33 db                	xor    ebx,ebx
  4f9185:	89 01                	mov    DWORD PTR [ecx],eax
  4f9187:	33 c0                	xor    eax,eax
  4f9189:	8b 0e                	mov    ecx,DWORD PTR [esi]
  4f918b:	89 8d e8 ef ff ff    	mov    DWORD PTR [ebp-0x1018],ecx
  4f9191:	89 85 ec ef ff ff    	mov    DWORD PTR [ebp-0x1014],eax
  4f9197:	85 c9                	test   ecx,ecx
  4f9199:	0f 8e 7b 00 00 00    	jle    0x4f921a
  4f919f:	eb 06                	jmp    0x4f91a7
  4f91a1:	8b 85 ec ef ff ff    	mov    eax,DWORD PTR [ebp-0x1014]
  4f91a7:	83 f8 10             	cmp    eax,0x10
  4f91aa:	7d 6e                	jge    0x4f921a
  4f91ac:	8b 07                	mov    eax,DWORD PTR [edi]
  4f91ae:	8d 8d f0 ef ff ff    	lea    ecx,[ebp-0x1010]
  4f91b4:	6a 00                	push   0x0
  4f91b6:	68 00 10 00 00       	push   0x1000
  4f91bb:	51                   	push   ecx
  4f91bc:	8b cf                	mov    ecx,edi
  4f91be:	ff 50 20             	call   DWORD PTR [eax+0x20]
  4f91c1:	8b f0                	mov    esi,eax
  4f91c3:	85 f6                	test   esi,esi
  4f91c5:	75 06                	jne    0x4f91cd
  4f91c7:	ff 85 ec ef ff ff    	inc    DWORD PTR [ebp-0x1014]
  4f91cd:	d1 ee                	shr    esi,1
  4f91cf:	33 c9                	xor    ecx,ecx
  4f91d1:	85 f6                	test   esi,esi
  4f91d3:	7e 3d                	jle    0x4f9212
  4f91d5:	8b 85 e4 ef ff ff    	mov    eax,DWORD PTR [ebp-0x101c]
  4f91db:	f3 0f 10 0d 28 64 a0 	movss  xmm1,DWORD PTR ds:0xa06428
  4f91e2:	00 
  4f91e3:	8b 00                	mov    eax,DWORD PTR [eax]
  4f91e5:	8d 14 98             	lea    edx,[eax+ebx*4]
  4f91e8:	43                   	inc    ebx
  4f91e9:	8d 46 ff             	lea    eax,[esi-0x1]
  4f91ec:	d1 e8                	shr    eax,1
  4f91ee:	03 d8                	add    ebx,eax
  4f91f0:	0f bf 84 4d f0 ef ff 	movsx  eax,WORD PTR [ebp+ecx*2-0x1010]
  4f91f7:	ff 
  4f91f8:	8d 52 04             	lea    edx,[edx+0x4]
  4f91fb:	83 c1 02             	add    ecx,0x2
  4f91fe:	66 0f 6e c0          	movd   xmm0,eax
  4f9202:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4f9205:	f3 0f 59 c1          	mulss  xmm0,xmm1
  4f9209:	f3 0f 11 42 fc       	movss  DWORD PTR [edx-0x4],xmm0
  4f920e:	3b ce                	cmp    ecx,esi
  4f9210:	7c de                	jl     0x4f91f0
  4f9212:	3b 9d e8 ef ff ff    	cmp    ebx,DWORD PTR [ebp-0x1018]
  4f9218:	7c 87                	jl     0x4f91a1
  4f921a:	8b 35 e4 d3 92 00    	mov    esi,DWORD PTR ds:0x92d3e4
  4f9220:	8d 87 28 02 00 00    	lea    eax,[edi+0x228]
  4f9226:	68 00 01 00 00       	push   0x100
  4f922b:	50                   	push   eax
  4f922c:	ff b5 dc ef ff ff    	push   DWORD PTR [ebp-0x1024]
  4f9232:	ff d6                	call   esi
  4f9234:	68 00 01 00 00       	push   0x100
  4f9239:	8d 47 28             	lea    eax,[edi+0x28]
  4f923c:	50                   	push   eax
  4f923d:	ff b5 e0 ef ff ff    	push   DWORD PTR [ebp-0x1020]
  4f9243:	ff d6                	call   esi
  4f9245:	8b 07                	mov    eax,DWORD PTR [edi]
  4f9247:	83 c4 18             	add    esp,0x18
  4f924a:	8b cf                	mov    ecx,edi
  4f924c:	6a 01                	push   0x1
  4f924e:	ff 10                	call   DWORD PTR [eax]
  4f9250:	83 bd ec ef ff ff 10 	cmp    DWORD PTR [ebp-0x1014],0x10
  4f9257:	0f 95 c0             	setne  al
  4f925a:	eb 0a                	jmp    0x4f9266
  4f925c:	8b 07                	mov    eax,DWORD PTR [edi]
  4f925e:	8b cf                	mov    ecx,edi
  4f9260:	6a 01                	push   0x1
  4f9262:	ff 10                	call   DWORD PTR [eax]
  4f9264:	32 c0                	xor    al,al
  4f9266:	8b 4d f4             	mov    ecx,DWORD PTR [ebp-0xc]
  4f9269:	64 89 0d 00 00 00 00 	mov    DWORD PTR fs:0x0,ecx
  4f9270:	59                   	pop    ecx
  4f9271:	5f                   	pop    edi
  4f9272:	5e                   	pop    esi
  4f9273:	5b                   	pop    ebx
  4f9274:	8b 4d f0             	mov    ecx,DWORD PTR [ebp-0x10]
  4f9277:	33 cd                	xor    ecx,ebp
  4f9279:	e8 da f6 3f 00       	call   0x8f8958
  4f927e:	8b e5                	mov    esp,ebp
  4f9280:	5d                   	pop    ebp
  4f9281:	c3                   	ret
