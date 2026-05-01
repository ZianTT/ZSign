// 0x2BF4E50 @ 0x2BF4E50
bool __fastcall sub_2BF4E50(__int64 a1, __int64 a2, __int64 a3, __int64 a4, int a5)
{
  __int64 v8; // rax
  __int64 v9; // rbx
  char *v10; // rax
  __int64 v11; // rax
  __int64 v12; // rax
  __int64 v13; // rax
  __int64 v14; // rdi
  int v15; // ebp
  char v17; // [rsp+0h] [rbp-388h] BYREF
  char v18; // [rsp+1h] [rbp-387h] BYREF
  void *v19; // [rsp+10h] [rbp-378h]
  __int64 v20; // [rsp+18h] [rbp-370h] BYREF
  __int64 v21; // [rsp+20h] [rbp-368h]
  _BYTE v22[16]; // [rsp+28h] [rbp-360h] BYREF
  void *v23; // [rsp+38h] [rbp-350h]
  _BYTE v24[16]; // [rsp+40h] [rbp-348h] BYREF
  void *v25; // [rsp+50h] [rbp-338h]
  _QWORD dest[31]; // [rsp+58h] [rbp-330h] BYREF
  unsigned __int8 v27; // [rsp+157h] [rbp-231h]
  _BYTE v28[256]; // [rsp+158h] [rbp-230h] BYREF
  _BYTE v29[304]; // [rsp+258h] [rbp-130h] BYREF

  if ( (*(_BYTE *)(a1 + 8) & 1) != 0 ) /*0x2bf4e73*/
    goto LABEL_24; /*0x2bf4e73*/
  *(_BYTE *)(a1 + 8) = 1; /*0x2bf4e7e*/
  sub_2C63050(v24, a1 + 112); /*0x2bf4e8d*/
  sub_2BF55C0(49, 0, "nt_mmkv_o3", &byte_7BD53E, v24); /*0x2bf4eaa*/
  if ( (*(_BYTE *)(a1 + 16) & 1) != 0 ) /*0x2bf4eb3*/
    v8 = *(_QWORD *)(a1 + 32); /*0x2bf4eb5*/
  else
    v8 = a1 + 17; /*0x2bf4ebb*/
  dest[0] = v8; /*0x2bf4ebf*/
  sub_29FF8E0(&v20); /*0x2bf4ec9*/
  sub_29FFC30(&v17, v20); /*0x2bf4ed6*/
  v9 = v21; /*0x2bf4edb*/
  if ( v21 && !_InterlockedExchangeAdd64((volatile signed __int64 *)(v21 + 8), 0xFFFFFFFFFFFFFFFFLL) ) /*0x2bf4ef5*/
  {
    (*(void (__fastcall **)(__int64))(*(_QWORD *)v9 + 16LL))(v9); /*0x2bf4f0a*/
    sub_2C61BF0(v9); /*0x2bf4f10*/
    if ( (v17 & 1) != 0 ) /*0x2bf4f19*/
      goto LABEL_8; /*0x2bf4f19*/
LABEL_10:
    v10 = &v18; /*0x2bf4f1b*/
    goto LABEL_11; /*0x2bf4f1b*/
  }
  if ( (v17 & 1) == 0 ) /*0x2bf4efb*/
    goto LABEL_10; /*0x2bf4efb*/
LABEL_8:
  v10 = (char *)v19; /*0x2bf4efd*/
LABEL_11:
  dest[1] = v10; /*0x2bf4f20*/
  if ( (*(_BYTE *)(a1 + 64) & 1) != 0 ) /*0x2bf4f29*/
    v11 = *(_QWORD *)(a1 + 80); /*0x2bf4f2b*/
  else
    v11 = a1 + 65; /*0x2bf4f31*/
  dest[2] = v11; /*0x2bf4f35*/
  if ( (*(_BYTE *)(a1 + 88) & 1) != 0 ) /*0x2bf4f3e*/
    v12 = *(_QWORD *)(a1 + 104); /*0x2bf4f40*/
  else
    v12 = a1 + 89; /*0x2bf4f46*/
  dest[3] = v12; /*0x2bf4f4a*/
  if ( (*(_BYTE *)(a1 + 112) & 1) != 0 ) /*0x2bf4f53*/
    v13 = *(_QWORD *)(a1 + 128); /*0x2bf4f55*/
  else
    v13 = a1 + 113; /*0x2bf4f5e*/
  dest[4] = v13; /*0x2bf4f62*/
  sub_5574B1D((__int64)sub_2BF4610, (__int64)sub_2BF4A80, (__int64)sub_2BF4C90); /*0x2bf4f7c*/
  sub_5575184((__int64)dest); /*0x2bf4f86*/
  sub_2BF4CD0(a1); /*0x2bf4f8e*/
  if ( (v17 & 1) != 0 ) /*0x2bf4f97*/
    operator delete(v19); /*0x2bf4f9e*/
  if ( (v24[0] & 1) != 0 ) /*0x2bf4fa8*/
    operator delete(v25); /*0x2bf4faf*/
LABEL_24:
  if ( (*(_BYTE *)a2 & 1) != 0 ) /*0x2bf4fb8*/
    v14 = *(_QWORD *)(a2 + 16); /*0x2bf4fba*/
  else
    v14 = a2 + 1; /*0x2bf4fc0*/
  v15 = sub_557A6A0(v14, *(_QWORD *)a3, *(_DWORD *)(a3 + 8) - (unsigned int)*(_QWORD *)a3, a5, dest); /*0x2bf4fdb*/
  if ( v15 ) /*0x2bf4fdf*/
  {
    sub_2C63050(v22, a2); /*0x2bf4fec*/
    sub_2326DB0( /*0x2bf5021*/
      "MSFSecuritySignCallback",
      4,
      "msf_security_sign_callback.cc",
      138,
      "MSFSign",
      "MSFSign failed, module_id:{} data:{}",
      v22,
      *(_QWORD *)(a3 + 8) - *(_QWORD *)a3);
    if ( (v22[0] & 1) != 0 ) /*0x2bf502f*/
      operator delete(v23); /*0x2bf5036*/
  }
  else
  {
    sub_2C63AB0(a4, dest, v27); /*0x2bf504d*/
    sub_2C63AB0(a4 + 24, v28, v28[255]); /*0x2bf5066*/
    sub_2C63AB0(a4 + 48, v29, v29[255]); /*0x2bf5082*/
  }
  return v15 == 0; /*0x2bf508c*/
}
