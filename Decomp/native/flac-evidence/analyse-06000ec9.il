TOKEN [Method:0x0ec9] System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::gaAudioAnalysis.analyse(gaAudioAnalysis* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst),System.Single modopt(System.Runtime.CompilerServices.IsConst)*,System.Int32,System.Int32,System.Boolean modreq(System.Runtime.CompilerServices.IsVolatile)*,System.Single*,std.basic_string<char,std::char_traits<char>,std::allocator<char> > modreq(System.Runtime.CompilerServices.IsCopyConstructed)*)
IL_0000: ldarg.0
IL_0001: ldc.i4 176
IL_0006: add
IL_0007: ldarg.s _debugName
IL_0009: call std.basic_string<char,std::char_traits<char>,std::allocator<char> >* modopt(System.Runtime.CompilerServices.IsImplicitlyDereferenced) modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.basic_string<char,std::char_traits<char>,std::allocator<char> >.=(std.basic_string<char,std::char_traits<char>,std::allocator<char> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst),std.basic_string<char,std::char_traits<char>,std::allocator<char> > modopt(System.Runtime.CompilerServices.IsConst)* modopt(System.Runtime.CompilerServices.IsImplicitlyDereferenced))
IL_000e: pop
IL_000f: call System.UInt32 modopt(System.Runtime.CompilerServices.CallConvCdecl) <Module>::elOSGetTimeInMicroSeconds()
IL_0014: pop
IL_0015: ldarg.2
IL_0016: conv.r4
IL_0017: conv.r8
IL_0018: ldarg.3
IL_0019: conv.r4
IL_001a: conv.r8
IL_001b: div
IL_001c: conv.r4
IL_001d: stloc.0
IL_001e: ldarg.0
IL_001f: ldc.i4.s 16
IL_0021: add
IL_0022: ldloc.0
IL_0023: stind.r4
IL_0024: ldarg.0
IL_0025: ldc.i4 164
IL_002a: add
IL_002b: ldc.r4 0
IL_0030: stind.r4
IL_0031: ldarg.0
IL_0032: ldc.i4 168
IL_0037: add
IL_0038: ldloc.0
IL_0039: stind.r4
IL_003a: ldloca.s V_3
IL_003c: ldc.i4.0
IL_003d: stind.i4
IL_003e: ldloca.s V_3
IL_0040: ldc.i4.4
IL_0041: add
IL_0042: ldc.i4.0
IL_0043: stind.i4
IL_0044: ldloca.s V_3
IL_0046: ldc.i4.8
IL_0047: add
IL_0048: ldc.i4.0
IL_0049: stind.i4
IL_004a: ldloca.s V_3
IL_004c: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.vector<float,std::allocator<float> >.clear(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_0051: ldloc.2
IL_0052: stloc.1
IL_0053: ldloca.s V_3
IL_0055: ldarg.1
IL_0056: ldarg.2
IL_0057: ldc.i4.4
IL_0058: mul
IL_0059: ldarg.1
IL_005a: add
IL_005b: ldloc.1
IL_005c: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.vector<float,std::allocator<float> >._Assign<float const *>(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst),System.Single modopt(System.Runtime.CompilerServices.IsConst)*,System.Single modopt(System.Runtime.CompilerServices.IsConst)*,std.forward_iterator_tag)
IL_0061: call System.Void modopt(System.Runtime.CompilerServices.CallConvCdecl) <Module>::essentia.init()
IL_0066: ldc.i4.0
IL_0067: call System.Void modopt(System.Runtime.CompilerServices.CallConvCdecl) <Module>::essentia.setDebugLevel(System.Int32)
IL_006c: call System.UInt32 modopt(System.Runtime.CompilerServices.CallConvCdecl) <Module>::elOSGetTimeInMicroSeconds()
IL_0071: pop
IL_0072: ldarg.s r_nextProgress
IL_0074: brfalse.s IL_007e
IL_0076: ldarg.s r_nextProgress
IL_0078: ldc.r4 25
IL_007d: stind.r4
IL_007e: ldarg.s _analysisCancelled
IL_0080: volatile.
IL_0082: ldind.u1
IL_0083: brtrue.s IL_0087
IL_0085: leave.s IL_00bc
IL_0087: leave.s IL_0097
IL_0089: ldftn System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.vector<float,std::allocator<float> >.{dtor}(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_008f: ldloca.s V_3
IL_0091: call System.Void <Module>::___CxxCallUnwindDtor(method System.Void *(System.Void*),System.Void*)
IL_0096: endfinally
IL_0097: ldloca.s V_3
IL_0099: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.vector<float,std::allocator<float> >._Tidy(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_009e: leave.s IL_00ae
IL_00a0: ldftn System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.basic_string<char,std::char_traits<char>,std::allocator<char> >.{dtor}(std.basic_string<char,std::char_traits<char>,std::allocator<char> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_00a6: ldarg.s _debugName
IL_00a8: call System.Void <Module>::___CxxCallUnwindDtor(method System.Void *(System.Void*),System.Void*)
IL_00ad: endfinally
IL_00ae: ldarg.s _debugName
IL_00b0: ldc.i4.1
IL_00b1: ldc.i4.0
IL_00b2: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.basic_string<char,std::char_traits<char>,std::allocator<char> >._Tidy(std.basic_string<char,std::char_traits<char>,std::allocator<char> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst),System.Boolean,System.UInt32)
IL_00b7: br IL_028d
IL_00bc: nop
IL_00bd: ldarg.0
IL_00be: ldloca.s V_3
IL_00c0: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::gaAudioAnalysis.analyse_volume(gaAudioAnalysis* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst),std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsImplicitlyDereferenced))
IL_00c5: call System.UInt32 modopt(System.Runtime.CompilerServices.CallConvCdecl) <Module>::elOSGetTimeInMicroSeconds()
IL_00ca: pop
IL_00cb: ldarg.s r_nextProgress
IL_00cd: brfalse.s IL_00d7
IL_00cf: ldarg.s r_nextProgress
IL_00d1: ldc.r4 75
IL_00d6: stind.r4
IL_00d7: ldarg.s _analysisCancelled
IL_00d9: volatile.
IL_00db: ldind.u1
IL_00dc: brtrue.s IL_00e0
IL_00de: leave.s IL_0115
IL_00e0: leave.s IL_00f0
IL_00e2: ldftn System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.vector<float,std::allocator<float> >.{dtor}(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_00e8: ldloca.s V_3
IL_00ea: call System.Void <Module>::___CxxCallUnwindDtor(method System.Void *(System.Void*),System.Void*)
IL_00ef: endfinally
IL_00f0: ldloca.s V_3
IL_00f2: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.vector<float,std::allocator<float> >._Tidy(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_00f7: leave.s IL_0107
IL_00f9: ldftn System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.basic_string<char,std::char_traits<char>,std::allocator<char> >.{dtor}(std.basic_string<char,std::char_traits<char>,std::allocator<char> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_00ff: ldarg.s _debugName
IL_0101: call System.Void <Module>::___CxxCallUnwindDtor(method System.Void *(System.Void*),System.Void*)
IL_0106: endfinally
IL_0107: ldarg.s _debugName
IL_0109: ldc.i4.1
IL_010a: ldc.i4.0
IL_010b: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.basic_string<char,std::char_traits<char>,std::allocator<char> >._Tidy(std.basic_string<char,std::char_traits<char>,std::allocator<char> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst),System.Boolean,System.UInt32)
IL_0110: br IL_028d
IL_0115: nop
IL_0116: ldarg.0
IL_0117: ldloca.s V_3
IL_0119: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::gaAudioAnalysis.analyse_rhythm_2013(gaAudioAnalysis* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst),std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsImplicitlyDereferenced))
IL_011e: call System.UInt32 modopt(System.Runtime.CompilerServices.CallConvCdecl) <Module>::elOSGetTimeInMicroSeconds()
IL_0123: pop
IL_0124: ldarg.s r_nextProgress
IL_0126: brfalse.s IL_0130
IL_0128: ldarg.s r_nextProgress
IL_012a: ldc.r4 98
IL_012f: stind.r4
IL_0130: ldarg.s _analysisCancelled
IL_0132: volatile.
IL_0134: ldind.u1
IL_0135: brtrue.s IL_0139
IL_0137: leave.s IL_016e
IL_0139: leave.s IL_0149
IL_013b: ldftn System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.vector<float,std::allocator<float> >.{dtor}(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_0141: ldloca.s V_3
IL_0143: call System.Void <Module>::___CxxCallUnwindDtor(method System.Void *(System.Void*),System.Void*)
IL_0148: endfinally
IL_0149: ldloca.s V_3
IL_014b: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.vector<float,std::allocator<float> >._Tidy(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_0150: leave.s IL_0160
IL_0152: ldftn System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.basic_string<char,std::char_traits<char>,std::allocator<char> >.{dtor}(std.basic_string<char,std::char_traits<char>,std::allocator<char> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_0158: ldarg.s _debugName
IL_015a: call System.Void <Module>::___CxxCallUnwindDtor(method System.Void *(System.Void*),System.Void*)
IL_015f: endfinally
IL_0160: ldarg.s _debugName
IL_0162: ldc.i4.1
IL_0163: ldc.i4.0
IL_0164: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.basic_string<char,std::char_traits<char>,std::allocator<char> >._Tidy(std.basic_string<char,std::char_traits<char>,std::allocator<char> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst),System.Boolean,System.UInt32)
IL_0169: br IL_028d
IL_016e: nop
IL_016f: ldarg.0
IL_0170: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::gaAudioAnalysis.adjustBpm(gaAudioAnalysis* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_0175: call System.UInt32 modopt(System.Runtime.CompilerServices.CallConvCdecl) <Module>::elOSGetTimeInMicroSeconds()
IL_017a: pop
IL_017b: ldarg.s r_nextProgress
IL_017d: brfalse.s IL_0187
IL_017f: ldarg.s r_nextProgress
IL_0181: ldc.r4 100
IL_0186: stind.r4
IL_0187: ldarg.s _analysisCancelled
IL_0189: volatile.
IL_018b: ldind.u1
IL_018c: brtrue.s IL_0190
IL_018e: leave.s IL_01c5
IL_0190: leave.s IL_01a0
IL_0192: ldftn System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.vector<float,std::allocator<float> >.{dtor}(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_0198: ldloca.s V_3
IL_019a: call System.Void <Module>::___CxxCallUnwindDtor(method System.Void *(System.Void*),System.Void*)
IL_019f: endfinally
IL_01a0: ldloca.s V_3
IL_01a2: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.vector<float,std::allocator<float> >._Tidy(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_01a7: leave.s IL_01b7
IL_01a9: ldftn System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.basic_string<char,std::char_traits<char>,std::allocator<char> >.{dtor}(std.basic_string<char,std::char_traits<char>,std::allocator<char> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_01af: ldarg.s _debugName
IL_01b1: call System.Void <Module>::___CxxCallUnwindDtor(method System.Void *(System.Void*),System.Void*)
IL_01b6: endfinally
IL_01b7: ldarg.s _debugName
IL_01b9: ldc.i4.1
IL_01ba: ldc.i4.0
IL_01bb: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.basic_string<char,std::char_traits<char>,std::allocator<char> >._Tidy(std.basic_string<char,std::char_traits<char>,std::allocator<char> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst),System.Boolean,System.UInt32)
IL_01c0: br IL_028d
IL_01c5: nop
IL_01c6: ldarg.0
IL_01c7: ldloca.s V_3
IL_01c9: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::gaAudioAnalysis.analyse_sections(gaAudioAnalysis* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst),std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsImplicitlyDereferenced))
IL_01ce: call System.UInt32 modopt(System.Runtime.CompilerServices.CallConvCdecl) <Module>::elOSGetTimeInMicroSeconds()
IL_01d3: pop
IL_01d4: ldarg.s _analysisCancelled
IL_01d6: volatile.
IL_01d8: ldind.u1
IL_01d9: brtrue.s IL_01dd
IL_01db: leave.s IL_0212
IL_01dd: leave.s IL_01ed
IL_01df: ldftn System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.vector<float,std::allocator<float> >.{dtor}(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_01e5: ldloca.s V_3
IL_01e7: call System.Void <Module>::___CxxCallUnwindDtor(method System.Void *(System.Void*),System.Void*)
IL_01ec: endfinally
IL_01ed: ldloca.s V_3
IL_01ef: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.vector<float,std::allocator<float> >._Tidy(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_01f4: leave.s IL_0204
IL_01f6: ldftn System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.basic_string<char,std::char_traits<char>,std::allocator<char> >.{dtor}(std.basic_string<char,std::char_traits<char>,std::allocator<char> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_01fc: ldarg.s _debugName
IL_01fe: call System.Void <Module>::___CxxCallUnwindDtor(method System.Void *(System.Void*),System.Void*)
IL_0203: endfinally
IL_0204: ldarg.s _debugName
IL_0206: ldc.i4.1
IL_0207: ldc.i4.0
IL_0208: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.basic_string<char,std::char_traits<char>,std::allocator<char> >._Tidy(std.basic_string<char,std::char_traits<char>,std::allocator<char> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst),System.Boolean,System.UInt32)
IL_020d: br IL_028d
IL_0212: nop
IL_0213: ldarg.0
IL_0214: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::gaAudioAnalysis.analyse_bars(gaAudioAnalysis* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_0219: ldarg.0
IL_021a: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::gaAudioAnalysis.snapSectionsToBars(gaAudioAnalysis* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_021f: ldarg.0
IL_0220: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::gaAudioAnalysis.measureSectionLoudness(gaAudioAnalysis* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_0225: ldarg.0
IL_0226: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::gaAudioAnalysis.measureBeatSpanVols(gaAudioAnalysis* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_022b: call System.UInt32 modopt(System.Runtime.CompilerServices.CallConvCdecl) <Module>::elOSGetTimeInMicroSeconds()
IL_0230: pop
IL_0231: call System.Void modopt(System.Runtime.CompilerServices.CallConvCdecl) <Module>::essentia.shutdown()
IL_0236: ldarg.0
IL_0237: ldc.i4.s 96
IL_0239: add
IL_023a: call System.Void modopt(System.Runtime.CompilerServices.CallConvCdecl) <Module>::?A0x21595610.clear_vector<float>(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsImplicitlyDereferenced))
IL_023f: ldarg.0
IL_0240: ldc.i4.s 48
IL_0242: add
IL_0243: call System.Void modopt(System.Runtime.CompilerServices.CallConvCdecl) <Module>::?A0x21595610.clear_vector<float>(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsImplicitlyDereferenced))
IL_0248: ldarg.0
IL_0249: ldc.i4.s 36
IL_024b: add
IL_024c: call System.Void modopt(System.Runtime.CompilerServices.CallConvCdecl) <Module>::?A0x21595610.clear_vector<float>(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsImplicitlyDereferenced))
IL_0251: call System.UInt32 modopt(System.Runtime.CompilerServices.CallConvCdecl) <Module>::elOSGetTimeInMicroSeconds()
IL_0256: pop
IL_0257: call System.UInt32 modopt(System.Runtime.CompilerServices.CallConvCdecl) <Module>::elOSGetTimeInMicroSeconds()
IL_025c: pop
IL_025d: leave.s IL_026d
IL_025f: ldftn System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.vector<float,std::allocator<float> >.{dtor}(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_0265: ldloca.s V_3
IL_0267: call System.Void <Module>::___CxxCallUnwindDtor(method System.Void *(System.Void*),System.Void*)
IL_026c: endfinally
IL_026d: ldloca.s V_3
IL_026f: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.vector<float,std::allocator<float> >._Tidy(std.vector<float,std::allocator<float> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_0274: leave.s IL_0284
IL_0276: ldftn System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.basic_string<char,std::char_traits<char>,std::allocator<char> >.{dtor}(std.basic_string<char,std::char_traits<char>,std::allocator<char> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst))
IL_027c: ldarg.s _debugName
IL_027e: call System.Void <Module>::___CxxCallUnwindDtor(method System.Void *(System.Void*),System.Void*)
IL_0283: endfinally
IL_0284: ldarg.s _debugName
IL_0286: ldc.i4.1
IL_0287: ldc.i4.0
IL_0288: call System.Void modopt(System.Runtime.CompilerServices.CallConvThiscall) <Module>::std.basic_string<char,std::char_traits<char>,std::allocator<char> >._Tidy(std.basic_string<char,std::char_traits<char>,std::allocator<char> >* modopt(System.Runtime.CompilerServices.IsConst) modopt(System.Runtime.CompilerServices.IsConst),System.Boolean,System.UInt32)
IL_028d: ret
