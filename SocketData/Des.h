#ifndef _DES_H_
#define _DES_H_
enum    {ENCRYPT,DECRYPT};

// Type��ENCRYPT:����,DECRYPT:����
// ���������(Out)�ĳ��� >= ((datalen+7)/8)*8,����datalen�������8�ı�������С������
// In ����= Out,��ʱ��/���ܺ󽫸������뻺����(In)������
// ��keylen>8ʱϵͳ�Զ�ʹ��3��DES��/����,����ʹ�ñ�׼DES��/����.����16�ֽں�ֻȡǰ16�ֽ�
class CDES{
public:
	CDES(){}
	~CDES(){}
	bool Des_Go(char *Out,char *In,long datalen,const char *Key,int keylen,bool Type = ENCRYPT);
};
#endif
