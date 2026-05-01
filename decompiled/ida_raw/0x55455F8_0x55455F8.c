// 0x55455F8 @ 0x55455F8
__int64 __fastcall sub_55455F8(__int64 a1, __int64 a2)
{
  _BYTE *src; // rsi
  _BYTE *v5; // rax
  __int64 v6; // rdx
  size_t n; // rdx
  _BYTE *dest; // rdi
  __int64 v9; // rax

  src = *(_BYTE **)a2; /*0x5545602*/
  if ( src == (_BYTE *)(a2 + 16) ) /*0x554560c*/
  {
    n = *(_QWORD *)(a2 + 8); /*0x554563f*/
    if ( n ) /*0x5545646*/
    {
      dest = *(_BYTE **)a1; /*0x5545648*/
      if ( n == 1 ) /*0x554564f*/
        *dest = *src; /*0x5545653*/
      else
        memcpy(dest, src, n); /*0x554565f*/
    }
    v9 = *(_QWORD *)(a2 + 8); /*0x5545664*/
    *(_QWORD *)(a1 + 8) = v9; /*0x5545668*/
    *(_BYTE *)(*(_QWORD *)a1 + v9) = 0; /*0x554566f*/
    v5 = *(_BYTE **)a2; /*0x5545673*/
  }
  else
  {
    v5 = *(_BYTE **)a1; /*0x5545612*/
    v6 = *(_QWORD *)(a1 + 16); /*0x5545615*/
    *(_QWORD *)a1 = src; /*0x5545619*/
    *(_QWORD *)(a1 + 8) = *(_QWORD *)(a2 + 8); /*0x5545620*/
    *(_QWORD *)(a1 + 16) = *(_QWORD *)(a2 + 16); /*0x5545628*/
    if ( v5 == (_BYTE *)(a1 + 16) || !v5 ) /*0x5545634*/
    {
      *(_QWORD *)a2 = a2 + 16; /*0x5545657*/
      v5 = (_BYTE *)(a2 + 16); /*0x554565a*/
    }
    else
    {
      *(_QWORD *)a2 = v5; /*0x5545636*/
      *(_QWORD *)(a2 + 16) = v6; /*0x5545639*/
    }
  }
  *(_QWORD *)(a2 + 8) = 0; /*0x5545676*/
  *v5 = 0; /*0x554567e*/
  return a1; /*0x5545688*/
}
