// 0x5B6CBD2 @ 0x5B6CBD2
// The function seems has been flattened
__int64 __fastcall sub_5B6CBD2(unsigned __int16 *n992921659, int *a2)
{
  __int64 result; // rax
  unsigned __int16 v3; // [rsp+0h] [rbp-18h]

  v3 = n992921659[2]; /*0x5b6cbd6*/
  result = HIBYTE(*n992921659) & 0xF; /*0x5b6cbee*/
  switch ( *n992921659 >> 12 ) /*0x5b6cd1a*/
  {
    case 1: /*0x5b6cd1a*/
      goto LABEL_4;
    case 2: /*0x5b6cd1a*/
      a2[1] = (v3 >> 4) & 0xF; /*0x5b6cc38*/
LABEL_4:
      *a2 = v3 & 0xF; /*0x5b6ccf4*/
      return result; /*0x5b6cd21*/
    case 3: /*0x5b6cd1a*/
      goto LABEL_6;
    case 4: /*0x5b6cd1a*/
      goto LABEL_3;
    case 5: /*0x5b6cd1a*/
      a2[4] = result; /*0x5b6cd39*/
      while ( 1 ) /*0x5b6cc73*/
      {
LABEL_3:
        a2[3] = v3 >> 12; /*0x5b6cca0*/
LABEL_6:
        a2[2] = HIBYTE(v3) & 0xF; /*0x5b6cd26*/
      }
    default:
      return result;
  }
}
