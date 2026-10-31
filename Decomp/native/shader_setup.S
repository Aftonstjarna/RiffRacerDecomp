# Reviewed against original instructions and Ghidra; see SHADERS.md. Exact bytes checked by native-check.
# Original VA range 0x52db30..0x52f4bb
.intel_syntax noprefix
.code32
.text
.global original_shader_setup
original_shader_setup:
.L52db30:
 push   ebx
.L52db31:
 push   esi
.L52db32:
 push   edi
.L52db33:
 {load} mov    esi,ecx
.L52db35:
 {load} xor    bl,bl
.L52db37:
 push   0x9a67c0
.L52db3c:
 push   0x9e97c0
.L52db41:
 lea    ecx,[esi+0x8]
.L52db44:
 call target_52d840
.L52db49:
 test   al,al
.L52db4b:
 movzx  ebx,bl
.L52db4e:
 push   0x9baea8
.L52db53:
 mov    edi,0x1
.L52db58:
 lea    ecx,[esi+0x18]
.L52db5b:
 push   0x9e97c0
.L52db60:
 cmove  ebx,edi
.L52db63:
 call target_52d840
.L52db68:
 test   al,al
.L52db6a:
 movzx  ebx,bl
.L52db6d:
 push   0x9a0910
.L52db72:
 push   0x9e97c0
.L52db77:
 lea    ecx,[esi+0x28]
.L52db7a:
 cmove  ebx,edi
.L52db7d:
 call target_52d840
.L52db82:
 test   al,al
.L52db84:
 movzx  ebx,bl
.L52db87:
 push   0x9ce768
.L52db8c:
 push   0x9e97c0
.L52db91:
 lea    ecx,[esi+0x38]
.L52db94:
 cmove  ebx,edi
.L52db97:
 call target_52d840
.L52db9c:
 test   al,al
.L52db9e:
 movzx  ebx,bl
.L52dba1:
 push   0x99f810
.L52dba6:
 push   0x9e97c0
.L52dbab:
 lea    ecx,[esi+0x48]
.L52dbae:
 cmove  ebx,edi
.L52dbb1:
 call target_52d840
.L52dbb6:
 test   al,al
.L52dbb8:
 movzx  ebx,bl
.L52dbbb:
 push   0x9c2c08
.L52dbc0:
 push   0x9e97c0
.L52dbc5:
 lea    ecx,[esi+0x58]
.L52dbc8:
 cmove  ebx,edi
.L52dbcb:
 call target_52d840
.L52dbd0:
 test   al,al
.L52dbd2:
 movzx  ebx,bl
.L52dbd5:
 push   0x9cc6b0
.L52dbda:
 push   0x9e97c0
.L52dbdf:
 lea    ecx,[esi+0x68]
.L52dbe2:
 cmove  ebx,edi
.L52dbe5:
 call target_52d840
.L52dbea:
 test   al,al
.L52dbec:
 movzx  ebx,bl
.L52dbef:
 push   0x9e3600
.L52dbf4:
 push   0x9e4280
.L52dbf9:
 lea    ecx,[esi+0x78]
.L52dbfc:
 cmove  ebx,edi
.L52dbff:
 call target_52d840
.L52dc04:
 test   al,al
.L52dc06:
 movzx  ebx,bl
.L52dc09:
 push   0x9e80a0
.L52dc0e:
 push   0x9b1258
.L52dc13:
 lea    ecx,[esi+0x88]
.L52dc19:
 cmove  ebx,edi
.L52dc1c:
 call target_52d840
.L52dc21:
 test   al,al
.L52dc23:
 movzx  ebx,bl
.L52dc26:
 push   0x9eb160
.L52dc2b:
 push   0x9cb928
.L52dc30:
 lea    ecx,[esi+0x98]
.L52dc36:
 cmove  ebx,edi
.L52dc39:
 call target_52d840
.L52dc3e:
 test   al,al
.L52dc40:
 movzx  ebx,bl
.L52dc43:
 push   0x9e1bc8
.L52dc48:
 push   0x9dc570
.L52dc4d:
 lea    ecx,[esi+0xca8]
.L52dc53:
 cmove  ebx,edi
.L52dc56:
 call target_52d840
.L52dc5b:
 movzx  ebx,bl
.L52dc5e:
 test   al,al
.L52dc60:
 lea    ecx,[esi+0xcb8]
.L52dc66:
 push   0x99d488
.L52dc6b:
 push   0x9a42b0
.L52dc70:
 cmove  ebx,edi
.L52dc73:
 call target_52d840
.L52dc78:
 test   al,al
.L52dc7a:
 movzx  ebx,bl
.L52dc7d:
 push   0x9bbe98
.L52dc82:
 push   0x9b2f70
.L52dc87:
 lea    ecx,[esi+0xa8]
.L52dc8d:
 cmove  ebx,edi
.L52dc90:
 call target_52d840
.L52dc95:
 test   al,al
.L52dc97:
 movzx  ebx,bl
.L52dc9a:
 push   0x9afd10
.L52dc9f:
 push   0x9af528
.L52dca4:
 lea    ecx,[esi+0xb8]
.L52dcaa:
 cmove  ebx,edi
.L52dcad:
 call target_52d840
.L52dcb2:
 test   al,al
.L52dcb4:
 movzx  ebx,bl
.L52dcb7:
 push   0x99f728
.L52dcbc:
 push   0x9b3fd8
.L52dcc1:
 lea    ecx,[esi+0xc8]
.L52dcc7:
 cmove  ebx,edi
.L52dcca:
 call target_52d840
.L52dccf:
 test   al,al
.L52dcd1:
 movzx  ebx,bl
.L52dcd4:
 push   0x9b2b28
.L52dcd9:
 push   0x9c86b0
.L52dcde:
 lea    ecx,[esi+0xd8]
.L52dce4:
 cmove  ebx,edi
.L52dce7:
 call target_52d840
.L52dcec:
 test   al,al
.L52dcee:
 movzx  ebx,bl
.L52dcf1:
 push   0x99f4f0
.L52dcf6:
 push   0x9a64d8
.L52dcfb:
 lea    ecx,[esi+0xe8]
.L52dd01:
 cmove  ebx,edi
.L52dd04:
 call target_52d840
.L52dd09:
 test   al,al
.L52dd0b:
 movzx  ebx,bl
.L52dd0e:
 push   0x9e3430
.L52dd13:
 push   0x9b3cf0
.L52dd18:
 lea    ecx,[esi+0xf8]
.L52dd1e:
 cmove  ebx,edi
.L52dd21:
 call target_52d840
.L52dd26:
 test   al,al
.L52dd28:
 movzx  ebx,bl
.L52dd2b:
 push   0x9dc1f8
.L52dd30:
 push   0x9a3420
.L52dd35:
 lea    ecx,[esi+0x108]
.L52dd3b:
 cmove  ebx,edi
.L52dd3e:
 call target_52d840
.L52dd43:
 test   al,al
.L52dd45:
 movzx  ebx,bl
.L52dd48:
 push   0x9dfa38
.L52dd4d:
 push   0x9cdf08
.L52dd52:
 lea    ecx,[esi+0x118]
.L52dd58:
 cmove  ebx,edi
.L52dd5b:
 call target_52d840
.L52dd60:
 test   al,al
.L52dd62:
 movzx  ebx,bl
.L52dd65:
 push   0x9ee018
.L52dd6a:
 push   0x9a3fa0
.L52dd6f:
 lea    ecx,[esi+0x128]
.L52dd75:
 cmove  ebx,edi
.L52dd78:
 call target_52d840
.L52dd7d:
 test   al,al
.L52dd7f:
 movzx  ebx,bl
.L52dd82:
 push   0x9a2d80
.L52dd87:
 push   0x9e0fa8
.L52dd8c:
 lea    ecx,[esi+0x138]
.L52dd92:
 cmove  ebx,edi
.L52dd95:
 call target_52d840
.L52dd9a:
 test   al,al
.L52dd9c:
 movzx  ebx,bl
.L52dd9f:
 push   0x9ae1b0
.L52dda4:
 cmove  ebx,edi
.L52dda7:
 push   0x9cadd8
.L52ddac:
 lea    ecx,[esi+0x148]
.L52ddb2:
 call target_52d840
.L52ddb7:
 test   al,al
.L52ddb9:
 movzx  ebx,bl
.L52ddbc:
 push   0x9c1c18
.L52ddc1:
 push   0x9ac898
.L52ddc6:
 lea    ecx,[esi+0x168]
.L52ddcc:
 cmove  ebx,edi
.L52ddcf:
 call target_52d840
.L52ddd4:
 test   al,al
.L52ddd6:
 movzx  ebx,bl
.L52ddd9:
 push   0x9a0d70
.L52ddde:
 push   0x9db4d8
.L52dde3:
 lea    ecx,[esi+0x178]
.L52dde9:
 cmove  ebx,edi
.L52ddec:
 call target_52d840
.L52ddf1:
 test   al,al
.L52ddf3:
 movzx  ebx,bl
.L52ddf6:
 push   0x9a8ac0
.L52ddfb:
 push   0x9b44b0
.L52de00:
 lea    ecx,[esi+0x188]
.L52de06:
 cmove  ebx,edi
.L52de09:
 call target_52d840
.L52de0e:
 test   al,al
.L52de10:
 movzx  ebx,bl
.L52de13:
 push   0x9aebb0
.L52de18:
 push   0x9bcb58
.L52de1d:
 lea    ecx,[esi+0x158]
.L52de23:
 cmove  ebx,edi
.L52de26:
 call target_52d840
.L52de2b:
 test   al,al
.L52de2d:
 movzx  ebx,bl
.L52de30:
 push   0x9e2be0
.L52de35:
 push   0x9e0e48
.L52de3a:
 lea    ecx,[esi+0x198]
.L52de40:
 cmove  ebx,edi
.L52de43:
 call target_52d840
.L52de48:
 test   al,al
.L52de4a:
 movzx  ebx,bl
.L52de4d:
 push   0x9bb2f8
.L52de52:
 push   0x9e0e48
.L52de57:
 lea    ecx,[esi+0x1a8]
.L52de5d:
 cmove  ebx,edi
.L52de60:
 call target_52d840
.L52de65:
 test   al,al
.L52de67:
 movzx  ebx,bl
.L52de6a:
 push   0x9c7118
.L52de6f:
 push   0x9b39e0
.L52de74:
 lea    ecx,[esi+0x1b8]
.L52de7a:
 cmove  ebx,edi
.L52de7d:
 call target_52d840
.L52de82:
 test   al,al
.L52de84:
 movzx  ebx,bl
.L52de87:
 push   0x9d0190
.L52de8c:
 push   0x9a8f30
.L52de91:
 lea    ecx,[esi+0x1c8]
.L52de97:
 cmove  ebx,edi
.L52de9a:
 call target_52d840
.L52de9f:
 test   al,al
.L52dea1:
 movzx  ebx,bl
.L52dea4:
 push   0x9b1e28
.L52dea9:
 push   0x9ab2c8
.L52deae:
 lea    ecx,[esi+0x1d8]
.L52deb4:
 cmove  ebx,edi
.L52deb7:
 call target_52d840
.L52debc:
 test   al,al
.L52debe:
 movzx  ebx,bl
.L52dec1:
 push   0x9bc5b8
.L52dec6:
 push   0x9cd390
.L52decb:
 lea    ecx,[esi+0x1e8]
.L52ded1:
 cmove  ebx,edi
.L52ded4:
 call target_52d840
.L52ded9:
 test   al,al
.L52dedb:
 movzx  ebx,bl
.L52dede:
 push   0x9dd288
.L52dee3:
 push   0x9a7e58
.L52dee8:
 lea    ecx,[esi+0x1f8]
.L52deee:
 cmove  ebx,edi
.L52def1:
 call target_52d840
.L52def6:
 movzx  ebx,bl
.L52def9:
 test   al,al
.L52defb:
 push   0x9e16a8
.L52df00:
 push   0x9b1ce8
.L52df05:
 lea    ecx,[esi+0x208]
.L52df0b:
 cmove  ebx,edi
.L52df0e:
 call target_52d840
.L52df13:
 test   al,al
.L52df15:
 movzx  ebx,bl
.L52df18:
 push   0x9d09a8
.L52df1d:
 push   0x9d3630
.L52df22:
 lea    ecx,[esi+0x218]
.L52df28:
 cmove  ebx,edi
.L52df2b:
 call target_52d840
.L52df30:
 test   al,al
.L52df32:
 movzx  ebx,bl
.L52df35:
 push   0x9b63c0
.L52df3a:
 push   0x9cec18
.L52df3f:
 lea    ecx,[esi+0x228]
.L52df45:
 cmove  ebx,edi
.L52df48:
 call target_52d840
.L52df4d:
 test   al,al
.L52df4f:
 movzx  ebx,bl
.L52df52:
 push   0x9da510
.L52df57:
 push   0x9a5340
.L52df5c:
 lea    ecx,[esi+0x238]
.L52df62:
 cmove  ebx,edi
.L52df65:
 call target_52d840
.L52df6a:
 test   al,al
.L52df6c:
 movzx  ebx,bl
.L52df6f:
 push   0x9a3dc8
.L52df74:
 push   0x9ad3f0
.L52df79:
 lea    ecx,[esi+0x248]
.L52df7f:
 cmove  ebx,edi
.L52df82:
 call target_52d840
.L52df87:
 test   al,al
.L52df89:
 movzx  ebx,bl
.L52df8c:
 push   0x9a7018
.L52df91:
 push   0x9e70d8
.L52df96:
 lea    ecx,[esi+0x258]
.L52df9c:
 cmove  ebx,edi
.L52df9f:
 call target_52d840
.L52dfa4:
 test   al,al
.L52dfa6:
 movzx  ebx,bl
.L52dfa9:
 push   0x9da3a8
.L52dfae:
 push   0x9d7648
.L52dfb3:
 lea    ecx,[esi+0x268]
.L52dfb9:
 cmove  ebx,edi
.L52dfbc:
 call target_52d840
.L52dfc1:
 test   al,al
.L52dfc3:
 movzx  ebx,bl
.L52dfc6:
 push   0x9ed220
.L52dfcb:
 push   0x9b6960
.L52dfd0:
 lea    ecx,[esi+0x278]
.L52dfd6:
 cmove  ebx,edi
.L52dfd9:
 call target_52d840
.L52dfde:
 test   al,al
.L52dfe0:
 movzx  ebx,bl
.L52dfe3:
 push   0x9a68a0
.L52dfe8:
 push   0x9b6960
.L52dfed:
 lea    ecx,[esi+0x288]
.L52dff3:
 cmove  ebx,edi
.L52dff6:
 call target_52d840
.L52dffb:
 test   al,al
.L52dffd:
 movzx  ebx,bl
.L52e000:
 push   0x9ba570
.L52e005:
 push   0x9b6960
.L52e00a:
 lea    ecx,[esi+0x298]
.L52e010:
 cmove  ebx,edi
.L52e013:
 call target_52d840
.L52e018:
 test   al,al
.L52e01a:
 movzx  ebx,bl
.L52e01d:
 push   0x9d8110
.L52e022:
 push   0x9c3820
.L52e027:
 lea    ecx,[esi+0x2a8]
.L52e02d:
 cmove  ebx,edi
.L52e030:
 call target_52d840
.L52e035:
 test   al,al
.L52e037:
 movzx  ebx,bl
.L52e03a:
 push   0x9a9f40
.L52e03f:
 cmove  ebx,edi
.L52e042:
 lea    ecx,[esi+0x2b8]
.L52e048:
 push   0x9d3b98
.L52e04d:
 call target_52d840
.L52e052:
 test   al,al
.L52e054:
 movzx  ebx,bl
.L52e057:
 push   0x9afe68
.L52e05c:
 push   0x9ae9f8
.L52e061:
 lea    ecx,[esi+0x2c8]
.L52e067:
 cmove  ebx,edi
.L52e06a:
 call target_52d840
.L52e06f:
 test   al,al
.L52e071:
 movzx  ebx,bl
.L52e074:
 push   0x9b5fc0
.L52e079:
 push   0x9e5488
.L52e07e:
 lea    ecx,[esi+0x2d8]
.L52e084:
 cmove  ebx,edi
.L52e087:
 call target_52d840
.L52e08c:
 test   al,al
.L52e08e:
 movzx  ebx,bl
.L52e091:
 push   0x9b5028
.L52e096:
 push   0x9e5d10
.L52e09b:
 lea    ecx,[esi+0x348]
.L52e0a1:
 cmove  ebx,edi
.L52e0a4:
 call target_52d840
.L52e0a9:
 test   al,al
.L52e0ab:
 movzx  ebx,bl
.L52e0ae:
 push   0x99d580
.L52e0b3:
 push   0x9e5d10
.L52e0b8:
 lea    ecx,[esi+0x358]
.L52e0be:
 cmove  ebx,edi
.L52e0c1:
 call target_52d840
.L52e0c6:
 test   al,al
.L52e0c8:
 movzx  ebx,bl
.L52e0cb:
 push   0x9ea358
.L52e0d0:
 push   0x9de460
.L52e0d5:
 lea    ecx,[esi+0x2e8]
.L52e0db:
 cmove  ebx,edi
.L52e0de:
 call target_52d840
.L52e0e3:
 test   al,al
.L52e0e5:
 movzx  ebx,bl
.L52e0e8:
 push   0x9dd048
.L52e0ed:
 push   0x9e8ca8
.L52e0f2:
 lea    ecx,[esi+0x2f8]
.L52e0f8:
 cmove  ebx,edi
.L52e0fb:
 call target_52d840
.L52e100:
 test   al,al
.L52e102:
 movzx  ebx,bl
.L52e105:
 push   0x9da6d8
.L52e10a:
 push   0x9df268
.L52e10f:
 lea    ecx,[esi+0x308]
.L52e115:
 cmove  ebx,edi
.L52e118:
 call target_52d840
.L52e11d:
 test   al,al
.L52e11f:
 movzx  ebx,bl
.L52e122:
 push   0x9a0ee8
.L52e127:
 push   0x9e8e28
.L52e12c:
 lea    ecx,[esi+0x318]
.L52e132:
 cmove  ebx,edi
.L52e135:
 call target_52d840
.L52e13a:
 test   al,al
.L52e13c:
 movzx  ebx,bl
.L52e13f:
 push   0x9acff0
.L52e144:
 push   0x9df268
.L52e149:
 lea    ecx,[esi+0x328]
.L52e14f:
 cmove  ebx,edi
.L52e152:
 call target_52d840
.L52e157:
 test   al,al
.L52e159:
 movzx  ebx,bl
.L52e15c:
 push   0x9b34a0
.L52e161:
 push   0x9e8e28
.L52e166:
 lea    ecx,[esi+0x338]
.L52e16c:
 cmove  ebx,edi
.L52e16f:
 call target_52d840
.L52e174:
 test   al,al
.L52e176:
 movzx  ebx,bl
.L52e179:
 push   0x9d0df0
.L52e17e:
 push   0x9e5b50
.L52e183:
 lea    ecx,[esi+0x368]
.L52e189:
 cmove  ebx,edi
.L52e18c:
 call target_52d840
.L52e191:
 test   al,al
.L52e193:
 movzx  ebx,bl
.L52e196:
 cmove  ebx,edi
.L52e199:
 push   0x9d8c60
.L52e19e:
 push   0x9a2e40
.L52e1a3:
 lea    ecx,[esi+0x378]
.L52e1a9:
 call target_52d840
.L52e1ae:
 test   al,al
.L52e1b0:
 movzx  ebx,bl
.L52e1b3:
 push   0x9ca3b8
.L52e1b8:
 push   0x9d9e20
.L52e1bd:
 lea    ecx,[esi+0x388]
.L52e1c3:
 cmove  ebx,edi
.L52e1c6:
 call target_52d840
.L52e1cb:
 test   al,al
.L52e1cd:
 movzx  ebx,bl
.L52e1d0:
 push   0x9cbe00
.L52e1d5:
 push   0x9c2d00
.L52e1da:
 lea    ecx,[esi+0x4d8]
.L52e1e0:
 cmove  ebx,edi
.L52e1e3:
 call target_52d840
.L52e1e8:
 test   al,al
.L52e1ea:
 movzx  ebx,bl
.L52e1ed:
 push   0x9d2858
.L52e1f2:
 push   0x9cef28
.L52e1f7:
 lea    ecx,[esi+0x4e8]
.L52e1fd:
 cmove  ebx,edi
.L52e200:
 call target_52d840
.L52e205:
 test   al,al
.L52e207:
 movzx  ebx,bl
.L52e20a:
 push   0x9c72a0
.L52e20f:
 push   0x9c2d00
.L52e214:
 lea    ecx,[esi+0x4f8]
.L52e21a:
 cmove  ebx,edi
.L52e21d:
 call target_52d840
.L52e222:
 test   al,al
.L52e224:
 movzx  ebx,bl
.L52e227:
 push   0x9e3088
.L52e22c:
 push   0x9a71e8
.L52e231:
 lea    ecx,[esi+0x508]
.L52e237:
 cmove  ebx,edi
.L52e23a:
 call target_52d840
.L52e23f:
 test   al,al
.L52e241:
 movzx  ebx,bl
.L52e244:
 push   0x9cd4d0
.L52e249:
 push   0x9eaf00
.L52e24e:
 lea    ecx,[esi+0x7e8]
.L52e254:
 cmove  ebx,edi
.L52e257:
 call target_52d840
.L52e25c:
 test   al,al
.L52e25e:
 movzx  ebx,bl
.L52e261:
 push   0x9a5940
.L52e266:
 push   0x9a5b08
.L52e26b:
 lea    ecx,[esi+0x7f8]
.L52e271:
 cmove  ebx,edi
.L52e274:
 call target_52d840
.L52e279:
 test   al,al
.L52e27b:
 movzx  ebx,bl
.L52e27e:
 push   0x9cd620
.L52e283:
 push   0x9b4b90
.L52e288:
 lea    ecx,[esi+0x398]
.L52e28e:
 cmove  ebx,edi
.L52e291:
 call target_52d840
.L52e296:
 test   al,al
.L52e298:
 movzx  ebx,bl
.L52e29b:
 push   0x9cf1b0
.L52e2a0:
 push   0x9a0128
.L52e2a5:
 lea    ecx,[esi+0x3a8]
.L52e2ab:
 cmove  ebx,edi
.L52e2ae:
 call target_52d840
.L52e2b3:
 test   al,al
.L52e2b5:
 movzx  ebx,bl
.L52e2b8:
 push   0x9eba78
.L52e2bd:
 push   0x9daaf8
.L52e2c2:
 lea    ecx,[esi+0x3b8]
.L52e2c8:
 cmove  ebx,edi
.L52e2cb:
 call target_52d840
.L52e2d0:
 test   al,al
.L52e2d2:
 movzx  ebx,bl
.L52e2d5:
 push   0x9dc0d0
.L52e2da:
 push   0x9c19b8
.L52e2df:
 lea    ecx,[esi+0x3c8]
.L52e2e5:
 cmove  ebx,edi
.L52e2e8:
 call target_52d840
.L52e2ed:
 test   al,al
.L52e2ef:
 movzx  ebx,bl
.L52e2f2:
 push   0x9d3280
.L52e2f7:
 push   0x9adff0
.L52e2fc:
 lea    ecx,[esi+0xd78]
.L52e302:
 cmove  ebx,edi
.L52e305:
 call target_52d840
.L52e30a:
 test   al,al
.L52e30c:
 movzx  ebx,bl
.L52e30f:
 push   0x9a21f8
.L52e314:
 push   0x9c0900
.L52e319:
 lea    ecx,[esi+0xd88]
.L52e31f:
 cmove  ebx,edi
.L52e322:
 call target_52d840
.L52e327:
 test   al,al
.L52e329:
 movzx  ebx,bl
.L52e32c:
 push   0x9e55a0
.L52e331:
 push   0x9c13e0
.L52e336:
 lea    ecx,[esi+0xd98]
.L52e33c:
 cmove  ebx,edi
.L52e33f:
 call target_52d840
.L52e344:
 test   al,al
.L52e346:
 movzx  ebx,bl
.L52e349:
 push   0x9b1f68
.L52e34e:
 push   0x9c2188
.L52e353:
 lea    ecx,[esi+0xda8]
.L52e359:
 cmove  ebx,edi
.L52e35c:
 call target_52d840
.L52e361:
 test   al,al
.L52e363:
 movzx  ebx,bl
.L52e366:
 push   0x9a3110
.L52e36b:
 push   0x9eda78
.L52e370:
 lea    ecx,[esi+0xdb8]
.L52e376:
 cmove  ebx,edi
.L52e379:
 call target_52d840
.L52e37e:
 test   al,al
.L52e380:
 movzx  ebx,bl
.L52e383:
 push   0x9c3938
.L52e388:
 push   0x9a54a0
.L52e38d:
 lea    ecx,[esi+0xdc8]
.L52e393:
 cmove  ebx,edi
.L52e396:
 call target_52d840
.L52e39b:
 test   al,al
.L52e39d:
 movzx  ebx,bl
.L52e3a0:
 push   0x9a7fe8
.L52e3a5:
 push   0x9c3cd0
.L52e3aa:
 lea    ecx,[esi+0xdd8]
.L52e3b0:
 cmove  ebx,edi
.L52e3b3:
 call target_52d840
.L52e3b8:
 test   al,al
.L52e3ba:
 movzx  ebx,bl
.L52e3bd:
 push   0x9a07e8
.L52e3c2:
 push   0x9abe78
.L52e3c7:
 lea    ecx,[esi+0xde8]
.L52e3cd:
 cmove  ebx,edi
.L52e3d0:
 call target_52d840
.L52e3d5:
 test   al,al
.L52e3d7:
 movzx  ebx,bl
.L52e3da:
 push   0x9c36b0
.L52e3df:
 push   0x9bc9b8
.L52e3e4:
 lea    ecx,[esi+0xdf8]
.L52e3ea:
 cmove  ebx,edi
.L52e3ed:
 call target_52d840
.L52e3f2:
 test   al,al
.L52e3f4:
 movzx  ebx,bl
.L52e3f7:
 push   0x9c51b8
.L52e3fc:
 push   0x9ab408
.L52e401:
 lea    ecx,[esi+0xe08]
.L52e407:
 cmove  ebx,edi
.L52e40a:
 call target_52d840
.L52e40f:
 test   al,al
.L52e411:
 movzx  ebx,bl
.L52e414:
 push   0x9e46e0
.L52e419:
 push   0x9eab98
.L52e41e:
 lea    ecx,[esi+0x3d8]
.L52e424:
 cmove  ebx,edi
.L52e427:
 call target_52d840
.L52e42c:
 test   al,al
.L52e42e:
 movzx  ebx,bl
.L52e431:
 push   0x9ec5f8
.L52e436:
 cmove  ebx,edi
.L52e439:
 push   0x9e51e0
.L52e43e:
 lea    ecx,[esi+0x3e8]
.L52e444:
 call target_52d840
.L52e449:
 test   al,al
.L52e44b:
 movzx  ebx,bl
.L52e44e:
 push   0x9c4d20
.L52e453:
 push   0x9c55a0
.L52e458:
 lea    ecx,[esi+0x3f8]
.L52e45e:
 cmove  ebx,edi
.L52e461:
 call target_52d840
.L52e466:
 test   al,al
.L52e468:
 movzx  ebx,bl
.L52e46b:
 push   0x9c4af0
.L52e470:
 push   0x9defe0
.L52e475:
 lea    ecx,[esi+0x408]
.L52e47b:
 cmove  ebx,edi
.L52e47e:
 call target_52d840
.L52e483:
 test   al,al
.L52e485:
 movzx  ebx,bl
.L52e488:
 push   0x9ac9d8
.L52e48d:
 push   0x9c19b8
.L52e492:
 lea    ecx,[esi+0x418]
.L52e498:
 cmove  ebx,edi
.L52e49b:
 call target_52d840
.L52e4a0:
 test   al,al
.L52e4a2:
 movzx  ebx,bl
.L52e4a5:
 push   0x9cb448
.L52e4aa:
 push   0x9e9f58
.L52e4af:
 lea    ecx,[esi+0x428]
.L52e4b5:
 cmove  ebx,edi
.L52e4b8:
 call target_52d840
.L52e4bd:
 test   al,al
.L52e4bf:
 movzx  ebx,bl
.L52e4c2:
 push   0x9dc0d0
.L52e4c7:
 push   0x9cccb0
.L52e4cc:
 lea    ecx,[esi+0x438]
.L52e4d2:
 cmove  ebx,edi
.L52e4d5:
 call target_52d840
.L52e4da:
 test   al,al
.L52e4dc:
 movzx  ebx,bl
.L52e4df:
 push   0x9ac9d8
.L52e4e4:
 push   0x9cccb0
.L52e4e9:
 lea    ecx,[esi+0x448]
.L52e4ef:
 cmove  ebx,edi
.L52e4f2:
 call target_52d840
.L52e4f7:
 test   al,al
.L52e4f9:
 movzx  ebx,bl
.L52e4fc:
 push   0x9e6f68
.L52e501:
 push   0x9c19b8
.L52e506:
 lea    ecx,[esi+0x458]
.L52e50c:
 cmove  ebx,edi
.L52e50f:
 call target_52d840
.L52e514:
 test   al,al
.L52e516:
 movzx  ebx,bl
.L52e519:
 push   0x9e6f68
.L52e51e:
 push   0x9cccb0
.L52e523:
 lea    ecx,[esi+0x468]
.L52e529:
 cmove  ebx,edi
.L52e52c:
 call target_52d840
.L52e531:
 test   al,al
.L52e533:
 movzx  ebx,bl
.L52e536:
 push   0x9c1640
.L52e53b:
 push   0x9c19b8
.L52e540:
 lea    ecx,[esi+0x478]
.L52e546:
 cmove  ebx,edi
.L52e549:
 call target_52d840
.L52e54e:
 test   al,al
.L52e550:
 movzx  ebx,bl
.L52e553:
 push   0x9c1640
.L52e558:
 push   0x9cccb0
.L52e55d:
 lea    ecx,[esi+0x488]
.L52e563:
 cmove  ebx,edi
.L52e566:
 call target_52d840
.L52e56b:
 test   al,al
.L52e56d:
 movzx  ebx,bl
.L52e570:
 push   0x9a2898
.L52e575:
 push   0x99d9f0
.L52e57a:
 lea    ecx,[esi+0x498]
.L52e580:
 cmove  ebx,edi
.L52e583:
 call target_52d840
.L52e588:
 movzx  ebx,bl
.L52e58b:
 test   al,al
.L52e58d:
 lea    ecx,[esi+0x4a8]
.L52e593:
 push   0x9c9f78
.L52e598:
 push   0x9d7968
.L52e59d:
 cmove  ebx,edi
.L52e5a0:
 call target_52d840
.L52e5a5:
 test   al,al
.L52e5a7:
 movzx  ebx,bl
.L52e5aa:
 push   0x9cb1a8
.L52e5af:
 push   0x9d7760
.L52e5b4:
 lea    ecx,[esi+0x4b8]
.L52e5ba:
 cmove  ebx,edi
.L52e5bd:
 call target_52d840
.L52e5c2:
 test   al,al
.L52e5c4:
 movzx  ebx,bl
.L52e5c7:
 push   0x9caf18
.L52e5cc:
 push   0x9ac6b0
.L52e5d1:
 lea    ecx,[esi+0x4c8]
.L52e5d7:
 cmove  ebx,edi
.L52e5da:
 call target_52d840
.L52e5df:
 test   al,al
.L52e5e1:
 movzx  ebx,bl
.L52e5e4:
 push   0x9c0f30
.L52e5e9:
 push   0x9deaf8
.L52e5ee:
 lea    ecx,[esi+0x518]
.L52e5f4:
 cmove  ebx,edi
.L52e5f7:
 call target_52d840
.L52e5fc:
 test   al,al
.L52e5fe:
 movzx  ebx,bl
.L52e601:
 push   0x9b8068
.L52e606:
 push   0x9e6900
.L52e60b:
 lea    ecx,[esi+0x538]
.L52e611:
 cmove  ebx,edi
.L52e614:
 call target_52d840
.L52e619:
 test   al,al
.L52e61b:
 movzx  ebx,bl
.L52e61e:
 push   0x9dcac0
.L52e623:
 push   0x9beb20
.L52e628:
 lea    ecx,[esi+0x528]
.L52e62e:
 cmove  ebx,edi
.L52e631:
 call target_52d840
.L52e636:
 test   al,al
.L52e638:
 movzx  ebx,bl
.L52e63b:
 push   0x9c66a0
.L52e640:
 push   0x9be308
.L52e645:
 lea    ecx,[esi+0x558]
.L52e64b:
 cmove  ebx,edi
.L52e64e:
 call target_52d840
.L52e653:
 test   al,al
.L52e655:
 movzx  ebx,bl
.L52e658:
 push   0x9a7580
.L52e65d:
 push   0x9dd6d8
.L52e662:
 lea    ecx,[esi+0x548]
.L52e668:
 cmove  ebx,edi
.L52e66b:
 call target_52d840
.L52e670:
 test   al,al
.L52e672:
 movzx  ebx,bl
.L52e675:
 push   0x9de6f8
.L52e67a:
 push   0x9d8eb8
.L52e67f:
 lea    ecx,[esi+0x568]
.L52e685:
 cmove  ebx,edi
.L52e688:
 call target_52d840
.L52e68d:
 test   al,al
.L52e68f:
 movzx  ebx,bl
.L52e692:
 push   0x9c0ac0
.L52e697:
 push   0x9d3770
.L52e69c:
 lea    ecx,[esi+0x588]
.L52e6a2:
 cmove  ebx,edi
.L52e6a5:
 call target_52d840
.L52e6aa:
 test   al,al
.L52e6ac:
 movzx  ebx,bl
.L52e6af:
 push   0x9a9500
.L52e6b4:
 push   0x9d5fa0
.L52e6b9:
 lea    ecx,[esi+0x578]
.L52e6bf:
 cmove  ebx,edi
.L52e6c2:
 call target_52d840
.L52e6c7:
 test   al,al
.L52e6c9:
 movzx  ebx,bl
.L52e6cc:
 push   0x9a1468
.L52e6d1:
 cmove  ebx,edi
.L52e6d4:
 push   0x9de018
.L52e6d9:
 lea    ecx,[esi+0x598]
.L52e6df:
 call target_52d840
.L52e6e4:
 test   al,al
.L52e6e6:
 movzx  ebx,bl
.L52e6e9:
 push   0x99ed18
.L52e6ee:
 push   0x9bba70
.L52e6f3:
 lea    ecx,[esi+0x5a8]
.L52e6f9:
 cmove  ebx,edi
.L52e6fc:
 call target_52d840
.L52e701:
 test   al,al
.L52e703:
 movzx  ebx,bl
.L52e706:
 push   0x9ecbf0
.L52e70b:
 push   0x9acb28
.L52e710:
 lea    ecx,[esi+0x5b8]
.L52e716:
 cmove  ebx,edi
.L52e719:
 call target_52d840
.L52e71e:
 test   al,al
.L52e720:
 movzx  ebx,bl
.L52e723:
 push   0x9c7458
.L52e728:
 push   0x9d86c8
.L52e72d:
 lea    ecx,[esi+0x5c8]
.L52e733:
 cmove  ebx,edi
.L52e736:
 call target_52d840
.L52e73b:
 test   al,al
.L52e73d:
 movzx  ebx,bl
.L52e740:
 push   0x9c4578
.L52e745:
 push   0x9bf6a8
.L52e74a:
 lea    ecx,[esi+0x5d8]
.L52e750:
 cmove  ebx,edi
.L52e753:
 call target_52d840
.L52e758:
 test   al,al
.L52e75a:
 movzx  ebx,bl
.L52e75d:
 push   0x9a9a00
.L52e762:
 push   0x9d2b18
.L52e767:
 lea    ecx,[esi+0x5e8]
.L52e76d:
 cmove  ebx,edi
.L52e770:
 call target_52d840
.L52e775:
 test   al,al
.L52e777:
 movzx  ebx,bl
.L52e77a:
 push   0x9d7b28
.L52e77f:
 push   0x9c1e70
.L52e784:
 lea    ecx,[esi+0x5f8]
.L52e78a:
 cmove  ebx,edi
.L52e78d:
 call target_52d840
.L52e792:
 test   al,al
.L52e794:
 movzx  ebx,bl
.L52e797:
 push   0x9bcc98
.L52e79c:
 push   0x9b8988
.L52e7a1:
 lea    ecx,[esi+0x608]
.L52e7a7:
 cmove  ebx,edi
.L52e7aa:
 call target_52d840
.L52e7af:
 test   al,al
.L52e7b1:
 movzx  ebx,bl
.L52e7b4:
 push   0x9d7b28
.L52e7b9:
 push   0x9ad530
.L52e7be:
 lea    ecx,[esi+0x618]
.L52e7c4:
 cmove  ebx,edi
.L52e7c7:
 call target_52d840
.L52e7cc:
 test   al,al
.L52e7ce:
 movzx  ebx,bl
.L52e7d1:
 push   0x9bcc98
.L52e7d6:
 push   0x9ad530
.L52e7db:
 lea    ecx,[esi+0x628]
.L52e7e1:
 cmove  ebx,edi
.L52e7e4:
 call target_52d840
.L52e7e9:
 test   al,al
.L52e7eb:
 movzx  ebx,bl
.L52e7ee:
 push   0x9d7b28
.L52e7f3:
 push   0x9ae650
.L52e7f8:
 lea    ecx,[esi+0x638]
.L52e7fe:
 cmove  ebx,edi
.L52e801:
 call target_52d840
.L52e806:
 test   al,al
.L52e808:
 movzx  ebx,bl
.L52e80b:
 push   0x9c79e0
.L52e810:
 push   0x9b48f0
.L52e815:
 lea    ecx,[esi+0x648]
.L52e81b:
 cmove  ebx,edi
.L52e81e:
 call target_52d840
.L52e823:
 movzx  ebx,bl
.L52e826:
 test   al,al
.L52e828:
 push   0x99f218
.L52e82d:
 push   0x9ab028
.L52e832:
 lea    ecx,[esi+0x658]
.L52e838:
 cmove  ebx,edi
.L52e83b:
 call target_52d840
.L52e840:
 test   al,al
.L52e842:
 movzx  ebx,bl
.L52e845:
 push   0x9dbd88
.L52e84a:
 push   0x9a9240
.L52e84f:
 lea    ecx,[esi+0x668]
.L52e855:
 cmove  ebx,edi
.L52e858:
 call target_52d840
.L52e85d:
 test   al,al
.L52e85f:
 movzx  ebx,bl
.L52e862:
 push   0x9a8190
.L52e867:
 push   0x9df380
.L52e86c:
 lea    ecx,[esi+0x678]
.L52e872:
 cmove  ebx,edi
.L52e875:
 call target_52d840
.L52e87a:
 test   al,al
.L52e87c:
 movzx  ebx,bl
.L52e87f:
 push   0x9caab0
.L52e884:
 push   0x9e1f90
.L52e889:
 lea    ecx,[esi+0x688]
.L52e88f:
 cmove  ebx,edi
.L52e892:
 call target_52d840
.L52e897:
 test   al,al
.L52e899:
 movzx  ebx,bl
.L52e89c:
 push   0x9b7c88
.L52e8a1:
 push   0x9ca0f8
.L52e8a6:
 lea    ecx,[esi+0x698]
.L52e8ac:
 cmove  ebx,edi
.L52e8af:
 call target_52d840
.L52e8b4:
 test   al,al
.L52e8b6:
 movzx  ebx,bl
.L52e8b9:
 push   0x9c5b38
.L52e8be:
 push   0x9c5878
.L52e8c3:
 lea    ecx,[esi+0x6a8]
.L52e8c9:
 cmove  ebx,edi
.L52e8cc:
 call target_52d840
.L52e8d1:
 test   al,al
.L52e8d3:
 movzx  ebx,bl
.L52e8d6:
 push   0x9bfaf0
.L52e8db:
 push   0x9ce958
.L52e8e0:
 lea    ecx,[esi+0x6b8]
.L52e8e6:
 cmove  ebx,edi
.L52e8e9:
 call target_52d840
.L52e8ee:
 test   al,al
.L52e8f0:
 movzx  ebx,bl
.L52e8f3:
 push   0x9db9b0
.L52e8f8:
 push   0x9ce958
.L52e8fd:
 lea    ecx,[esi+0x6c8]
.L52e903:
 cmove  ebx,edi
.L52e906:
 call target_52d840
.L52e90b:
 test   al,al
.L52e90d:
 movzx  ebx,bl
.L52e910:
 push   0x9e2e48
.L52e915:
 push   0x9a3cd0
.L52e91a:
 lea    ecx,[esi+0x6f8]
.L52e920:
 cmove  ebx,edi
.L52e923:
 call target_52d840
.L52e928:
 test   al,al
.L52e92a:
 movzx  ebx,bl
.L52e92d:
 push   0x9c3e90
.L52e932:
 push   0x9e4168
.L52e937:
 lea    ecx,[esi+0x708]
.L52e93d:
 cmove  ebx,edi
.L52e940:
 call target_52d840
.L52e945:
 test   al,al
.L52e947:
 movzx  ebx,bl
.L52e94a:
 push   0x9db7b0
.L52e94f:
 push   0x9a2c68
.L52e954:
 lea    ecx,[esi+0x718]
.L52e95a:
 cmove  ebx,edi
.L52e95d:
 call target_52d840
.L52e962:
 test   al,al
.L52e964:
 movzx  ebx,bl
.L52e967:
 push   0x9aeb10
.L52e96c:
 cmove  ebx,edi
.L52e96f:
 lea    ecx,[esi+0x728]
.L52e975:
 push   0x9a1970
.L52e97a:
 call target_52d840
.L52e97f:
 test   al,al
.L52e981:
 movzx  ebx,bl
.L52e984:
 push   0x9a9970
.L52e989:
 push   0x9d7380
.L52e98e:
 lea    ecx,[esi+0x738]
.L52e994:
 cmove  ebx,edi
.L52e997:
 call target_52d840
.L52e99c:
 test   al,al
.L52e99e:
 movzx  ebx,bl
.L52e9a1:
 push   0x9cb620
.L52e9a6:
 push   0x9b3190
.L52e9ab:
 lea    ecx,[esi+0x748]
.L52e9b1:
 cmove  ebx,edi
.L52e9b4:
 call target_52d840
.L52e9b9:
 test   al,al
.L52e9bb:
 movzx  ebx,bl
.L52e9be:
 push   0x9cd9e0
.L52e9c3:
 push   0x9e1c58
.L52e9c8:
 lea    ecx,[esi+0x758]
.L52e9ce:
 cmove  ebx,edi
.L52e9d1:
 call target_52d840
.L52e9d6:
 test   al,al
.L52e9d8:
 movzx  ebx,bl
.L52e9db:
 push   0x9b7bd8
.L52e9e0:
 push   0x9c3bb8
.L52e9e5:
 lea    ecx,[esi+0x768]
.L52e9eb:
 cmove  ebx,edi
.L52e9ee:
 call target_52d840
.L52e9f3:
 test   al,al
.L52e9f5:
 movzx  ebx,bl
.L52e9f8:
 push   0x99eb80
.L52e9fd:
 push   0x9a8ce0
.L52ea02:
 lea    ecx,[esi+0x778]
.L52ea08:
 cmove  ebx,edi
.L52ea0b:
 call target_52d840
.L52ea10:
 test   al,al
.L52ea12:
 movzx  ebx,bl
.L52ea15:
 push   0x9db618
.L52ea1a:
 push   0x9a8ce0
.L52ea1f:
 lea    ecx,[esi+0x788]
.L52ea25:
 cmove  ebx,edi
.L52ea28:
 call target_52d840
.L52ea2d:
 test   al,al
.L52ea2f:
 movzx  ebx,bl
.L52ea32:
 push   0x9e3298
.L52ea37:
 push   0x9a8ce0
.L52ea3c:
 lea    ecx,[esi+0x798]
.L52ea42:
 cmove  ebx,edi
.L52ea45:
 call target_52d840
.L52ea4a:
 test   al,al
.L52ea4c:
 movzx  ebx,bl
.L52ea4f:
 push   0x9e2af8
.L52ea54:
 push   0x9a7c98
.L52ea59:
 lea    ecx,[esi+0x7a8]
.L52ea5f:
 cmove  ebx,edi
.L52ea62:
 call target_52d840
.L52ea67:
 test   al,al
.L52ea69:
 movzx  ebx,bl
.L52ea6c:
 push   0x9b5288
.L52ea71:
 push   0x9a7c98
.L52ea76:
 lea    ecx,[esi+0x7b8]
.L52ea7c:
 cmove  ebx,edi
.L52ea7f:
 call target_52d840
.L52ea84:
 test   al,al
.L52ea86:
 movzx  ebx,bl
.L52ea89:
 push   0x9d00a8
.L52ea8e:
 push   0x9a7c98
.L52ea93:
 lea    ecx,[esi+0x7c8]
.L52ea99:
 cmove  ebx,edi
.L52ea9c:
 call target_52d840
.L52eaa1:
 test   al,al
.L52eaa3:
 movzx  ebx,bl
.L52eaa6:
 push   0x9d7ef8
.L52eaab:
 push   0x99fe20
.L52eab0:
 lea    ecx,[esi+0x7d8]
.L52eab6:
 cmove  ebx,edi
.L52eab9:
 call target_52d840
.L52eabe:
 test   al,al
.L52eac0:
 movzx  ebx,bl
.L52eac3:
 cmove  ebx,edi
.L52eac6:
 push   0x9d08c8
.L52eacb:
 push   0x9a7ad8
.L52ead0:
 lea    ecx,[esi+0x808]
.L52ead6:
 call target_52d840
.L52eadb:
 test   al,al
.L52eadd:
 movzx  ebx,bl
.L52eae0:
 push   0x9b9818
.L52eae5:
 push   0x9be7a0
.L52eaea:
 lea    ecx,[esi+0x8d8]
.L52eaf0:
 cmove  ebx,edi
.L52eaf3:
 call target_52d840
.L52eaf8:
 test   al,al
.L52eafa:
 movzx  ebx,bl
.L52eafd:
 push   0x9ac0d8
.L52eb02:
 push   0x9a1d28
.L52eb07:
 lea    ecx,[esi+0xa58]
.L52eb0d:
 cmove  ebx,edi
.L52eb10:
 call target_52d840
.L52eb15:
 test   al,al
.L52eb17:
 movzx  ebx,bl
.L52eb1a:
 push   0x9ac0d8
.L52eb1f:
 push   0x9b9968
.L52eb24:
 lea    ecx,[esi+0xa68]
.L52eb2a:
 cmove  ebx,edi
.L52eb2d:
 call target_52d840
.L52eb32:
 test   al,al
.L52eb34:
 movzx  ebx,bl
.L52eb37:
 push   0x9e9960
.L52eb3c:
 push   0x9c6bf8
.L52eb41:
 lea    ecx,[esi+0xa78]
.L52eb47:
 cmove  ebx,edi
.L52eb4a:
 call target_52d840
.L52eb4f:
 test   al,al
.L52eb51:
 movzx  ebx,bl
.L52eb54:
 push   0x9d9948
.L52eb59:
 push   0x9ca488
.L52eb5e:
 lea    ecx,[esi+0x818]
.L52eb64:
 cmove  ebx,edi
.L52eb67:
 call target_52d840
.L52eb6c:
 test   al,al
.L52eb6e:
 movzx  ebx,bl
.L52eb71:
 push   0x9cf7f0
.L52eb76:
 push   0x9c99d8
.L52eb7b:
 lea    ecx,[esi+0x828]
.L52eb81:
 cmove  ebx,edi
.L52eb84:
 call target_52d840
.L52eb89:
 test   al,al
.L52eb8b:
 movzx  ebx,bl
.L52eb8e:
 push   0x9cf7f0
.L52eb93:
 push   0x9d5408
.L52eb98:
 lea    ecx,[esi+0x838]
.L52eb9e:
 cmove  ebx,edi
.L52eba1:
 call target_52d840
.L52eba6:
 test   al,al
.L52eba8:
 movzx  ebx,bl
.L52ebab:
 push   0x9d3e08
.L52ebb0:
 push   0x9aee08
.L52ebb5:
 lea    ecx,[esi+0x858]
.L52ebbb:
 cmove  ebx,edi
.L52ebbe:
 call target_52d840
.L52ebc3:
 test   al,al
.L52ebc5:
 movzx  ebx,bl
.L52ebc8:
 push   0x9d3e08
.L52ebcd:
 push   0x9d4850
.L52ebd2:
 lea    ecx,[esi+0x868]
.L52ebd8:
 cmove  ebx,edi
.L52ebdb:
 call target_52d840
.L52ebe0:
 test   al,al
.L52ebe2:
 movzx  ebx,bl
.L52ebe5:
 push   0x9d3e08
.L52ebea:
 push   0x9b1690
.L52ebef:
 lea    ecx,[esi+0x878]
.L52ebf5:
 cmove  ebx,edi
.L52ebf8:
 call target_52d840
.L52ebfd:
 test   al,al
.L52ebff:
 movzx  ebx,bl
.L52ec02:
 push   0x9e5750
.L52ec07:
 push   0x9adba0
.L52ec0c:
 lea    ecx,[esi+0x848]
.L52ec12:
 cmove  ebx,edi
.L52ec15:
 call target_52d840
.L52ec1a:
 test   al,al
.L52ec1c:
 movzx  ebx,bl
.L52ec1f:
 push   0x9d16e0
.L52ec24:
 push   0x9e64d8
.L52ec29:
 lea    ecx,[esi+0x8c8]
.L52ec2f:
 cmove  ebx,edi
.L52ec32:
 call target_52d840
.L52ec37:
 test   al,al
.L52ec39:
 movzx  ebx,bl
.L52ec3c:
 push   0x9b03f0
.L52ec41:
 push   0x9e8f40
.L52ec46:
 lea    ecx,[esi+0x888]
.L52ec4c:
 cmove  ebx,edi
.L52ec4f:
 call target_52d840
.L52ec54:
 test   al,al
.L52ec56:
 movzx  ebx,bl
.L52ec59:
 push   0x9b03f0
.L52ec5e:
 push   0x99e280
.L52ec63:
 lea    ecx,[esi+0x898]
.L52ec69:
 cmove  ebx,edi
.L52ec6c:
 call target_52d840
.L52ec71:
 test   al,al
.L52ec73:
 movzx  ebx,bl
.L52ec76:
 push   0x9bd588
.L52ec7b:
 push   0x9c9230
.L52ec80:
 lea    ecx,[esi+0x8a8]
.L52ec86:
 cmove  ebx,edi
.L52ec89:
 call target_52d840
.L52ec8e:
 test   al,al
.L52ec90:
 movzx  ebx,bl
.L52ec93:
 push   0x9bd588
.L52ec98:
 push   0x9e03b8
.L52ec9d:
 lea    ecx,[esi+0x8b8]
.L52eca3:
 cmove  ebx,edi
.L52eca6:
 call target_52d840
.L52ecab:
 test   al,al
.L52ecad:
 movzx  ebx,bl
.L52ecb0:
 push   0x9cddb8
.L52ecb5:
 push   0x9bf508
.L52ecba:
 lea    ecx,[esi+0x8e8]
.L52ecc0:
 cmove  ebx,edi
.L52ecc3:
 call target_52d840
.L52ecc8:
 test   al,al
.L52ecca:
 movzx  ebx,bl
.L52eccd:
 push   0x9d1448
.L52ecd2:
 push   0x9e2498
.L52ecd7:
 lea    ecx,[esi+0x8f8]
.L52ecdd:
 cmove  ebx,edi
.L52ece0:
 call target_52d840
.L52ece5:
 test   al,al
.L52ece7:
 movzx  ebx,bl
.L52ecea:
 push   0x9e7ed0
.L52ecef:
 push   0x9cd130
.L52ecf4:
 lea    ecx,[esi+0x908]
.L52ecfa:
 cmove  ebx,edi
.L52ecfd:
 call target_52d840
.L52ed02:
 test   al,al
.L52ed04:
 movzx  ebx,bl
.L52ed07:
 push   0x9cc808
.L52ed0c:
 push   0x9c2f60
.L52ed11:
 lea    ecx,[esi+0x918]
.L52ed17:
 cmove  ebx,edi
.L52ed1a:
 call target_52d840
.L52ed1f:
 test   al,al
.L52ed21:
 movzx  ebx,bl
.L52ed24:
 push   0x9b8ca0
.L52ed29:
 push   0x9baa00
.L52ed2e:
 lea    ecx,[esi+0x948]
.L52ed34:
 cmove  ebx,edi
.L52ed37:
 call target_52d840
.L52ed3c:
 test   al,al
.L52ed3e:
 movzx  ebx,bl
.L52ed41:
 push   0x99cf00
.L52ed46:
 push   0x9b5b18
.L52ed4b:
 lea    ecx,[esi+0x958]
.L52ed51:
 cmove  ebx,edi
.L52ed54:
 call target_52d840
.L52ed59:
 test   al,al
.L52ed5b:
 movzx  ebx,bl
.L52ed5e:
 push   0x99dbd8
.L52ed63:
 cmove  ebx,edi
.L52ed66:
 push   0x9b7170
.L52ed6b:
 lea    ecx,[esi+0x928]
.L52ed71:
 call target_52d840
.L52ed76:
 test   al,al
.L52ed78:
 movzx  ebx,bl
.L52ed7b:
 push   0x99c948
.L52ed80:
 push   0x9b0030
.L52ed85:
 lea    ecx,[esi+0x938]
.L52ed8b:
 cmove  ebx,edi
.L52ed8e:
 call target_52d840
.L52ed93:
 test   al,al
.L52ed95:
 movzx  ebx,bl
.L52ed98:
 push   0x9aab20
.L52ed9d:
 push   0x9b5690
.L52eda2:
 lea    ecx,[esi+0x968]
.L52eda8:
 cmove  ebx,edi
.L52edab:
 call target_52d840
.L52edb0:
 test   al,al
.L52edb2:
 movzx  ebx,bl
.L52edb5:
 push   0x9bb480
.L52edba:
 push   0x9bef58
.L52edbf:
 lea    ecx,[esi+0x978]
.L52edc5:
 cmove  ebx,edi
.L52edc8:
 call target_52d840
.L52edcd:
 test   al,al
.L52edcf:
 movzx  ebx,bl
.L52edd2:
 push   0x9b6a78
.L52edd7:
 push   0x9d2dd8
.L52eddc:
 lea    ecx,[esi+0x998]
.L52ede2:
 cmove  ebx,edi
.L52ede5:
 call target_52d840
.L52edea:
 test   al,al
.L52edec:
 movzx  ebx,bl
.L52edef:
 push   0x9cbfb8
.L52edf4:
 push   0x9d2dd8
.L52edf9:
 lea    ecx,[esi+0x988]
.L52edff:
 cmove  ebx,edi
.L52ee02:
 call target_52d840
.L52ee07:
 test   al,al
.L52ee09:
 movzx  ebx,bl
.L52ee0c:
 push   0x9c7d08
.L52ee11:
 push   0x9c5f68
.L52ee16:
 lea    ecx,[esi+0x9e8]
.L52ee1c:
 cmove  ebx,edi
.L52ee1f:
 call target_52d840
.L52ee24:
 test   al,al
.L52ee26:
 movzx  ebx,bl
.L52ee29:
 push   0x9e7218
.L52ee2e:
 push   0x9c0548
.L52ee33:
 lea    ecx,[esi+0x9a8]
.L52ee39:
 cmove  ebx,edi
.L52ee3c:
 call target_52d840
.L52ee41:
 test   al,al
.L52ee43:
 movzx  ebx,bl
.L52ee46:
 push   0x9c8c18
.L52ee4b:
 push   0x9e93f0
.L52ee50:
 lea    ecx,[esi+0x9b8]
.L52ee56:
 cmove  ebx,edi
.L52ee59:
 call target_52d840
.L52ee5e:
 test   al,al
.L52ee60:
 movzx  ebx,bl
.L52ee63:
 push   0x9ce190
.L52ee68:
 push   0x9df668
.L52ee6d:
 lea    ecx,[esi+0x9c8]
.L52ee73:
 cmove  ebx,edi
.L52ee76:
 call target_52d840
.L52ee7b:
 test   al,al
.L52ee7d:
 movzx  ebx,bl
.L52ee80:
 push   0x9b7500
.L52ee85:
 push   0x9a4ab0
.L52ee8a:
 lea    ecx,[esi+0x9d8]
.L52ee90:
 cmove  ebx,edi
.L52ee93:
 call target_52d840
.L52ee98:
 test   al,al
.L52ee9a:
 movzx  ebx,bl
.L52ee9d:
 push   0x9e12a0
.L52eea2:
 push   0x99fa90
.L52eea7:
 lea    ecx,[esi+0x9f8]
.L52eead:
 cmove  ebx,edi
.L52eeb0:
 call target_52d840
.L52eeb5:
 movzx  ebx,bl
.L52eeb8:
 test   al,al
.L52eeba:
 lea    ecx,[esi+0xa08]
.L52eec0:
 push   0x9e7730
.L52eec5:
 push   0x9ba1b8
.L52eeca:
 cmove  ebx,edi
.L52eecd:
 call target_52d840
.L52eed2:
 test   al,al
.L52eed4:
 movzx  ebx,bl
.L52eed7:
 push   0x9b25f8
.L52eedc:
 push   0x9ea710
.L52eee1:
 lea    ecx,[esi+0xa18]
.L52eee7:
 cmove  ebx,edi
.L52eeea:
 call target_52d840
.L52eeef:
 test   al,al
.L52eef1:
 movzx  ebx,bl
.L52eef4:
 push   0x9ebfc0
.L52eef9:
 push   0x9ddb70
.L52eefe:
 lea    ecx,[esi+0xa28]
.L52ef04:
 cmove  ebx,edi
.L52ef07:
 call target_52d840
.L52ef0c:
 test   al,al
.L52ef0e:
 movzx  ebx,bl
.L52ef11:
 push   0x9d92b8
.L52ef16:
 push   0x9d9690
.L52ef1b:
 lea    ecx,[esi+0xa38]
.L52ef21:
 cmove  ebx,edi
.L52ef24:
 call target_52d840
.L52ef29:
 test   al,al
.L52ef2b:
 movzx  ebx,bl
.L52ef2e:
 push   0x9d0f98
.L52ef33:
 push   0x9b45f0
.L52ef38:
 lea    ecx,[esi+0xa48]
.L52ef3e:
 cmove  ebx,edi
.L52ef41:
 call target_52d840
.L52ef46:
 test   al,al
.L52ef48:
 movzx  ebx,bl
.L52ef4b:
 push   0x9d9fc8
.L52ef50:
 push   0x9a25d0
.L52ef55:
 lea    ecx,[esi+0xa88]
.L52ef5b:
 cmove  ebx,edi
.L52ef5e:
 call target_52d840
.L52ef63:
 test   al,al
.L52ef65:
 movzx  ebx,bl
.L52ef68:
 push   0x9e10c0
.L52ef6d:
 push   0x9e3f18
.L52ef72:
 lea    ecx,[esi+0xa98]
.L52ef78:
 cmove  ebx,edi
.L52ef7b:
 call target_52d840
.L52ef80:
 test   al,al
.L52ef82:
 movzx  ebx,bl
.L52ef85:
 push   0x9d8b10
.L52ef8a:
 push   0x9d1bf8
.L52ef8f:
 lea    ecx,[esi+0xaa8]
.L52ef95:
 cmove  ebx,edi
.L52ef98:
 call target_52d840
.L52ef9d:
 test   al,al
.L52ef9f:
 movzx  ebx,bl
.L52efa2:
 push   0x9b0b88
.L52efa7:
 push   0x9cb6c0
.L52efac:
 lea    ecx,[esi+0xab8]
.L52efb2:
 cmove  ebx,edi
.L52efb5:
 call target_52d840
.L52efba:
 test   al,al
.L52efbc:
 movzx  ebx,bl
.L52efbf:
 push   0x9ec8a8
.L52efc4:
 push   0x9c6410
.L52efc9:
 lea    ecx,[esi+0xac8]
.L52efcf:
 cmove  ebx,edi
.L52efd2:
 call target_52d840
.L52efd7:
 test   al,al
.L52efd9:
 movzx  ebx,bl
.L52efdc:
 push   0x9e2858
.L52efe1:
 push   0x9e2230
.L52efe6:
 lea    ecx,[esi+0xad8]
.L52efec:
 cmove  ebx,edi
.L52efef:
 call target_52d840
.L52eff4:
 test   al,al
.L52eff6:
 movzx  ebx,bl
.L52eff9:
 push   0x9b0eb0
.L52effe:
 cmove  ebx,edi
.L52f001:
 push   0x9e7c40
.L52f006:
 lea    ecx,[esi+0xae8]
.L52f00c:
 call target_52d840
.L52f011:
 test   al,al
.L52f013:
 movzx  ebx,bl
.L52f016:
 push   0x9a5fa8
.L52f01b:
 push   0x9d1e48
.L52f020:
 lea    ecx,[esi+0xaf8]
.L52f026:
 cmove  ebx,edi
.L52f029:
 call target_52d840
.L52f02e:
 test   al,al
.L52f030:
 movzx  ebx,bl
.L52f033:
 push   0x9bbf78
.L52f038:
 push   0x9e89b8
.L52f03d:
 lea    ecx,[esi+0xb18]
.L52f043:
 cmove  ebx,edi
.L52f046:
 call target_52d840
.L52f04b:
 test   al,al
.L52f04d:
 movzx  ebx,bl
.L52f050:
 push   0x9dc688
.L52f055:
 push   0x9c9708
.L52f05a:
 lea    ecx,[esi+0xb08]
.L52f060:
 cmove  ebx,edi
.L52f063:
 call target_52d840
.L52f068:
 test   al,al
.L52f06a:
 movzx  ebx,bl
.L52f06d:
 push   0x9d0318
.L52f072:
 push   0x9c9708
.L52f077:
 lea    ecx,[esi+0xb28]
.L52f07d:
 cmove  ebx,edi
.L52f080:
 call target_52d840
.L52f085:
 test   al,al
.L52f087:
 movzx  ebx,bl
.L52f08a:
 push   0x9bd0b8
.L52f08f:
 push   0x9e89b8
.L52f094:
 lea    ecx,[esi+0xb38]
.L52f09a:
 cmove  ebx,edi
.L52f09d:
 call target_52d840
.L52f0a2:
 test   al,al
.L52f0a4:
 movzx  ebx,bl
.L52f0a7:
 push   0x9c2728
.L52f0ac:
 push   0x9c8360
.L52f0b1:
 lea    ecx,[esi+0xb48]
.L52f0b7:
 cmove  ebx,edi
.L52f0ba:
 call target_52d840
.L52f0bf:
 test   al,al
.L52f0c1:
 movzx  ebx,bl
.L52f0c4:
 push   0x9c2728
.L52f0c9:
 push   0x9d21c0
.L52f0ce:
 lea    ecx,[esi+0xb58]
.L52f0d4:
 cmove  ebx,edi
.L52f0d7:
 call target_52d840
.L52f0dc:
 test   al,al
.L52f0de:
 movzx  ebx,bl
.L52f0e1:
 push   0x9c4090
.L52f0e6:
 push   0x9bdd90
.L52f0eb:
 lea    ecx,[esi+0xb68]
.L52f0f1:
 cmove  ebx,edi
.L52f0f4:
 call target_52d840
.L52f0f9:
 test   al,al
.L52f0fb:
 movzx  ebx,bl
.L52f0fe:
 push   0x9af7e0
.L52f103:
 push   0x9b6610
.L52f108:
 lea    ecx,[esi+0xb78]
.L52f10e:
 cmove  ebx,edi
.L52f111:
 call target_52d840
.L52f116:
 test   al,al
.L52f118:
 movzx  ebx,bl
.L52f11b:
 push   0x99a5b8
.L52f120:
 push   0x9d3cb0
.L52f125:
 lea    ecx,[esi+0x6d8]
.L52f12b:
 cmove  ebx,edi
.L52f12e:
 call target_52d840
.L52f133:
 test   al,al
.L52f135:
 movzx  ebx,bl
.L52f138:
 push   0x99ffe0
.L52f13d:
 push   0x9d3cb0
.L52f142:
 lea    ecx,[esi+0x6e8]
.L52f148:
 cmove  ebx,edi
.L52f14b:
 call target_52d840
.L52f150:
 movzx  ebx,bl
.L52f153:
 test   al,al
.L52f155:
 push   0x9acf68
.L52f15a:
 push   0x9ce860
.L52f15f:
 lea    ecx,[esi+0xb88]
.L52f165:
 cmove  ebx,edi
.L52f168:
 call target_52d840
.L52f16d:
 test   al,al
.L52f16f:
 movzx  ebx,bl
.L52f172:
 push   0x9b0dc0
.L52f177:
 push   0x9bc4a0
.L52f17c:
 lea    ecx,[esi+0xb98]
.L52f182:
 cmove  ebx,edi
.L52f185:
 call target_52d840
.L52f18a:
 test   al,al
.L52f18c:
 movzx  ebx,bl
.L52f18f:
 push   0x9d64d0
.L52f194:
 push   0x99f918
.L52f199:
 lea    ecx,[esi+0xbc8]
.L52f19f:
 cmove  ebx,edi
.L52f1a2:
 call target_52d840
.L52f1a7:
 test   al,al
.L52f1a9:
 movzx  ebx,bl
.L52f1ac:
 push   0x9def30
.L52f1b1:
 push   0x9de5e0
.L52f1b6:
 lea    ecx,[esi+0xbd8]
.L52f1bc:
 cmove  ebx,edi
.L52f1bf:
 call target_52d840
.L52f1c4:
 test   al,al
.L52f1c6:
 movzx  ebx,bl
.L52f1c9:
 push   0x9def30
.L52f1ce:
 push   0x9a0a38
.L52f1d3:
 lea    ecx,[esi+0xbe8]
.L52f1d9:
 cmove  ebx,edi
.L52f1dc:
 call target_52d840
.L52f1e1:
 test   al,al
.L52f1e3:
 movzx  ebx,bl
.L52f1e6:
 push   0x9d63c8
.L52f1eb:
 push   0x9be1d8
.L52f1f0:
 lea    ecx,[esi+0xbf8]
.L52f1f6:
 cmove  ebx,edi
.L52f1f9:
 call target_52d840
.L52f1fe:
 test   al,al
.L52f200:
 movzx  ebx,bl
.L52f203:
 push   0x9bf3e0
.L52f208:
 push   0x9e2ee8
.L52f20d:
 lea    ecx,[esi+0xc08]
.L52f213:
 cmove  ebx,edi
.L52f216:
 call target_52d840
.L52f21b:
 test   al,al
.L52f21d:
 movzx  ebx,bl
.L52f220:
 push   0x9a49e0
.L52f225:
 push   0x9a43f0
.L52f22a:
 lea    ecx,[esi+0xc18]
.L52f230:
 cmove  ebx,edi
.L52f233:
 call target_52d840
.L52f238:
 test   al,al
.L52f23a:
 movzx  ebx,bl
.L52f23d:
 push   0x9a49e0
.L52f242:
 push   0x9a85e0
.L52f247:
 lea    ecx,[esi+0xc28]
.L52f24d:
 cmove  ebx,edi
.L52f250:
 call target_52d840
.L52f255:
 test   al,al
.L52f257:
 movzx  ebx,bl
.L52f25a:
 push   0x9b3b20
.L52f25f:
 push   0x9cda90
.L52f264:
 lea    ecx,[esi+0xc38]
.L52f26a:
 cmove  ebx,edi
.L52f26d:
 call target_52d840
.L52f272:
 test   al,al
.L52f274:
 movzx  ebx,bl
.L52f277:
 push   0x9c17e8
.L52f27c:
 push   0x9cda90
.L52f281:
 lea    ecx,[esi+0xc48]
.L52f287:
 cmove  ebx,edi
.L52f28a:
 call target_52d840
.L52f28f:
 test   al,al
.L52f291:
 movzx  ebx,bl
.L52f294:
 push   0x9d06f8
.L52f299:
 cmove  ebx,edi
.L52f29c:
 lea    ecx,[esi+0xc58]
.L52f2a2:
 push   0x9cda90
.L52f2a7:
 call target_52d840
.L52f2ac:
 test   al,al
.L52f2ae:
 movzx  ebx,bl
.L52f2b1:
 push   0x9ced58
.L52f2b6:
 push   0x9cda90
.L52f2bb:
 lea    ecx,[esi+0xc68]
.L52f2c1:
 cmove  ebx,edi
.L52f2c4:
 call target_52d840
.L52f2c9:
 test   al,al
.L52f2cb:
 movzx  ebx,bl
.L52f2ce:
 push   0x9a9070
.L52f2d3:
 push   0x9cda90
.L52f2d8:
 lea    ecx,[esi+0xc78]
.L52f2de:
 cmove  ebx,edi
.L52f2e1:
 call target_52d840
.L52f2e6:
 test   al,al
.L52f2e8:
 movzx  ebx,bl
.L52f2eb:
 push   0x9ab5f0
.L52f2f0:
 push   0x9be0e0
.L52f2f5:
 lea    ecx,[esi+0xc88]
.L52f2fb:
 cmove  ebx,edi
.L52f2fe:
 call target_52d840
.L52f303:
 test   al,al
.L52f305:
 movzx  ebx,bl
.L52f308:
 push   0x9ab5f0
.L52f30d:
 push   0x9cf4e0
.L52f312:
 lea    ecx,[esi+0xc98]
.L52f318:
 cmove  ebx,edi
.L52f31b:
 call target_52d840
.L52f320:
 test   al,al
.L52f322:
 movzx  ebx,bl
.L52f325:
 push   0x9baf88
.L52f32a:
 push   0x9d1838
.L52f32f:
 lea    ecx,[esi+0xba8]
.L52f335:
 cmove  ebx,edi
.L52f338:
 call target_52d840
.L52f33d:
 test   al,al
.L52f33f:
 movzx  ebx,bl
.L52f342:
 push   0x9c89d0
.L52f347:
 push   0x9b4f10
.L52f34c:
 lea    ecx,[esi+0xbb8]
.L52f352:
 cmove  ebx,edi
.L52f355:
 call target_52d840
.L52f35a:
 test   al,al
.L52f35c:
 movzx  ebx,bl
.L52f35f:
 push   0x9af3d0
.L52f364:
 push   0x9d7498
.L52f369:
 lea    ecx,[esi+0xcc8]
.L52f36f:
 cmove  ebx,edi
.L52f372:
 call target_52d840
.L52f377:
 test   al,al
.L52f379:
 movzx  ebx,bl
.L52f37c:
 push   0x9a5d68
.L52f381:
 push   0x9d83c8
.L52f386:
 lea    ecx,[esi+0xcd8]
.L52f38c:
 cmove  ebx,edi
.L52f38f:
 call target_52d840
.L52f394:
 test   al,al
.L52f396:
 movzx  ebx,bl
.L52f399:
 push   0x9af3d0
.L52f39e:
 push   0x9a45b0
.L52f3a3:
 lea    ecx,[esi+0xce8]
.L52f3a9:
 cmove  ebx,edi
.L52f3ac:
 call target_52d840
.L52f3b1:
 test   al,al
.L52f3b3:
 movzx  ebx,bl
.L52f3b6:
 push   0x9a5d68
.L52f3bb:
 push   0x9e4948
.L52f3c0:
 lea    ecx,[esi+0xcf8]
.L52f3c6:
 cmove  ebx,edi
.L52f3c9:
 call target_52d840
.L52f3ce:
 test   al,al
.L52f3d0:
 movzx  ebx,bl
.L52f3d3:
 push   0x9bff18
.L52f3d8:
 push   0x9a3708
.L52f3dd:
 lea    ecx,[esi+0xd08]
.L52f3e3:
 cmove  ebx,edi
.L52f3e6:
 call target_52d840
.L52f3eb:
 test   al,al
.L52f3ed:
 movzx  ebx,bl
.L52f3f0:
 cmove  ebx,edi
.L52f3f3:
 push   0x9bff18
.L52f3f8:
 push   0x9ab678
.L52f3fd:
 lea    ecx,[esi+0xd18]
.L52f403:
 call target_52d840
.L52f408:
 test   al,al
.L52f40a:
 movzx  ebx,bl
.L52f40d:
 push   0x9a2a20
.L52f412:
 push   0x99e088
.L52f417:
 lea    ecx,[esi+0xd28]
.L52f41d:
 cmove  ebx,edi
.L52f420:
 call target_52d840
.L52f425:
 test   al,al
.L52f427:
 movzx  ebx,bl
.L52f42a:
 push   0x9b2278
.L52f42f:
 push   0x9a3ac0
.L52f434:
 lea    ecx,[esi+0xd38]
.L52f43a:
 cmove  ebx,edi
.L52f43d:
 call target_52d840
.L52f442:
 test   al,al
.L52f444:
 movzx  ebx,bl
.L52f447:
 push   0x9b2278
.L52f44c:
 push   0x9e5e50
.L52f451:
 lea    ecx,[esi+0xd48]
.L52f457:
 cmove  ebx,edi
.L52f45a:
 call target_52d840
.L52f45f:
 test   al,al
.L52f461:
 movzx  ebx,bl
.L52f464:
 push   0x9b9250
.L52f469:
 push   0x9a4e98
.L52f46e:
 lea    ecx,[esi+0xd58]
.L52f474:
 cmove  ebx,edi
.L52f477:
 call target_52d840
.L52f47c:
 test   al,al
.L52f47e:
 movzx  ebx,bl
.L52f481:
 push   0x9a1a70
.L52f486:
 push   0x9b5370
.L52f48b:
 lea    ecx,[esi+0xd68]
.L52f491:
 cmove  ebx,edi
.L52f494:
 call target_52d840
.L52f499:
 test   al,al
.L52f49b:
 je .L52f4ae
.L52f49d:
 test   bl,bl
.L52f49f:
 jne .L52f4ae
.L52f4a1:
 {load} mov    ecx,esi
.L52f4a3:
 call target_530200
.L52f4a8:
 mov    al,0x1
.L52f4aa:
 pop    edi
.L52f4ab:
 pop    esi
.L52f4ac:
 pop    ebx
.L52f4ad:
 ret
.L52f4ae:
 {load} mov    ecx,esi
.L52f4b0:
 call target_52f4c0
.L52f4b5:
 pop    edi
.L52f4b6:
 pop    esi
.L52f4b7:
 {load} xor    al,al
.L52f4b9:
 pop    ebx
.L52f4ba:
 ret
.equ target_52d840,0x52d840
.equ target_52f4c0,0x52f4c0
.equ target_530200,0x530200
