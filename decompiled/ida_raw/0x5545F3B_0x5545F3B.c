// 0x5545F3B @ 0x5545F3B
// The function seems has been flattened
unsigned __int64 __fastcall sub_5545F3B(
        char *s,
        int a2,
        const char *format_1,
        __int64 a4,
        unsigned int a5,
        __int64 a6,
        __m128 a7,
        __m128 a8,
        __m128 a9,
        __m128 a10,
        __m128 a11,
        __m128 a12,
        __m128 a13,
        __m128 a14,
        char a15)
{
  int v16; // r15d
  char *i; // rbx
  _OWORD *dest_1; // rax
  __int64 v19; // rcx
  const char *i_1; // rbp
  _BYTE *v21; // rax
  __int64 v22; // rcx
  _OWORD *dest_3; // rax
  __int64 v24; // rcx
  int maxlen; // [rsp+Ch] [rbp-36Ch]
  _BYTE *v27; // [rsp+10h] [rbp-368h]
  int n0x100; // [rsp+10h] [rbp-368h]
  __int64 v29; // [rsp+38h] [rbp-340h]
  __int64 v30; // [rsp+40h] [rbp-338h]
  char *sa; // [rsp+48h] [rbp-330h]
  __int64 *v32; // [rsp+50h] [rbp-328h]
  void (__fastcall *v35)(void *, __int64, _QWORD); // [rsp+88h] [rbp-2F0h]
  size_t v36; // [rsp+98h] [rbp-2E0h]
  const char *format; // [rsp+B0h] [rbp-2C8h]
  _BYTE v39[40]; // [rsp+C0h] [rbp-2B8h] BYREF
  __int64 v40; // [rsp+E8h] [rbp-290h]
  __m128 v41; // [rsp+F0h] [rbp-288h]
  __m128 v42; // [rsp+100h] [rbp-278h]
  __m128 v43; // [rsp+110h] [rbp-268h]
  __m128 v44; // [rsp+120h] [rbp-258h]
  __m128 v45; // [rsp+130h] [rbp-248h]
  __m128 v46; // [rsp+140h] [rbp-238h]
  __m128 v47; // [rsp+150h] [rbp-228h]
  __m128 v48; // [rsp+160h] [rbp-218h]
  _BYTE v49[24]; // [rsp+180h] [rbp-1F8h] BYREF
  __int128 v50; // [rsp+1A0h] [rbp-1D8h]
  _BYTE *v51; // [rsp+1B0h] [rbp-1C8h]
  void *dest; // [rsp+1C0h] [rbp-1B8h] BYREF
  __int128 v53; // [rsp+1C8h] [rbp-1B0h] BYREF
  void *dest_2; // [rsp+1E0h] [rbp-198h]
  __int128 v55; // [rsp+1E8h] [rbp-190h] BYREF
  void *s_1[2]; // [rsp+200h] [rbp-178h] BYREF
  _BYTE v57[240]; // [rsp+210h] [rbp-168h] BYREF
  _BYTE n[24]; // [rsp+300h] [rbp-78h] BYREF
  __int128 v59; // [rsp+320h] [rbp-58h] BYREF
  _BYTE *v60; // [rsp+330h] [rbp-48h]
  unsigned __int64 v61; // [rsp+340h] [rbp-38h]

  v41 = a7; /*0x5545f3b*/
  v42 = a8; /*0x5545f3b*/
  v43 = a9; /*0x5545f3b*/
  v44 = a10; /*0x5545f3b*/
  v45 = a11; /*0x5545f3b*/
  v46 = a12; /*0x5545f3b*/
  v47 = a13; /*0x5545f3b*/
  v48 = a14; /*0x5545f3b*/
  v40 = a6; /*0x5545f6b*/
  v61 = __readfsqword(0x28u); /*0x5545fbc*/
  if ( *(unsigned __int8 *)(sub_5570126() + 2) ) /*0x5545fc9*/
  {
    format = format_1; /*0x554600e*/
    dest_2 = (char *)&v55 + 8; /*0x5546030*/
    v16 = 0; /*0x5546038*/
    *(_QWORD *)&v55 = 0; /*0x554603b*/
    BYTE8(v55) = 0; /*0x5546043*/
    dest = (char *)&v53 + 8; /*0x5546065*/
    *(_QWORD *)&v53 = 0; /*0x554606d*/
    BYTE8(v53) = 0; /*0x5546075*/
    v36 = strlen(s); /*0x554609d*/
    for ( i = &s[v36]; ; --i ) /*0x55460b5*/
    {
LABEL_25:
      if ( v36 <= v16 ) /*0x55462f6*/
      {
        i_1 = i; /*0x55462fa*/
        goto LABEL_31; /*0x55462fe*/
      }
LABEL_20:
      if ( *i == 47 ) /*0x5546268*/
        break; /*0x5546268*/
LABEL_30:
      ++v16; /*0x5546373*/
    }
LABEL_37:
    i_1 = i + 1; /*0x554647e*/
LABEL_31:
    *(_QWORD *)&v59 = i_1; /*0x5546381*/
    maxlen = snprintf((char *)s_1, 0x100u, "%s:%d ", i_1, a2); /*0x55463c1*/
    if ( maxlen >= 0 ) /*0x55463d5*/
    {
LABEL_34:
      if ( (unsigned __int64)maxlen >= 0x100 ) /*0x5546439*/
      {
LABEL_33:
        std::string::resize(&dest, maxlen + 1, 0); /*0x55463f6*/
LABEL_17:
        sa = (char *)dest; /*0x55461f5*/
LABEL_28:
        snprintf(sa, maxlen, "%s:%d ", (const char *)v59, a2); /*0x554631d*/
      }
      else
      {
        do /*0x554616c*/
        {
          *(_QWORD *)n = &n[16]; /*0x554616c*/
          std::string::_M_construct<char const*>(n, s_1, (char *)s_1 + maxlen); /*0x554617f*/
          if ( *(_BYTE **)n == &n[16] ) /*0x554618f*/
          {
            if ( *(_QWORD *)&n[8] ) /*0x55464d1*/
            {
              if ( *(_QWORD *)&n[8] == 1 ) /*0x55464df*/
                *(_BYTE *)dest = n[16]; /*0x55464e8*/
              else
                memcpy(dest, &n[16], *(size_t *)&n[8]); /*0x554650e*/
            }
            *(_QWORD *)&v53 = *(_QWORD *)&n[8]; /*0x554651b*/
            *((_BYTE *)dest + *(_QWORD *)&n[8]) = 0; /*0x554652b*/
            dest_1 = *(_OWORD **)n; /*0x554652f*/
          }
          else
          {
            dest_1 = dest; /*0x5546195*/
            v19 = *((_QWORD *)&v53 + 1); /*0x554619d*/
            dest = *(void **)n; /*0x55461a5*/
            v53 = *(_OWORD *)&n[8]; /*0x55461b5*/
            if ( dest_1 == (__int128 *)((char *)&v53 + 8) || !dest_1 ) /*0x55461d1*/
            {
              *(_QWORD *)n = &n[16]; /*0x55464ec*/
              dest_1 = &n[16]; /*0x55464f4*/
            }
            else
            {
              *(_QWORD *)n = dest_1; /*0x55461d7*/
              *(_QWORD *)&n[16] = v19; /*0x55461df*/
            }
          }
          *(_QWORD *)&n[8] = 0; /*0x5546537*/
          *(_BYTE *)dest_1 = 0; /*0x5546543*/
          if ( *(_BYTE **)n == &n[16] ) /*0x5546557*/
            break; /*0x5546557*/
          operator delete(*(void **)n); /*0x554655d*/
          if ( (int)s > 1198499521 ) /*0x55460c5*/
          {
            if ( (int)s > 1431051939 ) /*0x55460ce*/
            {
              if ( (int)s > 1610979759 ) /*0x55460db*/
              {
                if ( (_DWORD)s == 1610979760 ) /*0x55460e8*/
                  goto LABEL_34; /*0x55460e8*/
                break; /*0x55460e8*/
              }
              if ( (_DWORD)s == 1431051940 ) /*0x5546354*/
                goto LABEL_38; /*0x5546354*/
              goto LABEL_30; /*0x5546354*/
            }
            if ( (int)s <= 1358074480 ) /*0x55461f3*/
              goto LABEL_17; /*0x55461f3*/
            if ( (_DWORD)s == 1358074481 ) /*0x5546278*/
              goto LABEL_33; /*0x5546278*/
            goto LABEL_23; /*0x5546278*/
          }
          if ( (int)s <= -616271121 ) /*0x554611b*/
          {
            if ( (int)s <= -1594658150 ) /*0x554623a*/
            {
              if ( (_DWORD)s == -1906028808 ) /*0x5546243*/
                goto LABEL_36; /*0x5546243*/
              goto LABEL_20; /*0x5546243*/
            }
            if ( (_DWORD)s == -1594658149 ) /*0x55462bf*/
              break; /*0x55462bf*/
            goto LABEL_25; /*0x55462bf*/
          }
          if ( (int)s <= -277299237 ) /*0x5546128*/
          {
            if ( (_DWORD)s == -616271120 ) /*0x554630a*/
              goto LABEL_37; /*0x554630a*/
            goto LABEL_28; /*0x554630a*/
          }
          if ( (_DWORD)s == -277299236 ) /*0x5546135*/
            goto LABEL_31; /*0x5546135*/
        }
        while ( (_DWORD)s == 796451878 ); /*0x554616c*/
      }
    }
    else
    {
LABEL_23:
      *(_OWORD *)v49 = 0; /*0x554628b*/
      v27 = v49; /*0x554629e*/
      v32 = (__int64 *)v49; /*0x55462a8*/
LABEL_38:
      v29 = *v32; /*0x55464a0*/
      v30 = *((_QWORD *)v27 + 1); /*0x55464b6*/
LABEL_36:
      std::string::_M_replace(&dest, 0, v53, v29, v30); /*0x5546442*/
    }
    v51 = v39; /*0x5546506*/
    *((_QWORD *)&v50 + 1) = &a15; /*0x5546a8f*/
    *(_QWORD *)&v50 = 0x3000000028LL; /*0x5546a9d*/
    *(_QWORD *)v49 = &v49[16]; /*0x5546595*/
    *(_QWORD *)&v49[8] = 0; /*0x554659d*/
    v49[16] = 0; /*0x55465a9*/
    v60 = v39; /*0x55466fa*/
    v59 = v50; /*0x5546701*/
    n0x100 = vsnprintf((char *)s_1, 0x100u, format, &v59); /*0x5546728*/
    if ( n0x100 >= 0 ) /*0x55466a8*/
    {
      if ( (unsigned __int64)n0x100 >= 0x100 ) /*0x5546674*/
      {
        std::string::resize(v49, n0x100 + 1, 0); /*0x5546748*/
        *(_OWORD *)n = v50; /*0x5546755*/
        *(_QWORD *)&n[16] = v51; /*0x5546761*/
        vsnprintf(*(char **)v49, n0x100 + 1, format, n); /*0x554677a*/
      }
      else
      {
        *(_QWORD *)n = &n[16]; /*0x55467c3*/
        std::string::_M_construct<char const*>(n, s_1, (char *)s_1 + n0x100); /*0x55467d5*/
        if ( *(_BYTE **)n == &n[16] ) /*0x55467e5*/
        {
          if ( *(_QWORD *)&n[8] ) /*0x554683e*/
          {
            if ( *(_QWORD *)&n[8] == 1 ) /*0x554684c*/
              **(_BYTE **)v49 = n[16]; /*0x5546855*/
            else
              memcpy(*(void **)v49, &n[16], *(size_t *)&n[8]); /*0x554687a*/
          }
          *(_QWORD *)&v49[8] = *(_QWORD *)&n[8]; /*0x5546887*/
          *(_BYTE *)(*(_QWORD *)v49 + *(_QWORD *)&n[8]) = 0; /*0x5546897*/
          v21 = *(_BYTE **)n; /*0x554689b*/
        }
        else
        {
          v21 = *(_BYTE **)v49; /*0x55467e7*/
          v22 = *(_QWORD *)&v49[16]; /*0x55467ef*/
          *(_QWORD *)v49 = *(_QWORD *)n; /*0x55467f7*/
          *(_OWORD *)&v49[8] = *(_OWORD *)&n[8]; /*0x5546807*/
          if ( v21 == &v49[16] || !v21 ) /*0x554681f*/
          {
            *(_QWORD *)n = &n[16]; /*0x5546859*/
            v21 = &n[16]; /*0x5546861*/
          }
          else
          {
            *(_QWORD *)n = v21; /*0x5546821*/
            *(_QWORD *)&n[16] = v22; /*0x5546829*/
          }
        }
        *(_QWORD *)&n[8] = 0; /*0x55468a3*/
        *v21 = 0; /*0x55468af*/
        if ( *(_BYTE **)n != &n[16] ) /*0x55468bd*/
          operator delete(*(void **)n); /*0x55468bf*/
      }
    }
    else
    {
      std::string::_M_replace(v49, 0, *(_QWORD *)&v49[8], 0, 0); /*0x55467b4*/
    }
    if ( *(_BYTE **)v49 == &v49[16] ) /*0x5546a1e*/
    {
      if ( *(_QWORD *)&v49[8] ) /*0x5546ab5*/
      {
        if ( *(_QWORD *)&v49[8] == 1 ) /*0x5546ac3*/
          *(_BYTE *)dest_2 = v49[16]; /*0x5546acc*/
        else
          memcpy(dest_2, &v49[16], *(size_t *)&v49[8]); /*0x5546aea*/
      }
      *(_QWORD *)&v55 = *(_QWORD *)&v49[8]; /*0x5546af7*/
      *((_BYTE *)dest_2 + *(_QWORD *)&v49[8]) = 0; /*0x5546b07*/
      dest_3 = *(_OWORD **)v49; /*0x5546b0b*/
    }
    else
    {
      dest_3 = dest_2; /*0x5546a24*/
      v24 = *((_QWORD *)&v55 + 1); /*0x5546a2c*/
      dest_2 = *(void **)v49; /*0x5546a34*/
      v55 = *(_OWORD *)&v49[8]; /*0x5546a44*/
      if ( dest_3 == (__int128 *)((char *)&v55 + 8) || !dest_3 ) /*0x5546a5c*/
      {
        dest_3 = &v49[16]; /*0x5546ad0*/
        *(_QWORD *)v49 = &v49[16]; /*0x5546ad8*/
      }
      else
      {
        *(_QWORD *)v49 = dest_3; /*0x5546a5e*/
        *(_QWORD *)&v49[16] = v24; /*0x5546a66*/
      }
    }
    *(_QWORD *)&v49[8] = 0; /*0x5546b13*/
    *(_BYTE *)dest_3 = 0; /*0x5546b1f*/
    if ( *(_BYTE **)v49 != &v49[16] ) /*0x5546b35*/
      operator delete(*(void **)v49); /*0x5546b37*/
    v35 = (void (__fastcall *)(void *, __int64, _QWORD))unk_7A16398; /*0x5546b4e*/
    if ( unk_7A16398 ) /*0x5546b69*/
    {
      s_1[0] = v57; /*0x55468ec*/
      std::string::_M_construct<char *>(s_1, dest, (char *)dest + v53); /*0x5546912*/
      std::string::_M_append(s_1, dest_2, v55); /*0x554692a*/
      v35(s_1[0], a4, a5); /*0x554694b*/
      if ( s_1[0] != v57 ) /*0x5546958*/
        operator delete(s_1[0]); /*0x554695a*/
    }
    if ( dest != (char *)&v53 + 8 ) /*0x55469bf*/
      operator delete(dest); /*0x55469c1*/
    if ( dest_2 != (char *)&v55 + 8 ) /*0x55469de*/
      operator delete(dest_2); /*0x55469e0*/
  }
  return __readfsqword(0x28u); /*0x5546b84*/
}
