#include "main.h"

//LEA128 ��ȣȭ ���ִ� �Լ�
void LEA_Round_Decrypt(const uint8_t input[16], uint32_t RK[24][6], uint8_t output[16]) {
	//input(��ȣ��)�� state�� ��Ƽ� de_pt�� 24���� �����ϸ鼭
	//��ȣȭ �Ұ�
	uint32_t state[4];
	memcpy(state, (uint32_t*)input, 16 * sizeof(uint8_t));
	uint32_t de_pt[4] = { 0x00, };

	//24���� ��ȣȭ ����
	for (int i = 23; i >= 0; i--) {
		de_pt[0] = state[3];
		de_pt[1] = (ROR(state[0], 9) - (de_pt[0] ^ RK[i][0])) ^ RK[i][1];
		de_pt[2] = (ROL(state[1], 5) - (de_pt[1] ^ RK[i][2])) ^ RK[i][3];
		de_pt[3] = (ROL(state[2], 3) - (de_pt[2] ^ RK[i][4])) ^ RK[i][5];
		for (int j = 0; j < 4; j++)
			state[j] = de_pt[j];
	}

	//����� 
	memcpy(output, (uint8_t*)state, 16 * sizeof(uint8_t));
}