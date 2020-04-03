/*********************************************************************************
* ����дʱ�䡿�� 2014��3��5��
* ����    �ߡ��� �������:03
* ����    ������ 1.0
* ����    վ���� http://www.qxmcu.com/ 
* ���Ա����̡��� http://qxmcu.taobao.com/ (ֱ����)  http://qx-mcu.taobao.com/  ���ܵ꣩
* ��ʵ��ƽ̨���� QX-MCS51 ��Ƭ��������
* ���ⲿ���񡿣� 11.0592mhz	
* ������оƬ���� STC89C52RC
* �����뻷������ Keil ��Visio4	
* �������ܡ��� ��ʱ��ʵ��			   			            			    
* ��ʹ��˵������ ʹ��ǰ���ȶ̽�J2����ñ
				 ��ʱ��0����ͨ����ʱ����ʱʵ��led����˸
**********************************************************************************/


#include<reg52.h> //�������⹦�ܼĴ����Ķ���
#define LED P1     //�궨��LED����P1

/* �������� -----------------------------------------------*/
void Init_Timer0(void);


/*
********************************************************************************
** �������� �� main(void)
** �������� �� ������
********************************************************************************
*/
main()
{
	Init_Timer0();
	while(1);
}


/*
********************************************************************************
** �������� �� Init_Timer0(void)
** �������� �� ��ʱ����ʼ���ӳ���
********************************************************************************
*/
void Init_Timer0(void)		  //��ʱ����ʼ���ӳ���
{
	TMOD |= 0x01;	  //ʹ��ģʽ1��16λ��ʱ����ʹ��"|"���ſ�����ʹ�ö����ʱ��ʱ����Ӱ��		     
	TH0=0x00;	      //������ֵ������ʹ�ö�ʱ�����ֵ��0��ʼ����һֱ��65535���
	TL0=0x00;
	EA=1;            //���жϴ�
	ET0=1;           //��ʱ���жϴ�
	TR0=1;           //��ʱ�����ش�
}

/*
********************************************************************************
** �������� �� Timer0_isr(void) interrupt 1 using 1
** �������� �� ��ʱ���жϳ���
********************************************************************************
*/
void Timer0_isr(void) interrupt 1 using 1
{
	TH0=0x00;		  //���¸�ֵ����ʽ1��16λ������������Ӳ����װ��ʼֵ
	TL0=0x00;
	
	LED=~LED;        //ָʾ�Ʒ��࣬���Կ�����˸

}