// 0x5B62EE8 @ 0x5B62EE8
__int64 __fastcall sub_5B62EE8(__int64 a1, unsigned __int16 *a2)
{
  *(_QWORD *)a1 = a2; /*0x5b62eec*/
  sub_5B62F12(a1 + 8, *a2); /*0x5b62ef6*/
  *(_QWORD *)(a1 + 64) = a1 + 80; /*0x5b62eff*/
  *(_QWORD *)(a1 + 72) = 0; /*0x5b62f03*/
  *(_BYTE *)(a1 + 80) = 0; /*0x5b62f0b*/
  return a1 + 80; /*0x5b62f0f*/
}
