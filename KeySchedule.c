#include "main.h"

//Ű������ �������� �ʿ��� Ű�����ٻ��
const static uint32_t keyschedule_con[8] = { 0xc3efe9db,0x44626b02,0x79e27c8a,0x78df30ec,0x715ea49e,0xc785da0a,0xe04ef22a,0xe5c40957 };


//128-bit key schedule
//key�� Ű������ input���� 128��Ʈ ���Ű, rk�� Ű������ ������� 24���� 192��Ʈ ����Ű
void LEA_Keyschedule(const  uint8_t key[16], uint32_t rk[24][6]) {
	//8��Ʈ�� ������ ����Ǿ� �ִ� Ű���� 32��Ʈ�� ��� ����!
	uint32_t state[4] = { 0x00, };
	memcpy(state, (uint32_t*)key, 16 * sizeof(unsigned char));

	//24���� ����Ű ����
	for (uint32_t i = 0; i < 24; i++) {
		state[0] = ROL(state[0] + ROL(keyschedule_con[i % 4], (i + 0)), 1);
		state[1] = ROL(state[1] + ROL(keyschedule_con[i % 4], (i + 1)), 3);
		state[2] = ROL(state[2] + ROL(keyschedule_con[i % 4], (i + 2)), 6);
		state[3] = ROL(state[3] + ROL(keyschedule_con[i % 4], (i + 3)), 11);

		//�� ���� Ű ����
		rk[i][0] = state[0];
		rk[i][1] = state[1];
		rk[i][2] = state[2];
		rk[i][3] = state[1];
		rk[i][4] = state[3];
		rk[i][5] = state[1];
	}
}