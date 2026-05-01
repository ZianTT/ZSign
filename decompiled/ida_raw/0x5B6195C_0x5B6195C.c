// 0x5B6195C @ 0x5B6195C
__int64 __fastcall sub_5B6195C(__int64 a1)
{
  int v2; // eax
  void *v3; // rdi
  void *ptr; // [rsp+10h] [rbp-18h]

  ptr = *(void **)a1; /*0x5b61972*/
  v2 = -1530169691; /*0x5b61977*/
  while ( v2 != -2141092799 ) /*0x5b61986*/
  {
    if ( v2 == -1865856479 ) /*0x5b6198d*/
    {
      free(ptr); /*0x5b619ab*/
      *(_QWORD *)a1 = 0; /*0x5b619b5*/
      v2 = -2141092799; /*0x5b619bc*/
    }
    else
    {
      v2 = -1865856479; /*0x5b6199c*/
      if ( !ptr ) /*0x5b619a1*/
        v2 = -2141092799; /*0x5b619a1*/
    }
  }
  v3 = *(void **)(a1 + 64); /*0x5b619c3*/
  if ( v3 != (void *)(a1 + 80) ) /*0x5b619ce*/
    operator delete(v3); /*0x5b619d0*/
  return sub_5B6254C(a1 + 8); /*0x5b619dc*/
}
