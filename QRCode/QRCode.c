#include "QRCode.h"
#include <stdbool.h>
#include <string.h>
#include "mbedtls/aes.h"
#include "mbedtls/config.h"
//#include<sys/time.h>

//*******************Modbus_CRC验证*********************
unsigned short ModbusCRC16(unsigned char *ptr, unsigned char len)

{
	unsigned long wcrc = 0XFFFF;//预置16位crc寄存器，初值全部为1

	unsigned int i = 0, j = 0;//定义计数

	for (i = 0; i < len; i++)//循环计算每个数据

	{

		wcrc ^= *ptr++;//将八位数据与crc寄存器亦或.指针地址增加，指向下个数据

		for (j = 0; j < 8; j++)//循环计算数据的

		{

			if (wcrc & 0X0001)//判断右移出的是不是1，如果是1则与多项式进行异或。

			{
				wcrc = wcrc >> 1 ^ 0XA001;//先将数据右移一位再与上面的多项式进行异或
			}

			else//如果不是1，则直接移出

			{
				wcrc >>= 1;//直接移出
			}
		}
	}
	return wcrc << 8 | wcrc >> 8;//低八位在前，高八位在后
}
//char a[6] = { 01, 03 ,0x22 ,0x33 ,0x44, 01 };
//printf("%x \n", crc16(a, 6));



//检测二维码
//code:字符串二维码
//DoorNum:一个字节，存储开门权限
//Priority:优先级
//InOrOut:出true,入false
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
			//unix时间戳
//			gettimeofday(&NowTime, NULL);
//			printf("tv_sec  : %lx  \n",NowTime.tv_sec);
			if (strncmp(data.ID, g_IDKey, sizeof(g_IDKey)) == 0)//判断秘钥是否相同
			{
				switch (data.Kind)//二维码类型
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
//					if ((NowTime.tv_sec >= data.CreateTime) && (NowTime.tv_sec <= data.EndTime))//时间验证
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


//设置
//Key:四个字节
void SetQRCode(char * Key)
{
	char * OEMCode = "P21kc0QU";
	char  *SetKey = "0009000D0AADCABDFAC16F33331267CC";
	//进行解密

	//比较OEM码
//	if(strncmp(Key, SetKey))
//	strncpy(g_IDKey, Key, sizeof(g_IDKey));

}




