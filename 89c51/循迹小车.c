//使用光电传感器的智能循迹小车
by yyz in 2018
#include <reg52.h>

sbit LED1 = P0^0;
sbit LED2 = P0^1;

sbit IN4 = P1^4;
sbit IN3 = P1^5;
sbit IN2 = P1^6;
sbit IN1 = P1^7; 


sbit LC = P2^0;
sbit RC = P2^1;
sbit ZC = P2^3;

sbit PWM = P1^0;

/************************************/
void forward(){
	IN4 = PWM;
	IN3 = 1;
	IN2 = PWM;
	IN1 = 1;
}

void backward()
{
	IN4 = 1;
	IN3 = PWM;
	IN2 = 1;
	IN1 = PWM;	
}

void turnLeft(){
	IN4 = PWM;
	IN3 = 1;
	IN2 = 1;
	IN1 = 1;
}

void turnRight(){  	
	IN4 = 1;
	IN3 = 1;
	IN2 = PWM;
	IN1 = 1;	
}

void stop(){
	IN4 = 1;
	IN3 = 1;
	IN2 = 1;
	IN1 = 1;
}

void delay(int i)
{
	while (i)
		i--;
}

/***************************/

/************************************/
void Timer0_Init()
{
	EA = 1;
	ET0 = 1;	  				//配置IE（中断允许计数器），等价于EA=1;ET0=1;
	TMOD=0x01;					//TCON?
	TH0=(65536-10)/256;  		//10ms进入一次中断
	TL0=(65536-10)%256;  
	TR0=1;					   
}

void PWM1() interrupt 1
{
	static int count;
	TH0=(65536-10)/256;  		//重装初值
	TL0=(65536-10)%256;
	if (count < 15) PWM = 0;
	if (count >= 15) PWM = 1;
	if (count == 100) count = 0;
	count++;
}
/************************************/
void main(){
 Timer0_Init();

	while(1)
	{
	P0 = 0X00;
	{
		if (RC == 1 && LC == 0 )
		{						   //检测到黑线输出高电平
	 		turnRight();
			delay(5);
			continue;
		}
		if (LC == 1 && RC == 0 )
		{
	 		turnLeft();
			delay(5);
			continue;
		}
		if (LC == 0 && RC == 0 )
		{
			forward();
			delay(5);
			continue;
		}


	}	
		
	}
}

