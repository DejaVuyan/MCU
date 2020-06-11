#include<reg52.h>
sbit led=P3^7;
void delay(unsigned int t);
void main(void)
{
	unsigned int CYCLE=600,PWM_LOW=0;
	while(1)
	{
		led=1;
	
		delay(50);
		for(PWM_LOW=1;PWM_LOW<CYCLE;PWM_LOW++)
		{
			led=0;
		
			delay(PWM_LOW);
			led=1;
		
			delay(CYCLE-PWM_LOW);
		}
			led=0;
			
			for(PWM_LOW=CYCLE-1;PWM_LOW>0;PWM_LOW--)
			{
				led=0;
			
				delay(PWM_LOW);
				led=1;
			
				delay(CYCLE-PWM_LOW);
			}
	}
}
void delay(unsigned int t)
{
	unsigned int x,y;
	for(y=0;y<t;y++)
	for(x=0;x<123;x++);
}	
