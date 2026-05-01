// 0x5B61D31 @ 0x5B61D31
// The function may be unflattened
__int64 __fastcall sub_5B61D31(const void *src_1, unsigned int n8, _QWORD a3, const void *src, unsigned int a5)
{
  __int64 v5; // r15
  int n2000730641; // eax
  void *dest; // rax
  void *s; // rax
  bool v12; // [rsp+Eh] [rbp-8Ah]
  bool v13; // [rsp+Fh] [rbp-89h]
  __int64 v14; // [rsp+30h] [rbp-68h]
  unsigned int *ptr_1; // [rsp+40h] [rbp-58h]
  __int64 v16; // [rsp+48h] [rbp-50h]
  unsigned int *ptr; // [rsp+50h] [rbp-48h]
  _WORD *v18; // [rsp+58h] [rbp-40h]

  v12 = src_1 == 0 || n8 == 0 || src == 0; /*0x5b61d73*/
  v13 = a5 == 0; /*0x5b61d7a*/
  v14 = a5; /*0x5b61d82*/
  n2000730641 = -1938472105; /*0x5b61d96*/
  while ( 1 ) /*0x5b61da0*/
  {
    while ( n2000730641 <= 846223535 ) /*0x5b61da0*/
    {
      if ( n2000730641 == -1938472105 ) /*0x5b61da7*/
      {
        n2000730641 = 2000730641; /*0x5b61e67*/
        if ( v13 ) /*0x5b61e71*/
          n2000730641 = -370173457; /*0x5b61e71*/
        if ( v12 ) /*0x5b61e76*/
          n2000730641 = -370173457; /*0x5b61e76*/
      }
      else if ( n2000730641 == -1438291548 ) /*0x5b61db2*/
      {
        ptr = ptr_1; /*0x5b61e83*/
        *ptr_1 = a5; /*0x5b61e88*/
        *((_WORD *)ptr_1 + 2) = 30; /*0x5b61e8b*/
        v16 = v14; /*0x5b61e96*/
        n2000730641 = 1348068788; /*0x5b61e9b*/
      }
      else
      {
        n2000730641 = 846223536; /*0x5b61dbf*/
        v5 = 0; /*0x5b61dc4*/
      }
    }
    if ( n2000730641 == 846223536 ) /*0x5b61dce*/
      break; /*0x5b61dce*/
    if ( n2000730641 == 1348068788 ) /*0x5b61dd9*/
    {
      s = malloc(v16 + 1); /*0x5b61ead*/
      *((_QWORD *)ptr + 1) = s; /*0x5b61eb7*/
      memset(s, 0, *ptr); /*0x5b61ec2*/
      memcpy(*((void **)ptr + 1), src, *ptr); /*0x5b61ed0*/
      v5 = sub_5B61848((unsigned __int64)"LLIJL"); /*0x5b61f02*/
      ptr = 0; /*0x5b61f14*/
      n2000730641 = 846223536; /*0x5b61f3f*/
    }
    else
    {
      v18 = malloc(0x10u); /*0x5b61e05*/
      *(_DWORD *)v18 = n8; /*0x5b61e0a*/
      v18[2] = 30; /*0x5b61e0d*/
      dest = malloc(n8 + 1LL); /*0x5b61e18*/
      *((_QWORD *)v18 + 1) = dest; /*0x5b61e1d*/
      memcpy(dest, src_1, n8); /*0x5b61e31*/
      ptr_1 = (unsigned int *)malloc(0x10u); /*0x5b61e4f*/
      n2000730641 = -1438291548; /*0x5b61e54*/
    }
  }
  return v5; /*0x5b61f5c*/
}
