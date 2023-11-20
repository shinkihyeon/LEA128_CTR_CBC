#include "main.h"

//키스케줄 과정에서 필요한 키스케줄상수
const static uint32_t keyschedule_con[8] = { 0xc3efe9db,0x44626b02,0x79e27c8a,0x78df30ec,0x715ea49e,0xc785da0a,0xe04ef22a,0xe5c40957 };


//128-bit key schedule
//key는 키스케줄 input값인 128비트 비밀키, rk는 키스케줄 결과값인 24개의 192비트 라운드키
void LEA_Keyschedule(const  uint8_t key[16], uint32_t rk[24][6]) {
	//8비트씩 끊어져 저장되어 있는 키값을 32비트씩 끊어서 저장!
	uint32_t state[4] = { 0x00, };
	memcpy(state, (uint32_t*)key, 16 * sizeof(unsigned char));

	//24라운드 라운드키 생성
	for (uint32_t i = 0; i < 24; i++) {
		state[0] = ROL(state[0] + ROL(keyschedule_con[i % 4], (i + 0)), 1);
		state[1] = ROL(state[1] + ROL(keyschedule_con[i % 4], (i + 1)), 3);
		state[2] = ROL(state[2] + ROL(keyschedule_con[i % 4], (i + 2)), 6);
		state[3] = ROL(state[3] + ROL(keyschedule_con[i % 4], (i + 3)), 11);

		//각 라운드 키 세팅
		rk[i][0] = state[0];
		rk[i][1] = state[1];
		rk[i][2] = state[2];
		rk[i][3] = state[1];
		rk[i][4] = state[3];
		rk[i][5] = state[1];
	}
}