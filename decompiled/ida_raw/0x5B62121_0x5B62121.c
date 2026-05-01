// 0x5B62121 @ 0x5B62121
// The function seems has been flattened
__int64 __fastcall sub_5B62121(__int64 a1, const void *src, __int64 a3, const void *src_1, __int64 n)
{
  size_t n_4; // rbp
  _WORD *v6; // r14
  unsigned __int64 n_2; // rdx
  bool v8; // cf
  unsigned __int64 n_7; // rdx
  size_t n_5; // rax
  __int64 v11; // rdx
  __int64 n_6; // r8
  __int64 v13; // r13
  char *dest_1; // r12
  void *s; // rax
  bool v17; // [rsp+3h] [rbp-95h]
  unsigned int na; // [rsp+4h] [rbp-94h]
  size_t n_3; // [rsp+10h] [rbp-88h]
  __int64 size; // [rsp+18h] [rbp-80h]
  int n_1; // [rsp+30h] [rbp-68h]
  unsigned int v23; // [rsp+40h] [rbp-58h]
  unsigned int *ptr_1; // [rsp+48h] [rbp-50h]
  void *dest; // [rsp+50h] [rbp-48h]
  unsigned int *ptr; // [rsp+58h] [rbp-40h]

  n_1 = n; /*0x5b6217d*/
  n_2 = (unsigned int)(n + 1); /*0x5b62182*/
  v8 = n_2 < (unsigned int)n; /*0x5b62192*/
  n_7 = n_2 - (unsigned int)n; /*0x5b62192*/
  n_5 = 0; /*0x5b62195*/
  if ( !v8 ) /*0x5b6219a*/
    n_5 = n_7; /*0x5b6219a*/
  n_3 = n_5; /*0x5b6219e*/
LABEL_15:
  if ( v17 || !src ) /*0x5b62214*/
  {
LABEL_20:
    v13 = 0; /*0x5b6222f*/
    goto LABEL_7; /*0x5b62237*/
  }
LABEL_24:
  ptr = (unsigned int *)malloc(0x10u); /*0x5b622ec*/
  *ptr = v23; /*0x5b6230f*/
  *((_WORD *)ptr + 2) = 30; /*0x5b62311*/
  ptr_1 = ptr; /*0x5b62317*/
LABEL_25:
  s = malloc(*ptr_1 + 1LL); /*0x5b62326*/
  *((_QWORD *)ptr + 1) = s; /*0x5b6233a*/
  memset(s, 0, *ptr + 1); /*0x5b62347*/
  dest = (void *)*((_QWORD *)ptr + 1); /*0x5b62350*/
  na = *ptr; /*0x5b62357*/
LABEL_11:
  memcpy(dest, src, na); /*0x5b621c8*/
  v6 = 0; /*0x5b621db*/
  v23 = v11; /*0x5b6214d*/
  v17 = v11 == 0; /*0x5b62155*/
  n_4 = (unsigned int)n_6; /*0x5b6215f*/
  size = (unsigned int)n_6 + 1LL; /*0x5b62166*/
  if ( n_6 ) /*0x5b62179*/
  {
LABEL_22:
    v6 = malloc(0x10u); /*0x5b62247*/
    *(_DWORD *)v6 = n_1; /*0x5b62259*/
    v6[2] = 30; /*0x5b6225c*/
    dest_1 = (char *)malloc(size); /*0x5b6226d*/
    *((_QWORD *)v6 + 1) = dest_1; /*0x5b62270*/
    memset(&dest_1[n_4], 0, n_3); /*0x5b6227f*/
    memcpy(dest_1, src_1, n_4); /*0x5b6228f*/
  }
LABEL_23:
  v13 = sub_5B61AFB(a1, (__int64)"LLL", ptr, v6); /*0x5b6229e*/
  ptr = 0; /*0x5b622d4*/
  do /*0x5b6236a*/
  {
    while ( 1 ) /*0x5b621ad*/
    {
LABEL_7:
      while ( (int)&unk_1CEF0BD > 1352695063 ) /*0x5b621ad*/
      {
        if ( (int)&unk_1CEF0BD > 1540709637 ) /*0x5b621b4*/
        {
          if ( (unsigned int)&unk_1CEF0BD == 1540709638 ) /*0x5b6221e*/
            goto LABEL_25; /*0x5b6221e*/
          if ( (unsigned int)&unk_1CEF0BD == 1970258602 ) /*0x5b62229*/
            goto LABEL_20; /*0x5b62229*/
        }
        else
        {
          if ( (unsigned int)&unk_1CEF0BD == 1352695064 ) /*0x5b621bb*/
            goto LABEL_24; /*0x5b621bb*/
          if ( (unsigned int)&unk_1CEF0BD == 1469454286 ) /*0x5b621c6*/
            goto LABEL_11; /*0x5b621c6*/
        }
      }
      if ( (int)&unk_1CEF0BD > -110789668 ) /*0x5b621e8*/
        break; /*0x5b621e8*/
      if ( (unsigned int)&unk_1CEF0BD == -2131831225 ) /*0x5b621ef*/
        goto LABEL_23; /*0x5b621ef*/
      if ( (unsigned int)&unk_1CEF0BD == -485937608 ) /*0x5b621fa*/
        goto LABEL_15; /*0x5b621fa*/
    }
    if ( (unsigned int)&unk_1CEF0BD == -110789667 ) /*0x5b62241*/
      goto LABEL_22; /*0x5b62241*/
  }
  while ( (unsigned int)&unk_1CEF0BD != (_DWORD)&unk_1CEF0BD ); /*0x5b6236a*/
  return v13; /*0x5b62383*/
}
