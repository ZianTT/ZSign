// 0x5B7D5DC @ 0x5B7D5DC
__int64 sub_5B7D5DC(unsigned __int64 sub_5B7CB6C, ...)
{
  void *dest_1; // r15
  __int128 *i1_1; // rbp
  __int128 v3; // xmm1
  __int128 v4; // xmm2
  __int64 v5; // rbx
  _BYTE dest[3120]; // [rsp+B0h] [rbp-D88h] BYREF
  __int128 v8; // [rsp+CE0h] [rbp-158h]
  __int128 v9; // [rsp+CF0h] [rbp-148h]
  __int128 v10; // [rsp+D00h] [rbp-138h]
  _BYTE dst[112]; // [rsp+D10h] [rbp-128h] BYREF
  gcc_va_list va; // [rsp+D80h] [rbp-B8h] BYREF
  __int64 i1[19]; // [rsp+DA0h] [rbp-98h] BYREF

  va_start(va, sub_5B7CB6C); /*0x5b7d70c*/
  i1[12] = __readfsqword(0x28u); /*0x5b7d645*/
  dest_1 = malloc(0xCC0u); /*0x5b7d657*/
  sub_55FDCC0(&once_control_); /*0x5b7d669*/
  i1_1 = (__int128 *)::i1; /*0x5b7d675*/
  memcpy(dest, &src__2, sizeof(dest)); /*0x5b7d692*/
  v3 = i1_1[1]; /*0x5b7d69b*/
  v4 = i1_1[2]; /*0x5b7d69f*/
  v8 = *i1_1; /*0x5b7d6a3*/
  v9 = v3; /*0x5b7d6ac*/
  v10 = v4; /*0x5b7d6b5*/
  qmemcpy(dst, &src__3, 0x80u); /*0x5b7d6d2*/
  memcpy(dest_1, dest, 0xCC0u); /*0x5b7d6e0*/
  sub_5B62EE8((__int64)i1, (unsigned __int16 *)dest_1); /*0x5b7d6f3*/
  sub_5B62F7E((unsigned __int16 **)i1, sub_5B7CB6C, (int *)va); /*0x5b7d723*/
  v5 = sub_5B64F10((__int64)i1, sub_5B7CB6C); /*0x5b7d730*/
  sub_5B6195C((__int64)i1); /*0x5b7d736*/
  return v5; /*0x5b7d751*/
}
