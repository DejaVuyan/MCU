#include <reg52.h>
#define uchar unsigned char		   
#define uint unsigned int
sbit butter = P3^5;

uchar dismem[16];
uchar code ann[]={1,1,1,1,1,1,1,1,2,3,6,10,14,20,35,50,35,20,14,10,6,3,2,1,1,1,1,1,1,1,1,1};

void Timer0_Init()
{
IE=0x82;	  				//����IE���ж���������������ȼ���EA=1;ET0=1;
TMOD=0x01;
TH0=(65536-10)/256;  
TL0=(65536-10)%256; 
TR0=1;					   
}

/*P0�ڵ�λ������*/
uchar bitcountp0(uchar n)
{
uchar i,p=0;
for (i=0;i<8;i++)			 
{
if (dismem[i]<n)			//��ann����ȷ��һ����ֵ�������жϴ��������ӣ�P0��LED��ռ�ձ����˼�С��P0^0Ϊ��С
{
p=p|(1<<i);					//Ϩ��(i+1)����
butter = 1;					//�÷������������
}
else butter = 0;

}
return p;				    //��P����ȥ
}

/*P2�ڵ�λ������*/
uchar bitcountp2(uchar n)	//P2��P0�˿ڲ����෴�����Ժ�����ͬ����ʵ���෴��Ч��
{
uchar i,p=0;
for (i=0;i<8;i++)			
{
if (dismem[i]<n)
p=p|(1<<i);
}
return p;
}


/*��LEDʵ�ֺ���Ч��*/
void huxi()                 
{
uchar i,j;
	for (i=0;i<16;i++)
	{
		for (j=0;j<16;j++)
		{
			dismem[j]=ann[i+j];	   //ʵ�ֺ����Ƶ�λ��
		}

	}
	

	for (i=16;i>0;i--)
	{
		for (j=0;j<16;j++)
		{
			dismem[j]=ann[i+j];
		}

	}
	
}

void main()
{
Timer0_Init();
	while(1)
	{
		huxi();
		butter = 1;
	}
}

void print() interrupt 1
{
static uchar i=1;			   //���徲̬����i
char b;
P0=bitcountp0(i);
P2=bitcountp2(i);
b=bitcountp0;
butter = 1; 
if (i<50)					   //ÿ����50���ж�Ϊһ����
i++;
else 
i=1;
TH0=(65536-10)/256; 			//�����ж�ʱ��ԼΪ10us
TL0=(65536-10)%256; 
}
