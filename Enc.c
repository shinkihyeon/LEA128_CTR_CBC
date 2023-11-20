#include "main.h"

//LEA128 ��ȣȭ ���ִ� �Լ�
void LEA_Round_Encrypt(uint8_t input[16], uint32_t RK[24][6], uint8_t output[16])
{
	uint32_t Plain[4] = { 0x00, };
	uint32_t ct[4] = { 0x00, };

	//input���� Plain�� �����Ͽ� Plain���� 24���� ��ȣȭ�� ��ȣ������ �����
	memcpy(Plain + 0, (unsigned int*)input + 0, 4 * sizeof(unsigned char));
	memcpy(Plain + 1, (unsigned int*)input + 1, 4 * sizeof(unsigned char));
	memcpy(Plain + 2, (unsigned int*)input + 2, 4 * sizeof(unsigned char));
	memcpy(Plain + 3, (unsigned int*)input + 3, 4 * sizeof(unsigned char));

	//24���� ��ȣȭ ����
	for (int i = 0; i < 24; i++) {
		ct[0] = ROL(((Plain[0] ^ RK[i][0]) + (Plain[1] ^ RK[i][1])), 9);
		ct[1] = ROR(((Plain[1] ^ RK[i][2]) + (Plain[2] ^ RK[i][3])), 5);
		ct[2] = ROR(((Plain[2] ^ RK[i][4]) + (Plain[3] ^ RK[i][5])), 3);
		ct[3] = Plain[0];
		for (int j = 0; j < 4; j++) {
			Plain[j] = ct[j];
		}
	}

	//����� 
	memcpy(output, (uint8_t*)Plain, 16 * sizeof(uint8_t));
}
