// 0x557A6A0 @ 0x557A6A0
// The function may be unflattened
__int64 __fastcall sub_557A6A0(__int64 a1, __int64 a2, unsigned int a3, int a4, _BYTE *dest)
{
  int v7; // r9d
  void *n256054845; // rax
  bool v9; // zf
  char n_3; // bp
  int v11; // ecx
  _BYTE *v12; // rax
  int n334428131; // eax
  char *src_3; // r13
  char n_5; // bp
  char n_6; // bp
  char v18; // [rsp+6h] [rbp-1B2h]
  char v19; // [rsp+7h] [rbp-1B1h]
  _BYTE *v20; // [rsp+8h] [rbp-1B0h]
  int v22; // [rsp+18h] [rbp-1A0h]
  char n0xC_2; // [rsp+1Ch] [rbp-19Ch]
  char *haystack; // [rsp+28h] [rbp-190h]
  char n_4; // [rsp+98h] [rbp-120h]
  char n0xC_1; // [rsp+A0h] [rbp-118h]
  Dl_info info; // [rsp+A8h] [rbp-110h] BYREF
  unsigned __int64 n0xC; // [rsp+C8h] [rbp-F0h]
  void *src_1; // [rsp+D0h] [rbp-E8h]
  size_t n_1; // [rsp+D8h] [rbp-E0h]
  char v31; // [rsp+E0h] [rbp-D8h] BYREF
  void *src_2; // [rsp+F0h] [rbp-C8h] BYREF
  size_t n_2; // [rsp+F8h] [rbp-C0h]
  char v34; // [rsp+100h] [rbp-B8h] BYREF
  void *src; // [rsp+110h] [rbp-A8h] BYREF
  size_t n; // [rsp+118h] [rbp-A0h]
  char v37; // [rsp+120h] [rbp-98h] BYREF
  void *v38[2]; // [rsp+130h] [rbp-88h] BYREF
  _BYTE v39[16]; // [rsp+140h] [rbp-78h] BYREF
  void *v40[2]; // [rsp+150h] [rbp-68h] BYREF
  char v41; // [rsp+160h] [rbp-58h] BYREF
  char v42; // [rsp+170h] [rbp-48h]
  _BYTE _Y_M[ZLZ_tHJ@F_[13]; // [rsp+171h] [rbp-47h] BYREF
  _BYTE v44[2]; // [rsp+17Eh] [rbp-3Ah] BYREF
  _QWORD v45[7]; // [rsp+180h] [rbp-38h] BYREF
  const void *address; // [rsp+1B8h] [rbp+0h]

  v45[0] = __readfsqword(0x28u); /*0x557a6cf*/
  v22 = dladdr(address, &info); /*0x557a6f6*/
  LODWORD(n256054845) = 646869836; /*0x557a735*/
  do /*0x557ac7b*/
  {
    while ( 1 ) /*0x557a78f*/
    {
      while ( 1 ) /*0x557a755*/
      {
        while ( (int)n256054845 <= 256054845 ) /*0x557a755*/
        {
          if ( (int)n256054845 > -1223931268 ) /*0x557a75c*/
          {
            if ( (_DWORD)n256054845 == -1223931267 ) /*0x557a7c0*/
            {
              dest[767] = n_4; /*0x557ab73*/
              src_3 = (char *)src_1; /*0x557ab7a*/
              n_5 = n_1; /*0x557ab82*/
              memcpy(dest, src_1, n_1); /*0x557ab93*/
              dest[255] = n_5; /*0x557ab98*/
              n_6 = n_2; /*0x557aba7*/
              memcpy(dest + 256, src_2, n_2); /*0x557abb7*/
              dest[511] = n_6; /*0x557abbc*/
              if ( src_3 != &v31 ) /*0x557abce*/
                operator delete(src_3); /*0x557abd3*/
              if ( src_2 != &v34 ) /*0x557abf8*/
                operator delete(src_2); /*0x557abfa*/
              if ( src != &v37 ) /*0x557ac2a*/
                operator delete(src); /*0x557ac2c*/
              if ( v38[0] != v39 ) /*0x557ac41*/
                operator delete(v38[0]); /*0x557ac43*/
              if ( v40[0] != &v41 ) /*0x557ac60*/
                operator delete(v40[0]); /*0x557ac62*/
              LODWORD(n256054845) = 1768913227; /*0x557ac6c*/
            }
            else if ( (_DWORD)n256054845 == (_DWORD)&unk_1A87882 ) /*0x557a7cb*/
            {
              __gnu_cxx::__to_xstring<std::string,char>( /*0x557a7fc*/
                (unsigned int)v40,
                (unsigned int)&vsnprintf,
                16,
                (unsigned int)"%d",
                a4,
                v7);
              v38[0] = v39; /*0x557a81b*/
              std::string::_M_construct<char const*>(v38, a2, a2 + a3); /*0x557a833*/
              sub_55658EF(&src, a1, v40, v38); /*0x557a869*/
              sub_556440D(&src_2, a1, v38); /*0x557a886*/
              sub_5555707(); /*0x557a89d*/
              n_3 = n; /*0x557a8aa*/
              memcpy(dest + 512, src, n); /*0x557a8ba*/
              n_4 = n_3; /*0x557a8bf*/
              LODWORD(n256054845) = -1223931267; /*0x557a8cc*/
            }
          }
          else if ( (_DWORD)n256054845 == -1736224168 ) /*0x557a763*/
          {
            dword_79ED398 = 1; /*0x557ab4f*/
            n256054845 = &unk_1A87882; /*0x557ab59*/
          }
          else if ( (_DWORD)n256054845 == -1659708823 ) /*0x557a76e*/
          {
            haystack = (char *)info.dli_fname; /*0x557a778*/
            v9 = info.dli_fname == 0; /*0x557a77d*/
            LODWORD(n256054845) = 1889080702; /*0x557a783*/
LABEL_11:
            if ( v9 ) /*0x557a7b6*/
              LODWORD(n256054845) = (unsigned int)&unk_1A87882; /*0x557a7b6*/
          }
        }
        if ( (int)n256054845 > 1768913226 ) /*0x557a78f*/
          break; /*0x557a78f*/
        if ( (_DWORD)n256054845 == 256054846 ) /*0x557a79a*/
        {
          dword_79ED398 = 0; /*0x557a995*/
          n256054845 = &unk_1A87882; /*0x557a99f*/
        }
        else if ( (_DWORD)n256054845 == 646869836 ) /*0x557a7a5*/
        {
          v9 = v22 == 0; /*0x557a7a7*/
          LODWORD(n256054845) = -1659708823; /*0x557a7ac*/
          goto LABEL_11; /*0x557a7ac*/
        }
      }
      if ( (_DWORD)n256054845 != 1889080702 ) /*0x557a8db*/
        break; /*0x557a8db*/
      v42 = 1; /*0x557a8e1*/
      qmemcpy(_Y_M[ZLZ_tHJ@F_, "#Y_M[ZLZ\tHJ@F", sizeof(_Y_M[ZLZ_tHJ@F_)); /*0x557a8e9*/
      v20 = v45; /*0x557a959*/
      v11 = -2022760694; /*0x557a95e*/
      v12 = v44; /*0x557a963*/
      while ( v11 != -419899678 ) /*0x557a971*/
      {
        *v12++ = 0; /*0x557a97b*/
        v11 = -2022760694; /*0x557a986*/
        if ( v12 == (_BYTE *)v45 ) /*0x557a990*/
          v11 = -419899678; /*0x557a990*/
      }
      v18 = v42; /*0x557a9bd*/
      n334428131 = 334428131; /*0x557a9c1*/
      do /*0x557ab27*/
      {
        while ( 1 ) /*0x557aa02*/
        {
          while ( 1 ) /*0x557a9cb*/
          {
            while ( n334428131 > -146520598 ) /*0x557a9cb*/
            {
              if ( n334428131 > 334428130 ) /*0x557a9d2*/
              {
                if ( n334428131 == 1977942317 ) /*0x557aa47*/
                {
                  n334428131 = -146520597; /*0x557ab15*/
                  if ( n0xC < 0xC ) /*0x557ab1a*/
                    n334428131 = (unsigned int)&loc_5C8AAB8; /*0x557ab1a*/
                }
                else if ( n334428131 == 334428131 ) /*0x557aa52*/
                {
                  n334428131 = -2026043262; /*0x557aa5d*/
                  if ( (v18 & 1) == 0 ) /*0x557aa62*/
                    n334428131 = -1273985286; /*0x557aa62*/
                }
              }
              else if ( n334428131 == -146520597 ) /*0x557a9d9*/
              {
                v44[0] = 0; /*0x557aae7*/
                v44[1] = 0; /*0x557aaef*/
                v42 = 0; /*0x557aafc*/
                n334428131 = -1273985286; /*0x557aaff*/
              }
              else if ( n334428131 == (_DWORD)&loc_5C8AAB8 ) /*0x557a9e4*/
              {
                n0xC_1 = n0xC; /*0x557a9ee*/
                n334428131 = -1098341218; /*0x557a9f6*/
              }
            }
            if ( n334428131 <= -1189486069 ) /*0x557aa02*/
              break; /*0x557aa02*/
            if ( n334428131 == -1189486068 ) /*0x557aa09*/
            {
              v20[n0xC++] = v19 ^ ((n0xC_2 + 1) & ~_Y_M[ZLZ_tHJ@F_[0] | _Y_M[ZLZ_tHJ@F_[0] & (-2 - n0xC_2)) ^ 0xC; /*0x557aacc*/
              n334428131 = 1977942317; /*0x557aad8*/
            }
            else if ( n334428131 == -1098341218 ) /*0x557aa14*/
            {
              n0xC_2 = n0xC_1; /*0x557aa1e*/
              v20 = &_Y_M[ZLZ_tHJ@F_[1]; /*0x557aa22*/
              v19 = _Y_M[ZLZ_tHJ@F_[n0xC + 1]; /*0x557aa37*/
              n334428131 = -1189486068; /*0x557aa3b*/
            }
          }
          if ( n334428131 != -2026043262 ) /*0x557aa70*/
            break; /*0x557aa70*/
          n0xC = 0; /*0x557aa80*/
          n334428131 = 1977942317; /*0x557aa8c*/
        }
      }
      while ( n334428131 != -1273985286 ); /*0x557ab27*/
      v9 = strstr(haystack, &_Y_M[ZLZ_tHJ@F_[1]) == 0; /*0x557ab3a*/
      LODWORD(n256054845) = 256054846; /*0x557ab3d*/
      if ( v9 ) /*0x557ab47*/
        LODWORD(n256054845) = -1736224168; /*0x557ab47*/
    }
  }
  while ( (_DWORD)n256054845 != 1768913227 ); /*0x557ac7b*/
  return 0; /*0x557ac9b*/
}
