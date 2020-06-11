#include "reg52.h"
sbit LED = P0^0;
unsigned char PWM_COUNT; //计数
unsigned int HUXI_COUNT;    //占空比更新时间
unsigned char PWM_VLAUE;    //占空比比对值
bit direc_flag;             //占空比更新方向

void timer0_init()
{
    TMOD=0x02;          //模式设置，00010000，定时器0，工作于模式2（M1=1，M0=0）
    TH0=0x47;               //定时器溢出值设置，每隔200us发起一次中断。
    TL0=0X47;
    TR0=1;                  //定时器0开始计时
    ET0=1;                  //开定时器0中断
    EA=1;                       //开总中断
    PWM_COUNT =0;
}
void time0() interrupt 1
{   
    PWM_COUNT++;
    HUXI_COUNT++;
    if(PWM_COUNT == PWM_VLAUE)      //判断是否到了点亮LED的时候
        LED = 0;                    //点亮LED
    if(PWM_COUNT == 10)             //当前周期结束
    {
        LED = 1;                    //熄灭LED
        PWM_COUNT = 0;              //重新计时
    }
    if((HUXI_COUNT == 600) && (direc_flag == 0))
    {                               //占空比增加10%
        HUXI_COUNT = 0;
        PWM_VLAUE++;
        if(PWM_VLAUE == 9)          //占空比更改方向
            direc_flag = 1; 
    }
    if((HUXI_COUNT == 600) && (direc_flag == 1))
    {                               //占空比减少10%
        HUXI_COUNT = 0;
        PWM_VLAUE--;
        if(PWM_VLAUE == 1)          //占空比更改方向
            direc_flag = 0; 
    }   
}
void main()
{
    HUXI_COUNT = 0;
    PWM_COUNT = 0;
    PWM_VLAUE = 5;
    direc_flag = 0;
    LED = 0;            //默认LED熄灭   
    timer0_init();      //定时器0初始化
    while(1);
}
