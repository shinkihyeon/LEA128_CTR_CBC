#include "main.h"

//ECB, CTR, CBC 운영모드 별로
//암호문, 복호화된 평문 출력해주는 함수

void ECB_Encrypt_printstate(uint8_t DATA[16], uint32_t datalen) {
	printf("ECB_Last_CT: ");

	for (int i = 0; i < datalen; i++)
	{
		printf("%02X ", DATA[i]);

	}

	printf("\n");
}

void CTR_Encrypt_printstate(uint8_t DATA[16], uint32_t datalen) {
	printf("Last_CTR_CT: ");

	for (int i = 0; i < datalen; i++)
	{
		printf("%02X ", DATA[i]);

	}


	printf("\n");
}

void CBC_Encrypt_printstate(uint8_t DATA[16], uint32_t datalen) {
	printf("Last_CBC_CT: ");

	for (int i = 0; i < datalen; i++)
	{
		printf("%02X ", DATA[i]);

	}


	printf("\n");
}

void ECB_Decrypt_printstate(uint8_t DATA[16], uint32_t datalen) {
	printf("ECB_De_PT: ");

	for (int i = 0; i < datalen; i++)
	{
		printf("%02X ", DATA[i]);

	}

	printf("\n");
}

void CTR_Decrypt_printstate(uint8_t DATA[16], uint32_t datalen) {
	printf("CTR_De_PT: ");

	for (int i = 0; i < datalen; i++)
	{
		printf("%02X ", DATA[i]);

	}

	printf("\n");
}

void CBC_Decrypt_printstate(uint8_t DATA[16], uint32_t datalen) {
	printf("CBC_De_PT: ");

	for (int i = 0; i < datalen; i++)
	{
		printf("%02X ", DATA[i]);

	}

	printf("\n");
}
