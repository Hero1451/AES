#pragma once
#ifndef QRCODE_H
#define QRCODE_H
#pragma warning(disable:4996)

#define QRCodeMaxLegth       24+4*20
//��ʶ��
#define SignCode1            0x99
#define SignCode2            0x03
#define SignCode             (SignCode1 *0xFF | SignCode2)
//��ά������
#define OnlineCheck          0x00   //���߼�Ȩ
#define OfflineCheckNotTime  0x05   //��У���ά������ʱ��
#define OfflineCheckIsTime   0x06   //У���ά����ʱ��
#define OfflineCheckNum      0x07   //ֻ��һ����Ч

struct g_QRCode
{
	unsigned short Sign;//2���ֽ�
	char Kind;
	char ID[4];
	unsigned int StratTime;
	unsigned int EndTime;
	unsigned int CreateTime;
	char OutNum;
	char ToNum;
	char Limit;
	unsigned short LimitNum;
};


struct g_SetQRCode//ʹ���ַ���ԭ������
{
	char Sign[4];
	char OEMCode[16];
	char Version[2];
	char Command[2];
	char GroupID[8];
	char CreateTime[8];
	char OpenKeyLen[4];
};
//������Ϣ
void SetQRCode(char * Key);

//���
_Bool CheckCode(char * code,unsigned char * DoorNum,unsigned char * Priority, _Bool InOrOut);

#endif