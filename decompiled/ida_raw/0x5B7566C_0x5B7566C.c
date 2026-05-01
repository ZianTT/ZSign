// 0x5B7566C @ 0x5B7566C
// The function seems has been flattened
_QWORD *__fastcall sub_5B7566C(_QWORD *a1, _QWORD *i1, void **login)
{
  char *v4; // rcx
  void *v5; // rdx
  __int64 v6; // rax
  bool v8; // zf
  size_t v9; // rax

  v4 = (char *)login[1]; /*0x5b7568e*/
  if ( v4 ) /*0x5b75695*/
  {
    v5 = *login; /*0x5b75697*/
    v6 = (__int64)v4; /*0x5b7569a*/
    while ( v6-- != 0 ) /*0x5b7569d*/
    {
      v8 = v4[(_QWORD)v5 - 1] == 47; /*0x5b756a3*/
      v4 = (char *)v6; /*0x5b756a8*/
      if ( v8 ) /*0x5b756ab*/
        goto LABEL_7; /*0x5b756ab*/
    }
  }
  v6 = -1; /*0x5b756af*/
LABEL_7:
  if ( v6 == -1 ) /*0x5b75716*/
  {
    *a1 = a1 + 2; /*0x5b7571b*/
    v9 = strlen_w(&s_); /*0x5b75721*/
    std::string::_M_construct<char const*>(a1, &s_, &s_ + v9); /*0x5b75730*/
  }
  else
  {
    sub_55455C8(a1, login, 0, v6); /*0x5b7575f*/
  }
  return a1; /*0x5b75781*/
}
