// 0x5B6CA2E @ 0x5B6CA2E
// The function seems has been flattened
__int64 __fastcall sub_5B6CA2E(__int64 i1, __int64 (__fastcall *sub_5B7CB6C)(), unsigned __int16 *n992921659)
{
  unsigned int v3; // ebp
  _QWORD *v4; // rbx
  __int64 v5; // rax
  __int64 v6; // rax
  __int64 v7; // rax
  int v9; // [rsp+14h] [rbp-94h]
  __int64 v10; // [rsp+20h] [rbp-88h]
  __int64 v11; // [rsp+28h] [rbp-80h]
  __int64 v12; // [rsp+50h] [rbp-58h] BYREF
  unsigned int v13; // [rsp+58h] [rbp-50h]
  unsigned int v14; // [rsp+5Ch] [rbp-4Ch]
  unsigned int v15; // [rsp+60h] [rbp-48h]
  unsigned __int64 v16; // [rsp+70h] [rbp-38h]

  v16 = __readfsqword(0x28u); /*0x5b6ca4e*/
  v4 = (_QWORD *)(i1 + 8); /*0x5b6ca63*/
  if ( n992921659 && sub_5B7CB6C ) /*0x5b6cb41*/
  {
    sub_5B6CBD2(n992921659, &v12); /*0x5b6cb5a*/
    LOBYTE(v6) = sub_5B62E30(v4, HIDWORD(v12)); /*0x5b6cb6d*/
    v10 = v6; /*0x5b6cb72*/
    LOBYTE(v7) = sub_5B62E30(v4, v13); /*0x5b6cb80*/
    v11 = v7; /*0x5b6cb85*/
    v9 = *(_DWORD *)(*(_QWORD *)(i1 + 24) + 8LL * v14); /*0x5b6cb9a*/
    LOBYTE(v5) = sub_5B62E30((_QWORD *)(i1 + 8), v15); /*0x5b6caf3*/
    ((void (__fastcall *)(_QWORD, _QWORD, _QWORD))sub_5B7CB6C)( /*0x5b6cad9*/
      *(_QWORD *)(v10 + 8),
      *(_QWORD *)(v11 + 8) + v9,
      *(_QWORD *)(v5 + 8));
    LOBYTE(v3) = 1; /*0x5b6cae5*/
  }
  else
  {
    v3 = 0; /*0x5b6ca9c*/
  }
  LOBYTE(v3) = v3 & 1; /*0x5b6cbb8*/
  return v3; /*0x5b6cbbe*/
}
