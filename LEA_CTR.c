#include "main.h"

//iv = nonce(8)  + counter(8)
//CTR�� +1�� ��Ű�� �Լ�
void CTR_inc(uint8_t* iv) {
	//����� ���� ������
	//+1�� �ϸ� �ڸ����� �ö󰡴� ���� �׳� �ش� �ڸ����� +1�� �� �� �ִ� ���
	for (int i = 15; i > 7; i--)//iv���� counter�κ�(8����Ʈ)�� ������ų �Ŷ� -> 8����
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

//LEA128�� CTR����� ��ȣȭ �������ִ� �Լ�
void LEA_CTR(uint8_t* pt, uint8_t* iv, uint32_t ptlen, uint8_t* key, uint8_t* ct)
{
	uint8_t copy_counter[LEA_BLOCKLEN];
	memcpy(copy_counter, iv, LEA_BLOCKLEN);


	//���� ���̰� 16�� ����� �ƴҶ� �ش� ���̿���
	//���� ����� 16�ǹ���� ã�°� -> CTR���� ��� ��ȣȭ ����� �ϴ��� �˱� ���ؼ�!
	uint32_t enc_len = (ptlen % LEA_BLOCKLEN == 0) ? ptlen : ptlen + (LEA_BLOCKLEN - (ptlen % LEA_BLOCKLEN)); 

	//Counter ��ȣȭ�ؼ� �Ʒ� �޸𸮿� ���� ��!
	uint8_t* copy_ct = (uint8_t*)calloc(enc_len, sizeof(uint8_t));
	assert(copy_ct != NULL);

	//KEY SCHEDULE
	uint32_t rk[24][6] = { 0x00, };
	LEA_Keyschedule(key, rk);

	//counter�� ��ȣȭ
	for (int cnt_i = 0; cnt_i < (enc_len >> 4); cnt_i++) {
		LEA_Round_Encrypt(copy_counter, rk, copy_ct + (cnt_i * LEA_BLOCKLEN));
		//counter�� ����!	
		CTR_inc(copy_counter);
	}

	//��ȣȭ�� Counter �� ���� xor���ִ� ����
	for (int cnt_i = 0; cnt_i < ptlen; cnt_i++) {
		ct[cnt_i] = copy_ct[cnt_i] ^ pt[cnt_i];
	}

	//�޸� ����
	free(copy_ct);
	copy_ct = NULL;
}