// 0x5B63780 @ 0x5B63780
// The function seems has been flattened
unsigned __int64 __fastcall sub_5B63780(__int64 a1, __int64 a2, __int64 a3, unsigned int a4)
{
  __int64 v4; // rax
  __int64 v5; // r15
  __int64 v7; // [rsp+8h] [rbp-50h]
  _QWORD v8[8]; // [rsp+18h] [rbp-40h] BYREF

  if ( (_DWORD)v4 != -1353097785 ) /*0x5b6381c*/
    goto LABEL_7; /*0x5b6381c*/
  v8[1] = v4; /*0x5b637b5*/
  if ( a4 ) /*0x5b637c7*/
    sub_5B743EC(a1, v7, a3, a4); /*0x5b63864*/
  if ( (_DWORD)v4 != -932647562 ) /*0x5b6387a*/
  {
    v5 = a3; /*0x5b63793*/
    if ( a3 ) /*0x5b637b2*/
    {
LABEL_7:
      *(_BYTE *)(*(_QWORD *)(a1 + 24) + a2) = 1; /*0x5b63827*/
      v8[0] = 0; /*0x5b63838*/
      sub_5B749DE(a1, v5, v8); /*0x5b63898*/
      *(_QWORD *)(*(_QWORD *)(a1 + 16) + 8 * a2) = v8[0]; /*0x5b638ba*/
      return __readfsqword(0x28u); /*0x5b638c7*/
    }
    *(_QWORD *)(*(_QWORD *)(a1 + 16) + 8 * a2) = 0; /*0x5b637fe*/
  }
  return __readfsqword(0x28u); /*0x5b638dc*/
}
