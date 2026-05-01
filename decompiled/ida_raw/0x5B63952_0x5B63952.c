// 0x5B63952 @ 0x5B63952
unsigned __int64 __fastcall sub_5B63952(__int64 i1, char *login, unsigned __int64 i, unsigned __int64 k)
{
  void *i1_1; // r12
  void *n788152950; // rbx
  char *p_n0x12_5; // rax
  char *n0x12_2; // rcx
  int n1657293156; // eax
  unsigned __int64 k_5; // rax
  void **p_filename_2; // r12
  size_t v11; // rax
  void **p_filename_3; // rdi
  FILE *v13; // rax
  char *n0x45_3; // rcx
  char *n0x12_5; // rax
  int n220751368; // ecx
  _BYTE *n0x45_4; // rax
  char *dest_1; // rbx
  char *p_n0x12_11; // rax
  char *n0x12_4; // rcx
  int n1657293156_1; // eax
  _BYTE *p_n0x12_12; // rax
  _BYTE *p_n0x12_6; // rax
  int j; // ecx
  char *p_n0x12_8; // rcx
  char *n0x12_3; // rax
  _BYTE *p_n0x12_9; // rax
  _BYTE *v29; // [rsp+0h] [rbp-220h] BYREF
  char *s_1; // [rsp+8h] [rbp-218h]
  unsigned __int64 k_2; // [rsp+10h] [rbp-210h]
  char *s_2; // [rsp+18h] [rbp-208h]
  __m128i *p_si128; // [rsp+20h] [rbp-200h]
  const __m128i *v34; // [rsp+28h] [rbp-1F8h]
  __int64 v35; // [rsp+30h] [rbp-1F0h]
  __int64 v36; // [rsp+38h] [rbp-1E8h]
  void *dest; // [rsp+40h] [rbp-1E0h]
  _DWORD *v38; // [rsp+48h] [rbp-1D8h]
  _BYTE *v39; // [rsp+50h] [rbp-1D0h]
  _BYTE *p_n0x12_7; // [rsp+58h] [rbp-1C8h]
  _BYTE *p_n0x12_4; // [rsp+60h] [rbp-1C0h]
  _BYTE *n0x45_2; // [rsp+68h] [rbp-1B8h]
  _BYTE *p_n0x12_10; // [rsp+70h] [rbp-1B0h]
  void *src; // [rsp+78h] [rbp-1A8h]
  const __m128i *v45; // [rsp+80h] [rbp-1A0h]
  void *s_4; // [rsp+88h] [rbp-198h]
  _DWORD *v47; // [rsp+90h] [rbp-190h]
  FILE **p_stream_1; // [rsp+98h] [rbp-188h]
  void **p_filename_1; // [rsp+A0h] [rbp-180h]
  _QWORD *v50; // [rsp+A8h] [rbp-178h]
  _QWORD *v51; // [rsp+B0h] [rbp-170h]
  __int64 *v52; // [rsp+B8h] [rbp-168h]
  _BYTE *v53; // [rsp+C0h] [rbp-160h]
  _QWORD *s_3; // [rsp+C8h] [rbp-158h]
  char *haystack_1; // [rsp+D0h] [rbp-150h]
  _QWORD *v56; // [rsp+D8h] [rbp-148h]
  unsigned __int64 k_3; // [rsp+E0h] [rbp-140h]
  int i_1; // [rsp+E8h] [rbp-138h]
  unsigned int ia; // [rsp+ECh] [rbp-134h]
  unsigned __int64 k_6; // [rsp+F0h] [rbp-130h]
  void *s_5; // [rsp+F8h] [rbp-128h]
  void *s; // [rsp+100h] [rbp-120h]
  __m128i *p_si128_1; // [rsp+108h] [rbp-118h]
  __m128i *v64; // [rsp+110h] [rbp-110h]
  _BYTE *p_n0x12_2; // [rsp+118h] [rbp-108h]
  _BYTE *p_n0x12_1; // [rsp+120h] [rbp-100h]
  _BYTE *n0x45_1; // [rsp+128h] [rbp-F8h]
  _BYTE *p_n0x12_3; // [rsp+130h] [rbp-F0h]
  void **logina; // [rsp+138h] [rbp-E8h]
  _DWORD *v70; // [rsp+140h] [rbp-E0h]
  _QWORD *v71; // [rsp+148h] [rbp-D8h]
  _DWORD *v72; // [rsp+150h] [rbp-D0h]
  _QWORD *v73; // [rsp+158h] [rbp-C8h]
  _QWORD *v74; // [rsp+160h] [rbp-C0h]
  void **p_filename; // [rsp+168h] [rbp-B8h]
  unsigned int n4_1; // [rsp+174h] [rbp-ACh]
  unsigned int n4; // [rsp+178h] [rbp-A8h]
  unsigned int k_4; // [rsp+17Ch] [rbp-A4h]
  char *haystack; // [rsp+180h] [rbp-A0h]
  FILE **p_stream; // [rsp+188h] [rbp-98h]
  int n2; // [rsp+194h] [rbp-8Ch]
  unsigned __int64 *k_1; // [rsp+198h] [rbp-88h]
  char **p_n0x12; // [rsp+1A0h] [rbp-80h]
  char v84; // [rsp+1AAh] [rbp-76h]
  char v85; // [rsp+1ABh] [rbp-75h]
  int n0x12_6; // [rsp+1ACh] [rbp-74h]
  char *n0x12_1; // [rsp+1B0h] [rbp-70h]
  __int64 v88; // [rsp+1B8h] [rbp-68h] BYREF
  char *n0x12; // [rsp+1C0h] [rbp-60h] BYREF
  unsigned __int64 n0x45; // [rsp+1C8h] [rbp-58h] BYREF
  __m128i si128; // [rsp+1D0h] [rbp-50h] BYREF
  __m128i v92; // [rsp+1E0h] [rbp-40h] BYREF
  unsigned __int64 v93; // [rsp+1F0h] [rbp-30h]

  ia = i; /*0x5b63966*/
  dest = login; /*0x5b6396c*/
  i1_1 = (void *)i1; /*0x5b63973*/
  v93 = __readfsqword(0x28u); /*0x5b6397f*/
  v38 = (_DWORD *)(i1 + 52); /*0x5b63987*/
  v39 = (_BYTE *)(i1 + 48); /*0x5b63992*/
  n788152950 = &loc_4814D90; /*0x5b63999*/
  do /*0x5b64ee7*/
  {
    while ( 1 ) /*0x5b63b5d*/
    {
      while ( 1 ) /*0x5b63b51*/
      {
        while ( 1 ) /*0x5b639d7*/
        {
          while ( 1 ) /*0x5b639cb*/
          {
            while ( 1 ) /*0x5b639c3*/
            {
              while ( (int)n788152950 <= -51024906 ) /*0x5b639c3*/
              {
                if ( (int)n788152950 > -1428043109 ) /*0x5b63a2b*/
                {
                  if ( (int)n788152950 <= -509529065 ) /*0x5b63a83*/
                  {
                    if ( (int)n788152950 > -1138025788 ) /*0x5b63d44*/
                    {
                      if ( (_DWORD)n788152950 == -1138025787 ) /*0x5b63e10*/
                      {
                        LODWORD(n788152950) = -1515106128; /*0x5b642d5*/
                        if ( !i_1 ) /*0x5b642df*/
                          LODWORD(n788152950) = 2076341563; /*0x5b642df*/
                      }
                      else if ( (_DWORD)n788152950 == -622888238 ) /*0x5b63e1c*/
                      {
                        v35 = v88; /*0x5b63e26*/
                        LODWORD(n788152950) = 1446338001; /*0x5b63e2d*/
                      }
                    }
                    else if ( (_DWORD)n788152950 == -1428043108 ) /*0x5b63d50*/
                    {
                      if ( (n2 & 0xFFFFFFFD) == 0 ) /*0x5b64168*/
                        goto LABEL_86; /*0x5b64168*/
LABEL_89:
                      sub_5B75608(p_stream, login, i, k, 3879402463LL); /*0x5b641ba*/
                      LODWORD(n788152950) = 424671078; /*0x5b641fb*/
                      if ( *p_filename != p_filename + 2 ) /*0x5b64203*/
                        operator delete(*p_filename); /*0x5b64209*/
                    }
                    else if ( (_DWORD)n788152950 == -1425534050 ) /*0x5b63d5c*/
                    {
                      LODWORD(n788152950) = 620840580; /*0x5b63d62*/
                      n4 = 4; /*0x5b63d67*/
                    }
                  }
                  else if ( (int)n788152950 <= -176883314 ) /*0x5b63a8f*/
                  {
                    if ( (_DWORD)n788152950 == -509529064 ) /*0x5b640b4*/
                    {
                      v36 = *v71 - v88; /*0x5b64b49*/
                      sub_5536FD0(logina, s_4, v73); /*0x5b64b73*/
                      login = (char *)logina; /*0x5b64b78*/
                      sub_5B7543A(i1_1, logina); /*0x5b64b82*/
                      if ( *logina != logina + 2 ) /*0x5b64b98*/
                        operator delete(*logina); /*0x5b64b9a*/
                      LODWORD(n788152950) = -51024905; /*0x5b64ba6*/
                      k_3 = 0; /*0x5b64bad*/
                    }
                    else if ( (_DWORD)n788152950 == -238376491 ) /*0x5b640c0*/
                    {
                      *v53 = 1; /*0x5b640cd*/
                      v72 = v38; /*0x5b640d7*/
                      *v38 = 0; /*0x5b640e5*/
                      v64 = &v92; /*0x5b640ef*/
                      LODWORD(n788152950) = 1777073726; /*0x5b640f6*/
                    }
                  }
                  else
                  {
                    switch ( (_DWORD)n788152950 ) /*0x5b63a9b*/
                    {
                      case 0xF574F98F: /*0x5b63a9b*/
                        LODWORD(n788152950) = 788152951; /*0x5b64c54*/
                        n4_1 = 0; /*0x5b64c59*/
                        break;
                      case 0xF61043F9: /*0x5b63a9b*/
                        v47 = v70; /*0x5b64e34*/
                        *v70 = 0; /*0x5b64e49*/
                        s_4 = s_3; /*0x5b64e56*/
                        login = "%lx-%lx %*s %lx %*x:%*x %*d %s%n"; /*0x5b64e7d*/
                        LODWORD(n788152950) = -1650255174; /*0x5b64eae*/
                        if ( sscanf(haystack, "%lx-%lx %*s %lx %*x:%*x %*d %s%n", &v88, v71, v56, s_3, v70) == 4 ) /*0x5b64eb8*/
                          LODWORD(n788152950) = 86511158; /*0x5b64eb8*/
                        break;
                      case 0xF853D5C3: /*0x5b63a9b*/
                        login = (_BYTE *)(&qword_60 + 5); /*0x5b63ac7*/
                        sub_5545F3B(s_1, (char)v29); /*0x5b63adb*/
                        LODWORD(n788152950) = -24204128; /*0x5b63b00*/
                        break;
                    }
                  }
                }
                else if ( (int)n788152950 <= -1738556109 ) /*0x5b63a33*/
                {
                  if ( (int)n788152950 > -1905020922 ) /*0x5b63b8a*/
                  {
                    if ( (_DWORD)n788152950 == -1905020921 ) /*0x5b63da5*/
                    {
                      n0x45_2 = n0x45_1; /*0x5b6422c*/
                      n0x45_3 = n0x45_1; /*0x5b6423a*/
                      *n0x45_1 = 1; /*0x5b64241*/
                      n0x45_3[1] = 12; /*0x5b64244*/
                      n0x45_3[2] = 107; /*0x5b64248*/
                      n0x45_3[3] = 125; /*0x5b6424e*/
                      n0x45_3[4] = 127; /*0x5b64253*/
                      qmemcpy(n0x45_3 + 5, "v~8pe7f`|}y", 11); /*0x5b64256*/
                      n0x45_3[16] = 127; /*0x5b64281*/
                      n0x45_3[17] = 105; /*0x5b64284*/
                      n0x45_3[18] = 47; /*0x5b64288*/
                      n0x45_3[19] = 62; /*0x5b6428c*/
                      n0x12_5 = n0x45_3 + 20; /*0x5b64290*/
                      n0x12_1 = n0x45_3 + 22; /*0x5b64298*/
                      n220751368 = 220751368; /*0x5b6429c*/
                      while ( n220751368 != -1725201370 ) /*0x5b642ab*/
                      {
                        *n0x12_5++ = 0; /*0x5b642b5*/
                        n220751368 = 220751368; /*0x5b642bf*/
                        if ( n0x12_5 == n0x12_1 ) /*0x5b642c9*/
                          n220751368 = -1725201370; /*0x5b642c9*/
                      }
                      n0x45_4 = n0x45_1; /*0x5b642e7*/
                      n0x45 = (unsigned __int64)n0x45_1; /*0x5b642ee*/
                      v85 = *n0x45_1; /*0x5b642f8*/
                      k = (unsigned __int64)(n0x45_1 + 2); /*0x5b642fb*/
                      for ( i = 4236409147LL; ; i = 3990489244LL ) /*0x5b642ff*/
                      {
                        while ( 1 ) /*0x5b6430a*/
                        {
                          while ( (int)i > -304478053 ) /*0x5b6430a*/
                          {
                            if ( (int)i > 592667713 ) /*0x5b64312*/
                            {
                              if ( (_DWORD)i == 592667714 ) /*0x5b64380*/
                              {
                                n0x12_6 = (int)n0x12; /*0x5b643fc*/
                                k_1 = (unsigned __int64 *)k; /*0x5b643ff*/
                                login = (char *)k; /*0x5b6440a*/
                                v84 = n0x12[k]; /*0x5b64414*/
                                i = 3302940371LL; /*0x5b64417*/
                              }
                              else
                              {
                                n0x12 = n0x12_1 + 1; /*0x5b64395*/
                                i = 3990489244LL; /*0x5b64399*/
                              }
                            }
                            else if ( (_DWORD)i == -304478052 ) /*0x5b6431a*/
                            {
                              i = 3184707443LL; /*0x5b643ea*/
                              if ( (unsigned __int64)n0x12 < 0x12 ) /*0x5b643ef*/
                                i = 592667714; /*0x5b643ef*/
                            }
                            else
                            {
                              i = 3852595550LL; /*0x5b6432c*/
                              if ( (v85 & 1) == 0 ) /*0x5b64331*/
                                i = 3692792907LL; /*0x5b64331*/
                            }
                          }
                          if ( (int)i > -602174390 ) /*0x5b6433d*/
                            break; /*0x5b6433d*/
                          if ( (_DWORD)i == -1110259853 ) /*0x5b64345*/
                          {
                            n0x45_4[20] = 0; /*0x5b643c9*/
                            n0x45_4[21] = 0; /*0x5b643cd*/
                            *(_BYTE *)n0x45 = 0; /*0x5b643d5*/
                            i = 3692792907LL; /*0x5b643d8*/
                          }
                          else
                          {
                            login = n0x12; /*0x5b6435d*/
                            n0x12[(_QWORD)k_1] = n0x45_4[1] ^ v84 ^ (n0x12_6 + 1) ^ 0x12; /*0x5b64368*/
                            n0x12_1 = n0x12; /*0x5b6436f*/
                            i = 1434066114; /*0x5b64373*/
                          }
                        }
                        if ( (_DWORD)i != -442371746 ) /*0x5b643a9*/
                          break; /*0x5b643a9*/
                        p_n0x12 = &n0x12; /*0x5b643ab*/
                        n0x12 = 0; /*0x5b643b3*/
                      }
                      k_2 = k; /*0x5b6442d*/
                      LODWORD(n788152950) = -1685289128; /*0x5b64434*/
                    }
                    else if ( (_DWORD)n788152950 == -1792751364 ) /*0x5b63db1*/
                    {
                      src = (void *)&v45[1]; /*0x5b63dc2*/
                      k = 496; /*0x5b63dd0*/
                      v34 = v45 + 32; /*0x5b63dd8*/
                      LODWORD(n788152950) = -1515106128; /*0x5b63df8*/
                      if ( _mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128(v45), v92)) == 0xFFFF ) /*0x5b63e02*/
                        LODWORD(n788152950) = 2112518926; /*0x5b63e02*/
                    }
                  }
                  else if ( (_DWORD)n788152950 == -2142661342 ) /*0x5b63b96*/
                  {
                    LODWORD(n788152950) = 2116396813; /*0x5b6414d*/
                  }
                  else if ( (_DWORD)n788152950 == -1909451175 ) /*0x5b63ba2*/
                  {
                    *v72 = 1; /*0x5b63baf*/
                    p_n0x12_4 = p_n0x12_1; /*0x5b63bbc*/
                    p_n0x12_5 = p_n0x12_1; /*0x5b63bca*/
                    *p_n0x12_1 = 1; /*0x5b63bd1*/
                    p_n0x12_5[1] = 12; /*0x5b63bd7*/
                    qmemcpy(p_n0x12_5 + 2, "g9%\"8`*$6,26k+/7-#u%jkq!<2&3;%;", 31); /*0x5b63bdb*/
                    p_n0x12_5[33] = 26; /*0x5b63c59*/
                    p_n0x12_5[34] = 71; /*0x5b63c5d*/
                    p_n0x12_5[35] = 39; /*0x5b63c61*/
                    p_n0x12_5[36] = 3; /*0x5b63c67*/
                    p_n0x12_5[37] = 3; /*0x5b63c6a*/
                    p_n0x12_5[38] = 25; /*0x5b63c70*/
                    p_n0x12_5[39] = 23; /*0x5b63c76*/
                    p_n0x12_5[40] = 65; /*0x5b63c79*/
                    p_n0x12_5[41] = 16; /*0x5b63c80*/
                    p_n0x12_5[42] = 9; /*0x5b63c84*/
                    p_n0x12_5[43] = 13; /*0x5b63c88*/
                    p_n0x12_5[44] = 22; /*0x5b63c8e*/
                    p_n0x12_5[45] = 0; /*0x5b63c91*/
                    p_n0x12_5[46] = 22; /*0x5b63c95*/
                    p_n0x12_5[47] = 23; /*0x5b63c98*/
                    p_n0x12_5[48] = 20; /*0x5b63c9d*/
                    p_n0x12_5[49] = 28; /*0x5b63ca2*/
                    p_n0x12_5[50] = 12; /*0x5b63ca5*/
                    p_n0x12_5[51] = 30; /*0x5b63ca9*/
                    p_n0x12_5[52] = 8; /*0x5b63cad*/
                    p_n0x12_5[53] = 82; /*0x5b63cb3*/
                    p_n0x12_5[54] = 82; /*0x5b63cb6*/
                    p_n0x12_5[55] = 81; /*0x5b63cbb*/
                    p_n0x12_5[56] = 81; /*0x5b63cbe*/
                    p_n0x12_5[57] = 2; /*0x5b63cc1*/
                    p_n0x12_5[58] = 25; /*0x5b63cc5*/
                    p_n0x12_5[59] = 20; /*0x5b63cc9*/
                    p_n0x12_5[60] = 28; /*0x5b63ccc*/
                    p_n0x12_5[61] = 90; /*0x5b63ccf*/
                    p_n0x12_5[62] = 27; /*0x5b63cd3*/
                    p_n0x12_5[63] = 68; /*0x5b63cd7*/
                    p_n0x12_5[64] = 16; /*0x5b63cdb*/
                    p_n0x12_5[65] = 108; /*0x5b63ce5*/
                    p_n0x12_5[66] = 87; /*0x5b63ce9*/
                    p_n0x12_5[67] = 124; /*0x5b63ced*/
                    p_n0x12_5[68] = 104; /*0x5b63cf1*/
                    p_n0x12_5[69] = 35; /*0x5b63cf5*/
                    p_n0x12_5[70] = 100; /*0x5b63cf9*/
                    n0x12_2 = p_n0x12_5 + 71; /*0x5b63cfd*/
                    n0x12_1 = p_n0x12_5 + 73; /*0x5b63d05*/
                    n1657293156 = 1657293156; /*0x5b63d09*/
                    while ( n1657293156 != 1053686639 ) /*0x5b63d18*/
                    {
                      *n0x12_2++ = 0; /*0x5b63d25*/
                      n1657293156 = 1657293156; /*0x5b63d2f*/
                      i = 1053686639; /*0x5b63d34*/
                      if ( n0x12_2 == n0x12_1 ) /*0x5b63d39*/
                        n1657293156 = 1053686639; /*0x5b63d39*/
                    }
                    p_n0x12_6 = p_n0x12_1; /*0x5b648f9*/
                    p_n0x12 = (char **)p_n0x12_1; /*0x5b64900*/
                    LOBYTE(n0x12_6) = *p_n0x12_1; /*0x5b6490a*/
                    for ( j = -994152388; ; j = 1880218905 ) /*0x5b6490d*/
                    {
                      while ( 1 ) /*0x5b64918*/
                      {
                        while ( j > 436352572 ) /*0x5b64918*/
                        {
                          if ( j > 1348257098 ) /*0x5b64920*/
                          {
                            if ( j == 1348257099 ) /*0x5b64975*/
                            {
                              p_n0x12_6[71] = 0; /*0x5b64a13*/
                              p_n0x12_6[72] = 0; /*0x5b64a17*/
                              *(_BYTE *)p_n0x12 = 0; /*0x5b64a1f*/
                              j = 203562583; /*0x5b64a22*/
                            }
                            else
                            {
                              LODWORD(n0x12) = (_DWORD)n0x12_1; /*0x5b64987*/
                              j = -1233702890; /*0x5b6498a*/
                            }
                          }
                          else if ( j == 436352573 ) /*0x5b64928*/
                          {
                            k_1 = &n0x45; /*0x5b649ec*/
                            n0x45 = 0; /*0x5b649fa*/
                            j = 1272364195; /*0x5b64a02*/
                          }
                          else
                          {
                            j = 1348257099; /*0x5b6493e*/
                            if ( n0x45 < 0x45 ) /*0x5b64943*/
                              j = -206214472; /*0x5b64943*/
                          }
                        }
                        if ( j > -206214473 ) /*0x5b6494f*/
                          break; /*0x5b6494f*/
                        if ( j == -1233702890 ) /*0x5b64957*/
                        {
                          login = (char *)((unsigned __int8)(-2 - (_BYTE)n0x12) & 0xD4); /*0x5b649c3*/
                          i = n0x45; /*0x5b649d6*/
                          p_n0x12_6[n0x45 + 2] ^= ((unsigned __int8)login | ((_BYTE)n0x12 + 1) & 0x2B) /*0x5b649da*/
                                                ^ p_n0x12_6[1]
                                                ^ 0x91;
                          ++n0x45; /*0x5b649de*/
                          j = 1272364195; /*0x5b649e2*/
                        }
                        else
                        {
                          j = 436352573; /*0x5b64965*/
                          if ( (n0x12_6 & 1) == 0 ) /*0x5b6496a*/
                            j = 203562583; /*0x5b6496a*/
                        }
                      }
                      if ( j != -206214472 ) /*0x5b64997*/
                        break; /*0x5b64997*/
                      n0x12_1 = (char *)n0x45; /*0x5b649a1*/
                    }
                    s_1 = p_n0x12_6 + 2; /*0x5b64a3c*/
                    p_n0x12_7 = p_n0x12_2; /*0x5b64a4a*/
                    p_n0x12_8 = p_n0x12_2; /*0x5b64a58*/
                    *p_n0x12_2 = 1; /*0x5b64a5f*/
                    p_n0x12_8[1] = 12; /*0x5b64a62*/
                    LOBYTE(login) = 57; /*0x5b64a66*/
                    qmemcpy(p_n0x12_8 + 2, "9nz~q{?yb2aa{x~fn*9\"", 20); /*0x5b64a69*/
                    LOBYTE(i) = 97; /*0x5b64a96*/
                    n0x12_3 = p_n0x12_8 + 22; /*0x5b64abc*/
                    n0x12_1 = p_n0x12_8 + 24; /*0x5b64ac4*/
                    k = 3788292950LL; /*0x5b64ac8*/
                    while ( (_DWORD)k != 1517994734 ) /*0x5b64ad3*/
                    {
                      *n0x12_3++ = 0; /*0x5b64add*/
                      k = 3788292950LL; /*0x5b64ae7*/
                      i = 1517994734; /*0x5b64aec*/
                      if ( n0x12_3 == n0x12_1 ) /*0x5b64af1*/
                        k = 1517994734; /*0x5b64af1*/
                    }
                    LODWORD(n788152950) = 1430878499; /*0x5b64af6*/
                  }
                }
                else if ( (int)n788152950 <= -1650255175 ) /*0x5b63a3f*/
                {
                  if ( (_DWORD)n788152950 == -1738556108 ) /*0x5b64041*/
                  {
                    k_3 = k_6 + 1; /*0x5b64b2a*/
                    LODWORD(n788152950) = -51024905; /*0x5b64b31*/
                  }
                  else if ( (_DWORD)n788152950 == -1685289128 ) /*0x5b6404d*/
                  {
                    k_4 = 1; /*0x5b64061*/
                    login = (_BYTE *)(&qword_58 + 1); /*0x5b6406b*/
                    sub_5545F3B(s_2, (char)v29); /*0x5b6407f*/
                    LODWORD(n788152950) = 232683021; /*0x5b640a4*/
                  }
                }
                else
                {
                  switch ( (_DWORD)n788152950 ) /*0x5b63a4b*/
                  {
                    case 0x9DA31ABA: /*0x5b63a4b*/
                      login = 0; /*0x5b64c27*/
                      memset(haystack, 0, 0x400u); /*0x5b64c29*/
                      LODWORD(n788152950) = -1428043108; /*0x5b64c40*/
                      n2 = 2; /*0x5b64c45*/
                      break;
                    case 0xA303AFC2: /*0x5b63a4b*/
                      p_n0x12_1 = &v29; /*0x5b64deb*/
                      p_n0x12_2 = &v29 - 4; /*0x5b64dfc*/
                      v53 = v39; /*0x5b64e0a*/
                      LODWORD(n788152950) = 2116396813; /*0x5b64e1b*/
                      if ( !*v39 ) /*0x5b64e18*/
                        LODWORD(n788152950) = -238376491; /*0x5b64e25*/
                      break;
                    case 0xA5B150B0: /*0x5b63a4b*/
                      LODWORD(n788152950) = 232683021; /*0x5b63a69*/
                      k_4 = 0; /*0x5b63a6e*/
                      break;
                  }
                }
              }
              if ( (int)n788152950 > 788152950 ) /*0x5b639cb*/
                break; /*0x5b639cb*/
              if ( (int)n788152950 <= (int)&byte_655E41D ) /*0x5b63b10*/
              {
                if ( (int)n788152950 > (int)&loc_4814D8B + 4 ) /*0x5b63d7c*/
                {
                  if ( (_DWORD)n788152950 == (_DWORD)&loc_4814D90 ) /*0x5b63e3d*/
                  {
                    v71 = &v29; /*0x5b64483*/
                    v56 = &v29; /*0x5b64494*/
                    p_filename = (void **)&v29; /*0x5b644a5*/
                    v74 = &v29; /*0x5b644b6*/
                    haystack_1 = (char *)&v29; /*0x5b644c9*/
                    s_3 = &v29; /*0x5b644dc*/
                    p_stream = (FILE **)&v29; /*0x5b644ed*/
                    v70 = &v29; /*0x5b644fe*/
                    logina = (void **)&v29; /*0x5b6450f*/
                    v73 = &v29; /*0x5b64520*/
                    p_n0x12_3 = &v29; /*0x5b64531*/
                    n0x45_1 = &v29 - 4; /*0x5b64542*/
                    LODWORD(n788152950) = -1560039486; /*0x5b64549*/
                  }
                  else if ( (_DWORD)n788152950 == 86511158 ) /*0x5b63e49*/
                  {
                    login = "qq"; /*0x5b63e56*/
                    LODWORD(n788152950) = -509529064; /*0x5b63e77*/
                    if ( !strstr(haystack, "qq") ) /*0x5b63e5d*/
                      LODWORD(n788152950) = 1391577108; /*0x5b63e81*/
                  }
                }
                else if ( (_DWORD)n788152950 == -51024905 ) /*0x5b63d88*/
                {
                  k_6 = k_3; /*0x5b64445*/
                  k = k_3; /*0x5b6445d*/
                  LODWORD(n788152950) = -1425534050; /*0x5b64467*/
                  if ( k_3 < v36 - 528 ) /*0x5b64471*/
                    LODWORD(n788152950) = -622888238; /*0x5b64471*/
                }
                else if ( (_DWORD)n788152950 == -24204128 ) /*0x5b63d94*/
                {
                  goto LABEL_89; /*0x5b63d94*/
                }
              }
              else if ( (int)n788152950 <= 424671077 ) /*0x5b63b1c*/
              {
                if ( (_DWORD)n788152950 == (_DWORD)::n788152950 ) /*0x5b64106*/
                {
                  *v72 = -1; /*0x5b64bd2*/
                  LODWORD(n788152950) = -24204128; /*0x5b64bd8*/
                }
                else if ( (_DWORD)n788152950 == 232683021 ) /*0x5b64112*/
                {
                  k = k_4; /*0x5b64118*/
                  LODWORD(n788152950) = 620840580; /*0x5b64120*/
                  if ( !k_4 ) /*0x5b6412a*/
                    LODWORD(n788152950) = -1738556108; /*0x5b6412a*/
                  n4 = k_4; /*0x5b6412d*/
                }
              }
              else
              {
                switch ( (_DWORD)n788152950 ) /*0x5b63b28*/
                {
                  case 0x194FF766: /*0x5b63b28*/
                    LODWORD(n788152950) = -2142661342; /*0x5b64c7d*/
                    break;
                  case 0x25014684: /*0x5b63b28*/
                    k = n4; /*0x5b64ec0*/
                    LODWORD(n788152950) = 788152951; /*0x5b64ec9*/
                    if ( n4 == 4 ) /*0x5b64ed3*/
                      LODWORD(n788152950) = -176883313; /*0x5b64ed3*/
                    n4_1 = n4; /*0x5b64ed6*/
                    break;
                  case 0x2A469344: /*0x5b63b28*/
LABEL_86:
                    haystack = haystack_1; /*0x5b6416a*/
                    login = (_BYTE *)(&stru_3F8 + 8); /*0x5b64189*/
                    LODWORD(n788152950) = -166706183; /*0x5b641a8*/
                    if ( !fgets(haystack_1, 1024, *p_stream) ) /*0x5b6418e*/
                      LODWORD(n788152950) = -1909451175; /*0x5b641b2*/
                    break;
                }
              }
            }
            if ( (int)n788152950 > 1777073725 ) /*0x5b639d7*/
              break; /*0x5b639d7*/
            if ( (int)n788152950 <= 1391577107 ) /*0x5b639e3*/
            {
              if ( (_DWORD)n788152950 == 788152951 ) /*0x5b63ef7*/
              {
                k = n4_1; /*0x5b64b00*/
                LODWORD(n788152950) = -1428043108; /*0x5b64b08*/
                if ( !n4_1 ) /*0x5b64b12*/
                  LODWORD(n788152950) = 1391577108; /*0x5b64b12*/
                n2 = n4_1; /*0x5b64b15*/
              }
              else if ( (_DWORD)n788152950 == 1124181627 ) /*0x5b63f03*/
              {
                p_filename_1 = p_filename; /*0x5b63f10*/
                n788152950 = i1_1; /*0x5b63f2c*/
                p_filename_2 = p_filename; /*0x5b63f2f*/
                *p_filename = p_filename + 2; /*0x5b63f42*/
                v11 = strlen_w("/proc/self/maps"); /*0x5b63f50*/
                p_filename_3 = p_filename_2; /*0x5b63f59*/
                i1_1 = n788152950; /*0x5b63f5c*/
                std::string::_M_construct<char const*>(p_filename_3, "/proc/self/maps", &aProcSelfMaps[v11]); /*0x5b63f68*/
                s = haystack_1; /*0x5b63f7b*/
                memset(haystack_1, 0, 0x400u); /*0x5b63f97*/
                s_5 = s_3; /*0x5b63fa3*/
                memset(s_3, 0, 0x100u); /*0x5b63fbf*/
                p_stream_1 = p_stream; /*0x5b63fcb*/
                login = "r"; /*0x5b63fe3*/
                v13 = fopen((const char *)*p_filename, "r"); /*0x5b63fea*/
                k = (unsigned __int64)p_stream; /*0x5b64001*/
                *p_stream = v13; /*0x5b64008*/
                *(_QWORD *)(k + 8) = 0; /*0x5b6400b*/
                *(_QWORD *)(k + 16) = &fclose; /*0x5b6401a*/
                LODWORD(n788152950) = 709268292; /*0x5b64029*/
                if ( !*p_stream ) /*0x5b64025*/
                  LODWORD(n788152950) = (unsigned int)::n788152950; /*0x5b64033*/
              }
            }
            else
            {
              switch ( (_DWORD)n788152950 ) /*0x5b639ef*/
              {
                case 0x52F1C814: /*0x5b639ef*/
                  n2 = 0; /*0x5b64be9*/
                  login = 0; /*0x5b64bf8*/
                  memset(haystack, 0, 0x400u); /*0x5b64bfa*/
                  LODWORD(n788152950) = -1428043108; /*0x5b64c11*/
                  break;
                case 0x55497923: /*0x5b639ef*/
                  p_n0x12_9 = p_n0x12_2; /*0x5b64c87*/
                  p_n0x12 = (char **)p_n0x12_2; /*0x5b64c8e*/
                  LOBYTE(n0x12_6) = *p_n0x12_2; /*0x5b64c98*/
                  for ( k = 1321248058; ; k = 3879402463LL ) /*0x5b64c9b*/
                  {
                    while ( 1 ) /*0x5b64cab*/
                    {
                      while ( (int)k > 1143506360 ) /*0x5b64cab*/
                      {
                        if ( (int)k > 1640434999 ) /*0x5b64cb3*/
                        {
                          if ( (_DWORD)k == 1640435000 ) /*0x5b64d13*/
                          {
                            i = n0x45; /*0x5b64d83*/
                            LOBYTE(i) = ((-2 - n0x45) & 0xE0 | (n0x45 + 1) & 0x1F) /*0x5b64da8*/
                                      ^ p_n0x12_9[1]
                                      ^ p_n0x12_9[n0x45 + 2]
                                      ^ 0xF4;
                            LOBYTE(n0x12) = i; /*0x5b64dab*/
                            login = &p_n0x12_9[n0x45 + 2]; /*0x5b64dae*/
                            n0x12_1 = login; /*0x5b64db2*/
                            k = 1143506361; /*0x5b64db6*/
                          }
                          else
                          {
                            ++n0x45; /*0x5b64d1d*/
                            k = 2925965913LL; /*0x5b64d21*/
                          }
                        }
                        else if ( (_DWORD)k == 1143506361 ) /*0x5b64cbb*/
                        {
                          i = (unsigned __int64)n0x12_1; /*0x5b64d6f*/
                          *n0x12_1 = (char)n0x12; /*0x5b64d73*/
                          k = 1802766361; /*0x5b64d75*/
                        }
                        else
                        {
                          k = 2988147870LL; /*0x5b64ccd*/
                          if ( (n0x12_6 & 1) == 0 ) /*0x5b64cd2*/
                            k = 3879402463LL; /*0x5b64cd2*/
                        }
                      }
                      if ( (int)k > -1019968017 ) /*0x5b64cde*/
                        break; /*0x5b64cde*/
                      if ( (_DWORD)k == -1369001383 ) /*0x5b64ce6*/
                      {
                        k = 3274999280LL; /*0x5b64d5f*/
                        if ( n0x45 < 0x14 ) /*0x5b64d64*/
                          k = 1640435000; /*0x5b64d64*/
                      }
                      else
                      {
                        k_1 = &n0x45; /*0x5b64cf0*/
                        n0x45 = 0; /*0x5b64cfe*/
                        k = 2925965913LL; /*0x5b64d06*/
                      }
                    }
                    if ( (_DWORD)k != -1019968016 ) /*0x5b64d31*/
                      break; /*0x5b64d31*/
                    p_n0x12_9[22] = 0; /*0x5b64d3e*/
                    p_n0x12_9[23] = 0; /*0x5b64d42*/
                    *(_BYTE *)p_n0x12 = 0; /*0x5b64d4a*/
                  }
                  v29 = p_n0x12_9 + 2; /*0x5b64dd0*/
                  LODWORD(n788152950) = -128723517; /*0x5b64dd7*/
                  break;
                case 0x56355DD1: /*0x5b639ef*/
                  v45 = (const __m128i *)(k_6 + v35); /*0x5b63a17*/
                  LODWORD(n788152950) = -1792751364; /*0x5b63a1e*/
                  break;
              }
            }
          }
          if ( (int)n788152950 > 2076341562 ) /*0x5b63b51*/
            break; /*0x5b63b51*/
          if ( (_DWORD)n788152950 == 1777073726 ) /*0x5b63e8f*/
          {
            *v64 = (__m128i)xmmword_990F60; /*0x5b64568*/
            p_si128_1 = &si128; /*0x5b6456f*/
            si128 = _mm_load_si128((const __m128i *)&xmmword_98FC90); /*0x5b6458c*/
            v52 = &v88; /*0x5b64594*/
            v51 = v71; /*0x5b645a9*/
            v50 = v56; /*0x5b645be*/
            LODWORD(n788152950) = 1124181627; /*0x5b645cc*/
          }
          else if ( (_DWORD)n788152950 == 1969045716 ) /*0x5b63e9b*/
          {
            login = (char *)p_si128; /*0x5b63ea8*/
            k_5 = _byteswap_uint64(v34->m128i_i64[0]); /*0x5b63eb2*/
            k = _byteswap_uint64(p_si128->m128i_i64[0]); /*0x5b63eb8*/
            if ( k_5 != k /*0x5b63ed3*/
              || (k_5 = _byteswap_uint64(v34->m128i_u64[1]), k = _byteswap_uint64(p_si128->m128i_u64[1]),
                                                             i = 0,
                                                             k_5 != k) )
            {
              i = 2 * (unsigned int)(k_5 >= k) - 1; /*0x5b63edf*/
            }
            i_1 = i; /*0x5b63ee1*/
            LODWORD(n788152950) = -1138025787; /*0x5b63ee7*/
          }
        }
        if ( (_DWORD)n788152950 != 2076341563 ) /*0x5b63b5d*/
          break; /*0x5b63b5d*/
        dest_1 = (char *)dest; /*0x5b645e2*/
        memcpy(dest, src, 0x1F0u); /*0x5b645ec*/
        login = dest_1; /*0x5b645f4*/
        sub_5B754F0(i1_1, dest_1, 496, ia); /*0x5b64602*/
        *v72 = 2; /*0x5b6461a*/
        p_n0x12_10 = p_n0x12_3; /*0x5b64627*/
        p_n0x12_11 = p_n0x12_3; /*0x5b64635*/
        *p_n0x12_3 = 1; /*0x5b6463c*/
        LOBYTE(login) = 12; /*0x5b6463f*/
        p_n0x12_11[1] = 12; /*0x5b64642*/
        qmemcpy(p_n0x12_11 + 2, "g9%\"8`*$6,26k+/7-#u%jkq!<2&3;%;", 31); /*0x5b64646*/
        p_n0x12_11[33] = 26; /*0x5b646c4*/
        p_n0x12_11[34] = 71; /*0x5b646c8*/
        p_n0x12_11[35] = 39; /*0x5b646cc*/
        p_n0x12_11[36] = 3; /*0x5b646d2*/
        p_n0x12_11[37] = 3; /*0x5b646d5*/
        p_n0x12_11[38] = 25; /*0x5b646db*/
        p_n0x12_11[39] = 23; /*0x5b646e1*/
        p_n0x12_11[40] = 65; /*0x5b646e4*/
        p_n0x12_11[41] = 16; /*0x5b646eb*/
        p_n0x12_11[42] = 9; /*0x5b646ef*/
        p_n0x12_11[43] = 13; /*0x5b646f3*/
        p_n0x12_11[44] = 22; /*0x5b646f9*/
        p_n0x12_11[45] = 0; /*0x5b646fc*/
        p_n0x12_11[46] = 22; /*0x5b64700*/
        p_n0x12_11[47] = 23; /*0x5b64703*/
        LOBYTE(i) = 20; /*0x5b64706*/
        p_n0x12_11[48] = 20; /*0x5b64708*/
        p_n0x12_11[49] = 28; /*0x5b6470d*/
        p_n0x12_11[50] = 12; /*0x5b64710*/
        p_n0x12_11[51] = 30; /*0x5b64714*/
        p_n0x12_11[52] = 8; /*0x5b64718*/
        p_n0x12_11[53] = 82; /*0x5b6471e*/
        p_n0x12_11[54] = 82; /*0x5b64721*/
        p_n0x12_11[55] = 81; /*0x5b64726*/
        p_n0x12_11[56] = 81; /*0x5b64729*/
        p_n0x12_11[57] = 2; /*0x5b6472c*/
        p_n0x12_11[58] = 25; /*0x5b64730*/
        p_n0x12_11[59] = 20; /*0x5b64734*/
        p_n0x12_11[60] = 28; /*0x5b64737*/
        p_n0x12_11[61] = 90; /*0x5b6473a*/
        p_n0x12_11[62] = 27; /*0x5b6473e*/
        p_n0x12_11[63] = 68; /*0x5b64742*/
        p_n0x12_11[64] = 16; /*0x5b64746*/
        p_n0x12_11[65] = 108; /*0x5b64750*/
        p_n0x12_11[66] = 87; /*0x5b64754*/
        p_n0x12_11[67] = 124; /*0x5b64758*/
        p_n0x12_11[68] = 104; /*0x5b6475c*/
        p_n0x12_11[69] = 35; /*0x5b64760*/
        p_n0x12_11[70] = 100; /*0x5b64764*/
        n0x12_4 = p_n0x12_11 + 71; /*0x5b64768*/
        n0x12_1 = p_n0x12_11 + 73; /*0x5b64770*/
        n1657293156_1 = 1657293156; /*0x5b64774*/
        while ( n1657293156_1 != 1053686639 ) /*0x5b64783*/
        {
          *n0x12_4++ = 0; /*0x5b6478c*/
          n1657293156_1 = 1657293156; /*0x5b64796*/
          i = 1053686639; /*0x5b6479b*/
          if ( n0x12_4 == n0x12_1 ) /*0x5b647a0*/
            n1657293156_1 = 1053686639; /*0x5b647a0*/
        }
        p_n0x12_12 = p_n0x12_3; /*0x5b647a5*/
        p_n0x12 = (char **)p_n0x12_3; /*0x5b647ac*/
        LOBYTE(n0x12_6) = *p_n0x12_3; /*0x5b647b6*/
        for ( k = 3300814908LL; ; k = 1880218905 ) /*0x5b647b9*/
        {
          while ( 1 ) /*0x5b647c4*/
          {
            while ( (int)k > 436352572 ) /*0x5b647c4*/
            {
              if ( (int)k > 1348257098 ) /*0x5b647cc*/
              {
                if ( (_DWORD)k == 1348257099 ) /*0x5b64821*/
                {
                  p_n0x12_12[71] = 0; /*0x5b648bf*/
                  p_n0x12_12[72] = 0; /*0x5b648c3*/
                  *(_BYTE *)p_n0x12 = 0; /*0x5b648cb*/
                  k = 203562583; /*0x5b648ce*/
                }
                else
                {
                  LODWORD(n0x12) = (_DWORD)n0x12_1; /*0x5b64833*/
                  k = 3061264406LL; /*0x5b64836*/
                }
              }
              else if ( (_DWORD)k == 436352573 ) /*0x5b647d4*/
              {
                k_1 = &n0x45; /*0x5b64898*/
                n0x45 = 0; /*0x5b648a6*/
                k = 1272364195; /*0x5b648ae*/
              }
              else
              {
                k = 1348257099; /*0x5b647ea*/
                if ( n0x45 < 0x45 ) /*0x5b647ef*/
                  k = 4088752824LL; /*0x5b647ef*/
              }
            }
            if ( (int)k > -206214473 ) /*0x5b647fb*/
              break; /*0x5b647fb*/
            if ( (_DWORD)k == -1233702890 ) /*0x5b64803*/
            {
              login = (char *)((unsigned __int8)(-2 - (_BYTE)n0x12) & 0xD4); /*0x5b6486f*/
              i = n0x45; /*0x5b64882*/
              p_n0x12_12[n0x45 + 2] ^= ((unsigned __int8)login | ((_BYTE)n0x12 + 1) & 0x2B) ^ p_n0x12_12[1] ^ 0x91; /*0x5b64886*/
              ++n0x45; /*0x5b6488a*/
              k = 1272364195; /*0x5b6488e*/
            }
            else
            {
              k = 436352573; /*0x5b64811*/
              if ( (n0x12_6 & 1) == 0 ) /*0x5b64816*/
                k = 203562583; /*0x5b64816*/
            }
          }
          if ( (_DWORD)k != -206214472 ) /*0x5b64843*/
            break; /*0x5b64843*/
          n0x12_1 = (char *)n0x45; /*0x5b6484d*/
        }
        s_2 = p_n0x12_12 + 2; /*0x5b648e8*/
        LODWORD(n788152950) = -1905020921; /*0x5b648ef*/
      }
      if ( (_DWORD)n788152950 != 2112518926 ) /*0x5b63b69*/
        break; /*0x5b63b69*/
      p_si128 = &si128; /*0x5b63b73*/
      LODWORD(n788152950) = 1969045716; /*0x5b63b7a*/
    }
  }
  while ( (_DWORD)n788152950 != 2116396813 ); /*0x5b64ee7*/
  return __readfsqword(0x28u); /*0x5b64efc*/
}
