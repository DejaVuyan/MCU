#include "reg52.h"
sbit LED = P0^0;
unsigned char PWM_COUNT; //����
unsigned int HUXI_COUNT;    //ռ�ձȸ���ʱ��
unsigned char PWM_VLAUE;    //ռ�ձȱȶ�ֵ
bit direc_flag;             //ռ�ձȸ��·���

void timer0_init()
{
    TMOD=0x02;          //ģʽ���ã�00010000����ʱ��0��������ģʽ2��M1=1��M0=0��
    TH0=0x47;               //��ʱ�����ֵ���ã�ÿ��200us����һ���жϡ�
    TL0=0X47;
    TR0=1;                  //��ʱ��0��ʼ��ʱ
    ET0=1;                  //����ʱ��0�ж�
    EA=1;                       //�����ж�
    PWM_COUNT =0;
}
void time0() interrupt 1
{   
    PWM_COUNT++;
    HUXI_COUNT++;
    if(PWM_COUNT == PWM_VLAUE)      //�ж��Ƿ��˵���LED��ʱ��
        LED = 0;                    //����LED
    if(PWM_COUNT == 10)             //��ǰ���ڽ���
    {
        LED = 1;                    //Ϩ��LED
        PWM_COUNT = 0;              //���¼�ʱ
    }
    if((HUXI_COUNT == 600) && (direc_flag == 0))
    {                               //ռ�ձ�����10%
        HUXI_COUNT = 0;
        PWM_VLAUE++;
        if(PWM_VLAUE == 9)          //ռ�ձȸ��ķ���
            direc_flag = 1; 
    }
    if((HUXI_COUNT == 600) && (direc_flag == 1))
    {                               //ռ�ձȼ���10%
        HUXI_COUNT = 0;
        PWM_VLAUE--;
        if(PWM_VLAUE == 1)          //ռ�ձȸ��ķ���
            direc_flag = 0; 
    }   
}
void main()
{
    HUXI_COUNT = 0;
    PWM_COUNT = 0;
    PWM_VLAUE = 5;
    direc_flag = 0;
    LED = 0;            //Ĭ��LEDϨ��   
    timer0_init();      //��ʱ��0��ʼ��
    while(1);
}
