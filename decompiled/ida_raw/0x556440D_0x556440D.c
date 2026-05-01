// 0x556440D @ 0x556440D
// The function seems has been flattened
void **__fastcall sub_556440D(void **p_src, char *s, __int64 a3)
{
  unsigned __int64 n1309361403; // r15
  __int64 v4; // rax
  __int64 n520992540; // rbx
  void **v6; // rdi
  void **p_src_2; // rcx
  unsigned __int64 k; // r14
  char v9; // bl
  char v10; // r14
  int n1364789019; // eax
  unsigned __int64 m; // r14
  char v13; // bl
  unsigned __int64 n1309361403_1; // r13
  char v15; // bl
  int n1364789019_1; // eax
  unsigned __int64 n; // r14
  char v18; // bl
  unsigned __int64 n1309361403_3; // r13
  char v20; // bl
  int ii; // eax
  _BYTE *j_3; // rax
  _BYTE *k_3; // rcx
  int v24; // eax
  _BYTE *j_4; // r8
  const char *s2; // rsi
  int v27; // eax
  unsigned __int64 *p_i_3; // rax
  _BYTE *k_4; // rcx
  int n1937090853; // eax
  unsigned __int64 *p_i_4; // rsi
  _QWORD v33[5]; // [rsp+0h] [rbp-180h] BYREF
  void **v34; // [rsp+28h] [rbp-158h]
  unsigned __int64 *p_i_2; // [rsp+30h] [rbp-150h]
  _BYTE *j_2; // [rsp+38h] [rbp-148h]
  void **v37; // [rsp+40h] [rbp-140h]
  void **v38; // [rsp+48h] [rbp-138h]
  unsigned __int64 *p_i_1; // [rsp+50h] [rbp-130h]
  _BYTE *j_1; // [rsp+58h] [rbp-128h]
  char *s1; // [rsp+60h] [rbp-120h]
  void **p_src_1; // [rsp+68h] [rbp-118h]
  void ***p_p_src; // [rsp+70h] [rbp-110h]
  _QWORD *v44; // [rsp+78h] [rbp-108h]
  void **v45; // [rsp+80h] [rbp-100h]
  unsigned __int64 n1309361403_5; // [rsp+88h] [rbp-F8h]
  unsigned __int64 i_1; // [rsp+90h] [rbp-F0h]
  unsigned __int64 *p_i; // [rsp+98h] [rbp-E8h]
  char k_2; // [rsp+A7h] [rbp-D9h]
  void **p_src_3; // [rsp+A8h] [rbp-D8h] BYREF
  unsigned __int64 i; // [rsp+B0h] [rbp-D0h] BYREF
  void ***j; // [rsp+B8h] [rbp-C8h] BYREF
  unsigned __int64 k_1; // [rsp+C0h] [rbp-C0h] BYREF
  __int64 (__fastcall **v54)(); // [rsp+C8h] [rbp-B8h] BYREF
  void *v55; // [rsp+D0h] [rbp-B0h] BYREF
  unsigned __int64 n1309361403_6; // [rsp+D8h] [rbp-A8h]
  _BYTE v57[16]; // [rsp+E0h] [rbp-A0h] BYREF
  void *v58; // [rsp+F0h] [rbp-90h] BYREF
  unsigned __int64 n1309361403_2; // [rsp+F8h] [rbp-88h]
  _BYTE v60[16]; // [rsp+100h] [rbp-80h] BYREF
  void *v61; // [rsp+110h] [rbp-70h]
  unsigned __int64 n1309361403_4; // [rsp+118h] [rbp-68h]
  _BYTE v63[16]; // [rsp+120h] [rbp-60h] BYREF
  void *v64[2]; // [rsp+130h] [rbp-50h] BYREF
  char v65; // [rsp+140h] [rbp-40h] BYREF
  unsigned __int64 v66; // [rsp+150h] [rbp-30h]

  v33[0] = a3; /*0x5564421*/
  s1 = s; /*0x5564428*/
  v66 = __readfsqword(0x28u); /*0x5564438*/
  p_src_1 = p_src; /*0x556443c*/
  v34 = p_src + 2; /*0x5564447*/
LABEL_9:
  j_1 = &v33[-8]; /*0x55644df*/
  p_i_1 = &v33[-8]; /*0x55644fa*/
  v45 = (void **)&v33[-4]; /*0x556450b*/
  v38 = (void **)&v33[-4]; /*0x556451c*/
  v37 = (void **)&v33[-4]; /*0x556452d*/
  v44 = &v33[-2]; /*0x556453e*/
  v33[4] = v64; /*0x5564549*/
  v4 = sub_5564244(); /*0x5564557*/
  sub_5536FD0(v64, *(_QWORD *)(v4 + 64), &k_1); /*0x556456a*/
  v33[3] = &v54; /*0x5564576*/
  v54 = &off_78E9490; /*0x556458b*/
  v55 = v57; /*0x5564599*/
  n1309361403_6 = 0; /*0x55645a0*/
  v57[0] = 0; /*0x55645a7*/
  v58 = v60; /*0x55645b2*/
  n1309361403_2 = 0; /*0x55645b9*/
  v60[0] = 0; /*0x55645c0*/
  v61 = v63; /*0x55645c8*/
  n1309361403_4 = 0; /*0x55645cc*/
  v63[0] = 0; /*0x55645d0*/
  std::string::_M_assign(&v58, v64); /*0x55645de*/
  j_2 = j_1; /*0x55645ea*/
LABEL_5:
  j_3 = j_1; /*0x5564489*/
  *j_1 = 1; /*0x556529d*/
  qmemcpy(j_3 + 1, "#e`cw;y$6|y", 11); /*0x55652a0*/
  j_3[12] = 127; /*0x55652d6*/
  j_3[13] = 116; /*0x55652d9*/
  j_3[14] = 66; /*0x55652e0*/
  j_3[15] = 127; /*0x55652e4*/
  qmemcpy(j_3 + 16, "|cdqp*@ec`Hihi~}!cB]vGAWUTPISoU_MEjGZ", 37); /*0x55652e7*/
  k_3 = j_3 + 53; /*0x5565377*/
  k_1 = (unsigned __int64)(j_3 + 55); /*0x556537f*/
  v24 = -2048446510; /*0x5565386*/
  while ( v24 != -1237076071 ) /*0x5565390*/
  {
    *k_3++ = 0; /*0x5565399*/
    v24 = -2048446510; /*0x55653a6*/
    if ( k_3 == (_BYTE *)k_1 ) /*0x55653b0*/
      v24 = -1237076071; /*0x55653b0*/
  }
  j_4 = j_1; /*0x55653b5*/
  j = (void ***)j_1; /*0x55653bc*/
  LOBYTE(p_p_src) = *j_1; /*0x55653cc*/
  s2 = j_1 + 2; /*0x55653d2*/
  if ( ((unsigned __int8)p_p_src & 1) != 0 ) /*0x55654a5*/
  {
    p_i = &i; /*0x55653ff*/
    for ( i = 0; i < 0x33; ++i ) /*0x556540d*/
    {
      i_1 = i; /*0x5565509*/
      LODWORD(n1309361403_5) = i; /*0x5565476*/
      k_1 = (unsigned __int64)s2; /*0x556547c*/
      s2[i] ^= ((i + 1) & ~j_4[1] | j_4[1] & (-2 - i)) ^ 0x33; /*0x55654ee*/
    }
    j_4[53] = 0; /*0x556543e*/
    j_4[54] = 0; /*0x5565442*/
    *(_BYTE *)j = 0; /*0x556544d*/
  }
  v27 = strcmp(s1, s2); /*0x5565546*/
  p_i_2 = p_i_1; /*0x5565554*/
  if ( v27 ) /*0x556556c*/
    goto LABEL_108; /*0x556556c*/
  while ( 1 ) /*0x5564651*/
  {
    v33[2] = v45; /*0x5564651*/
    n520992540 = sub_5536E8A(); /*0x5564664*/
    v6 = v38; /*0x5564667*/
    *v38 = v38 + 2; /*0x5564672*/
    std::string::_M_construct<char *>(v6, *(_QWORD *)v33[0], *(_QWORD *)v33[0] + *(_QWORD *)(v33[0] + 8LL)); /*0x5564686*/
    v33[1] = v44; /*0x5564692*/
    sub_5536FD0(v37, s1, v44); /*0x55646bc*/
    sub_58FC982(v45, n520992540, v38, v37); /*0x55646d9*/
    sub_55455F8(&v55, v45); /*0x55646ec*/
    if ( *v45 != v45 + 2 ) /*0x5564702*/
      operator delete(*v45); /*0x5564704*/
    if ( *v37 == v37 + 2 ) /*0x556471f*/
      break; /*0x556471f*/
    operator delete(*v37); /*0x5564725*/
    if ( (int)n520992540 <= -140246170 ) /*0x556446f*/
    {
      if ( (int)n520992540 > -1195352653 ) /*0x55644c1*/
      {
        if ( (_DWORD)n520992540 == -1195352652 ) /*0x5564638*/
          break; /*0x5564638*/
      }
      else
      {
        if ( (_DWORD)n520992540 != -1828878212 ) /*0x55644cd*/
        {
          if ( (_DWORD)n520992540 != -1358824706 ) /*0x55644d9*/
            goto LABEL_120; /*0x55644d9*/
          goto LABEL_9; /*0x55644d9*/
        }
LABEL_108:
        p_i_3 = p_i_1; /*0x55655b5*/
        *(_BYTE *)p_i_1 = 1; /*0x55655bc*/
        qmemcpy((char *)p_i_3 + 1, "#x}~j&d9+adbi_ba~ylm7]x~}Ututc`<~_@}LK^X@eDEDSP", 47); /*0x55655bf*/
        k_4 = p_i_3 + 6; /*0x5565682*/
        k_1 = (unsigned __int64)p_i_3 + 50; /*0x556568a*/
        n1937090853 = -1900087633; /*0x5565691*/
        while ( n1937090853 != 1937090853 ) /*0x55656ac*/
        {
          *k_4++ = 0; /*0x55656b5*/
          n1937090853 = -1900087633; /*0x55656c2*/
          if ( k_4 == (_BYTE *)k_1 ) /*0x55656cc*/
            n1937090853 = 1937090853; /*0x55656cc*/
        }
        p_i_4 = p_i_1; /*0x55656d1*/
        p_i = p_i_1; /*0x55656d8*/
        LOBYTE(i) = *(_BYTE *)p_i_1; /*0x55656e8*/
        if ( (i & 1) != 0 ) /*0x55657cc*/
        {
          i_1 = (unsigned __int64)&j; /*0x55657d4*/
          for ( j = 0; (unsigned __int64)j < 0x2E; j = (void ***)((char *)j + 1) ) /*0x55657e2*/
          {
            *((_BYTE *)j + (_QWORD)p_i_4 + 2) ^= *((_BYTE *)p_i_4 + 1) ^ ((_BYTE)j + 1) ^ 0x2E; /*0x5565770*/
            k_1 = (unsigned __int64)j + 1; /*0x556577e*/
          }
          *((_BYTE *)p_i_4 + 48) = 0; /*0x556571e*/
          *((_BYTE *)p_i_4 + 49) = 0; /*0x5565722*/
          *(_BYTE *)p_i = 0; /*0x556572d*/
        }
        if ( strcmp(s1, (const char *)p_i_4 + 2) ) /*0x5565825*/
          goto LABEL_17; /*0x5565844*/
      }
    }
    else
    {
      if ( (int)n520992540 > 520992539 ) /*0x5564477*/
      {
        if ( (_DWORD)n520992540 == 520992540 ) /*0x5564483*/
          break; /*0x5564483*/
        goto LABEL_5; /*0x5564483*/
      }
      if ( (_DWORD)n520992540 == -140246169 ) /*0x5564608*/
        goto LABEL_17; /*0x5564608*/
    }
  }
  if ( *v38 != v38 + 2 ) /*0x556558c*/
    operator delete(*v38); /*0x556558e*/
LABEL_17:
  p_src_2 = p_src_1; /*0x556472f*/
  *p_src_1 = v34; /*0x556473d*/
  p_src_2[1] = 0; /*0x5564740*/
  *((_BYTE *)p_src_2 + 16) = 0; /*0x5564748*/
  p_p_src = &p_src_3; /*0x5564753*/
  p_src_3 = p_src_2; /*0x5564761*/
  n1309361403_5 = n1309361403_6; /*0x556476f*/
  if ( n1309361403_6 )
  {
    for ( k = 10; ; k = i )
    {
      k_1 = k; /*0x5564804*/
      k_2 = k; /*0x5564812*/
      v9 = k < 0x81 ? k_2 : k_2 | 0x80;
      i = k_1 >> 7; /*0x55648e5*/
      j = &p_src_3; /*0x55648f3*/
      sub_558672E(p_src_3, (unsigned int)v9); /*0x5564907*/
      if ( i <= 0x7F ) /*0x5564921*/
        break; /*0x5564921*/
    }
    if ( i ) /*0x55647e6*/
    {
      p_i = (unsigned __int64 *)*j; /*0x5564896*/
      i_1 = (unsigned __int8)i; /*0x5564859*/
      sub_558672E(p_i, (unsigned int)(char)i); /*0x55648cb*/
    }
    n1309361403 = 1309361403; /*0x5564a28*/
    if ( n1309361403_6 )
    {
      while ( 1 )
      {
        k_1 = n1309361403; /*0x55649af*/
        k_2 = n1309361403; /*0x55649bd*/
        v10 = n1309361403 < 0x81 ? k_2 : k_2 | 0x80;
        i = k_1 >> 7; /*0x5564a8d*/
        j = &p_src_3; /*0x5564a9b*/
        sub_558672E(p_src_3, (unsigned int)v10); /*0x5564ab0*/
        if ( i <= 0x7F ) /*0x5564aca*/
          break; /*0x5564aca*/
        n1309361403 = i; /*0x5564acd*/
      }
      if ( i ) /*0x5564991*/
      {
        p_i = (unsigned __int64 *)*j; /*0x5564a3c*/
        i_1 = (unsigned __int8)i; /*0x5564a05*/
        sub_558672E(p_i, (unsigned int)(char)i); /*0x5564a73*/
      }
    }
    std::string::_M_append(p_src_3, v55, n1309361403_6); /*0x5564af9*/
  }
  n1309361403_5 = n1309361403_2; /*0x5564b22*/
  n1364789019 = 1364789019; /*0x5564b29*/
  while ( 1 )
  {
    while ( n1364789019 == 740971099 )
    {
      for ( m = 18; ; m = i )
      {
        k_1 = m; /*0x5564bb7*/
        k_2 = m; /*0x5564bc5*/
        v13 = m < 0x81 ? k_2 : k_2 | 0x80;
        i = k_1 >> 7; /*0x5564c98*/
        j = &p_src_3; /*0x5564ca6*/
        sub_558672E(p_src_3, (unsigned int)v13); /*0x5564cba*/
        if ( i <= 0x7F ) /*0x5564cd4*/
          break; /*0x5564cd4*/
      }
      if ( i ) /*0x5564b99*/
      {
        p_i = (unsigned __int64 *)*j; /*0x5564c49*/
        i_1 = (unsigned __int8)i; /*0x5564c0c*/
        sub_558672E(p_i, (unsigned int)(char)i); /*0x5564c7e*/
      }
      n1309361403_1 = n1309361403; /*0x5564dd8*/
      n1309361403 = n1309361403_2; /*0x5564cee*/
      if ( n1309361403_2 )
      {
        while ( 1 )
        {
          k_1 = n1309361403_1; /*0x5564d60*/
          k_2 = n1309361403_1; /*0x5564d6e*/
          v15 = n1309361403_1 < 0x81 ? k_2 : k_2 | 0x80;
          i = k_1 >> 7; /*0x5564e3c*/
          j = &p_src_3; /*0x5564e4a*/
          sub_558672E(p_src_3, (unsigned int)v15); /*0x5564e5e*/
          if ( i <= 0x7F ) /*0x5564e78*/
            break; /*0x5564e78*/
          n1309361403_1 = i; /*0x5564e7b*/
        }
        if ( i ) /*0x5564d42*/
        {
          p_i = (unsigned __int64 *)*j; /*0x5564ded*/
          i_1 = (unsigned __int8)i; /*0x5564db5*/
          sub_558672E(p_i, (unsigned int)(char)i); /*0x5564e22*/
        }
      }
      std::string::_M_append(p_src_3, v58, n1309361403_2); /*0x5564ea7*/
      n1364789019 = 1158903918; /*0x5564eac*/
    }
    if ( n1364789019 == 1158903918 ) /*0x5564b3a*/
      break; /*0x5564b3a*/
    n1364789019 = 740971099; /*0x5564b4f*/
    if ( !n1309361403_5 ) /*0x5564b59*/
      n1364789019 = 1158903918; /*0x5564b59*/
  }
  n1309361403_5 = n1309361403_4; /*0x5564ecd*/
  n1364789019_1 = 1364789019; /*0x5564ed4*/
  while ( 1 )
  {
    while ( n1364789019_1 == 740971099 )
    {
      for ( n = 26; ; n = i )
      {
        k_1 = n; /*0x5564f62*/
        k_2 = n; /*0x5564f70*/
        v18 = n < 0x81 ? k_2 : k_2 | 0x80;
        i = k_1 >> 7; /*0x5565043*/
        j = &p_src_3; /*0x5565051*/
        sub_558672E(p_src_3, (unsigned int)v18); /*0x5565065*/
        if ( i <= 0x7F ) /*0x556507f*/
          break; /*0x556507f*/
      }
      if ( i ) /*0x5564f44*/
      {
        p_i = (unsigned __int64 *)*j; /*0x5564ff4*/
        i_1 = (unsigned __int8)i; /*0x5564fb7*/
        sub_558672E(p_i, (unsigned int)(char)i); /*0x5565029*/
      }
      n1309361403_3 = n1309361403; /*0x5565180*/
      n1309361403 = n1309361403_4; /*0x5565099*/
      if ( n1309361403_4 )
      {
        while ( 1 )
        {
          k_1 = n1309361403_3; /*0x5565108*/
          k_2 = n1309361403_3; /*0x5565116*/
          v20 = n1309361403_3 < 0x81 ? k_2 : k_2 | 0x80;
          i = k_1 >> 7; /*0x55651e4*/
          j = &p_src_3; /*0x55651f2*/
          sub_558672E(p_src_3, (unsigned int)v20); /*0x5565206*/
          if ( i <= 0x7F ) /*0x5565220*/
            break; /*0x5565220*/
          n1309361403_3 = i; /*0x5565223*/
        }
        if ( i ) /*0x55650ea*/
        {
          p_i = (unsigned __int64 *)*j; /*0x5565195*/
          i_1 = (unsigned __int8)i; /*0x556515d*/
          sub_558672E(p_i, (unsigned int)(char)i); /*0x55651ca*/
        }
      }
      std::string::_M_append(p_src_3, v61, n1309361403_4); /*0x5565249*/
      n1364789019_1 = 1158903918; /*0x556524e*/
    }
    if ( n1364789019_1 == 1158903918 ) /*0x5564ee5*/
      break; /*0x5564ee5*/
    n1364789019_1 = 740971099; /*0x5564efa*/
    if ( !n1309361403_5 ) /*0x5564f04*/
      n1364789019_1 = 1158903918; /*0x5564f04*/
  }
  for ( ii = -1870087588; ii != -1505560417; ii = -1505560417 ) /*0x556526b*/
    ; /*0x5565285*/
LABEL_120:
  v54 = &off_78E9490; /*0x5565858*/
  if ( v61 != v63 ) /*0x5565871*/
    operator delete(v61); /*0x5565873*/
  if ( v58 != v60 ) /*0x5565886*/
    operator delete(v58); /*0x5565888*/
  if ( v55 != v57 ) /*0x556589e*/
    operator delete(v55); /*0x55658a0*/
  if ( v64[0] != &v65 ) /*0x55658b7*/
    operator delete(v64[0]); /*0x55658b9*/
  return p_src_1; /*0x55658db*/
}
