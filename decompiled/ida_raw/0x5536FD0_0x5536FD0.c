// 0x5536FD0 @ 0x5536FD0
__int64 __fastcall sub_5536FD0(_QWORD *a1, const char *s)
{
  __int64 v2; // rdx

  *a1 = a1 + 2; /*0x5536fde*/
  if ( s ) /*0x5536fe4*/
    v2 = (__int64)&s[strlen_w(s)]; /*0x5536ff1*/
  else
    v2 = -1; /*0x5536ff6*/
  return std::string::_M_construct<char const*>(a1, s, v2); /*0x5537007*/
}
