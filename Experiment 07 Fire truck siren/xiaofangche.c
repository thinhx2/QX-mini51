/*********************************************************************************
* 【编写时间】： 2014年4月1日
* 【作    者】： 326电子工作室
* 【版    本】： TS-51 V1.0
* 【网    站】： http://ttsemb.taobao.com/ 
* 【声    明】： 此程序仅用于学习与参考，引用请注明版权和作者信息！
* 【函数功能】： 蜂鸣器测试-模拟消防车报警声			   			            			    
* 【使用说明】： 
                 按下独立按键k1，蜂鸣器模拟消防车报警声
                 按下独立按键k2，停止
**********************************************************************************/

#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char
#define uint  unsigned int

uchar  Count;
	
sbit  K1 = P3^5 ;
sbit  K2 = P3^4 ;
sbit BEEP = P3^6 ;          //蜂鸣器

/********************************************************
 延时函数
*********************************************************/
void  delay(void)
{
  uint  k;
  for(k=1700;k>0;k--);
}

/********************************************************
 键控制函数
*********************************************************/
void key_control()
{
  
   if(K1==0)
   {
   	 while(K1==0);
   	 TR0=1;
   }  
   if(K2==0)
   {
     while(K2==0);
   	 TR0=0;
   }
}
/********************************************************
 主函数
*********************************************************/
main()
{
   P0=0x0;
   P1=0xff;
   P2=0xff;
   Count=0x00;
   BEEP=1;

   TMOD=0x01; 
   TH0=0x00; TL0=0xff;      
   EA=1; ET0=1; 

   while(1)
   {      
     do
     {
       Count++;
	   key_control();
       delay();
     }while(Count!=0xff);

     do
     {
       Count--;
	   key_control();
       delay();
     }while(Count!=0x00);
   }
}

/*********************************************************
  Time0中断函数
**********************************************************/
void Time0(void) interrupt 1 using 0
{
   TH0=0xfe;               
   TL0=Count;
   BEEP=~BEEP;
}
   
/*********************************************************/
