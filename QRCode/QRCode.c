#include "QRCode.h"
#include <stdbool.h>
#include <string.h>
#include "mbedtls/aes.h"
#include "mbedtls/config.h"
//#include<sys/time.h>

//*******************Modbus_CRC��֤*********************
unsigned short ModbusCRC16(unsigned char *ptr, unsigned char len)

{
	unsigned long wcrc = 0XFFFF;//Ԥ��16λcrc�Ĵ�������ֵȫ��Ϊ1

	unsigned int i = 0, j = 0;//�������

	for (i = 0; i < len; i++)//ѭ������ÿ������

	{

		wcrc ^= *ptr++;//����λ������crc�Ĵ������.ָ���ַ���ӣ�ָ���¸�����

		for (j = 0; j < 8; j++)//ѭ���������ݵ�

		{

			if (wcrc & 0X0001)//�ж����Ƴ����ǲ���1�������1�������ʽ�������

			{
				wcrc = wcrc >> 1 ^ 0XA001;//�Ƚ���������һλ��������Ķ���ʽ�������
			}

			else//�������1����ֱ���Ƴ�

			{
				wcrc >>= 1;//ֱ���Ƴ�
			}
		}
	}
	return wcrc << 8 | wcrc >> 8;//�Ͱ�λ��ǰ���߰�λ�ں�
}
//char a[6] = { 01, 03 ,0x22 ,0x33 ,0x44, 01 };
//printf("%x \n", crc16(a, 6));



//����ά��
//code:�ַ�����ά��
//DoorNum:һ���ֽڣ��洢����Ȩ��
//Priority:���ȼ�
//InOrOut:��true,��false
_Bool CheckCode(char * code,unsigned char * DoorNum ,unsigned char * Priority,_Bool InOrOut)
{
	_Bool CheckResult = false;
//	struct timeval NowTime;
	struct g_QRCode data;
	char g_IDKey[4] = { 0 };

	if (strlen(code) < QRCodeMaxLegth)
	{
		strncpy((char*)&data, code, sizeof(data));
		if (data.Sign == SignCode )
		{
			//unixʱ���
//			gettimeofday(&NowTime, NULL);
//			printf("tv_sec  : %lx  \n",NowTime.tv_sec);
			if (strncmp(data.ID, g_IDKey, sizeof(g_IDKey)) == 0)//�ж���Կ�Ƿ���ͬ
			{
				switch (data.Kind)//��ά������
				{
				case OnlineCheck:
				{

					CheckResult = true;
					break;

				}
				case OfflineCheckNotTime:
				{
					break;

				}
				case OfflineCheckIsTime:
				{
//					if ((NowTime.tv_sec >= data.CreateTime) && (NowTime.tv_sec <= data.EndTime))//ʱ����֤
					{
						CheckResult = true;
					}

					break;
				}
				case OfflineCheckNum:
				{
					break;
				}



				}
				*DoorNum = data.Limit >> 4;
				*Priority = (char)(data.Limit | 0x0f);
			}





		}





	}


	return CheckResult;
}


//����
//Key:�ĸ��ֽ�
void SetQRCode(char * Key)
{
	char * OEMCode = "P21kc0QU";
	char  *SetKey = "0009000D0AADCABDFAC16F33331267CC";
	//���н���

	//�Ƚ�OEM��
//	if(strncmp(Key, SetKey))
//	strncpy(g_IDKey, Key, sizeof(g_IDKey));

}




