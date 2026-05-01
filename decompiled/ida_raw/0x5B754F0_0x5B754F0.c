// 0x5B754F0 @ 0x5B754F0
// The function seems has been flattened
unsigned __int64 __fastcall sub_5B754F0(void *i1, char *dest, int n496, unsigned int i)
{
  int j; // r11d
  int j_1; // ebx
  _BYTE v7[4]; // [rsp+14h] [rbp-14h]
  unsigned __int64 v8; // [rsp+18h] [rbp-10h]

  v8 = __readfsqword(0x28u); /*0x5b754fe*/
  v7[0] = HIBYTE(i); /*0x5b75567*/
  v7[1] = BYTE2(i); /*0x5b7556b*/
  v7[2] = BYTE1(i); /*0x5b75570*/
  v7[3] = i; /*0x5b7558c*/
  for ( j = 0; j < n496; ++j ) /*0x5b75595*/
  {
    j_1 = j + 3; /*0x5b755bd*/
    if ( j >= 0 ) /*0x5b755c2*/
      j_1 = j; /*0x5b755c2*/
    dest[j] ^= v7[j - (j_1 & 0xFFFFFFFC)]; /*0x5b755d1*/
  }
  return __readfsqword(0x28u); /*0x5b755fc*/
}
