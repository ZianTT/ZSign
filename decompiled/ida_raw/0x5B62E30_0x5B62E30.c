// 0x5B62E30 @ 0x5B62E30
// The function seems has been flattened
char __fastcall sub_5B62E30(_QWORD *a1, __int64 a2)
{
  char v2; // al

  v2 = *(_BYTE *)(a1[3] + a2); /*0x5b62e34*/
  if ( (v2 & 1) != 0 ) /*0x5b62e9e*/
    return *(_QWORD *)(a1[4] + 8LL * *(_QWORD *)(a1[2] + 8 * a2)); /*0x5b62e88*/
  else
    return 0; /*0x5b62ea9*/
}
