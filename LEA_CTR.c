#include "main.h"

//iv = nonce(8)  + counter(8)
//CTR값 +1씩 시키는 함수
void CTR_inc(uint8_t* iv) {
	//경우의 수를 나누자
	//+1을 하면 자릿수가 올라가는 경우와 그냥 해당 자리에서 +1를 할 수 있는 경우
	for (int i = 15; i > 7; i--)//iv에서 counter부분(8바이트)만 증가시킬 거라서 -> 8까지
	{
		if (iv[i] != 0xff) {
			iv[i]++;
			break;
		}
		else
		{
			iv[i] = 0x00;
		}
	}
}

//LEA128을 CTR운영모드로 암호화 진행해주는 함수
void LEA_CTR(uint8_t* pt, uint8_t* iv, uint32_t ptlen, uint8_t* key, uint8_t* ct)
{
	uint8_t copy_counter[LEA_BLOCKLEN];
	memcpy(copy_counter, iv, LEA_BLOCKLEN);


	//평문의 길이가 16의 배수가 아닐때 해당 길이에서
	//가장 가까운 16의배수를 찾는것 -> CTR값을 몇번 암호화 해줘야 하는지 알기 위해서!
	uint32_t enc_len = (ptlen % LEA_BLOCKLEN == 0) ? ptlen : ptlen + (LEA_BLOCKLEN - (ptlen % LEA_BLOCKLEN)); 

	//Counter 암호화해서 아래 메모리에 넣을 것!
	uint8_t* copy_ct = (uint8_t*)calloc(enc_len, sizeof(uint8_t));
	assert(copy_ct != NULL);

	//KEY SCHEDULE
	uint32_t rk[24][6] = { 0x00, };
	LEA_Keyschedule(key, rk);

	//counter값 암호화
	for (int cnt_i = 0; cnt_i < (enc_len >> 4); cnt_i++) {
		LEA_Round_Encrypt(copy_counter, rk, copy_ct + (cnt_i * LEA_BLOCKLEN));
		//counter값 증가!	
		CTR_inc(copy_counter);
	}

	//암호화된 Counter 와 평문을 xor해주는 과정
	for (int cnt_i = 0; cnt_i < ptlen; cnt_i++) {
		ct[cnt_i] = copy_ct[cnt_i] ^ pt[cnt_i];
	}

	//메모리 해제
	free(copy_ct);
	copy_ct = NULL;
}