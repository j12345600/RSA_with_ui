#include  "RSA_util.h"
using namespace std;
RSA_util::RSA_util() {
	ctx = BN_CTX_new();
	pbkey= BN_new();
	pvkey = BN_new();
	pq = BN_new();
	p = BN_new();
	q = BN_new();
	qcp = BN_new();
	pcq = BN_new();
	tmp1= BN_new();
	tmp2= BN_new();
	tmp3= BN_new();
	mode = -1;
};
RSA_util::RSA_util(int ini) {
	ctx = BN_CTX_new();
	pbkey = BN_new();
	pvkey = BN_new();
	pq = BN_new();
	p = BN_new();
	q = BN_new();
	qcp = BN_new();
	pcq = BN_new();
	tmp1 = BN_new();
	tmp2 = BN_new();
	tmp3 = BN_new();
	RSA_key_pair_gen(ini);
};
void RSA_util::square_and_multiply(BIGNUM*r, BIGNUM *a, BIGNUM *exp, BIGNUM *modN) {
	BN_CTX *ctx= BN_CTX_new();
	BIGNUM* tmp= BN_new();
	//BN_set_word(r, 1);	//initialize r;
	BN_copy(r, a);
	int bits_of_exp= BN_num_bits(exp)%8;
	int sizeEXP = BN_num_bytes(exp);
	int bit[] = { 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 };
	unsigned char *bin_of_exp = (unsigned char *)malloc(sizeEXP);
	BN_bn2bin(exp, bin_of_exp);
	cout << endl;
	for (int i =( 8-bits_of_exp+1>8)?1: 8 - bits_of_exp + 1; i < 8; i++) {
		BN_mod_sqr(tmp,r, modN, ctx);
		BN_copy(r, tmp);
		if ((bin_of_exp[0] & bit[i]) > 0) {
			BN_mod_mul(tmp,r,a, modN,ctx);
			BN_copy(r, tmp);
		}
	}
	for (int j = 1; j < sizeEXP; j++) {
		for (int i = 0; i < 8; i++) {

			BN_mod_sqr(tmp, r, modN, ctx);
			BN_copy(r, tmp);
			if ((bin_of_exp[j] & bit[i] )> 0) {
				BN_mod_mul(tmp, r, a, modN, ctx);
				BN_copy(r, tmp);
			}
		}
	}
		
}
int RSA_util::RSA_key_pair_gen(int length) {
	if (!(length == 1024 || length == 512 || length == 2048 || length == 4096)) return 1;
	mode = length;
	BN_CTX *ctx = BN_CTX_new();

	// create two large prime number p and q
	do {
		primeNumGen(p, length / 2);
		primeNumGen(q, length / 2);
	}while(BN_cmp(p, q)==0);

	//calculate pq=p*q
	BN_mul(pq, p, q, ctx);

	//calculate (p-1)*(q-1)
	BN_copy(tmp1, p);
	BN_copy(tmp2, q);
	BN_sub_word(tmp1, 1);
	BN_sub_word(tmp2, 1);
	BN_mul(tmp3, tmp1, tmp2, ctx);

	//tmp3=(p-1)*(q-1), generate public key 
	//by selecting a number P such that P and tmp3 are coprime
	do {
		BN_rand(tmp1, 24, -1, 0);
		BN_gcd(tmp2, tmp1, tmp3, ctx);
		//cout << "in" << endl;
	} while (!BN_is_one(tmp2));
	BN_copy(pbkey, tmp1);

	//compute pvkey
	BN_mod_inverse(pvkey, pbkey,tmp3,ctx);

	return 0;
}
void RSA_util::primeNumGen(BIGNUM*r, int length) {
	DH *p = DH_new();
	DH_generate_parameters_ex(p, length, 5, NULL);
	BN_copy(r, p->p);
	DH_free(p);
}
string RSA_util::printBIGNUM(BIGNUM* to_be_printed) {
	string s;
	stringstream  ss;
	char *c_str = BN_bn2hex(to_be_printed);
	s+= c_str;
	return s;
}
string RSA_util::printRSA() {
	string s;
	s += "p\n"; s += printBIGNUM(p); s += "\n";
	s += "q\n"; s += printBIGNUM(q); s += "\n";
	s += "pq\n"; s += printBIGNUM(pq); s += "\n";
	s += "pbkey\n"; s += printBIGNUM(pbkey); s += "\n";
	s += "pvkey\n"; s += printBIGNUM(pvkey); s += "\n";
	return s;
}
BIGNUM* RSA_util::RSA_encryption(BIGNUM* msg, BIGNUM* pubKey, BIGNUM* N) {
	BIGNUM *result = BN_new();
	square_and_multiply(result, msg, pubKey, N);
	return result;
}
BIGNUM* RSA_util::RSA_decryption(BIGNUM* msg, BIGNUM* prvKey, BIGNUM* N) {
	BIGNUM *result = BN_new();
	square_and_multiply(result, msg, prvKey, N);
	return result;
}
char*  RSA_util::RSA_encryption(const char* msg, BIGNUM* pubKey, BIGNUM* N) {
	char* result;
	BIGNUM *tmp = BN_bin2bn((unsigned char*)msg, sizeof(char)*strlen(msg),NULL);
	tmp = RSA_encryption(tmp, pubKey, N);
	//result = (unsigned char *)malloc(BN_num_bytes(tmp));
	result=BN_bn2hex(tmp);
	return (char*)result;
}
char*  RSA_util::RSA_decryption(const char* msg, BIGNUM* prvKey, BIGNUM* N) {
	unsigned char* result;
	BIGNUM* tmp = BN_new();
	int len = BN_hex2bn(&tmp,msg);
	tmp = RSA_decryption(tmp, prvKey, N);
	result=(unsigned char *)malloc(BN_num_bytes(tmp));
	BN_bn2bin(tmp, result);
	return (char*)result;
}
void RSA_util::RSA_CRT_Preprocessing(void) {
	BIGNUM*cp = tmp1;
	BIGNUM*cq = tmp2;
	BN_mod_inverse(cp, q, p, ctx);
	BN_mod_inverse(cq, p, q, ctx);
	BN_mul(qcp, q, cp, ctx);
	BN_mul(pcq, p, cq, ctx);
}
char*  RSA_util::RSA_decryption_with_CRT(const char* msg) {
	unsigned char* result;
	//convert msg to bigNum and store the result in tmp1
	int len = BN_hex2bn(&tmp1, msg);

	BIGNUM* x = tmp1;
	BIGNUM* xp = tmp2;
	BIGNUM* xq = tmp3;
	BIGNUM* tmp = BN_new();
	BIGNUM* dq= BN_new();
	BIGNUM* dp=BN_new();
	BIGNUM* pm = BN_new();
	BIGNUM* qm = BN_new(); 
	BIGNUM* yp = BN_new();
	BIGNUM* yq = BN_new();

	//CRT decryption
	BN_nnmod(xp, x, p, ctx);
	BN_nnmod(xq, x, q, ctx);
	BN_copy(pm, p);
	BN_copy(qm, q);
	BN_sub_word(pm, 1);
	BN_sub_word(qm, 1);
	BN_nnmod(dp, pvkey, pm, ctx);
	BN_nnmod(dq, pvkey, qm, ctx);
	square_and_multiply(yp, xp, dp, p);
	square_and_multiply(yq, xq, dq, q);

	BN_mul(tmp1, qcp, yp, ctx);
	BN_mul(tmp2, pcq, yq, ctx);
	BN_mod_add(tmp3, tmp1, tmp2, pq,ctx);
	BN_free(tmp);BN_free(dq);BN_free(dp);
	BN_free(pm);BN_free(qm);BN_free(yp);BN_free(yq);
	//convert bigNum to char
	result = (unsigned char *)malloc(BN_num_bytes(tmp3));
	BN_bn2bin(tmp3, result);
	return (char*)result;
}