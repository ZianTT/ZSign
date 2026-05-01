// 0x5B74386 @ 0x5B74386
// The function seems has been flattened
bool __fastcall sub_5B74386(__int64 i1, int a2, int a3)
{
  __int64 v3; // rcx
  int v4; // eax
  int v7; // [rsp+0h] [rbp-8h]

  v3 = *(_QWORD *)(i1 + 16); /*0x5b74389*/
  v7 = *(_DWORD *)(v3 + 8LL * a2); /*0x5b74390*/
  v4 = *(_DWORD *)(v3 + 8LL * a3); /*0x5b74397*/
  return v7 == v4 || (unsigned __int8)v7 == (unsigned __int8)v4; /*0x5b743ea*/
}
