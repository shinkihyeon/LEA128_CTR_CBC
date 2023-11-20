#include "main.h"

//LEA128 복호화 해주는 함수
void LEA_Round_Decrypt(const uint8_t input[16], uint32_t RK[24][6], uint8_t output[16]) {
	//input(암호문)을 state에 담아서 de_pt와 24라운드 진행하면서
	//복호화 할것
	uint32_t state[4];
	memcpy(state, (uint32_t*)input, 16 * sizeof(uint8_t));
	uint32_t de_pt[4] = { 0x00, };

	//24라운드 복호화 진행
	for (int i = 23; i >= 0; i--) {
		de_pt[0] = state[3];
		de_pt[1] = (ROR(state[0], 9) - (de_pt[0] ^ RK[i][0])) ^ RK[i][1];
		de_pt[2] = (ROL(state[1], 5) - (de_pt[1] ^ RK[i][2])) ^ RK[i][3];
		de_pt[3] = (ROL(state[2], 3) - (de_pt[2] ^ RK[i][4])) ^ RK[i][5];
		for (int j = 0; j < 4; j++)
			state[j] = de_pt[j];
	}

	//결과값 
	memcpy(output, (uint8_t*)state, 16 * sizeof(uint8_t));
}