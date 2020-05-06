/*********************************************************************************
* 【编写时间】： 2014年3月5日
* 【作    者】： 清翔电子:03
* 【版    本】： 1.0
* 【网    站】： http://www.qxmcu.com/ 
* 【淘宝店铺】： http://qxmcu.taobao.com/ (直销店)  http://qx-mcu.taobao.com/  （总店）
* 【实验平台】： QX-MCS51 单片机开发板
* 【外部晶振】： 11.0592mhz	
* 【主控芯片】： STC89C52RC
* 【编译环境】： Keil μVisio4	
* 【程序功能】： 汉字液晶显示程序			   			            			    
* 【使用说明】： 使用时请取下J6跳线帽，将本店汉字液晶插入L1排母接口，液晶面向开发板
外部
**********************************************************************************/
#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char
#define xchar unsigned char code

sbit	 RST = P0^3;
sbit     A0 = P0^7;
sbit     E1 = P0^6;
sbit     E2 = P0^5;
sbit     RRW = P0^4;
sbit BF_12232 = ACC^7;

xchar picture[]={

/*--  调入了一幅图像：C:\Users\Administrator\Desktop\未标题-1.bmp  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x70,0xF0,0xE0,0xE0,0xC0,0x00,0x00,0x60,0xE0,
0xE3,0xFF,0xFF,0xFF,0xFC,0xF8,0xD0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0xF8,0xF8,0xF0,0xFC,0xFC,0xFC,0xDC,0xC0,
0xC0,0xE0,0xE0,0xE0,0xE0,0xE0,0x70,0x70,0x78,0x38,0xF8,0xF8,0xF0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0xF0,0xF0,0xF0,0xE0,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0x70,
0xF0,0xF0,0xF0,0xF0,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x38,
0x38,0x38,0xB8,0xF1,0xF1,0xF0,0x70,0xF2,0xFF,0xBF,0xFF,0xFF,0xFF,0xFF,0xFD,0xFD,
0xFC,0xFC,0xDC,0x1C,0x1C,0x1C,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0x73,0xF7,0xFF,0xFF,0xFF,0xFB,0xD9,0xC9,0x1D,0x3D,0xF9,0xF1,0xFF,0xFF,0xFF,0xFF,
0x78,0x70,0x60,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x3E,
0xFE,0xFC,0xFC,0xDC,0xFF,0xFF,0xFF,0x7F,0x77,0xA7,0xE7,0xFF,0xFF,0x7F,0x06,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,
0xC0,0xE0,0xE0,0xE0,0xE0,0xF8,0xFC,0xFC,0xFE,0xFF,0x77,0x73,0x71,0x70,0x70,0xF0,
0xF0,0xF0,0x60,0x00,0x00,0x00,0x00,0x00,0x60,0xF0,0xF8,0xFE,0x3F,0x07,0x01,0x00,
0x00,0xFF,0xFF,0xFF,0xFF,0xDF,0xFF,0xEE,0xEC,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x0E,0x0E,0x8F,0xF7,0xFF,0xFF,0x3F,0x07,0x01,
0x01,0x0D,0x0E,0xEF,0xE7,0xC3,0xFF,0xFF,0xFF,0x1F,0x3E,0x1F,0x0F,0xFF,0xFF,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x1F,0x1F,0x1D,0xFF,0xFF,
0xFF,0x8E,0x07,0x07,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0xE0,0xF0,0xF0,0x80,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x80,0xC0,
0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0x1F,0x1F,0x01,0x01,
0x01,0x10,0x38,0x70,0xFF,0xFF,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x10,0x1C,0x1E,0x1F,0x0F,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,
0x03,0x03,0x03,0x00,0x02,0x07,0x0F,0x1F,0x1F,0x3F,0x1F,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x07,0x07,0x07,0x07,0x07,
0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x07,0x07,0x01,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

};

xchar hanzi[]={

/*--  文字:  清  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x60,0x02,0x8C,0x00,0x44,0x54,0x54,0x54,0x7F,0x54,0x54,0x54,0x44,0x40,0x00,
0x04,0x04,0x7E,0x01,0x00,0x00,0xFF,0x15,0x15,0x15,0x55,0x95,0x7F,0x00,0x00,0x00,

/*--  文字:  翔  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x08,0x49,0x4E,0xF8,0x4C,0x4B,0x08,0x12,0x22,0xFE,0x00,0x12,0x22,0xFE,0x00,0x00,
0x82,0x42,0x32,0x0F,0x02,0x02,0x02,0x44,0x82,0x7F,0x04,0x42,0x81,0x7F,0x00,0x00,

/*--  文字:  电  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00,

/*--  文字:  子  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x80,0x82,0x82,0x82,0x82,0x82,0x82,0xE2,0xA2,0x92,0x8A,0x86,0x82,0x80,0x80,0x00,
0x00,0x00,0x00,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  科  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x24,0x24,0xA4,0xFE,0xA3,0x22,0x00,0x22,0xCC,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,
0x08,0x06,0x01,0xFF,0x00,0x01,0x04,0x04,0x04,0x04,0x04,0xFF,0x02,0x02,0x02,0x00,

/*--  文字:  技  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x10,0x10,0xFF,0x10,0x90,0x08,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x08,0x00,
0x04,0x44,0x82,0x7F,0x01,0x80,0x80,0x40,0x43,0x2C,0x10,0x28,0x46,0x81,0x80,0x00,


/*--  文字:  液  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x60,0x02,0x8C,0x00,0x84,0xE4,0x1C,0x05,0xC6,0xBC,0x24,0x24,0xE4,0x04,0x00,
0x04,0x04,0x7E,0x01,0x00,0x00,0xFF,0x82,0x41,0x26,0x18,0x29,0x46,0x81,0x80,0x00,

/*--  文字:  晶  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x00,0x00,0x7F,0x49,0x49,0x49,0x49,0x49,0x7F,0x00,0x00,0x00,0x00,0x00,
0x00,0xFF,0x49,0x49,0x49,0x49,0xFF,0x00,0xFF,0x49,0x49,0x49,0x49,0xFF,0x00,0x00,

/*--  文字:  测  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x60,0x02,0x8C,0x00,0xFE,0x02,0xF2,0x02,0xFE,0x00,0xF8,0x00,0xFF,0x00,0x00,
0x04,0x04,0x7E,0x01,0x80,0x47,0x30,0x0F,0x10,0x27,0x00,0x47,0x80,0x7F,0x00,0x00,

/*--  文字:  试  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x40,0x42,0xCC,0x00,0x90,0x90,0x90,0x90,0x90,0xFF,0x10,0x11,0x16,0x10,0x00,
0x00,0x00,0x00,0x3F,0x10,0x28,0x60,0x3F,0x10,0x10,0x01,0x0E,0x30,0x40,0xF0,0x00,

/*--  文字:  ！  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x33,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,


};
//---------------------------------------------
//void delayus(uint us)
//{
//	while(us!=0) us--;
//}
//---------------------------------------------
void delayms(uint ms)
{
	unsigned int x,y;
	for(x=ms;x>0;x--)
		for(y=100;y>0;y--);

}
//-------------------------------------------
void wcomd(uchar c)
{
	A0=0;RRW=0;P2=c;
}
//-------------------------------------------
void wdata(uchar d)
{
	A0=1;RRW=0;P2=d;
}

//-------------------------------------------
void initial()
{
	wcomd(0xaf);E1=0;E2=0;E1=1;E2=1; // Display On
	wcomd(0xc0);E1=0;E2=0;E1=1;E2=1; //Set Display Start Line
	wcomd(0xb8);E1=0;E2=0;E1=1;E2=1; //Set Page-Address
	wcomd(0x4f);E1=0;E2=0;E1=1;E2=1; //Set Column-Address
	wcomd(0xa0);E1=0;E2=0;E1=1;E2=1; //ADC select
	wcomd(0xa4);E1=0;E2=0;E1=1;E2=1; //Static drive off
	wcomd(0xa9);E1=0;E2=0;E1=1;E2=1; //1/32 duty
	wcomd(0xe0);E1=0;E2=0;E1=1;E2=1; //Read modify write mode end
	wcomd(0xee);E1=0;E2=0;E1=1;E2=1; //Release from the read modify write mode
	wcomd(0xe2);E1=0;E2=0;E1=1;E2=1; //Reset line,column,counter register to "0
}
//-------------------------------------------
void disp_bmp(xchar *str)
{
	uint i=0,j=0,k=0;
	uchar temp;

	temp=0xb8;
	
	wcomd(0xaf);E1=0;delayms(1);E1=1;
	for(k=0;k<4;k++)
	{
		wcomd(temp);E1=0;delayms(1);E1=1;
		wcomd(0x00);E1=0;delayms(1);E1=1;
		wcomd(0xc0);E1=0;delayms(1);E1=1;
		for(i=0;i<61;i++)
		{
			wdata(str[i+k*122]);E1=0;E1=1;
		}
		temp++;
	}
	
	temp=0xb8;
	wcomd(0xaf);E2=0;delayms(1);E2=1;
	for(k=0;k<4;k++)
	{
		wcomd(temp);E2=0;delayms(1);E2=1;
		wcomd(0x00);E2=0;delayms(1);E2=1;
		wcomd(0xc0);E2=0;delayms(1);E2=1;
		for(i=0;i<61;i++)
		{
			wdata(str[61+i+k*122]);E2=0;E2=1;
		}
		temp++;
	}
}

void dis_chinese(uchar x,uchar y,uchar h)
{
	uint i=0;
	if(x<46)									//能在第一页完全显示的条件
	{
		wcomd(0xaf);E1=0;E1=1;
		wcomd(0xb8+y);E1=0;delayms(1);E1=1;
		wcomd(x);E1=0;delayms(1);E1=1;
		wcomd(0xc0);E1=0;delayms(1);E1=1;
		for(i=0;i<16;i++)
		{
			wdata(hanzi[i+h*32]);E1=0;E1=1;
		}
		wcomd(0xb8+y+1);E1=0;delayms(1);E1=1;
		wcomd(x);E1=0;delayms(1);E1=1;
		wcomd(0xc0);E1=0;delayms(1);E1=1;
		for(i=0;i<16;i++)
		{
			wdata(hanzi[i+h*32+16]);E1=0;E1=1;
		}
	}
	else if(x>60)								//能在第二页完全显示的条件
	{
		wcomd(0xaf);E2=0;E2=1;
		wcomd(0xb8+y);E2=0;delayms(1);E2=1;
		wcomd(x-61);E2=0;delayms(1);E2=1;
		wcomd(0xc0);E2=0;delayms(1);E2=1;
		for(i=0;i<16;i++)
		{
			wdata(hanzi[i+h*32]);E2=0;E2=1;
		}
		wcomd(0xb8+y+1);E2=0;delayms(1);E2=1;
		wcomd(x-61);E2=0;delayms(1);E2=1;
		wcomd(0xc0);E2=0;delayms(1);E2=1;
		for(i=0;i<16;i++)
		{
			wdata(hanzi[i+h*32+16]);E2=0;E2=1;
		}
	}
	else										//拼接显示 		先写左半部分在第一页再写右半部分在第二页
 	{
		wcomd(0xaf);E1=0;E1=1;
		wcomd(0xb8+y);E1=0;delayms(1);E1=1;
		wcomd(x);E1=0;delayms(1);E1=1;
		wcomd(0xc0);E1=0;delayms(1);E1=1;
		for(i=0;i<(61-x);i++)
		{
			wdata(hanzi[i+h*32]);E1=0;E1=1;
		}
		wcomd(0xb8+y+1);E1=0;delayms(1);E1=1;
		wcomd(x);E1=0;delayms(1);E1=1;
		wcomd(0xc0);E1=0;delayms(1);E1=1;
		for(i=0;i<(61-x);i++)
		{
			wdata(hanzi[i+h*32+16]);E1=0;E1=1;
		}
		
		wcomd(0xaf);E2=0;E2=1;
		wcomd(0xb8+y);E2=0;delayms(1);E2=1;
		wcomd(0);E2=0;delayms(1);E2=1;
		wcomd(0xc0);E2=0;delayms(1);E2=1;
		for(i=(61-x);i<16;i++)
		{
			wdata(hanzi[i+h*32]);E2=0;E2=1;
		}
		wcomd(0xb8+y+1);E2=0;delayms(1);E2=1;
		wcomd(0);E2=0;delayms(1);E2=1;
		wcomd(0xc0);E2=0;delayms(1);E2=1;
		for(i=(61-x);i<16;i++)
		{
			wdata(hanzi[i+h*32+16]);E2=0;E2=1;
		}
	}
}

void dis_clear()
{
	uint i=0,j=0;
	
	for(j=0;j<4;j++)
	{
		wcomd(0xb8+j);E1=0;delayms(1);E1=1;
		wcomd(0x00);E1=0;delayms(1);E1=1;
		wcomd(0xc0);E1=0;delayms(1);E1=1;
		for(i=0;i<61;i++)
		{
			wdata(0x00);E1=0;E1=1;
		}
		wcomd(0xb8+j);E2=0;delayms(1);E2=1;
		wcomd(0x00);E2=0;delayms(1);E2=1;
		wcomd(0xc0);E2=0;delayms(1);E2=1;
		for(i=0;i<61;i++)
		{
			wdata(0x00);E2=0;E2=1;
		}
	}	
}
//-------------------------------------------
/////////////// MAIN //////////////////////
/////////////////////////////////////////////
void main(void)
{
	RST=0;
	delayms(10);
	RST=1;
	delayms(2);
	initial();           
	dis_clear();
	dis_clear();
	while(1)
	{    
		//dis_chinese(0,0,0);		
		dis_chinese(15,0,0);//清
		dis_chinese(30,0,1);//翔
		dis_chinese(45,0,2);//电
		dis_chinese(60,0,3);//子
		dis_chinese(75,0,4);//科
		dis_chinese(90,0,5);//技
		
		dis_chinese(43,2,6);//液
		dis_chinese(58,2,7);//晶
		dis_chinese(73,2,8);//测
		dis_chinese(88,2,9);//试
		dis_chinese(103,2,10);//！     
//测试屏幕组合显示
		delayms(5000);

		disp_bmp(picture); 
		
		delayms(8000);
		dis_clear();
		delayms(100);
	}
}