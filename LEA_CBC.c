#include "main.h"

void CBCmode_Encrypt_LEA(const uint8_t* pt, const uint8_t* iv, const uint32_t ptlen, const uint8_t* key, uint8_t* ct)
{
	//key schedule �κ�
	uint32_t rk[24][6] = { 0x00, };
	LEA_Keyschedule(key, rk);

	// pt�� �Ѻ�(16����Ʈ)�� �ƴҶ�, �������κп� �е������! 
	//! calloc�� ���� ��簪���� 0���� �ʱ�ȭ �Ǳ� ������ ptlen��ŭ�� pt�� inner_pt�� �Űܳ����� �������� 0������ ���õǱ� ������
	//! �ڵ����� ���� padding��!
	uint32_t enc_len = (ptlen % 16 == 0) ? ptlen : ptlen + (16 - (ptlen % 16));
	uint8_t* inner_pt = (uint8_t*)calloc(enc_len, sizeof(uint8_t));
	assert(inner_pt != NULL);
	//zero padding finish
	memcpy(inner_pt, pt, ptlen); 
	
	//����)���࿡ 0x80�е��� �ϰ� �ʹٸ�? inner_pt[ptlen] = (ptlen % LEA_BLOCKLEN == 0) ? 0 : 0x80;

	//�е��� ���� CBC��� ����� LEA128�� ��ȣȭ ����
	for (int cnt_i = 0; cnt_i < (enc_len / LEA_BLOCKLEN); cnt_i++) {
		for (int cnt_j = 0; cnt_j < LEA_BLOCKLEN; cnt_j++) {
			inner_pt[cnt_j + LEA_BLOCKLEN * cnt_i] = pt[cnt_j + LEA_BLOCKLEN * cnt_i] ^ iv[cnt_j];
		}
		LEA_Round_Encrypt(inner_pt + (LEA_BLOCKLEN * cnt_i), rk, ct + (LEA_BLOCKLEN * cnt_i));
		//iv ����
		iv = ct + (LEA_BLOCKLEN * cnt_i);
	}

	//�޸� ����
	free(inner_pt);
	inner_pt = NULL;
}

//CTR ���� ��ȣȭ �Լ��� �ʿ���°Ͱ� �ٸ���
//CBC�� �ʿ���
void CBCmode_Decrypt_LEA(const uint8_t* ct, const uint8_t* iv, const uint32_t ctlen, const uint8_t* key, uint8_t* pt) {
	//Key Schedule Part
	uint32_t rk[24][6] = { 0x00, };
	LEA_Keyschedule(key, rk);

	//CBC��� ����� LEA128�� ��ȣȭ ����
	for (int cnt_i = 0; cnt_i < ctlen / LEA_BLOCKLEN; cnt_i++) {
		LEA_Round_Decrypt(ct + (LEA_BLOCKLEN * cnt_i), rk, pt + (LEA_BLOCKLEN * cnt_i));
		for (int cnt_j = 0; cnt_j < LEA_BLOCKLEN; cnt_j++) {
			pt[cnt_j + (LEA_BLOCKLEN * cnt_i)] = iv[cnt_j] ^ pt[cnt_j + (LEA_BLOCKLEN * cnt_i)];
		}
		iv = ct + (LEA_BLOCKLEN * cnt_i);
	}
}