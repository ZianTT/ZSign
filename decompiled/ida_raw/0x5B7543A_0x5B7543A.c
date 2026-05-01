// 0x5B7543A @ 0x5B7543A
// The function seems has been flattened
unsigned __int64 __fastcall sub_5B7543A(_QWORD *i1, void **login)
{
  void *v3[2]; // [rsp+8h] [rbp-50h] BYREF
  char v4; // [rsp+18h] [rbp-40h] BYREF
  unsigned __int64 v5; // [rsp+28h] [rbp-30h]

  v5 = __readfsqword(0x28u); /*0x5b75455*/
  if ( !i1[8] ) /*0x5b7548f*/
  {
    sub_5B7566C(v3, i1, login); /*0x5b754a7*/
    sub_55455F8(i1 + 7, v3); /*0x5b754b3*/
    if ( v3[0] != &v4 ) /*0x5b754c0*/
      operator delete(v3[0]); /*0x5b754c2*/
  }
  return __readfsqword(0x28u); /*0x5b754de*/
}
