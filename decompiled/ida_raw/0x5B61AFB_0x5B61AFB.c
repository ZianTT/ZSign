// 0x5B61AFB @ 0x5B61AFB
__int64 sub_5B61AFB(__int64 a1, unsigned __int64 LLL, ...)
{
  void *dest; // rbx
  __int64 v3; // rbx
  gcc_va_list va; // [rsp+B0h] [rbp-A8h] BYREF
  __int64 i1[8]; // [rsp+C8h] [rbp-90h] BYREF
  _BYTE v7[32]; // [rsp+108h] [rbp-50h] BYREF
  unsigned __int64 v8; // [rsp+128h] [rbp-30h]

  va_start(va, LLL); /*0x5b61bc2*/
  v8 = __readfsqword(0x28u); /*0x5b61b62*/
  dest = malloc(0x17Au); /*0x5b61b74*/
  memcpy(dest, &src_, 0x17Au); /*0x5b61b86*/
  sub_5B62EE8((__int64)i1, (unsigned __int16 *)dest); /*0x5b61b99*/
  std::string::_M_assign(v7, a1); /*0x5b61ba9*/
  sub_5B62F7E((unsigned __int16 **)i1, LLL, (int *)va); /*0x5b61bd9*/
  v3 = sub_5B64F10((__int64)i1, LLL); /*0x5b61be6*/
  sub_5B6195C(i1); /*0x5b61bec*/
  return v3; /*0x5b61c07*/
}
