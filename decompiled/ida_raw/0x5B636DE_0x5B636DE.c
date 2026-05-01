// 0x5B636DE @ 0x5B636DE
// The function seems has been flattened
__int64 __fastcall sub_5B636DE(__int64 a1)
{
  char *v1; // rdi
  unsigned int i; // ecx
  unsigned int i_1; // edx
  char n74; // [rsp+1h] [rbp-Dh]

  v1 = (char *)(a1 + 1); /*0x5b636de*/
  for ( i = 0; ; i = i_1 ) /*0x5b636e6*/
  {
    n74 = *v1; /*0x5b63728*/
    if ( !*v1 ) /*0x5b63728*/
      break; /*0x5b63728*/
    if ( n74 == 74 || n74 == 68 ) /*0x5b6375a*/
      i_1 = i + 2; /*0x5b63760*/
    else
      i_1 = i + 1; /*0x5b6376e*/
    ++v1; /*0x5b63741*/
  }
  return i; /*0x5b6377e*/
}
