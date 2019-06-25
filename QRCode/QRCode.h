#pragma once
#ifndef QRCODE_H
#define QRCODE_H
#pragma warning(disable:4996)

#define QRCodeMaxLegth       24+4*20
//标识码
#define SignCode1            0x99
#define SignCode2            0x03
#define SignCode             (SignCode1 *0xFF | SignCode2)
//二维码类型
#define OnlineCheck          0x00   //在线鉴权
#define OfflineCheckNotTime  0x05   //不校验二维码生成时间
#define OfflineCheckIsTime   0x06   //校验二维生产时间
#define OfflineCheckNum      0x07   //只有一次有效

struct g_QRCode
{
	unsigned short Sign;//2个字节
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


struct g_SetQRCode//使用字符是原来两倍
{
	char Sign[4];
	char OEMCode[16];
	char Version[2];
	char Command[2];
	char GroupID[8];
	char CreateTime[8];
	char OpenKeyLen[4];
};
//设置信息
void SetQRCode(char * Key);

//检测
_Bool CheckCode(char * code,unsigned char * DoorNum,unsigned char * Priority, _Bool InOrOut);

#endif