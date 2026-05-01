// 0x557566C @ 0x557566C
// The function seems has been flattened
unsigned __int64 __fastcall sub_557566C(
        _QWORD *dest,
        int n58,
        __m128 a3,
        __m128 a4,
        __m128 a5,
        __m128 a6,
        __m128 a7,
        __m128 a8,
        __m128 a9,
        __m128 a10)
{
  unsigned __int64 j_5; // r13
  unsigned __int64 n0x81_1; // r15
  char *p_k_1; // rax
  char *i_3; // rax
  int n364817133; // edx
  const char *s1; // r14
  const char *s2; // rbp
  size_t n_1; // rax
  __int64 n148; // rsi
  __int64 v19; // rdx
  __int64 v20; // rax
  char v21; // cl
  __int64 v22; // r9
  __m128 v23; // xmm4
  __m128 v24; // xmm5
  int n1593566315; // ecx
  _BYTE *nn_6; // rax
  int v27; // ecx
  _BYTE *nn_5; // rax
  int n2026163102; // ecx
  _BYTE *nn_3; // rax
  int v31; // ecx
  char *v32; // rax
  int n1143292907; // ecx
  _BYTE *j_1; // rax
  int v35; // ecx
  _BYTE *nn_2; // rax
  size_t v37; // rax
  unsigned __int64 jj; // rbp
  char v39; // bl
  unsigned __int64 j_3; // rbp
  char v41; // bl
  unsigned __int64 ii; // rbp
  char v43; // bl
  unsigned __int64 n0x81; // rbp
  char v45; // bl
  __m128 v46; // xmm4
  __m128 v47; // xmm5
  int v48; // ecx
  char *v49; // rax
  int n688378388; // ecx
  _BYTE *j_4; // rax
  char *v52; // rax
  __m128 v53; // xmm4
  __m128 v54; // xmm5
  int v55; // ecx
  char *v56; // rax
  int v57; // ecx
  char *m_2; // rax
  size_t v59; // rax
  void *n1448808005; // rbx
  unsigned int v61; // ebp
  __int64 v62; // rdx
  __int64 v63; // rcx
  __int64 v64; // r13
  void *v65; // rdi
  __int64 v66; // rdi
  void *v67; // rax
  const char *s_5; // rbp
  size_t v69; // rax
  __int64 v70; // rbp
  size_t v71; // rax
  __int64 v72; // rax
  const char *s_6; // rbx
  size_t v74; // rax
  const char *s_7; // rbx
  __int64 v76; // rbp
  size_t v77; // rax
  __int64 v78; // rbx
  size_t v79; // rax
  size_t *i_4; // rax
  size_t v81; // rcx
  const char *s_8; // rbx
  __int64 v83; // r13
  size_t v84; // rax
  const char *s_9; // rbx
  __int64 v86; // rbp
  size_t v87; // rax
  char v89; // [rsp+0h] [rbp-548h]
  char v90; // [rsp+0h] [rbp-548h]
  unsigned __int64 jj_1; // [rsp+8h] [rbp-540h]
  unsigned __int64 n0x7F; // [rsp+8h] [rbp-540h]
  const char **p_s; // [rsp+20h] [rbp-528h]
  unsigned int v94; // [rsp+34h] [rbp-514h]
  _QWORD *v95; // [rsp+38h] [rbp-510h]
  int v97; // [rsp+5Ch] [rbp-4ECh]
  __int64 *v98; // [rsp+60h] [rbp-4E8h]
  __int64 v99; // [rsp+C8h] [rbp-480h]
  pthread_mutex_t *mutex; // [rsp+E8h] [rbp-460h]
  void *nn_4; // [rsp+F0h] [rbp-458h]
  _QWORD *k_2; // [rsp+F8h] [rbp-450h]
  const char *s_2; // [rsp+100h] [rbp-448h]
  _BYTE *v104; // [rsp+108h] [rbp-440h]
  __int64 v105; // [rsp+110h] [rbp-438h]
  __int64 v106; // [rsp+118h] [rbp-430h]
  unsigned __int64 n4; // [rsp+120h] [rbp-428h]
  char *s; // [rsp+128h] [rbp-420h]
  time_t v109; // [rsp+130h] [rbp-418h]
  char *s_4; // [rsp+138h] [rbp-410h]
  _QWORD *s_ouko2rvntz_; // [rsp+140h] [rbp-408h]
  int *v112; // [rsp+148h] [rbp-400h]
  _BYTE *v113; // [rsp+150h] [rbp-3F8h]
  void **i; // [rsp+168h] [rbp-3E0h] BYREF
  char v115; // [rsp+170h] [rbp-3D8h] BYREF
  __int64 v116; // [rsp+178h] [rbp-3D0h]
  char *v117; // [rsp+180h] [rbp-3C8h]
  __int64 v118; // [rsp+190h] [rbp-3B8h]
  unsigned __int64 k; // [rsp+198h] [rbp-3B0h] BYREF
  int v120; // [rsp+1A0h] [rbp-3A8h] BYREF
  __int64 n148_3; // [rsp+1A8h] [rbp-3A0h]
  int *v122; // [rsp+1B0h] [rbp-398h]
  int *v123; // [rsp+1B8h] [rbp-390h]
  __int64 v124; // [rsp+1C0h] [rbp-388h]
  __int64 v125; // [rsp+1C8h] [rbp-380h]
  char *v126; // [rsp+1D0h] [rbp-378h]
  void (__fastcall ***v127)(void **); // [rsp+1D8h] [rbp-370h] BYREF
  void (__fastcall ***v128)(void **); // [rsp+1E0h] [rbp-368h]
  char **m_1; // [rsp+1E8h] [rbp-360h] BYREF
  unsigned __int64 mm; // [rsp+1F0h] [rbp-358h]
  char *kk; // [rsp+1F8h] [rbp-350h] BYREF
  unsigned __int64 nn; // [rsp+200h] [rbp-348h] BYREF
  unsigned __int64 m; // [rsp+208h] [rbp-340h] BYREF
  void *nn_1; // [rsp+210h] [rbp-338h] BYREF
  _QWORD s_ouko2rvntz__32[3]; // [rsp+218h] [rbp-330h] BYREF
  void *v136; // [rsp+230h] [rbp-318h] BYREF
  _QWORD s1_8_3y_zddgga_b(&4(___2_[3]; // [rsp+238h] [rbp-310h] BYREF
  void *v138; // [rsp+250h] [rbp-2F8h] BYREF
  __int128 v139; // [rsp+258h] [rbp-2F0h] BYREF
  char n2; // [rsp+268h] [rbp-2E0h]
  char n75; // [rsp+269h] [rbp-2DFh]
  char v142; // [rsp+26Ah] [rbp-2DEh] BYREF
  char v143; // [rsp+26Bh] [rbp-2DDh]
  _BYTE v144[4]; // [rsp+26Ch] [rbp-2DCh] BYREF
  void *desta; // [rsp+270h] [rbp-2D8h]
  __int128 v146; // [rsp+278h] [rbp-2D0h] BYREF
  void *v147; // [rsp+290h] [rbp-2B8h] BYREF
  __int64 v148; // [rsp+298h] [rbp-2B0h]
  _BYTE v149[16]; // [rsp+2A0h] [rbp-2A8h] BYREF
  int n4_1; // [rsp+2B0h] [rbp-298h]
  _BYTE *v151; // [rsp+2B8h] [rbp-290h] BYREF
  __int64 v152; // [rsp+2C0h] [rbp-288h]
  _BYTE v153[16]; // [rsp+2C8h] [rbp-280h] BYREF
  void *p_k; // [rsp+2D8h] [rbp-270h] BYREF
  __int64 v155; // [rsp+2E0h] [rbp-268h]
  char n80; // [rsp+2E8h] [rbp-260h] BYREF
  char n5; // [rsp+2E9h] [rbp-25Fh] BYREF
  char n31; // [rsp+2EAh] [rbp-25Eh]
  _BYTE i_2[13]; // [rsp+2EBh] [rbp-25Dh] BYREF
  void *v160; // [rsp+2F8h] [rbp-250h] BYREF
  _QWORD s1_8_3y_zddgga_b(&4(___2__1[3]; // [rsp+300h] [rbp-248h] BYREF
  void *v162; // [rsp+318h] [rbp-230h]
  __int128 v163; // [rsp+320h] [rbp-228h] BYREF
  char n2_1; // [rsp+330h] [rbp-218h]
  char n75_1; // [rsp+331h] [rbp-217h]
  _BYTE nn_7[2]; // [rsp+332h] [rbp-216h] BYREF
  char v167; // [rsp+334h] [rbp-214h] BYREF
  void *v168; // [rsp+338h] [rbp-210h]
  __int64 v169; // [rsp+340h] [rbp-208h]
  _BYTE v170[16]; // [rsp+348h] [rbp-200h] BYREF
  void *v171[2]; // [rsp+358h] [rbp-1F0h] BYREF
  char v172; // [rsp+368h] [rbp-1E0h] BYREF
  char v173; // [rsp+378h] [rbp-1D0h] BYREF
  _BYTE _YF@_tMFZQ]_[13]; // [rsp+379h] [rbp-1CFh] BYREF
  _BYTE S_n[2]; // [rsp+386h] [rbp-1C2h] BYREF
  _BYTE nn_10[2]; // [rsp+388h] [rbp-1C0h] BYREF
  char v177; // [rsp+38Ah] [rbp-1BEh] BYREF
  void *i_1; // [rsp+390h] [rbp-1B8h] BYREF
  size_t n[2]; // [rsp+398h] [rbp-1B0h] BYREF
  char n67; // [rsp+3A8h] [rbp-1A0h]
  char n19; // [rsp+3A9h] [rbp-19Fh]
  char n14; // [rsp+3AAh] [rbp-19Eh]
  char v183; // [rsp+3ABh] [rbp-19Dh]
  char n20; // [rsp+3ACh] [rbp-19Ch]
  char v185; // [rsp+3ADh] [rbp-19Bh]
  char n9; // [rsp+3AEh] [rbp-19Ah]
  char n23; // [rsp+3AFh] [rbp-199h]
  char n9_1; // [rsp+3B0h] [rbp-198h]
  char n40; // [rsp+3B1h] [rbp-197h]
  char n117; // [rsp+3B2h] [rbp-196h]
  char n21; // [rsp+3B3h] [rbp-195h]
  _BYTE _11_%s1_8_3y_zddgga_b(&4(___2___T[40]; // [rsp+3B4h] [rbp-194h] BYREF
  _BYTE TR@__WNu]GDKC[14]; // [rsp+3DCh] [rbp-16Ch] BYREF
  _BYTE nn_9[2]; // [rsp+3EAh] [rbp-15Eh] BYREF
  char v195; // [rsp+3ECh] [rbp-15Ch] BYREF
  void *n1448808005_1; // [rsp+3F0h] [rbp-158h] BYREF
  __int64 v197; // [rsp+3F8h] [rbp-150h]
  char v198; // [rsp+400h] [rbp-148h] BYREF
  char *s_1; // [rsp+410h] [rbp-138h] BYREF
  __int64 v200; // [rsp+418h] [rbp-130h]
  _BYTE s_3[16]; // [rsp+420h] [rbp-128h] BYREF
  _BYTE k_1[40]; // [rsp+430h] [rbp-118h] BYREF
  _BYTE @TLO[4]; // [rsp+458h] [rbp-F0h] BYREF
  _BYTE nn_8[2]; // [rsp+45Ch] [rbp-ECh] BYREF
  char v205; // [rsp+45Eh] [rbp-EAh] BYREF
  void *n148_1[2]; // [rsp+460h] [rbp-E8h] BYREF
  char v207[16]; // [rsp+470h] [rbp-D8h] BYREF
  char kk_1[8]; // [rsp+480h] [rbp-C8h] BYREF
  _BYTE LU_V_QFEVOL_n[14]; // [rsp+488h] [rbp-C0h] BYREF
  char AKA[9]; // [rsp+496h] [rbp-B2h] BYREF
  char v211; // [rsp+49Fh] [rbp-A9h] BYREF
  void *n148_2[2]; // [rsp+4A0h] [rbp-A8h] BYREF
  __m128 v213; // [rsp+4B0h] [rbp-98h] BYREF
  _BYTE v214[40]; // [rsp+4C0h] [rbp-88h] BYREF
  char v215; // [rsp+4E8h] [rbp-60h]
  char v216; // [rsp+4E9h] [rbp-5Fh] BYREF
  void *j; // [rsp+4F0h] [rbp-58h] BYREF
  unsigned __int64 n0x81_2; // [rsp+4F8h] [rbp-50h]
  _BYTE j_2[16]; // [rsp+500h] [rbp-48h] BYREF
  unsigned __int64 v220; // [rsp+510h] [rbp-38h]

  v220 = __readfsqword(0x28u); /*0x557568b*/
  nn_1 = (void *)0x39617B7C603E2301LL; /*0x557569b*/
  qmemcpy(s_ouko2rvntz__32, "s}ouko2rvntz,|32", 16); /*0x55756bb*/
  s_ouko2rvntz__32[2] = 0x7C626A7F6B657828LL; /*0x55756fe*/
  v136 = (void *)0x4E405A5A7E1E4362LL; /*0x557571f*/
  s1_8_3y_zddgga_b(&4(___2_[0] = 0x707678687F7E7E18LL; /*0x557573f*/
  LOWORD(s1_8_3y_zddgga_b(&4(___2_[1]) = 3659; /*0x557575b*/
  qmemcpy((char *)&s1_8_3y_zddgga_b(&4(___2_[1] + 2, "BRS", 3); /*0x5575763*/
  p_k_1 = (char *)&s1_8_3y_zddgga_b(&4(___2_[1] + 5; /*0x557576f*/
  p_k = (char *)&s1_8_3y_zddgga_b(&4(___2_[1] + 7; /*0x557577f*/
  do /*0x55757b4*/
    *p_k_1++ = 0; /*0x55757a1*/
  while ( p_k_1 != p_k ); /*0x55757b4*/
  k = (unsigned __int64)&nn_1; /*0x55757c1*/
  LOBYTE(j) = (_BYTE)nn_1; /*0x55757d3*/
  if ( ((unsigned __int8)j & 1) != 0 ) /*0x55758dc*/
  {
    *(_QWORD *)v214 = &i; /*0x557581d*/
    for ( i = 0; (unsigned __int64)i < 0x33; i = (void **)((char *)i + 1) ) /*0x557582d*/
    {
      i_1 = i; /*0x5575953*/
      *(_DWORD *)k_1 = (_DWORD)i; /*0x55758aa*/
      p_k = (char *)&nn_1 + 2; /*0x55758b1*/
      *((_BYTE *)i + (_QWORD)&nn_1 + 2) ^= (((_BYTE)i + 1) & ~BYTE1(nn_1) | BYTE1(nn_1) & (-2 - (_BYTE)i)) ^ 0x33; /*0x5575936*/
    }
    *(_WORD *)((char *)&s1_8_3y_zddgga_b(&4(___2_[1] + 5) = 0; /*0x5575864*/
    *(_BYTE *)k = 0; /*0x557587c*/
  }
  p_k = (void *)0x4F5D494B5E582301LL; /*0x5575995*/
  v155 = 0x7011A48404B4D0BLL; /*0x55759b4*/
  n80 = 80; /*0x55759d2*/
  i_3 = &n5; /*0x55759d6*/
  i_1 = i_2; /*0x55759e6*/
  n364817133 = 364817133; /*0x55759ee*/
  while ( n364817133 != -1603741965 ) /*0x55759fe*/
  {
    *i_3++ = 0; /*0x5575a08*/
    n364817133 = 364817133; /*0x5575a16*/
    if ( i_3 == i_1 ) /*0x5575a1b*/
      n364817133 = -1603741965; /*0x5575a1b*/
  }
  *(_QWORD *)k_1 = &p_k; /*0x5575a28*/
  LOBYTE(n148_1[0]) = (_BYTE)p_k; /*0x5575a3a*/
  if ( ((__int64)n148_1[0] & 1) != 0 ) /*0x5575b55*/
  {
    i = &j; /*0x5575b16*/
    for ( j = 0; (unsigned __int64)j < 0xF; j = (char *)j + 1 ) /*0x5575b26*/
    {
      LODWORD(n148_2[0]) = (_DWORD)j; /*0x5575a8b*/
      k = (unsigned __int64)&p_k + 2; /*0x5575a9a*/
      *(_QWORD *)v214 = (char *)j + (_QWORD)&p_k + 2; /*0x5575ab2*/
      *((_BYTE *)j + (_QWORD)&p_k + 2) ^= ((_BYTE)j + 1) ^ BYTE1(p_k) ^ 0xF; /*0x5575b8f*/
      i_1 = j; /*0x5575ba2*/
    }
    n5 = 0; /*0x5575bd6*/
    n31 = 0; /*0x5575bdd*/
    **(_BYTE **)k_1 = 0; /*0x5575bec*/
  }
  p_s = (const char **)(dest + 3); /*0x5575c0e*/
  sub_5545F3B( /*0x5575c37*/
    (char *)&nn_1 + 2,
    218,
    (const char *)&p_k + 2,
    (__int64)"[FGESDK]",
    1u,
    dest[3],
    a3,
    a4,
    a5,
    a6,
    a7,
    a8,
    a9,
    a10,
    v89);
  s1 = (const char *)dest[3]; /*0x5575c41*/
  s2 = (const char *)*((_QWORD *)sub_5564244() + 12); /*0x5575c49*/
  n_1 = strlen((const char *)dest[3]); /*0x5575c55*/
  n148 = (__int64)s2; /*0x5575c5d*/
  if ( !strncmp(s1, s2, n_1) ) /*0x5575cad*/
    goto LABEL_302; /*0x5575cad*/
  v20 = sub_5564328(s1, s2, v19, 2906748372LL); /*0x5575cb2*/
  v104 = (_BYTE *)(v20 + 264); /*0x5575cd9*/
  s_2 = (const char *)(v20 + 266); /*0x5575ce8*/
  v106 = v20 + 16; /*0x5575cf4*/
  v98 = (__int64 *)(v20 + 64); /*0x5575d00*/
  k_2 = (_QWORD *)(v20 + 104); /*0x5575d09*/
  nn_4 = (void *)(v20 + 240); /*0x5575d18*/
  v95 = (_QWORD *)v20; /*0x5575d20*/
  mutex = (pthread_mutex_t *)(v20 + 384); /*0x5575d2c*/
LABEL_44:
  sub_55880A2(mutex); /*0x5575edc*/
LABEL_62:
  if ( !v98[1] ) /*0x55763e5*/
  {
LABEL_55:
    i_1 = (void *)0x520A10170B552301LL; /*0x557602c*/
    n[0] = 0x195904001E041618LL; /*0x5576086*/
    n[1] = 0x59581747111F051DLL; /*0x55760d1*/
    n67 = 67; /*0x5576115*/
    n19 = 19; /*0x557611d*/
    n14 = 14; /*0x5576125*/
    v183 = 0; /*0x557612d*/
    n20 = 20; /*0x5576134*/
    v185 = 1; /*0x557613c*/
    n9 = 9; /*0x5576145*/
    n23 = 23; /*0x557614c*/
    n9_1 = 9; /*0x5576153*/
    n40 = 40; /*0x557615c*/
    n117 = 117; /*0x5576165*/
    n21 = 21; /*0x557616c*/
    qmemcpy(_11_%s1_8_3y_zddgga_b(&4(___2___T, "11+%s1'8<3y{zddgga`b(&4(#\"2*/^T", 31); /*0x5576176*/
    _11_%s1_8_3y_zddgga_b(&4(___2___T[31] = 22; /*0x557627a*/
    _11_%s1_8_3y_zddgga_b(&4(___2___T[32] = 81; /*0x5576284*/
    _11_%s1_8_3y_zddgga_b(&4(___2___T[33] = 81; /*0x557628b*/
    _11_%s1_8_3y_zddgga_b(&4(___2___T[34] = 93; /*0x5576295*/
    _11_%s1_8_3y_zddgga_b(&4(___2___T[35] = 81; /*0x557629d*/
    _11_%s1_8_3y_zddgga_b(&4(___2___T[36] = 73; /*0x55762a4*/
    _11_%s1_8_3y_zddgga_b(&4(___2___T[37] = 87; /*0x55762ae*/
    _11_%s1_8_3y_zddgga_b(&4(___2___T[38] = 87; /*0x55762b5*/
    _11_%s1_8_3y_zddgga_b(&4(___2___T[39] = 30; /*0x55762bc*/
    qmemcpy(TR@__WNu]GDKC, "TR@\\WNu]GDKC", 12); /*0x55762c4*/
    TR@__WNu]GDKC[12] = 2; /*0x5576322*/
    TR@__WNu]GDKC[13] = 75; /*0x557632a*/
    nn_1 = &v195; /*0x5576339*/
    v27 = -945584324; /*0x5576341*/
    nn_5 = nn_9; /*0x5576346*/
    while ( v27 != -1488304518 ) /*0x5576354*/
    {
      *nn_5++ = 0; /*0x5576362*/
      v27 = -945584324; /*0x5576370*/
      if ( nn_5 == nn_1 ) /*0x557637a*/
        v27 = -1488304518; /*0x557637a*/
    }
    i = &i_1; /*0x5576404*/
    LOBYTE(n148_2[0]) = (_BYTE)i_1; /*0x5576416*/
    if ( ((__int64)n148_2[0] & 1) != 0 ) /*0x5576519*/
    {
      k = (unsigned __int64)k_1; /*0x557644e*/
      for ( *(_QWORD *)k_1 = 0; *(_QWORD *)k_1 < 0x58u; ++*(_QWORD *)k_1 ) /*0x557645e*/
      {
        LODWORD(j) = *(_DWORD *)k_1; /*0x55764d8*/
        *(_QWORD *)v214 = (char *)&i_1 + 2; /*0x55764df*/
        p_k = *(void **)k_1; /*0x55764ef*/
        *((_BYTE *)&i_1 + *(_QWORD *)k_1 + 2) ^= ((30 - k_1[0]) & 0x1B | (k_1[0] + 1) & 0xE4) ^ BYTE1(i_1) ^ 0x43; /*0x557656b*/
        nn_1 = (void *)(*(_QWORD *)k_1 + 1LL); /*0x5576579*/
      }
      nn_9[0] = 0; /*0x5576498*/
      nn_9[1] = 0; /*0x557649f*/
      *(_BYTE *)i = 0; /*0x55764ae*/
    }
    s = (char *)&i_1 + 2; /*0x55765c9*/
LABEL_46:
    v173 = 1; /*0x5575f21*/
    qmemcpy(_YF@_tMFZQ]_, "#YF@\tMFZQ]", 10); /*0x5575f2e*/
    _YF@_tMFZQ]_[10] = 6; /*0x5575f7e*/
    _YF@_tMFZQ]_[11] = 14; /*0x5575f86*/
    _YF@_tMFZQ]_[12] = 4; /*0x5575f8e*/
    qmemcpy(S_n, "S\n", sizeof(S_n)); /*0x5575f96*/
    nn_1 = &v177; /*0x5575fae*/
    n1593566315 = 1593566315; /*0x5575fb6*/
    nn_6 = nn_10; /*0x5575fbb*/
    while ( n1593566315 != -1409995595 ) /*0x5575fc9*/
    {
      *nn_6++ = 0; /*0x5575fd7*/
      n1593566315 = 1593566315; /*0x5575fe5*/
      if ( nn_6 == nn_1 ) /*0x5575fef*/
        n1593566315 = -1409995595; /*0x5575fef*/
    }
LABEL_74:
    *(_QWORD *)v214 = &v173; /*0x5576604*/
    k_1[0] = v173; /*0x557661e*/
    if ( (v173 & 1) != 0 ) /*0x55766ab*/
    {
      p_k = &k; /*0x55766c6*/
      for ( k = 0; k < 0xE; ++k ) /*0x55766d6*/
      {
        LODWORD(i) = k; /*0x5576671*/
        nn_1 = &_YF@_tMFZQ]_[1]; /*0x5576678*/
        _YF@_tMFZQ]_[k + 1] ^= ((k + 1) & ~_YF@_tMFZQ]_[0] | _YF@_tMFZQ]_[0] & (-2 - k)) ^ 0xE; /*0x5576763*/
      }
      nn_10[0] = 0; /*0x55766f6*/
      nn_10[1] = 0; /*0x55766fd*/
      **(_BYTE **)v214 = 0; /*0x557670c*/
    }
    n148 = 148; /*0x55767b2*/
    sub_5545F3B(s, 148, &_YF@_tMFZQ]_[1], (__int64)"[FGESDK]", 2u, *v98, a3, a4, a5, a6, v23, v24, a9, a10, v90); /*0x55767c9*/
    goto LABEL_299; /*0x55767e8*/
  }
LABEL_36:
  n4 = v98[1]; /*0x5575e64*/
LABEL_52:
  if ( n4 < 4 ) /*0x5576019*/
    goto LABEL_55; /*0x5576019*/
LABEL_72:
  if ( (v95[12] & 1) != 0 ) /*0x55765fc*/
    goto LABEL_23; /*0x55765fc*/
LABEL_61:
  v109 = time(0); /*0x55763b2*/
LABEL_255:
  while ( *v95 )
  {
LABEL_125:
    v120 = 0; /*0x55776aa*/
    n148_3 = 0; /*0x55776cf*/
    v122 = &v120; /*0x55776df*/
    v123 = &v120; /*0x55776e7*/
    v124 = 0; /*0x55776ef*/
    v94 = (*(__int64 (__fastcall **)(_QWORD))(*(_QWORD *)*v95 + 16LL))(*v95); /*0x5577708*/
    if ( v94 ) /*0x557771b*/
    {
LABEL_99:
      nn_1 = (void *)0x520A10170B552301LL; /*0x5576b14*/
      s_ouko2rvntz__32[0] = 0x195904001E041618LL; /*0x5576b5c*/
      s_ouko2rvntz__32[1] = 0x59581747111F051DLL; /*0x5576ba6*/
      s_ouko2rvntz__32[2] = 0x17090114000E1343LL; /*0x5576bea*/
      v136 = (void *)0x252B313115752809LL; /*0x5576c29*/
      qmemcpy(s1_8_3y_zddgga_b(&4(___2_, "s1'8<3y{zddgga`b(&4(#\"2*", sizeof(s1_8_3y_zddgga_b(&4(___2_)); /*0x5576c6a*/
      v138 = (void *)0x515D515116545E2FLL; /*0x5576d27*/
      LODWORD(v139) = 509040457; /*0x5576d67*/
      qmemcpy((char *)&v139 + 4, "TR@\\WNu]GDKC", 12); /*0x5576d87*/
      n2 = 2; /*0x5576df0*/
      n75 = 75; /*0x5576df8*/
      *(_QWORD *)v214 = v144; /*0x5576e07*/
      v31 = -945584324; /*0x5576e0f*/
      v32 = &v142; /*0x5576e14*/
      while ( v31 != -1488304518 ) /*0x5576e48*/
      {
        *v32++ = 0; /*0x5576e52*/
        v31 = -945584324; /*0x5576e60*/
        if ( v32 == *(char **)v214 ) /*0x5576e6a*/
          v31 = -1488304518; /*0x5576e6a*/
      }
      *(_QWORD *)kk_1 = &nn_1; /*0x5576e6f*/
      LOBYTE(nn) = (_BYTE)nn_1; /*0x5576e81*/
      if ( (nn & 1) != 0 ) /*0x5576f7c*/
      {
        n148_1[0] = &m; /*0x5576eb3*/
        for ( m = 0; m < 0x58; ++m ) /*0x5576ec3*/
        {
          n148_2[0] = (char *)&nn_1 + 2; /*0x5576f42*/
          j = (void *)m; /*0x5576f52*/
          *((_BYTE *)&nn_1 + m + 2) ^= ((30 - m) & 0x1B | (m + 1) & 0xE4) ^ BYTE1(nn_1) ^ 0x43; /*0x5576fcb*/
          *(_QWORD *)v214 = m + 1; /*0x5576fda*/
        }
        v142 = 0; /*0x5576efb*/
        v143 = 0; /*0x5576f03*/
        **(_BYTE **)kk_1 = 0; /*0x5576f13*/
      }
      v214[0] = 1; /*0x557702b*/
      qmemcpy(&v214[1], "#dv`cwe!jjzdin(`xq{5try}{{==h~lZICA", 35); /*0x5577033*/
      v214[36] = 31; /*0x557714a*/
      v214[37] = 7; /*0x5577152*/
      v214[38] = 71; /*0x557715a*/
      j = &v216; /*0x557716a*/
      n1143292907 = 1143292907; /*0x5577172*/
      j_1 = &v214[39]; /*0x5577177*/
      while ( n1143292907 != 1528955398 ) /*0x557718d*/
      {
        *j_1++ = 0; /*0x5577197*/
        n1143292907 = 1143292907; /*0x55771a5*/
        if ( j_1 == j ) /*0x55771af*/
          n1143292907 = 1528955398; /*0x55771af*/
      }
      n148_1[0] = v214; /*0x55771bc*/
      if ( (v214[0] & 1) != 0 ) /*0x55772bb*/
      {
        n148_2[0] = kk_1; /*0x55772c4*/
        for ( *(_QWORD *)kk_1 = 0; *(_QWORD *)kk_1 < 0x25u; ++*(_QWORD *)kk_1 ) /*0x55772d4*/
        {
          j = &v214[2]; /*0x5577272*/
          LOBYTE(m) = v214[1] ^ v214[*(_QWORD *)kk_1 + 2] ^ (kk_1[0] + 1) ^ 0x25; /*0x5577299*/
          v214[*(_QWORD *)kk_1 + 2] = m; /*0x5577242*/
        }
        v214[39] = 0; /*0x55772f2*/
        v215 = 0; /*0x55772fa*/
        *(_BYTE *)n148_1[0] = 0; /*0x557730a*/
      }
      sub_5545F3B( /*0x557733b*/
        (char *)&nn_1 + 2,
        249,
        &v214[2],
        (__int64)"[FGESDK]",
        2u,
        v94,
        a3,
        a4,
        a5,
        a6,
        v23,
        v24,
        a9,
        a10,
        v90);
      goto LABEL_84; /*0x5579005*/
    }
LABEL_253:
    if ( !v124 ) /*0x557901d*/
      goto LABEL_84; /*0x557901d*/
LABEL_135:
    sub_55A798E(&i, &k); /*0x55778f1*/
LABEL_141:
    if ( !v118 ) /*0x557796d*/
    {
LABEL_168:
      s_1 = s_3; /*0x5577c3a*/
      v37 = strlen_w(&s_); /*0x5577c54*/
      std::string::_M_construct<char const*>(&s_1, &s_, &s_ + v37); /*0x5577c68*/
      goto LABEL_136; /*0x5577c72*/
    }
LABEL_167:
    v126 = v117; /*0x5577c08*/
LABEL_161:
    nn_1 = &off_78E94A8; /*0x5577a7f*/
    a3 = 0; /*0x5577aac*/
    memset(s_ouko2rvntz__32, 0, sizeof(s_ouko2rvntz__32)); /*0x5577aaf*/
    v136 = &s1_8_3y_zddgga_b(&4(___2_[1]; /*0x5577aba*/
    s1_8_3y_zddgga_b(&4(___2_[0] = 0; /*0x5577ac2*/
    LOBYTE(s1_8_3y_zddgga_b(&4(___2_[1]) = 0; /*0x5577aca*/
    v99 = v106; /*0x5577af2*/
    v125 = sub_55A7366(v106, v98); /*0x5577b0c*/
LABEL_159:
    if ( v125 != v99 + 8 ) /*0x5577a77*/
LABEL_151:
      std::string::_M_assign(&v136, v125 + 72); /*0x55779e7*/
LABEL_157:
    while ( v126 != &v115 ) /*0x5577a51*/
    {
LABEL_169:
      s_ouko2rvntz_ = s_ouko2rvntz__32; /*0x5577c77*/
      v112 = (int *)(v126 + 32); /*0x5577cab*/
LABEL_147:
      v97 = *v112; /*0x557799a*/
      v113 = v126 + 32; /*0x55779b4*/
LABEL_162:
      n148_2[0] = &v213; /*0x5577b1e*/
      std::string::_M_construct<char *>(n148_2, *((_QWORD *)v113 + 1), *((_QWORD *)v113 + 1) + *((_QWORD *)v113 + 2)); /*0x5577b49*/
      *(_QWORD *)v214 = &off_78E9460; /*0x5577b59*/
      *(_DWORD *)&v214[8] = v97; /*0x5577b61*/
      *(_QWORD *)&v214[16] = &v214[32]; /*0x5577b70*/
      std::string::_M_construct<char *>(&v214[16], n148_2[0], (char *)n148_2[0] + (unsigned __int64)n148_2[1]); /*0x5577b93*/
      sub_55A73D2(s_ouko2rvntz_, v214); /*0x5577ba8*/
      *(_QWORD *)v214 = &off_78E9460; /*0x5577bad*/
      if ( *(_BYTE **)&v214[16] != &v214[32] ) /*0x5577bc0*/
        operator delete(*(void **)&v214[16]); /*0x5577bc2*/
      if ( n148_2[0] != &v213 ) /*0x5577bda*/
        operator delete(n148_2[0]); /*0x5577bdc*/
      v126 = (char *)std::_Rb_tree_increment(v126); /*0x5577bf6*/
    }
LABEL_172:
    s_1 = s_3; /*0x5577ccd*/
    v200 = 0; /*0x5577cdd*/
    s_3[0] = 0; /*0x5577ce9*/
    m_1 = &s_1; /*0x5577d11*/
    v128 = (void (__fastcall ***)(void **))s_ouko2rvntz__32[0]; /*0x5577d46*/
    mm = s_ouko2rvntz__32[1]; /*0x5577d99*/
    kk = (char *)&v127; /*0x5577da9*/
    v127 = (void (__fastcall ***)(void **))s_ouko2rvntz__32[1]; /*0x55785a4*/
    while ( v128 != v127 )
    {
      (**v128)(&j); /*0x55781b9*/
      if ( n0x81_2 )
      {
        for ( ii = 10; ; ii = nn )
        {
          n148_1[0] = (void *)ii; /*0x5578251*/
          v43 = ii < 0x81 ? ii : (unsigned __int8)ii | 0x80u;
          nn = (unsigned __int64)n148_1[0] >> 7; /*0x557832e*/
          sub_558672E(m_1, (unsigned int)v43); /*0x557834e*/
          if ( nn <= 0x7F ) /*0x5578369*/
            break; /*0x5578369*/
        }
        if ( nn ) /*0x5578232*/
        {
          m = (unsigned __int64)m_1; /*0x55782dd*/
          *(_QWORD *)kk_1 = (unsigned __int8)nn; /*0x55782a2*/
          sub_558672E(m_1, (unsigned int)(char)nn); /*0x5578313*/
        }
        n0x81 = n0x81_1; /*0x5578464*/
        n0x81_1 = n0x81_2; /*0x5578384*/
        LODWORD(j_5) = 946040811; /*0x557838f*/
        if ( n0x81_2 )
        {
          while ( 1 )
          {
            n148_1[0] = (void *)n0x81; /*0x55783ef*/
            v45 = n0x81 < 0x81 ? n0x81 : (unsigned __int8)n0x81 | 0x80u;
            nn = (unsigned __int64)n148_1[0] >> 7; /*0x55784c8*/
            sub_558672E(m_1, (unsigned int)v45); /*0x55784e8*/
            if ( nn <= 0x7F ) /*0x5578503*/
              break; /*0x5578503*/
            n0x81 = nn; /*0x5578506*/
          }
          if ( nn ) /*0x55783d0*/
          {
            m = (unsigned __int64)m_1; /*0x5578477*/
            *(_QWORD *)kk_1 = (unsigned __int8)nn; /*0x5578440*/
            sub_558672E(m_1, (unsigned int)(char)nn); /*0x55784ad*/
          }
        }
        else
        {
          LODWORD(j_5) = -847088690; /*0x5578395*/
        }
        std::string::_M_append(m_1, j, n0x81_2); /*0x5578536*/
      }
      if ( j != j_2 ) /*0x5578558*/
        operator delete(j); /*0x557855a*/
      v128 += 6; /*0x557855f*/
    }
    nn = s1_8_3y_zddgga_b(&4(___2_[0]; /*0x5577e1e*/
    if ( nn )
    {
      for ( jj = 18; ; jj = jj_1 )
      {
        j = (void *)jj; /*0x5577eaf*/
        v39 = jj < 0x81 ? jj : (unsigned __int8)jj | 0x80u;
        jj_1 = (unsigned __int64)j >> 7; /*0x5577f89*/
        m = (unsigned __int64)&m_1; /*0x5577f96*/
        sub_558672E(m_1, (unsigned int)v39); /*0x5577fac*/
        if ( jj_1 <= 0x7F ) /*0x5577fc4*/
          break; /*0x5577fc4*/
      }
      if ( jj_1 ) /*0x5577e90*/
      {
        *(_QWORD *)kk_1 = *(_QWORD *)m; /*0x5577f38*/
        n148_1[0] = (void *)(unsigned __int8)jj_1; /*0x5577efa*/
        sub_558672E(*(_QWORD *)kk_1, (unsigned int)(char)jj_1); /*0x5577f6e*/
      }
      j_3 = j_5; /*0x55780b3*/
      j_5 = s1_8_3y_zddgga_b(&4(___2_[0]; /*0x5577fdc*/
      if ( s1_8_3y_zddgga_b(&4(___2_[0] )
      {
        while ( 1 )
        {
          j = (void *)j_3; /*0x5578044*/
          v41 = j_3 < 0x81 ? j_3 : (unsigned __int8)j_3 | 0x80u;
          n0x7F = (unsigned __int64)j >> 7; /*0x557811a*/
          m = (unsigned __int64)&m_1; /*0x5578127*/
          sub_558672E(m_1, (unsigned int)v41); /*0x557813d*/
          if ( n0x7F <= 0x7F ) /*0x5578155*/
            break; /*0x5578155*/
          j_3 = n0x7F; /*0x5578158*/
        }
        if ( n0x7F ) /*0x5578025*/
        {
          *(_QWORD *)kk_1 = *(_QWORD *)m; /*0x55780c9*/
          n148_1[0] = (void *)(unsigned __int8)n0x7F; /*0x557808f*/
          sub_558672E(*(_QWORD *)kk_1, (unsigned int)(char)n0x7F); /*0x55780ff*/
        }
      }
      std::string::_M_append(m_1, v136, s1_8_3y_zddgga_b(&4(___2_[0]); /*0x5578185*/
    }
    nn_1 = &off_78E94A8; /*0x55785cc*/
    if ( v136 != &s1_8_3y_zddgga_b(&4(___2_[1] ) /*0x55785e7*/
      operator delete(v136); /*0x55785e9*/
    sub_55A796E(s_ouko2rvntz__32); /*0x55785f6*/
    do /*0x5577cc2*/
    {
      while ( 1 ) /*0x5577937*/
      {
        while ( 1 ) /*0x5577930*/
        {
LABEL_136:
          while ( (int)&unk_16FDF4A <= -32611385 ) /*0x5577930*/
          {
            if ( (int)&unk_16FDF4A > -1123402355 ) /*0x5577977*/
            {
              switch ( (unsigned int)&unk_16FDF4A ) /*0x5577a0f*/
              {
                case 0xBD0A3D8E: /*0x5577a0f*/
                  goto LABEL_161; /*0x5577a0f*/
                case 0xD0485B79: /*0x5577a0f*/
                  goto LABEL_168; /*0x5577a16*/
                case 0xD9DF5BA0: /*0x5577a0f*/
                  goto LABEL_172; /*0x5577a21*/
              }
            }
            else
            {
              switch ( (unsigned int)&unk_16FDF4A ) /*0x5577982*/
              {
                case 0x9367E0D4: /*0x5577982*/
                  goto LABEL_159; /*0x5577982*/
                case 0xA649197E: /*0x5577982*/
                  goto LABEL_167; /*0x557798d*/
                case 0xA6B09054: /*0x5577982*/
                  goto LABEL_147; /*0x5577998*/
              }
            }
          }
          if ( (int)&unk_16FDF4A <= 601302693 ) /*0x5577937*/
            break; /*0x5577937*/
          switch ( (unsigned int)&unk_16FDF4A ) /*0x55779cb*/
          {
            case 0x23D726A6u: /*0x55779cb*/
              goto LABEL_157; /*0x55779cb*/
            case 0x673FEE77u: /*0x55779cb*/
              goto LABEL_162; /*0x55779d6*/
            case 0x6946864Eu: /*0x55779cb*/
              goto LABEL_151; /*0x55779e1*/
          }
        }
        if ( (int)&unk_16FDF4A <= 172896733 ) /*0x5577942*/
          break; /*0x5577942*/
        if ( (unsigned int)&unk_16FDF4A == 172896734 ) /*0x557794d*/
          goto LABEL_169; /*0x557794d*/
        if ( (unsigned int)&unk_16FDF4A == 279300218 ) /*0x5577958*/
          goto LABEL_141; /*0x5577958*/
      }
      if ( (unsigned int)&unk_16FDF4A == -32611384 ) /*0x5577a31*/
        goto LABEL_157; /*0x5577a31*/
    }
    while ( (unsigned int)&unk_16FDF4A != (_DWORD)&unk_16FDF4A ); /*0x5577cc2*/
    std::_Rb_tree<int const,std::pair<int const,std::string>,std::_Select1st<std::pair<int const,std::string>>,std::less<int const>,std::allocator<std::pair<int const,std::string>>>::_M_erase( /*0x5578625*/
      &i,
      v116);
    nn_1 = (void *)0x520A10170B552301LL; /*0x557862d*/
    s_ouko2rvntz__32[0] = 0x195904001E041618LL; /*0x5578674*/
    s_ouko2rvntz__32[1] = 0x59581747111F051DLL; /*0x55786bf*/
    s_ouko2rvntz__32[2] = 0x17090114000E1343LL; /*0x5578703*/
    v136 = (void *)0x252B313115752809LL; /*0x5578742*/
    qmemcpy(s1_8_3y_zddgga_b(&4(___2_, "s1'8<3y{zddgga`b(&4(#\"2*", sizeof(s1_8_3y_zddgga_b(&4(___2_)); /*0x5578783*/
    v138 = (void *)0x515D515116545E2FLL; /*0x5578840*/
    LODWORD(v139) = 509040457; /*0x5578881*/
    qmemcpy((char *)&v139 + 4, "TR@\\WNu]GDKC", 12); /*0x55788a1*/
    n2 = 2; /*0x55788fe*/
    n75 = 75; /*0x5578906*/
    *(_QWORD *)v214 = v144; /*0x5578915*/
    v48 = -945584324; /*0x557891d*/
    v49 = &v142; /*0x5578922*/
    while ( v48 != -1488304518 ) /*0x5578954*/
    {
      *v49++ = 0; /*0x557895e*/
      v48 = -945584324; /*0x557896c*/
      if ( v49 == *(char **)v214 ) /*0x5578976*/
        v48 = -1488304518; /*0x5578976*/
    }
    *(_QWORD *)kk_1 = &nn_1; /*0x557897b*/
    LOBYTE(nn) = (_BYTE)nn_1; /*0x557898d*/
    if ( (nn & 1) != 0 ) /*0x5578a8a*/
    {
      n148_1[0] = &m; /*0x55789c1*/
      for ( m = 0; m < 0x58; ++m ) /*0x55789d1*/
      {
        n148_2[0] = (char *)&nn_1 + 2; /*0x5578a50*/
        j = (void *)m; /*0x5578a60*/
        *((_BYTE *)&nn_1 + m + 2) ^= ((30 - m) & 0x1B | (m + 1) & 0xE4) ^ BYTE1(nn_1) ^ 0x43; /*0x5578ad9*/
        *(_QWORD *)v214 = m + 1; /*0x5578ae8*/
      }
      v142 = 0; /*0x5578a09*/
      v143 = 0; /*0x5578a11*/
      **(_BYTE **)kk_1 = 0; /*0x5578a21*/
    }
    v214[0] = 1; /*0x5578b39*/
    v214[1] = 35; /*0x5578b41*/
    v214[2] = 69; /*0x5578b49*/
    v214[3] = 87; /*0x5578b53*/
    v214[4] = 84; /*0x5578b5a*/
    v214[5] = 91; /*0x5578b64*/
    v214[6] = 17; /*0x5578b6b*/
    v214[7] = 80; /*0x5578b75*/
    *(_QWORD *)&v214[8] = 0x4F4A5D4D1E5B5A46LL; /*0x5578b7c*/
    *(_QWORD *)&v214[16] = 0x71B4E424A055057LL; /*0x5578bbc*/
    v214[24] = 71; /*0x5578bf9*/
    j = &v214[27]; /*0x5578c09*/
    n688378388 = 688378388; /*0x5578c11*/
    j_4 = &v214[25]; /*0x5578c16*/
    while ( n688378388 != -1455040970 ) /*0x5578c29*/
    {
      *j_4++ = 0; /*0x5578c33*/
      n688378388 = 688378388; /*0x5578c41*/
      if ( j_4 == j ) /*0x5578c4b*/
        n688378388 = -1455040970; /*0x5578c4b*/
    }
    *(_QWORD *)kk_1 = v214; /*0x5578c58*/
    if ( (v214[0] & 1) != 0 ) /*0x5578daf*/
    {
      n148_1[0] = &m; /*0x5578d66*/
      for ( m = 0; m < 0x17; ++m ) /*0x5578d76*/
      {
        n148_2[0] = &v214[2]; /*0x5578d4d*/
        LOBYTE(nn) = (m + 1) ^ v214[1] ^ v214[m + 2] ^ 0x17; /*0x5578cbb*/
        j = &v214[m + 2]; /*0x5578cd2*/
        v214[m + 2] = nn; /*0x5578dc7*/
      }
      *(_WORD *)&v214[25] = 0; /*0x5578d06*/
      **(_BYTE **)kk_1 = 0; /*0x5578d1e*/
    }
    sub_5545F3B((char *)&nn_1 + 2, 245, &v214[2], (__int64)"[FGESDK]", 1u, v200, a3, a4, a5, a6, v46, v47, a9, a10, v90); /*0x5578e05*/
    while ( 1 ) /*0x557906b*/
    {
      sub_5536FD0(&n1448808005_1, s_1); /*0x557906b*/
      j = j_2; /*0x5579078*/
      std::string::_M_construct<char *>(&j, v95[8], v95[8] + v95[9]); /*0x5579098*/
      *(_QWORD *)v214 = v95; /*0x557909d*/
      *(_QWORD *)&v214[8] = &v214[24]; /*0x55790ad*/
      std::string::_M_construct<char *>(&v214[8], j, (char *)j + n0x81_2); /*0x55790d0*/
      v52 = (char *)operator new(0x28u); /*0x55790da*/
      *(_QWORD *)v52 = *(_QWORD *)v214; /*0x55790ea*/
      *((_QWORD *)v52 + 1) = v52 + 24; /*0x55790f1*/
      if ( *(_BYTE **)&v214[8] == &v214[24] ) /*0x5579100*/
      {
        a3 = *(__m128 *)&v214[24]; /*0x5579114*/
        *(_OWORD *)(v52 + 24) = *(_OWORD *)&v214[24]; /*0x5579117*/
      }
      else
      {
        *((_QWORD *)v52 + 1) = *(_QWORD *)&v214[8]; /*0x5579102*/
        *((_QWORD *)v52 + 3) = *(_QWORD *)&v214[24]; /*0x557910e*/
      }
      *((_QWORD *)v52 + 2) = *(_QWORD *)&v214[16]; /*0x5579132*/
      *(_QWORD *)&v214[8] = &v214[24]; /*0x5579136*/
      *(_QWORD *)&v214[16] = 0; /*0x557913e*/
      v214[24] = 0; /*0x557914c*/
      n148_2[0] = v52; /*0x5579153*/
      v213.m128_u64[1] = (unsigned __int64)sub_56084C6; /*0x5579162*/
      v213.m128_u64[0] = (unsigned __int64)&loc_56084DA; /*0x5579171*/
      nn_1 = (void *)0x520A10170B552301LL; /*0x557917b*/
      s_ouko2rvntz__32[0] = 0x195904001E041618LL; /*0x55791c1*/
      s_ouko2rvntz__32[1] = 0x59581747111F051DLL; /*0x5579207*/
      s_ouko2rvntz__32[2] = 0x17090114000E1343LL; /*0x557924b*/
      v136 = (void *)0x252B313115752809LL; /*0x5579289*/
      qmemcpy(s1_8_3y_zddgga_b(&4(___2_, "s1'8<3y{zddgga`b(&4(#\"2*", sizeof(s1_8_3y_zddgga_b(&4(___2_)); /*0x55792ca*/
      v138 = (void *)0x515D515116545E2FLL; /*0x5579387*/
      LODWORD(v139) = 509040457; /*0x55793c8*/
      qmemcpy((char *)&v139 + 4, "TR@\\WNu]GDKC", 12); /*0x55793e8*/
      n2 = 2; /*0x5579445*/
      n75 = 75; /*0x557944d*/
      *(_QWORD *)kk_1 = v144; /*0x557945c*/
      v55 = -945584324; /*0x5579464*/
      v56 = &v142; /*0x5579469*/
      while ( v55 != -1488304518 ) /*0x55794a1*/
      {
        *v56++ = 0; /*0x55794ab*/
        v55 = -945584324; /*0x55794b9*/
        if ( v56 == *(char **)kk_1 ) /*0x55794c3*/
          v55 = -1488304518; /*0x55794c3*/
      }
      if ( ((unsigned __int8)nn_1 & 1) != 0 ) /*0x55795bb*/
      {
        nn = (unsigned __int64)&kk; /*0x55794fd*/
        for ( kk = 0; (unsigned __int64)kk < 0x58; ++kk ) /*0x557950d*/
        {
          LODWORD(mm) = (_DWORD)kk; /*0x5579580*/
          m = (unsigned __int64)kk; /*0x5579594*/
          kk[(_QWORD)&nn_1 + 2] ^= ((30 - (_BYTE)kk) & 0x1B | ((_BYTE)kk + 1) & 0xE4) ^ BYTE1(nn_1) ^ 0x43; /*0x5579606*/
          *(_QWORD *)kk_1 = kk + 1; /*0x5579614*/
        }
        v142 = 0; /*0x5579543*/
        v143 = 0; /*0x557954a*/
        LOBYTE(nn_1) = 0; /*0x5579556*/
      }
      kk_1[0] = 1; /*0x5579664*/
      kk_1[1] = 35; /*0x557966c*/
      kk_1[2] = 91; /*0x5579674*/
      kk_1[3] = 95; /*0x557967e*/
      kk_1[4] = 92; /*0x5579685*/
      kk_1[5] = 85; /*0x557968f*/
      kk_1[6] = 83; /*0x5579696*/
      kk_1[7] = 30; /*0x557969e*/
      qmemcpy(LU_V_QFEVOL_n, "LU_V^QFEVOL\n", 12); /*0x55796a8*/
      LU_V_QFEVOL_n[12] = 17; /*0x5579704*/
      LU_V_QFEVOL_n[13] = 12; /*0x557970c*/
      strcpy(AKA, "AKA"); /*0x5579716*/
      AKA[4] = 27; /*0x5579734*/
      AKA[5] = 7; /*0x557973c*/
      AKA[6] = 71; /*0x5579744*/
      m = (unsigned __int64)&v211; /*0x5579754*/
      v57 = -2032791752; /*0x557975c*/
      m_2 = &AKA[7]; /*0x5579761*/
      while ( v57 != -285831972 ) /*0x557976f*/
      {
        *m_2++ = 0; /*0x5579779*/
        v57 = -2032791752; /*0x5579787*/
        if ( m_2 == (char *)m ) /*0x5579791*/
          v57 = -285831972; /*0x5579791*/
      }
      kk = kk_1; /*0x5579796*/
      if ( (kk_1[0] & 1) != 0 ) /*0x5579925*/
      {
        for ( mm = 0; mm < 0x1B; ++mm ) /*0x557988e*/
        {
          nn = (unsigned __int64)&kk_1[2]; /*0x55798ac*/
          kk_1[mm + 2] ^= ((mm + 1) & ~kk_1[1] | kk_1[1] & (-2 - mm)) ^ 0x1B; /*0x5579859*/
          m = mm + 1; /*0x5579867*/
        }
        AKA[7] = 0; /*0x55797e3*/
        AKA[8] = 0; /*0x55797ea*/
        *kk = 0; /*0x55797f9*/
      }
      sub_5545F3B( /*0x5579957*/
        (char *)&nn_1 + 2,
        260,
        &kk_1[2],
        (__int64)"[FGESDK]",
        1u,
        v197,
        a3,
        a4,
        a5,
        a6,
        v53,
        v54,
        a9,
        a10,
        v90);
      *((_BYTE *)v95 + 96) = 1; /*0x5579963*/
      v105 = sub_5536E8A((char *)&nn_1 + 2, 260); /*0x557996b*/
      if ( (*v104 & 1) != 0 ) /*0x5579a03*/
      {
        m = (unsigned __int64)&nn; /*0x5579aa6*/
        for ( nn = 0; nn < 8; ++nn ) /*0x5579ab6*/
        {
          *(_QWORD *)kk_1 = nn; /*0x5579a77*/
          *((_BYTE *)v95 + nn + 266) ^= *((_BYTE *)v95 + 265) ^ (nn + 1) ^ 8; /*0x5579a43*/
          nn_1 = (void *)nn; /*0x5579a52*/
        }
        *((_BYTE *)v95 + 274) = 0; /*0x5579ad6*/
        *((_BYTE *)v95 + 275) = 0; /*0x5579adc*/
        *v104 = 0; /*0x5579ae7*/
      }
      n148_1[0] = v207; /*0x5579b06*/
      v59 = strlen_w(s_2); /*0x5579b19*/
      std::string::_M_construct<char const*>(n148_1, s_2, (char *)v95 + v59 + 266); /*0x5579b2f*/
      n1448808005 = n1448808005_1; /*0x5579b34*/
      v61 = v197; /*0x5579b3c*/
      s_ouko2rvntz__32[1] = 0; /*0x5579b43*/
      if ( v213.m128_u64[0] ) /*0x5579b5a*/
      {
        ((void (__fastcall *)(void **, void **, __int64))v213.m128_u64[0])(&nn_1, n148_2, 2); /*0x5579b6c*/
        a3 = v213; /*0x5579b6e*/
        *(__m128 *)&s_ouko2rvntz__32[1] = v213; /*0x5579b76*/
      }
      n148 = (__int64)n148_1; /*0x5579b86*/
      sub_563AE46(v105, n148_1, n1448808005, v61, &nn_1); /*0x5579b91*/
      if ( s_ouko2rvntz__32[1] ) /*0x5579ba1*/
      {
        n148 = (__int64)&nn_1; /*0x5579ba6*/
        ((void (__fastcall *)(void **, void **, __int64))s_ouko2rvntz__32[1])(&nn_1, &nn_1, 3); /*0x5579bae*/
      }
      if ( n148_1[0] != v207 ) /*0x5579bc3*/
        operator delete(n148_1[0]); /*0x5579bc5*/
      if ( v213.m128_u64[0] ) /*0x5579bd5*/
      {
        n148 = (__int64)n148_2; /*0x5579bdf*/
        ((void (__fastcall *)(void **, void **, __int64))v213.m128_u64[0])(n148_2, n148_2, 3); /*0x5579be7*/
      }
      if ( j != j_2 ) /*0x5579bfc*/
        operator delete(j); /*0x5579bfe*/
      if ( n1448808005_1 == &v198 ) /*0x5579c26*/
        goto LABEL_97; /*0x5579c26*/
      operator delete(n1448808005_1); /*0x5579c2c*/
      if ( (int)n1448808005 > 1448808004 ) /*0x5576805*/
      {
        if ( (int)n1448808005 <= 1870204417 ) /*0x5576868*/
        {
          if ( (_DWORD)n1448808005 == 1448808005 ) /*0x5576874*/
            goto LABEL_99; /*0x5576874*/
          if ( (_DWORD)n1448808005 != 1472010461 ) /*0x5576880*/
            goto LABEL_23; /*0x5576880*/
          goto LABEL_253; /*0x5576880*/
        }
        if ( (_DWORD)n1448808005 != 1891993289 ) /*0x5576ac3*/
        {
          if ( (_DWORD)n1448808005 != 2077383536 ) /*0x5576acf*/
            goto LABEL_23; /*0x5576acf*/
LABEL_97:
          if ( s_1 != s_3 ) /*0x5576af0*/
            operator delete(s_1); /*0x5576af2*/
LABEL_84:
          n148 = n148_3; /*0x5576833*/
          std::_Rb_tree<int const,std::pair<int const,std::string>,std::_Select1st<std::pair<int const,std::string>>,std::less<int const>,std::allocator<std::pair<int const,std::string>>>::_M_erase( /*0x5576843*/
            &k,
            n148_3);
          goto LABEL_23; /*0x5576860*/
        }
        goto LABEL_135; /*0x5576ac3*/
      }
      if ( (int)n1448808005 <= -1001803730 ) /*0x557680d*/
        break; /*0x557680d*/
      if ( (_DWORD)n1448808005 == -1001803729 ) /*0x55768b2*/
        goto LABEL_125; /*0x55768b2*/
      if ( (_DWORD)n1448808005 != -298164919 ) /*0x55768be*/
        goto LABEL_91; /*0x55768be*/
    }
    if ( (_DWORD)n1448808005 == -1973640872 ) /*0x5576819*/
      break; /*0x5576819*/
    if ( (_DWORD)n1448808005 != -1836698331 ) /*0x5576825*/
      goto LABEL_84; /*0x5576825*/
  }
  p_k = (void *)0x520A10170B552301LL; /*0x557734a*/
  v155 = 0x195904001E041618LL; /*0x55773aa*/
  LOBYTE(v22) = 30; /*0x55773c4*/
  n80 = 29; /*0x55773f4*/
  n5 = 5; /*0x55773fc*/
  n31 = 31; /*0x5577404*/
  i_2[0] = 17; /*0x557740c*/
  i_2[1] = 71; /*0x5577417*/
  i_2[2] = 23; /*0x557741f*/
  i_2[3] = 88; /*0x5577426*/
  i_2[4] = 89; /*0x557742e*/
  i_2[5] = 67; /*0x5577438*/
  i_2[6] = 19; /*0x5577440*/
  i_2[7] = 14; /*0x5577448*/
  i_2[8] = 0; /*0x5577450*/
  i_2[9] = 20; /*0x5577458*/
  i_2[10] = 1; /*0x5577460*/
  i_2[11] = 9; /*0x5577469*/
  i_2[12] = 23; /*0x5577470*/
  v160 = (void *)0x252B313115752809LL; /*0x5577477*/
  qmemcpy(s1_8_3y_zddgga_b(&4(___2__1, "s1'8<3y{zddgga`b(&4(#\"2*", sizeof(s1_8_3y_zddgga_b(&4(___2__1)); /*0x55774b8*/
  v162 = (void *)0x515D515116545E2FLL; /*0x5577575*/
  LODWORD(v163) = 509040457; /*0x55775b5*/
  qmemcpy((char *)&v163 + 4, "TR@\\WNu]GDKC", 12); /*0x55775d5*/
  n2_1 = 2; /*0x557763d*/
  n75_1 = 75; /*0x5577645*/
  nn_1 = &v167; /*0x5577654*/
  v35 = -945584324; /*0x557765c*/
  nn_2 = nn_7; /*0x5577661*/
  while ( v35 != -1488304518 ) /*0x557767f*/
  {
    *nn_2++ = 0; /*0x557768d*/
    v35 = -945584324; /*0x557769b*/
    if ( nn_2 == nn_1 ) /*0x55776a5*/
      v35 = -1488304518; /*0x55776a5*/
  }
  n148_1[0] = &p_k; /*0x557772b*/
  if ( ((unsigned __int8)p_k & 1) != 0 ) /*0x557782f*/
  {
    n148_2[0] = kk_1; /*0x5577766*/
    for ( *(_QWORD *)kk_1 = 0; *(_QWORD *)kk_1 < 0x58u; ++*(_QWORD *)kk_1 ) /*0x5577776*/
    {
      LODWORD(m) = *(_DWORD *)kk_1; /*0x55777f1*/
      j = (char *)&p_k + 2; /*0x55777f8*/
      *(_QWORD *)v214 = *(_QWORD *)kk_1; /*0x5577808*/
      *((_BYTE *)&p_k + *(_QWORD *)kk_1 + 2) ^= ((30 - kk_1[0]) & 0x1B | (kk_1[0] + 1) & 0xE4) ^ BYTE1(p_k) ^ 0x43; /*0x5577881*/
      nn_1 = (void *)(*(_QWORD *)kk_1 + 1LL); /*0x557788f*/
    }
    nn_7[0] = 0; /*0x55777ae*/
    nn_7[1] = 0; /*0x55777b6*/
    *(_BYTE *)n148_1[0] = 0; /*0x55777c6*/
  }
  s_4 = (char *)&p_k + 2; /*0x55778df*/
LABEL_91:
  k_1[0] = 1; /*0x55768db*/
  qmemcpy(&k_1[1], "#kyolxj.eeukfa'ow~t:{}vrtt22xPr`@KN\nD_", 38); /*0x55768fb*/
  k_1[39] = 15; /*0x5576a2b*/
  qmemcpy(@TLO, "@TLO", sizeof(@TLO)); /*0x5576a33*/
  nn_1 = &v205; /*0x5576a5a*/
  n2026163102 = -1857522724; /*0x5576a62*/
  nn_3 = nn_8; /*0x5576a67*/
  while ( n2026163102 != 2026163102 ) /*0x5576a92*/
  {
    *nn_3++ = 0; /*0x5576aa0*/
    n2026163102 = -1857522724; /*0x5576aae*/
    if ( nn_3 == nn_1 ) /*0x5576ab8*/
      n2026163102 = 2026163102; /*0x5576ab8*/
  }
  n148_2[0] = k_1; /*0x5578e1c*/
  LOBYTE(nn) = k_1[0]; /*0x5578e2e*/
  if ( (nn & 1) != 0 ) /*0x5578f88*/
  {
    j = n148_1; /*0x5578f55*/
    for ( n148_1[0] = 0; n148_1[0] < (char *)&qword_28 + 2; ++n148_1[0] ) /*0x5578f65*/
    {
      *(_DWORD *)kk_1 = n148_1[0]; /*0x5578f99*/
      *(_QWORD *)v214 = &k_1[2]; /*0x5578fa0*/
      LOBYTE(m) = ((6 - kk_1[0]) & 5 | (kk_1[0] + 1) & 0xFA) ^ k_1[1] ^ k_1[(unsigned __int64)n148_1[0] + 2] ^ 0x2F; /*0x5578e88*/
      nn_1 = &k_1[(unsigned __int64)n148_1[0] + 2]; /*0x5578e9f*/
      k_1[(unsigned __int64)n148_1[0] + 2] = m; /*0x5578f09*/
    }
    nn_8[0] = 0; /*0x5578f30*/
    nn_8[1] = 0; /*0x5578f38*/
    *(_BYTE *)n148_2[0] = 0; /*0x5578f48*/
  }
  n148 = 237; /*0x5578fdc*/
  sub_5545F3B(s_4, 237, &k_1[2], (__int64)"[FGESDK]", 2u, v22, a3, a4, a5, a6, v23, v24, a9, a10, v90); /*0x5578ff0*/
  do /*0x5579c6c*/
  {
    while ( 1 ) /*0x5575d49*/
    {
      while ( 1 ) /*0x5575d3e*/
      {
LABEL_23:
        while ( (int)&unk_18B48AF > -716900473 ) /*0x5575d3e*/
        {
          if ( (int)&unk_18B48AF <= (int)&unk_18B48AE ) /*0x5575e41*/
          {
            switch ( (unsigned int)&unk_18B48AF ) /*0x5575ec0*/
            {
              case 0xD544F788: /*0x5575ec0*/
                goto LABEL_72; /*0x5575ec0*/
              case 0xD6F85319: /*0x5575ec0*/
                goto LABEL_255; /*0x5575ecb*/
              case 0xF72C16D6: /*0x5575ec0*/
                goto LABEL_44; /*0x5575ed6*/
            }
          }
          else if ( (int)&unk_18B48AF > 1253276928 ) /*0x5575e48*/
          {
            if ( (unsigned int)&unk_18B48AF == 1474405877 ) /*0x5575f10*/
              goto LABEL_46; /*0x5575f10*/
          }
          else
          {
            if ( (unsigned int)&unk_18B48AF == (_DWORD)&unk_18B48AF ) /*0x5575e53*/
              goto LABEL_299; /*0x5575e53*/
            if ( (unsigned int)&unk_18B48AF == 188618265 ) /*0x5575e5e*/
              goto LABEL_36; /*0x5575e5e*/
          }
        }
        if ( (int)&unk_18B48AF > -1271796461 ) /*0x5575d49*/
          break; /*0x5575d49*/
        if ( (int)&unk_18B48AF > -1630126688 ) /*0x5575d54*/
        {
          if ( (unsigned int)&unk_18B48AF == -1630126687 ) /*0x5575ff9*/
            goto LABEL_62; /*0x5575ff9*/
          if ( (unsigned int)&unk_18B48AF == -1415844768 ) /*0x5576004*/
            goto LABEL_52; /*0x5576004*/
        }
        else
        {
          if ( (unsigned int)&unk_18B48AF == -1667669813 ) /*0x5575d5f*/
            goto LABEL_61; /*0x5575d5f*/
          if ( (unsigned int)&unk_18B48AF == -1630752641 ) /*0x5575d6a*/
          {
            k = (unsigned __int64)k_2; /*0x5575d7c*/
            *(_QWORD *)v214 = *k_2; /*0x5575d8f*/
            p_k = (void *)(v109 - *(_QWORD *)v214); /*0x5575dc7*/
            nn_1 = nn_4; /*0x5575dd7*/
            n148 = 3605254104LL; /*0x5575e2f*/
            if ( (__int64)p_k >= *(_QWORD *)nn_1 ) /*0x5575e34*/
            {
              *(_QWORD *)k = v109; /*0x5575e0b*/
              v21 = 1; /*0x5575e13*/
            }
            else
            {
              v21 = 0; /*0x5575dff*/
            }
            if ( (v21 & 1) != 0 ) /*0x5576396*/
              goto LABEL_255; /*0x5576396*/
          }
        }
      }
      if ( (int)&unk_18B48AF > -1174854886 ) /*0x5575e84*/
        break; /*0x5575e84*/
      if ( (unsigned int)&unk_18B48AF == -1271796460 ) /*0x5575e8f*/
        goto LABEL_74; /*0x5575e8f*/
      if ( (unsigned int)&unk_18B48AF == -1270887751 ) /*0x5575e9a*/
        goto LABEL_52; /*0x5575e9a*/
    }
    if ( (unsigned int)&unk_18B48AF == -1039077366 ) /*0x5576026*/
      goto LABEL_55; /*0x5576026*/
  }
  while ( (unsigned int)&unk_18B48AF != -1174854885 ); /*0x5579c6c*/
LABEL_299:
  sub_55883A4(mutex); /*0x5579c72*/
  v64 = sub_5564328(mutex, n148, v62, v63); /*0x5579c89*/
  sub_5536FD0(v171, *p_s); /*0x5579ca2*/
  std::string::_M_assign(v64 + 64, v171); /*0x5579cae*/
  *(_BYTE *)(v64 + 96) = 0; /*0x5579cb5*/
  *(_QWORD *)(v64 + 104) = 0; /*0x5579cb9*/
  *(_BYTE *)(v64 + 376) = 0; /*0x5579cc1*/
  v65 = v171[0]; /*0x5579cc9*/
  if ( v171[0] != &v172 ) /*0x5579cdc*/
    operator delete(v171[0]); /*0x5579cde*/
  v66 = sub_5536E8A(v65, v171); /*0x5579ce8*/
  sub_58FC236(v66); /*0x5579ceb*/
LABEL_302:
  v67 = sub_5564244(); /*0x5579cfa*/
  sub_557E8BA(v67, *dest, dest[1], dest[2], *p_s, dest[4]); /*0x5579d1f*/
  p_k = &n80; /*0x5579d2c*/
  v155 = 0; /*0x5579d32*/
  n80 = 0; /*0x5579d36*/
  v160 = &s1_8_3y_zddgga_b(&4(___2__1[1]; /*0x5579d48*/
  s1_8_3y_zddgga_b(&4(___2__1[0] = 0; /*0x5579d4c*/
  LOBYTE(s1_8_3y_zddgga_b(&4(___2__1[1]) = 0; /*0x5579d50*/
  v162 = (char *)&v163 + 8; /*0x5579d5a*/
  *(_QWORD *)&v163 = 0; /*0x5579d5e*/
  BYTE8(v163) = 0; /*0x5579d62*/
  v168 = v170; /*0x5579d6c*/
  v169 = 0; /*0x5579d70*/
  v170[0] = 0; /*0x5579d74*/
  s_5 = (const char *)dest[2]; /*0x5579d76*/
  v69 = strlen_w(s_5); /*0x5579d7d*/
  std::string::_M_replace(&p_k, 0, 0, s_5, v69); /*0x5579d97*/
  v70 = s1_8_3y_zddgga_b(&4(___2__1[0]; /*0x5579d9c*/
  v71 = strlen_w("0.0.20"); /*0x5579daa*/
  std::string::_M_replace(&v160, 0, v70, "0.0.20", v71); /*0x5579dbd*/
  v72 = sub_557DE44(); /*0x5579dc2*/
  sub_5A33A04(v72, &p_k); /*0x5579dcd*/
  nn_1 = &s_ouko2rvntz__32[1]; /*0x5579dda*/
  s_ouko2rvntz__32[0] = 0; /*0x5579dde*/
  LOBYTE(s_ouko2rvntz__32[1]) = 0; /*0x5579de2*/
  v136 = &s1_8_3y_zddgga_b(&4(___2_[1]; /*0x5579df4*/
  s1_8_3y_zddgga_b(&4(___2_[0] = 0; /*0x5579df7*/
  LOBYTE(s1_8_3y_zddgga_b(&4(___2_[1]) = 0; /*0x5579dfb*/
  v138 = (char *)&v139 + 8; /*0x5579e07*/
  *(_QWORD *)&v139 = 0; /*0x5579e0b*/
  BYTE8(v139) = 0; /*0x5579e0f*/
  desta = (char *)&v146 + 8; /*0x5579e19*/
  *(_QWORD *)&v146 = 0; /*0x5579e1d*/
  BYTE8(v146) = 0; /*0x5579e21*/
  v147 = v149; /*0x5579e2c*/
  v148 = 0; /*0x5579e30*/
  v149[0] = 0; /*0x5579e34*/
  v151 = v153; /*0x5579e3e*/
  v152 = 0; /*0x5579e42*/
  v153[0] = 0; /*0x5579e46*/
  s_6 = *p_s; /*0x5579e4d*/
  v74 = strlen_w(*p_s); /*0x5579e53*/
  std::string::_M_replace(&nn_1, 0, 0, s_6, v74); /*0x5579e6d*/
  s_7 = (const char *)dest[4]; /*0x5579e72*/
  v76 = s1_8_3y_zddgga_b(&4(___2_[0]; /*0x5579e76*/
  v77 = strlen_w(s_7); /*0x5579e7e*/
  std::string::_M_replace(&v136, 0, v76, s_7, v77); /*0x5579e91*/
  v78 = v139; /*0x5579e96*/
  v79 = strlen_w(&s_); /*0x5579ea5*/
  std::string::_M_replace(&v138, 0, v78, &s_, v79); /*0x5579ebd*/
  sub_5555707(&i_1); /*0x5579ecd*/
  if ( i_1 == &n[1] ) /*0x5579ee0*/
  {
    if ( n[0] ) /*0x5579f31*/
    {
      if ( n[0] == 1 ) /*0x5579f3f*/
        *(_BYTE *)desta = *(_BYTE *)i_1; /*0x5579f43*/
      else
        memcpy(desta, i_1, n[0]); /*0x5579f54*/
    }
    *(_QWORD *)&v146 = n[0]; /*0x5579f61*/
    *((_BYTE *)desta + n[0]) = 0; /*0x5579f71*/
    i_4 = (size_t *)i_1; /*0x5579f75*/
  }
  else
  {
    i_4 = (size_t *)desta; /*0x5579ee2*/
    v81 = *((_QWORD *)&v146 + 1); /*0x5579eea*/
    desta = i_1; /*0x5579ef2*/
    v146 = *(_OWORD *)n; /*0x5579f02*/
    if ( i_4 == (size_t *)((char *)&v146 + 8) || !i_4 ) /*0x5579f12*/
    {
      i_1 = &n[1]; /*0x5579f47*/
      i_4 = &n[1]; /*0x5579f4f*/
    }
    else
    {
      i_1 = i_4; /*0x5579f14*/
      n[1] = v81; /*0x5579f1c*/
    }
  }
  n[0] = 0; /*0x5579f8d*/
  *(_BYTE *)i_4 = 0; /*0x5579f99*/
  if ( i_1 != &n[1] ) /*0x5579fa7*/
    operator delete(i_1); /*0x5579fa9*/
  s_8 = (const char *)dest[1]; /*0x5579fb3*/
  v83 = v148; /*0x5579fbf*/
  v84 = strlen_w(s_8); /*0x5579fca*/
  std::string::_M_replace(&v147, 0, v83, s_8, v84); /*0x5579fdd*/
  n4_1 = 4; /*0x5579fe2*/
  s_9 = (const char *)dest[2]; /*0x5579fee*/
  v86 = v152; /*0x5579ff2*/
  v87 = strlen_w(s_9); /*0x5579ffd*/
  std::string::_M_replace(&v151, 0, v86, s_9, v87); /*0x557a010*/
  sub_557EAAF(&nn_1); /*0x557a018*/
  if ( v151 != v153 ) /*0x557a030*/
    operator delete(v151); /*0x557a032*/
  if ( v147 != v149 ) /*0x557a04a*/
    operator delete(v147); /*0x557a04c*/
  if ( desta != (char *)&v146 + 8 ) /*0x557a064*/
    operator delete(desta); /*0x557a066*/
  if ( v138 != (char *)&v139 + 8 ) /*0x557a07e*/
    operator delete(v138); /*0x557a080*/
  if ( v136 != &s1_8_3y_zddgga_b(&4(___2_[1] ) /*0x557a098*/
    operator delete(v136); /*0x557a09a*/
  if ( nn_1 != &s_ouko2rvntz__32[1] ) /*0x557a0b2*/
    operator delete(nn_1); /*0x557a0b4*/
  if ( v168 != v170 ) /*0x557a0cc*/
    operator delete(v168); /*0x557a0ce*/
  if ( v162 != (char *)&v163 + 8 ) /*0x557a0e6*/
    operator delete(v162); /*0x557a0e8*/
  if ( v160 != &s1_8_3y_zddgga_b(&4(___2__1[1] ) /*0x557a100*/
    operator delete(v160); /*0x557a102*/
  if ( p_k != &n80 ) /*0x557a11a*/
    operator delete(p_k); /*0x557a11c*/
  return __readfsqword(0x28u); /*0x557a134*/
}
