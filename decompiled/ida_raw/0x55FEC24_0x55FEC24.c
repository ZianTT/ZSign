// 0x55FEC24 @ 0x55FEC24
__int64 __fastcall sub_55FEC24(__int64 a1, unsigned __int64 a2, unsigned __int64 a3, __int64 a4, __int64 a5)
{
  unsigned __int64 v5; // rax
  bool v6; // cf
  unsigned __int64 v7; // rax

  v5 = *(_QWORD *)(a1 + 8); /*0x55fec2c*/
  v6 = v5 < a2; /*0x55fec2f*/
  v7 = v5 - a2; /*0x55fec2f*/
  if ( v6 )
    std::__throw_out_of_range_fmt(
      "%s: __pos (which is %zu) > this->size() (which is %zu)",
      "basic_string::replace",
      a2,
      *(_QWORD *)(a1 + 8));
  if ( v7 > a3 ) /*0x55fec37*/
    v7 = a3; /*0x55fec37*/
  return std::string::_M_replace(a1, a2, v7, a4, a5);
}
