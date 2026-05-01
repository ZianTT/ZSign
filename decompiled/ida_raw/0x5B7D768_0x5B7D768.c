// 0x5B7D768 @ 0x5B7D768
__int64 __fastcall sub_5B7D768(void *src, unsigned int a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, char a7)
{
  _WORD *v7; // r14
  char *dest; // r12
  __int64 n_2; // rax
  size_t n_1; // rbx
  size_t n; // rdx

  v7 = malloc(0x10u); /*0x5b7d77f*/
  *(_DWORD *)v7 = a2; /*0x5b7d782*/
  v7[2] = 32; /*0x5b7d784*/
  dest = (char *)malloc(a2 + 1LL); /*0x5b7d794*/
  *((_QWORD *)v7 + 1) = dest; /*0x5b7d797*/
  n_2 = a2 + 1; /*0x5b7d79b*/
  n_1 = a2 - 1; /*0x5b7d79e*/
  n = n_2 - n_1; /*0x5b7d7a3*/
  if ( (unsigned int)n_2 <= (unsigned int)n_1 ) /*0x5b7d7aa*/
    n = 0; /*0x5b7d7aa*/
  memset(&dest[n_1], 0, n); /*0x5b7d7b4*/
  memcpy(dest, src, n_1); /*0x5b7d7c2*/
  dest[n_1] = 4; /*0x5b7d7c7*/
  return sub_5B7D5DC((unsigned __int64)"LL", a7); /*0x5b7d7dc*/
}
