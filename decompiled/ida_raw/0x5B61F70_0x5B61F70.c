// 0x5B61F70 @ 0x5B61F70
// The function may be unflattened
__int64 __fastcall sub_5B61F70(__int64 a1, const void *src, unsigned int a3, int a4)
{
  __int64 v4; // rbp
  __int64 size_1; // r12
  int n1673260775; // r15d
  int n581064928; // r14d
  int i; // eax
  void *s; // rax
  size_t size; // [rsp+18h] [rbp-50h]
  void *dest; // [rsp+20h] [rbp-48h]
  unsigned int *ptr; // [rsp+28h] [rbp-40h]

  size_1 = a3 + 1LL; /*0x5b61f95*/
  n1673260775 = 1673260775; /*0x5b61fa2*/
  if ( (a4 & 0xFFFFFFFE) != 0x14 ) /*0x5b61fad*/
    n1673260775 = 2108505193; /*0x5b61fad*/
  n581064928 = 581064928; /*0x5b61fb4*/
  if ( !src ) /*0x5b61fba*/
    n581064928 = 2108505193; /*0x5b61fba*/
  for ( i = 725708970; ; i = n1673260775 ) /*0x5b61fc3*/
  {
    while ( 1 ) /*0x5b61fcd*/
    {
      while ( i > 711819794 ) /*0x5b61fcd*/
      {
        if ( i > 1673260774 ) /*0x5b61fd4*/
        {
          if ( i == 1673260775 ) /*0x5b62010*/
          {
            ptr = (unsigned int *)malloc(0x10u); /*0x5b620a6*/
            *ptr = a3; /*0x5b620af*/
            *((_WORD *)ptr + 2) = 30; /*0x5b620b1*/
            size = size_1; /*0x5b620b7*/
            i = -322560534; /*0x5b620bc*/
          }
          else
          {
            i = 86742310; /*0x5b62019*/
            v4 = 0; /*0x5b6201e*/
          }
        }
        else if ( i == 711819795 ) /*0x5b61fdb*/
        {
          memcpy(dest, src, *ptr); /*0x5b62031*/
          v4 = sub_5B619E7((unsigned __int64)"VIPII"); /*0x5b62063*/
          ptr = 0; /*0x5b62075*/
          i = 86742310; /*0x5b62083*/
        }
        else
        {
          i = n581064928; /*0x5b61fe4*/
        }
      }
      if ( i != -322560534 ) /*0x5b61fee*/
        break; /*0x5b61fee*/
      s = malloc(size); /*0x5b620cb*/
      *((_QWORD *)ptr + 1) = s; /*0x5b620d5*/
      memset(s, 0, *ptr); /*0x5b620e2*/
      dest = (void *)*((_QWORD *)ptr + 1); /*0x5b620eb*/
      i = 711819795; /*0x5b620f0*/
    }
    if ( i == 86742310 ) /*0x5b61ff9*/
      break; /*0x5b61ff9*/
  }
  return v4; /*0x5b6210d*/
}
