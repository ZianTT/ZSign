// 0x5B6CFF4 @ 0x5B6CFF4
// The function seems has been flattened
unsigned __int64 __fastcall sub_5B6CFF4(__int64 a1, _OWORD *a2, __int64 a3, __int64 a4)
{
  _QWORD *v4; // r15
  _QWORD *v5; // rcx
  _QWORD *v6; // rsi
  _QWORD *v7; // r8
  int i; // r9d
  __int64 v9; // rax
  __int64 v10; // rax
  __int64 v11; // rax
  __int64 v12; // rax
  __int64 v13; // rax
  __int64 v14; // rax
  __int64 v15; // rax
  __int64 v16; // rax
  __int64 v17; // rax
  __int64 v18; // rax
  __int64 v19; // rax
  __int64 v20; // rax
  __int64 v21; // rax
  __int64 v22; // rax
  __int64 v23; // rax
  __int64 v24; // rax
  __int64 v25; // rax
  __int64 v26; // rax
  __int64 v27; // rax
  int j; // r11d
  __int64 v29; // rax
  __int64 v30; // rax
  __int64 v31; // rax
  __int64 v32; // rax
  __int64 v33; // rax
  __int64 v34; // rax
  __int64 v35; // rax
  __int64 v36; // rax
  __int64 v37; // rax
  __int64 v38; // rax
  __int64 v39; // rax
  __int64 v40; // rax
  __int64 v41; // rax
  __int64 v42; // rax
  __int64 v43; // rax
  __int64 v44; // rax
  __int64 v45; // rax
  __int64 v46; // rax
  __int64 v47; // rax
  __int64 v48; // rax
  __int64 v49; // rax
  __int64 v50; // rax
  __int64 v51; // rax
  __int64 v52; // rax
  int k; // r10d
  __int64 v54; // rax
  __int64 v55; // rax
  __int64 v56; // rax
  __int64 v57; // rax
  __int64 v58; // rax
  __int64 v59; // rax
  __int64 v60; // rax
  __int64 v61; // rax
  __int64 v62; // rax
  __int64 v63; // rax
  __int64 v64; // rax
  __int64 v65; // rax
  __int64 v66; // rax
  _DWORD *v68; // [rsp+0h] [rbp-178h]
  _DWORD *v69; // [rsp+8h] [rbp-170h]
  _DWORD *v70; // [rsp+10h] [rbp-168h]
  _DWORD *v71; // [rsp+20h] [rbp-158h]
  _DWORD *v72; // [rsp+38h] [rbp-140h]
  _DWORD *v73; // [rsp+50h] [rbp-128h]
  _DWORD *v74; // [rsp+68h] [rbp-110h]
  _QWORD *v75; // [rsp+98h] [rbp-E0h]
  _QWORD *v76; // [rsp+A0h] [rbp-D8h]
  _QWORD *v77; // [rsp+A8h] [rbp-D0h]
  _QWORD *v78; // [rsp+B0h] [rbp-C8h]
  _QWORD *v79; // [rsp+B8h] [rbp-C0h]
  _QWORD *v80; // [rsp+C0h] [rbp-B8h]
  _QWORD *v81; // [rsp+C8h] [rbp-B0h]
  _QWORD *v82; // [rsp+D0h] [rbp-A8h]
  _OWORD v83[3]; // [rsp+100h] [rbp-78h]
  __int64 v84; // [rsp+130h] [rbp-48h]
  __int64 v85; // [rsp+138h] [rbp-40h]
  unsigned __int64 v86; // [rsp+140h] [rbp-38h]

  v86 = __readfsqword(0x28u); /*0x5b6d00e*/
  v83[0] = xmmword_990380; /*0x5b6d035*/
  v83[1] = *a2; /*0x5b6d03b*/
  v83[2] = a2[1]; /*0x5b6d043*/
  v84 = a4; /*0x5b6d047*/
  v85 = a3; /*0x5b6d051*/
  v82 = (_QWORD *)(a1 + 32); /*0x5b6d05f*/
  v81 = (_QWORD *)(a1 + 96); /*0x5b6d06b*/
  v80 = (_QWORD *)(a1 + 64); /*0x5b6d077*/
  v79 = (_QWORD *)(a1 + 40); /*0x5b6d083*/
  v78 = (_QWORD *)(a1 + 8); /*0x5b6d08f*/
  v77 = (_QWORD *)(a1 + 104); /*0x5b6d09b*/
  v76 = (_QWORD *)(a1 + 72); /*0x5b6d0a7*/
  v4 = (_QWORD *)(a1 + 16); /*0x5b6d0b3*/
  v5 = (_QWORD *)(a1 + 80); /*0x5b6d0bb*/
  v6 = (_QWORD *)(a1 + 24); /*0x5b6d0c3*/
  v7 = (_QWORD *)(a1 + 88); /*0x5b6d0cb*/
  for ( i = 0; i < 16; ++i ) /*0x5b6d0d5*/
    *(_QWORD *)(a1 + 8LL * i) = *((unsigned int *)v83 + i); /*0x5b6d11d*/
  for ( j = 0; j < 10; ++j ) /*0x5b6d415*/
  {
    v68 = (_DWORD *)(a1 + 32); /*0x5b6d432*/
    v29 = *(_QWORD *)a1 + *(unsigned int *)v82; /*0x5b6d43c*/
    *(_QWORD *)a1 = v29; /*0x5b6d43f*/
    v71 = (_DWORD *)(a1 + 96); /*0x5b6d44c*/
    v30 = ((*(_DWORD *)(a1 + 96) ^ (unsigned int)v29) << 16) /*0x5b6d462*/
        | (unsigned int)((*(_QWORD *)(a1 + 96) ^ (unsigned __int64)(unsigned int)v29) >> 16);
    *v81 = v30; /*0x5b6d469*/
    v31 = *v80 + v30; /*0x5b6d47e*/
    *v80 = v31; /*0x5b6d486*/
    v32 = ((*v68 ^ (unsigned int)v31) << 12) /*0x5b6d49b*/
        | (unsigned int)((*(_QWORD *)v68 ^ (unsigned __int64)(unsigned int)v31) >> 20);
    *v82 = v32; /*0x5b6d4a1*/
    v33 = *(_QWORD *)a1 + v32; /*0x5b6d4a4*/
    *(_QWORD *)a1 = v33; /*0x5b6d4a7*/
    v34 = ((*v71 ^ (unsigned int)v33) << 8) /*0x5b6d4bd*/
        | (unsigned int)((*(_QWORD *)v71 ^ (unsigned __int64)(unsigned int)v33) >> 24);
    *v81 = v34; /*0x5b6d4c4*/
    v35 = *v80 + v34; /*0x5b6d4cc*/
    *v80 = v35; /*0x5b6d4d4*/
    *(_QWORD *)(a1 + 32) = ((*(_DWORD *)(a1 + 32) ^ (unsigned int)v35) << 7) /*0x5b6d4ef*/
                         | (unsigned int)((*(_QWORD *)(a1 + 32) ^ (unsigned __int64)(unsigned int)v35) >> 25);
    v69 = (_DWORD *)(a1 + 40); /*0x5b6d4fa*/
    v36 = *v78 + *(unsigned int *)v79; /*0x5b6d518*/
    *v78 = v36; /*0x5b6d520*/
    v72 = (_DWORD *)(a1 + 104); /*0x5b6d52b*/
    v37 = ((*(_DWORD *)(a1 + 104) ^ (unsigned int)v36) << 16) /*0x5b6d543*/
        | (unsigned int)((*(_QWORD *)(a1 + 104) ^ (unsigned __int64)(unsigned int)v36) >> 16);
    *v77 = v37; /*0x5b6d54a*/
    v38 = *v76 + v37; /*0x5b6d55f*/
    *v76 = v38; /*0x5b6d567*/
    v39 = ((*v69 ^ (unsigned int)v38) << 12) /*0x5b6d57d*/
        | (unsigned int)((*(_QWORD *)v69 ^ (unsigned __int64)(unsigned int)v38) >> 20);
    *v79 = v39; /*0x5b6d584*/
    v40 = *v78 + v39; /*0x5b6d58c*/
    *v78 = v40; /*0x5b6d594*/
    v41 = ((*v72 ^ (unsigned int)v40) << 8) /*0x5b6d5aa*/
        | (unsigned int)((*(_QWORD *)v72 ^ (unsigned __int64)(unsigned int)v40) >> 24);
    *v77 = v41; /*0x5b6d5b1*/
    v42 = *v76 + v41; /*0x5b6d5b9*/
    *v76 = v42; /*0x5b6d5c1*/
    *(_QWORD *)(a1 + 40) = ((*(_DWORD *)(a1 + 40) ^ (unsigned int)v42) << 7) /*0x5b6d5de*/
                         | (unsigned int)((*(_QWORD *)(a1 + 40) ^ (unsigned __int64)(unsigned int)v42) >> 25);
    v70 = (_DWORD *)(a1 + 48); /*0x5b6d5e1*/
    v43 = *v4 + *(unsigned int *)(a1 + 48); /*0x5b6d5f7*/
    *v4 = v43; /*0x5b6d5ff*/
    v73 = (_DWORD *)(a1 + 112); /*0x5b6d604*/
    v44 = ((*(_DWORD *)(a1 + 112) ^ (unsigned int)v43) << 16) /*0x5b6d61a*/
        | (unsigned int)((*(_QWORD *)(a1 + 112) ^ (unsigned __int64)(unsigned int)v43) >> 16);
    *(_QWORD *)(a1 + 112) = v44; /*0x5b6d621*/
    v45 = *v5 + v44; /*0x5b6d62e*/
    *v5 = v45; /*0x5b6d636*/
    v46 = ((*v70 ^ (unsigned int)v45) << 12) /*0x5b6d64c*/
        | (unsigned int)((*(_QWORD *)v70 ^ (unsigned __int64)(unsigned int)v45) >> 20);
    *(_QWORD *)(a1 + 48) = v46; /*0x5b6d653*/
    v47 = *(_QWORD *)(a1 + 16) + v46; /*0x5b6d65b*/
    *(_QWORD *)(a1 + 16) = v47; /*0x5b6d663*/
    v48 = ((*v73 ^ (unsigned int)v47) << 8) /*0x5b6d679*/
        | (unsigned int)((*(_QWORD *)v73 ^ (unsigned __int64)(unsigned int)v47) >> 24);
    *(_QWORD *)(a1 + 112) = v48; /*0x5b6d680*/
    v49 = *(_QWORD *)(a1 + 80) + v48; /*0x5b6d688*/
    *(_QWORD *)(a1 + 80) = v49; /*0x5b6d690*/
    *(_QWORD *)(a1 + 48) = ((*(_DWORD *)(a1 + 48) ^ (unsigned int)v49) << 7) /*0x5b6d6ad*/
                         | (unsigned int)((*(_QWORD *)(a1 + 48) ^ (unsigned __int64)(unsigned int)v49) >> 25);
    v50 = *v6 + *(unsigned int *)(a1 + 56); /*0x5b6d6c6*/
    *v6 = v50; /*0x5b6d6ce*/
    v74 = (_DWORD *)(a1 + 120); /*0x5b6d6d3*/
    v51 = ((*(_DWORD *)(a1 + 120) ^ (unsigned int)v50) << 16) /*0x5b6d6e9*/
        | (unsigned int)((*(_QWORD *)(a1 + 120) ^ (unsigned __int64)(unsigned int)v50) >> 16);
    *(_QWORD *)(a1 + 120) = v51; /*0x5b6d6f0*/
    v52 = *v7 + v51; /*0x5b6d6fd*/
    *v7 = v52; /*0x5b6d705*/
    v9 = (((unsigned int)*(_QWORD *)(a1 + 56) ^ (unsigned int)v52) << 12) /*0x5b6d1e6*/
       | (unsigned int)((*(_QWORD *)(a1 + 56) ^ (unsigned __int64)(unsigned int)v52) >> 20);
    *(_QWORD *)(a1 + 56) = v9; /*0x5b6d1ed*/
    v10 = *(_QWORD *)(a1 + 24) + v9; /*0x5b6d1f5*/
    *(_QWORD *)(a1 + 24) = v10; /*0x5b6d1fd*/
    v11 = ((*v74 ^ (unsigned int)v10) << 8) /*0x5b6d213*/
        | (unsigned int)((*(_QWORD *)v74 ^ (unsigned __int64)(unsigned int)v10) >> 24);
    *(_QWORD *)(a1 + 120) = v11; /*0x5b6d21a*/
    v12 = *(_QWORD *)(a1 + 88) + v11; /*0x5b6d222*/
    *(_QWORD *)(a1 + 88) = v12; /*0x5b6d22a*/
    *(_QWORD *)(a1 + 56) = ((*(_DWORD *)(a1 + 56) ^ (unsigned int)v12) << 7) /*0x5b6d247*/
                         | (unsigned int)((*(_QWORD *)(a1 + 56) ^ (unsigned __int64)(unsigned int)v12) >> 25);
    v13 = *(_QWORD *)a1 + *(unsigned int *)(a1 + 40); /*0x5b6d251*/
    *(_QWORD *)a1 = v13; /*0x5b6d254*/
    v14 = ((*v74 ^ (unsigned int)v13) << 16) /*0x5b6d26a*/
        | (unsigned int)((*(_QWORD *)v74 ^ (unsigned __int64)(unsigned int)v13) >> 16);
    *(_QWORD *)(a1 + 120) = v14; /*0x5b6d271*/
    v15 = *(_QWORD *)(a1 + 80) + v14; /*0x5b6d279*/
    *(_QWORD *)(a1 + 80) = v15; /*0x5b6d281*/
    v16 = ((*v69 ^ (unsigned int)v15) << 12) /*0x5b6d297*/
        | (unsigned int)((*(_QWORD *)v69 ^ (unsigned __int64)(unsigned int)v15) >> 20);
    *(_QWORD *)(a1 + 40) = v16; /*0x5b6d29e*/
    v17 = *(_QWORD *)a1 + v16; /*0x5b6d2a1*/
    *(_QWORD *)a1 = v17; /*0x5b6d2a4*/
    v18 = ((*v74 ^ (unsigned int)v17) << 8) /*0x5b6d2ba*/
        | (unsigned int)((*(_QWORD *)v74 ^ (unsigned __int64)(unsigned int)v17) >> 24);
    *(_QWORD *)(a1 + 120) = v18; /*0x5b6d2c1*/
    v19 = *(_QWORD *)(a1 + 80) + v18; /*0x5b6d2c9*/
    *(_QWORD *)(a1 + 80) = v19; /*0x5b6d2d1*/
    *(_QWORD *)(a1 + 40) = ((*(_DWORD *)(a1 + 40) ^ (unsigned int)v19) << 7) /*0x5b6d2ee*/
                         | (unsigned int)((*(_QWORD *)(a1 + 40) ^ (unsigned __int64)(unsigned int)v19) >> 25);
    v20 = *(_QWORD *)(a1 + 8) + *(unsigned int *)(a1 + 48); /*0x5b6d2fd*/
    *(_QWORD *)(a1 + 8) = v20; /*0x5b6d305*/
    v21 = ((*v71 ^ (unsigned int)v20) << 16) /*0x5b6d31b*/
        | (unsigned int)((*(_QWORD *)v71 ^ (unsigned __int64)(unsigned int)v20) >> 16);
    *(_QWORD *)(a1 + 96) = v21; /*0x5b6d322*/
    v22 = *(_QWORD *)(a1 + 88) + v21; /*0x5b6d32a*/
    *(_QWORD *)(a1 + 88) = v22; /*0x5b6d332*/
    v23 = ((*v70 ^ (unsigned int)v22) << 12) /*0x5b6d348*/
        | (unsigned int)((*(_QWORD *)v70 ^ (unsigned __int64)(unsigned int)v22) >> 20);
    *(_QWORD *)(a1 + 48) = v23; /*0x5b6d34f*/
    v24 = *(_QWORD *)(a1 + 8) + v23; /*0x5b6d357*/
    *(_QWORD *)(a1 + 8) = v24; /*0x5b6d35f*/
    v25 = ((*v71 ^ (unsigned int)v24) << 8) /*0x5b6d375*/
        | (unsigned int)((*(_QWORD *)v71 ^ (unsigned __int64)(unsigned int)v24) >> 24);
    *(_QWORD *)(a1 + 96) = v25; /*0x5b6d37c*/
    v26 = *(_QWORD *)(a1 + 88) + v25; /*0x5b6d384*/
    *(_QWORD *)(a1 + 88) = v26; /*0x5b6d38c*/
    *(_QWORD *)(a1 + 48) = ((*(_DWORD *)(a1 + 48) ^ (unsigned int)v26) << 7) /*0x5b6d3a9*/
                         | (unsigned int)((*(_QWORD *)(a1 + 48) ^ (unsigned __int64)(unsigned int)v26) >> 25);
    v27 = *(_QWORD *)(a1 + 16) + *(unsigned int *)(a1 + 56); /*0x5b6d3b8*/
    *(_QWORD *)(a1 + 16) = v27; /*0x5b6d3c0*/
    v54 = (((unsigned int)*(_QWORD *)(a1 + 104) ^ (unsigned int)v27) << 16) /*0x5b6d7d8*/
        | (unsigned int)((*(_QWORD *)(a1 + 104) ^ (unsigned __int64)(unsigned int)v27) >> 16);
    *(_QWORD *)(a1 + 104) = v54; /*0x5b6d7df*/
    v55 = *(_QWORD *)(a1 + 64) + v54; /*0x5b6d7e7*/
    *(_QWORD *)(a1 + 64) = v55; /*0x5b6d7ef*/
    v56 = ((*(_DWORD *)(a1 + 56) ^ (unsigned int)v55) << 12) /*0x5b6d805*/
        | (unsigned int)((*(_QWORD *)(a1 + 56) ^ (unsigned __int64)(unsigned int)v55) >> 20);
    *(_QWORD *)(a1 + 56) = v56; /*0x5b6d80c*/
    v57 = *(_QWORD *)(a1 + 16) + v56; /*0x5b6d814*/
    *(_QWORD *)(a1 + 16) = v57; /*0x5b6d81c*/
    v58 = ((*v72 ^ (unsigned int)v57) << 8) /*0x5b6d832*/
        | (unsigned int)((*(_QWORD *)v72 ^ (unsigned __int64)(unsigned int)v57) >> 24);
    *(_QWORD *)(a1 + 104) = v58; /*0x5b6d839*/
    v59 = *(_QWORD *)(a1 + 64) + v58; /*0x5b6d841*/
    *(_QWORD *)(a1 + 64) = v59; /*0x5b6d849*/
    *(_QWORD *)(a1 + 56) = ((*(_DWORD *)(a1 + 56) ^ (unsigned int)v59) << 7) /*0x5b6d866*/
                         | (unsigned int)((*(_QWORD *)(a1 + 56) ^ (unsigned __int64)(unsigned int)v59) >> 25);
    v60 = *(_QWORD *)(a1 + 24) + *(unsigned int *)(a1 + 32); /*0x5b6d874*/
    *(_QWORD *)(a1 + 24) = v60; /*0x5b6d87c*/
    v61 = ((*v73 ^ (unsigned int)v60) << 16) /*0x5b6d892*/
        | (unsigned int)((*(_QWORD *)v73 ^ (unsigned __int64)(unsigned int)v60) >> 16);
    *(_QWORD *)(a1 + 112) = v61; /*0x5b6d899*/
    v62 = *(_QWORD *)(a1 + 72) + v61; /*0x5b6d8a1*/
    *(_QWORD *)(a1 + 72) = v62; /*0x5b6d8a9*/
    v63 = ((*v68 ^ (unsigned int)v62) << 12) /*0x5b6d8be*/
        | (unsigned int)((*(_QWORD *)v68 ^ (unsigned __int64)(unsigned int)v62) >> 20);
    *(_QWORD *)(a1 + 32) = v63; /*0x5b6d8c4*/
    v64 = *(_QWORD *)(a1 + 24) + v63; /*0x5b6d8cc*/
    *(_QWORD *)(a1 + 24) = v64; /*0x5b6d8d4*/
    v65 = ((*v73 ^ (unsigned int)v64) << 8) /*0x5b6d8ea*/
        | (unsigned int)((*(_QWORD *)v73 ^ (unsigned __int64)(unsigned int)v64) >> 24);
    *(_QWORD *)(a1 + 112) = v65; /*0x5b6d8f1*/
    v66 = *(_QWORD *)(a1 + 72) + v65; /*0x5b6d8f9*/
    *(_QWORD *)(a1 + 72) = v66; /*0x5b6d901*/
    *(_QWORD *)(a1 + 32) = ((*(_DWORD *)(a1 + 32) ^ (unsigned int)v66) << 7) /*0x5b6d91c*/
                         | (unsigned int)((*(_QWORD *)(a1 + 32) ^ (unsigned __int64)(unsigned int)v66) >> 25);
  }
  for ( k = 0; k < 16; ++k ) /*0x5b6d93b*/
  {
    v75 = (_QWORD *)(a1 + 8LL * k); /*0x5b6d180*/
    *v75 = (unsigned int)(*(_DWORD *)v75 + *((_DWORD *)v83 + k)); /*0x5b6d78b*/
  }
  return __readfsqword(0x28u); /*0x5b6d98b*/
}
