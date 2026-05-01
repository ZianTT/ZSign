// 0x5B7CB6C @ 0x5B7CB6C
// The function seems has been flattened
__int64 __fastcall sub_5B7CB6C(unsigned int *a1, _DWORD *a2, _DWORD *i_1)
{
  unsigned int v3; // ebx
  unsigned __int32 v4; // r12d
  unsigned __int32 v5; // r8d
  unsigned __int32 v6; // r13d
  unsigned __int32 v7; // r11d
  unsigned int v9; // [rsp+0h] [rbp-94h]
  unsigned int v10; // [rsp+4h] [rbp-90h]
  unsigned int v11; // [rsp+8h] [rbp-8Ch]
  unsigned int v12; // [rsp+Ch] [rbp-88h]
  _DWORD *v13; // [rsp+14h] [rbp-80h]
  bool v14; // [rsp+1Ch] [rbp-78h]
  int n5; // [rsp+24h] [rbp-70h]
  _DWORD *i; // [rsp+44h] [rbp-50h]

  if ( a2 ) /*0x5b7cd28*/
  {
    if ( !a1 ) /*0x5b7cd3a*/
      goto LABEL_5; /*0x5b7cd3a*/
    v14 = i_1 != 0; /*0x5b7cbb7*/
  }
  else
  {
    if ( !a1 ) /*0x5b7cd3a*/
    {
LABEL_5:
      v14 = 0; /*0x5b7cd3a*/
      goto LABEL_7; /*0x5b7cd46*/
    }
    v14 = 0; /*0x5b7cd3e*/
  }
LABEL_7:
  if ( v14 ) /*0x5b7cdff*/
  {
    v7 = *i_1 ^ _byteswap_ulong(*a1); /*0x5b7cc08*/
    v4 = i_1[1] ^ _byteswap_ulong(a1[1]); /*0x5b7cc0e*/
    v5 = i_1[2] ^ _byteswap_ulong(a1[2]); /*0x5b7cc19*/
    v6 = i_1[3] ^ _byteswap_ulong(a1[3]); /*0x5b7cc24*/
    n5 = 5; /*0x5b7cc33*/
    for ( i = i_1; ; i += 8 ) /*0x5b7cc38*/
    {
      v9 = i[4] /*0x5b7d09d*/
         ^ dword_D58620[(unsigned __int8)v6]
         ^ dword_D58220[BYTE1(v5)]
         ^ dword_D57A20[HIBYTE(v7)]
         ^ dword_D57E20[BYTE2(v4)];
      v10 = i[5] /*0x5b7d0cd*/
          ^ dword_D58620[(unsigned __int8)v7]
          ^ dword_D58220[BYTE1(v6)]
          ^ dword_D57A20[HIBYTE(v4)]
          ^ dword_D57E20[BYTE2(v5)];
      v11 = i[6] /*0x5b7d0fd*/
          ^ dword_D58620[(unsigned __int8)v4]
          ^ dword_D58220[BYTE1(v7)]
          ^ dword_D57A20[HIBYTE(v5)]
          ^ dword_D57E20[BYTE2(v6)];
      v12 = i[7] /*0x5b7d130*/
          ^ dword_D58620[(unsigned __int8)v5]
          ^ dword_D58220[BYTE1(v4)]
          ^ dword_D57A20[HIBYTE(v6)]
          ^ dword_D57E20[BYTE2(v7)];
      v13 = i + 8; /*0x5b7d138*/
      if ( n5 == 1 ) /*0x5b7d159*/
        break; /*0x5b7d159*/
      v4 = i[9] /*0x5b7ce9c*/
         ^ dword_D58620[(unsigned __int8)v9]
         ^ dword_D58220[BYTE1(v12)]
         ^ *(_DWORD *)((char *)dword_D57A20 + (((unsigned __int64)v10 >> 22) & 0x3FC))
         ^ *(_DWORD *)((char *)dword_D57E20 + (((unsigned __int64)v11 >> 14) & 0x3FC));
      v5 = i[10] /*0x5b7cedd*/
         ^ dword_D58620[(unsigned __int8)v10]
         ^ dword_D58220[BYTE1(v9)]
         ^ *(_DWORD *)((char *)dword_D57A20 + (((unsigned __int64)v11 >> 22) & 0x3FC))
         ^ *(_DWORD *)((char *)dword_D57E20 + (((unsigned __int64)v12 >> 14) & 0x3FC));
      v6 = i[11] /*0x5b7cf1e*/
         ^ dword_D58620[(unsigned __int8)v11]
         ^ dword_D58220[BYTE1(v10)]
         ^ *(_DWORD *)((char *)dword_D57A20 + (((unsigned __int64)v12 >> 22) & 0x3FC))
         ^ *(_DWORD *)((char *)dword_D57E20 + (((unsigned __int64)v9 >> 14) & 0x3FC));
      --n5; /*0x5b7cf30*/
      v7 = *v13 /*0x5b7cf3b*/
         ^ dword_D58620[(unsigned __int8)v12]
         ^ *(_DWORD *)((char *)dword_D57A20 + (((unsigned __int64)v9 >> 22) & 0x3FC))
         ^ *(_DWORD *)((char *)dword_D57E20 + (((unsigned __int64)v10 >> 14) & 0x3FC))
         ^ dword_D58220[BYTE1(v11)];
    }
    *a2 = _byteswap_ulong( /*0x5b7cfa4*/
            *v13
          ^ ((byte_D58A20[(((unsigned __int64)v9 >> 22) & 0x3FC) + 3] << 24)
           | (byte_D58A20[(((unsigned __int64)v10 >> 14) & 0x3FC) + 2] << 16)
           | (byte_D58A20[4 * BYTE1(v11) + 1] << 8)
           | byte_D58A20[4 * (unsigned __int8)v12]));
    a2[1] = _byteswap_ulong( /*0x5b7cffa*/
              i[9]
            ^ ((byte_D58A20[(((unsigned __int64)v10 >> 22) & 0x3FC) + 3] << 24)
             | (byte_D58A20[(((unsigned __int64)v11 >> 14) & 0x3FC) + 2] << 16)
             | (byte_D58A20[4 * BYTE1(v12) + 1] << 8)
             | byte_D58A20[4 * (unsigned __int8)v9]));
    a2[2] = _byteswap_ulong( /*0x5b7cdb7*/
              ((byte_D58A20[(((unsigned __int64)v11 >> 22) & 0x3FC) + 3] << 24)
             | (byte_D58A20[(((unsigned __int64)v12 >> 14) & 0x3FC) + 2] << 16)
             | (byte_D58A20[4 * BYTE1(v9) + 1] << 8)
             | byte_D58A20[4 * (unsigned __int8)v10])
            ^ i[10]);
    a2[3] = _byteswap_ulong( /*0x5b7cd96*/
              i[11]
            ^ (byte_D58A20[4 * BYTE1(v10) + 1] << 8)
            ^ (byte_D58A20[(((unsigned __int64)v9 >> 14) & 0x3FC) + 2] << 16)
            ^ (byte_D58A20[(((unsigned __int64)v12 >> 22) & 0x3FC) + 3] << 24)
            ^ byte_D58A20[4 * (unsigned __int8)v11]);
    LOBYTE(v3) = 1; /*0x5b7cda2*/
  }
  else
  {
    v3 = 0; /*0x5b7d168*/
  }
  LOBYTE(v3) = v3 & 1; /*0x5b7d18f*/
  return v3; /*0x5b7d194*/
}
