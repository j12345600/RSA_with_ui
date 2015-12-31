#pragma once
#include"..\openssl-1.0.2e-vs2015\include\openssl\bn.h"
#include"..\openssl-1.0.2e-vs2015\include\openssl\dh.h"
#include <iostream>
#include "fstream"
#include <sstream>
#include <ctime>
#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0) 
//using namespace std;

class RSA_util
{
public:

	BIGNUM *pbkey,*pvkey, *pq, *p, *q,*qcp,*pcq,*tmp1,*tmp2,*tmp3;
	BN_CTX *ctx;
	int mode;
	RSA_util();
	RSA_util(int);
	static void  square_and_multiply(BIGNUM*r, BIGNUM *a, BIGNUM *exp, BIGNUM *modN);
	int RSA_key_pair_gen(int length);
	void primeNumGen(BIGNUM*r, int length);
	static std::string printBIGNUM(BIGNUM*);
	std::string printRSA();
	static BIGNUM*  RSA_encryption(BIGNUM* msg, BIGNUM* pubKey, BIGNUM* N);
	static BIGNUM*  RSA_decryption(BIGNUM* msg, BIGNUM* prvKey, BIGNUM* N);
	static char*  RSA_encryption(const char* msg, BIGNUM* pubKey, BIGNUM* N);
	static char*  RSA_decryption(const char* msg, BIGNUM* prvKey, BIGNUM* N);
	void RSA_CRT_Preprocessing(void);
	char*  RSA_decryption_with_CRT(const char* msg);

};
