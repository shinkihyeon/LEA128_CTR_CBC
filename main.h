#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define LEA_BLOCKLEN 16

//매크로로 32bit ROR,ROL함수 만들기
#define ROR(w,mv) ((w>>mv)|(w<<(32-mv))) 
#define ROL(w,mv) ((w<<mv)|(w>>(32-mv)))

//CBC 
void CBCmode_Encrypt_LEA(const uint8_t* pt, const uint8_t* iv, const uint32_t ptlen, const uint8_t* key, uint8_t* ct);
void CBCmode_Decrypt_LEA(const uint8_t* ct, const uint8_t* iv, const uint32_t ctlen, const uint8_t* key, uint8_t* pt);

//CTR 
void CTR_inc(uint8_t* iv);
void LEA_CTR(uint8_t* pt, uint8_t* iv, uint32_t ptlen, uint8_t* key, uint8_t* ct);

//DEC
void LEA_Round_Decrypt(const uint8_t input[16], uint32_t RK[24][6], uint8_t output[16]);

//ENC
void LEA_Round_Encrypt(uint8_t input[16], uint32_t RK[24][6], uint8_t output[16]);

//KEY SCHEDULE
void LEA_Keyschedule(const uint8_t key[16], uint32_t rk[24][6]);

//PrintState
void ECB_Encrypt_printstate(uint8_t DATA[16], uint32_t datalen);
void CTR_Encrypt_printstate(uint8_t DATA[16], uint32_t datalen);
void CBC_Encrypt_printstate(uint8_t DATA[16], uint32_t datalen);
void ECB_Decrypt_printstate(uint8_t DATA[16], uint32_t datalen);
void CTR_Decrypt_printstate(uint8_t DATA[16], uint32_t datalen);
void CBC_Decrypt_printstate(uint8_t DATA[16], uint32_t datalen);
