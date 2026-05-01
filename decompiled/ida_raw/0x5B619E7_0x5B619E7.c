// 0x5B619E7 @ 0x5B619E7
__int64 sub_5B619E7(unsigned __int64 sub_5B7CB6C, ...)
{
  void *dest; // rbx
  __int64 v2; // rbx
  gcc_va_list va; // [rsp+B0h] [rbp-A8h] BYREF
  __int64 i1[17]; // [rsp+D0h] [rbp-88h] BYREF

  va_start(va, sub_5B7CB6C); /*0x5b61aa2*/
  i1[12] = __readfsqword(0x28u); /*0x5b61a52*/
  dest = malloc(0x1BCu); /*0x5b61a64*/
  memcpy(dest, &src__0, 0x1BCu); /*0x5b61a76*/
  sub_5B62EE8((__int64)i1, (unsigned __int16 *)dest); /*0x5b61a89*/
  sub_5B62F7E((unsigned __int16 **)i1, sub_5B7CB6C, (int *)va); /*0x5b61ab9*/
  v2 = sub_5B64F10((__int64)i1, sub_5B7CB6C); /*0x5b61ac6*/
  sub_5B6195C((__int64)i1); /*0x5b61acc*/
  return v2; /*0x5b61ae7*/
}
