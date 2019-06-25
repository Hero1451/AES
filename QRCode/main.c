#include "QRCODE.h"
#include <stdio.h>
#include <stdbool.h>
#include "mbedtls/aes.h"
#include "mbedtls/config.h"
/*
char * code = "990312345D01ED515D11ED515D01ED52112222345456113";
char * mikey = "1234";
char OpenDoor = 0;
char Power = 0;



char * cypher = "U2FsdGVkX1+fkBxx+Wda3VMGdfaFQgVhbdAWR1OrqVE=";
char * plain_decrypt = "U2FsdGVkX1+fkBxx+Wda3VMGdfaFQgVhbdAWR1OrqVE=";
unsigned char IV = 0x55;




void main(void)
{
	printf("test QRCode \n");
	char * key = "0009000D0AADCABDFAC16F33331267CC";
	mbedtls_aes_context aes;
	printf("%d\n", strlen(cypher));
	mbedtls_aes_setkey_enc(&aes, key, 128);//  set encrypt key	
	printf("%d\n",mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, 45, IV, cypher, plain_decrypt));
	printf("%s\n",plain_decrypt);

/*	SetQRCode(mikey);

	if (CheckCode(code,&OpenDoor,&Power,true))
	{
		printf("识别成功");
	}
	else
	{
		printf("识别失败");
	}*/


//}


unsigned char key[] = { 1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6 };//"0009000D0AADCABD";//FAC16F33331267CC";//{ 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22 };
//unsigned char plain[32] = { 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 };
unsigned char plain_decrypt[32] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char IV[16];
unsigned char cypher[32] = {0};// = "4ff2b752113ccc949bc8b024d42b07ca";
unsigned char plain[32] = "123456";
int i = 0;
mbedtls_aes_context aes;
const char padding_char = '=';
const char * base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";





/*编码代码
* const unsigned char * sourcedata， 源数组
* char * base64 ，码字保存
*/
int base64_encode(const unsigned char * sourcedata, char * base64)
{
	int i = 0, j = 0;
	unsigned char trans_index = 0;    // 索引是8位，但是高两位都为0
	const int datalength = strlen((const char*)sourcedata);
	for (; i < datalength; i += 3) {
		// 每三个一组，进行编码
		// 要编码的数字的第一个
		trans_index = ((sourcedata[i] >> 2) & 0x3f);
		base64[j++] = base64char[(int)trans_index];
		// 第二个
		trans_index = ((sourcedata[i] << 4) & 0x30);
		if (i + 1 < datalength) {
			trans_index |= ((sourcedata[i + 1] >> 4) & 0x0f);
			base64[j++] = base64char[(int)trans_index];
		}
		else {
			base64[j++] = base64char[(int)trans_index];

			base64[j++] = padding_char;

			base64[j++] = padding_char;

			break;   // 超出总长度，可以直接break
		}
		// 第三个
		trans_index = ((sourcedata[i + 1] << 2) & 0x3c);
		if (i + 2 < datalength) { // 有的话需要编码2个
			trans_index |= ((sourcedata[i + 2] >> 6) & 0x03);
			base64[j++] = base64char[(int)trans_index];

			trans_index = sourcedata[i + 2] & 0x3f;
			base64[j++] = base64char[(int)trans_index];
		}
		else {
			base64[j++] = base64char[(int)trans_index];

			base64[j++] = padding_char;

			break;
		}
	}

	base64[j] = '\0';

	return 0;
}





void SetIV()
{
	int i;
	for (i = 0; i < 16; i++)
	{
		IV[i] = 5;
	}

}
int main()
{

	printf("start go \n");


	{
		mbedtls_aes_init(&aes);
		mbedtls_aes_setkey_enc(&aes, key, 128);//  set decrypt key
		SetIV();
		mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, 32, IV, plain, cypher);
		printf("%\n",cypher);

		const unsigned char *sourcedata = cypher;
		char base64[128];
		base64_encode(sourcedata, base64);
		printf("编码：%s\n", base64);


		mbedtls_aes_setkey_dec(&aes, key, 128);//  set decrypt key
		SetIV();
		printf("%d\n",mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, 32, IV, cypher, plain_decrypt));
		printf("%s \n",plain_decrypt);
		i++;
	}
}



