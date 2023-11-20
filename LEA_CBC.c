#include "main.h"

void CBCmode_Encrypt_LEA(const uint8_t* pt, const uint8_t* iv, const uint32_t ptlen, const uint8_t* key, uint8_t* ct)
{
	//key schedule 부분
	uint32_t rk[24][6] = { 0x00, };
	LEA_Keyschedule(key, rk);

	// pt가 한블럭(16바이트)가 아닐때, 마지막부분에 패딩해줘야! 
	//! calloc을 쓰면 모든값들이 0으로 초기화 되기 때문에 ptlen만큼만 pt를 inner_pt에 옮겨놓으면 나머지는 0값으로 세팅되기 때문에
	//! 자동으로 제로 padding됨!
	uint32_t enc_len = (ptlen % 16 == 0) ? ptlen : ptlen + (16 - (ptlen % 16));
	uint8_t* inner_pt = (uint8_t*)calloc(enc_len, sizeof(uint8_t));
	assert(inner_pt != NULL);
	//zero padding finish
	memcpy(inner_pt, pt, ptlen); 
	
	//참고)만약에 0x80패딩을 하고 싶다면? inner_pt[ptlen] = (ptlen % LEA_BLOCKLEN == 0) ? 0 : 0x80;

	//패딩된 평문을 CBC모드 기반의 LEA128로 암호화 진행
	for (int cnt_i = 0; cnt_i < (enc_len / LEA_BLOCKLEN); cnt_i++) {
		for (int cnt_j = 0; cnt_j < LEA_BLOCKLEN; cnt_j++) {
			inner_pt[cnt_j + LEA_BLOCKLEN * cnt_i] = pt[cnt_j + LEA_BLOCKLEN * cnt_i] ^ iv[cnt_j];
		}
		LEA_Round_Encrypt(inner_pt + (LEA_BLOCKLEN * cnt_i), rk, ct + (LEA_BLOCKLEN * cnt_i));
		//iv 갱신
		iv = ct + (LEA_BLOCKLEN * cnt_i);
	}

	//메모리 해제
	free(inner_pt);
	inner_pt = NULL;
}

//CTR 모드는 복호화 함수가 필요없는것과 다르게
//CBC는 필요함
void CBCmode_Decrypt_LEA(const uint8_t* ct, const uint8_t* iv, const uint32_t ctlen, const uint8_t* key, uint8_t* pt) {
	//Key Schedule Part
	uint32_t rk[24][6] = { 0x00, };
	LEA_Keyschedule(key, rk);

	//CBC모드 기반의 LEA128로 복호화 진행
	for (int cnt_i = 0; cnt_i < ctlen / LEA_BLOCKLEN; cnt_i++) {
		LEA_Round_Decrypt(ct + (LEA_BLOCKLEN * cnt_i), rk, pt + (LEA_BLOCKLEN * cnt_i));
		for (int cnt_j = 0; cnt_j < LEA_BLOCKLEN; cnt_j++) {
			pt[cnt_j + (LEA_BLOCKLEN * cnt_i)] = iv[cnt_j] ^ pt[cnt_j + (LEA_BLOCKLEN * cnt_i)];
		}
		iv = ct + (LEA_BLOCKLEN * cnt_i);
	}
}