// 0x5B61848 @ 0x5B61848
__int64 sub_5B61848(unsigned __int64 sub_5B7CB6C, ...)
{
  void *dest; // rbx
  __int64 v2; // rbx
  gcc_va_list va; // [rsp+B0h] [rbp-A8h] BYREF
  __int64 i1[17]; // [rsp+D0h] [rbp-88h] BYREF

  va_start(va, sub_5B7CB6C); /*0x5b61903*/
  i1[12] = __readfsqword(0x28u); /*0x5b618b3*/
  dest = malloc(0x1DEu); /*0x5b618c5*/
  memcpy(dest, &src__1, 0x1DEu); /*0x5b618d7*/
  sub_5B62EE8((__int64)i1, (unsigned __int16 *)dest); /*0x5b618ea*/
  sub_5B62F7E((unsigned __int16 **)i1, sub_5B7CB6C, (int *)va); /*0x5b6191a*/
  v2 = sub_5B64F10((__int64)i1, sub_5B7CB6C); /*0x5b61927*/
  sub_5B6195C((__int64)i1); /*0x5b6192d*/
  return v2; /*0x5b61948*/
}
