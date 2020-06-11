#include <reg52.h>
#define uchar unsigned char		   
#define uint unsigned int
sbit butter = P3^5;

uchar dismem[16];
uchar code ann[]={1,1,1,1,1,1,1,1,2,3,6,10,14,20,35,50,35,20,14,10,6,3,2,1,1,1,1,1,1,1,1,1};

void Timer0_Init()
{
IE=0x82;	  				//配置IE（中断允许计数器），等价于EA=1;ET0=1;
TMOD=0x01;
TH0=(65536-10)/256;  
TL0=(65536-10)%256; 
TR0=1;					   
}

/*P0口的位处理函数*/
uchar bitcountp0(uchar n)
{
uchar i,p=0;
for (i=0;i<8;i++)			 
{
if (dismem[i]<n)			//用ann数组确定一个阈值，随着中断次数的增加，P0口LED的占空比依此减小，P0^0为最小
{
p=p|(1<<i);					//熄灭(i+1)个灯
butter = 1;					//让蜂鸣器声音起伏
}
else butter = 0;

}
return p;				    //将P传回去
}

/*P2口的位处理函数*/
uchar bitcountp2(uchar n)	//P2与P0端口布局相反，所以函数相同可以实现相反的效果
{
uchar i,p=0;
for (i=0;i<8;i++)			
{
if (dismem[i]<n)
p=p|(1<<i);
}
return p;
}


/*让LED实现呼吸效果*/
void huxi()                 
{
uchar i,j;
	for (i=0;i<16;i++)
	{
		for (j=0;j<16;j++)
		{
			dismem[j]=ann[i+j];	   //实现呼吸灯的位移
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
static uchar i=1;			   //定义静态变量i
char b;
P0=bitcountp0(i);
P2=bitcountp2(i);
b=bitcountp0;
butter = 1; 
if (i<50)					   //每产生50次中断为一周期
i++;
else 
i=1;
TH0=(65536-10)/256; 			//进入中断时间约为10us
TL0=(65536-10)%256; 
}
