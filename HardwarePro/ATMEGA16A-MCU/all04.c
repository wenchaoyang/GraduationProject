#include <iom16v.h> 
#include <macros.h> 

unsigned char Re_buf[11],counter;//用来存放串口数据的数组，都是字符型
unsigned char ucStra[6],ucStrw[6],ucStrAngle[11];
unsigned char flag;
unsigned char usart_ok;

void delay(int time);
//*********发送一个字符************//
void put_c(unsigned char c) 
{
	while( !(UCSRA & (1<<UDRE)) );
	UDR=c;
}
//*********发送一串字符************//
void put_s(unsigned char *ptr)
{
	while (*ptr)
	{
		put_c(*ptr++);
	}
	put_c(0x0D);	  //换行
	//put_c(0x0A);  //回车
}
//*********USART 初始化************//
void USART_init(void)
{
 	UCSRB = 0x00;   //disable while setting baud rate
    //USART 9600 8, n,1  超级终端等也要设成同样的设置才能通讯
    UCSRC = (1<<URSEL) | 0x06;
    //异步，8位数据，无奇偶校验，一个停止位，无倍速  
    UBRRL= 12;//64、103、(F_CPU/BAUDRATE/8-1)%256;//=12即9600波特率
    UBRRH= 0;//3(F_CPU/BAUDRATE/8-1)/256;
    UCSRA = 0x02;//0x00;正常异步方式
    UCSRB = 0x98;   //接收中断允许，接收缓冲自动清空，接收允许    
}

//*********PWM功能定时器的初始化************//
void timer_init(void) 
{ 
 //SREG=0x80;         //使能全局中断
// TIMSK=(1<<OCIE1A); //使能比较匹配中断
 TCCR1A=0B10100001; //快速PWM模式，无分频，比较匹配时置零，TOP时置1
 TCCR1B=0B00001010;
}
 //*********毫秒延时************//
void delay(int time)
{
 int i;
 for(;time>0;time--)
  for(i=0;i<1141;i++);
}

//////////////////主函数////////////////////////////
void main(void) 
{  
 USART_init();
 //timer_init();

 SEI(); 
 DDRA=0XFF;
 PORTA=0X00; 
 
 delay(100);
 usart_ok=0;
 
 while(1)
 {
  if(flag>0)
  {    
   put_s(ucStrAngle); 
   PORTA = ~PORTA;    
   
   flag = 0;
   usart_ok = 0;
   counter = 0;
   SEI();   
  } 
  delay(10); 
  //put_s("fuck it");  
 }
}
/////////////////////中断接收数据//////////////
#pragma interrupt_handler uart0_rx_isr:12
void uart0_rx_isr(void)
{ 	 
	 
	Re_buf[counter]=UDR;		
	if(counter==0&&Re_buf[0]!=0x55) return;      //第0号数据不是帧头	             
	
	if(usart_ok == 0)
	{
		counter++; 
	    if(counter==11)             //接收到11个数据
	    {    
	       counter=0;               //重新赋值，准备下一帧数据的接收  		    
			switch(Re_buf [1])
			{
			case 0x51:
			ucStra[0]=Re_buf[2];
			ucStra[1]=Re_buf[3];
			ucStra[2]=Re_buf[4];
			ucStra[3]=Re_buf[5];
			ucStra[4]=Re_buf[6];
			ucStra[5]=Re_buf[7];
			break;
			case 0x52:	 
			ucStrw[0]=Re_buf[2];
			ucStrw[1]=Re_buf[3];
			ucStrw[2]=Re_buf[4];
			ucStrw[3]=Re_buf[5];
			ucStrw[4]=Re_buf[6];
			ucStrw[5]=Re_buf[7];
			break;
			case 0x53: 
			ucStrAngle[0]=Re_buf[0];
			ucStrAngle[1]=Re_buf[1];
			ucStrAngle[2]=Re_buf[2];
			ucStrAngle[3]=Re_buf[3];
			ucStrAngle[4]=Re_buf[4];
			ucStrAngle[5]=Re_buf[5];
			ucStrAngle[6]=Re_buf[6];
			ucStrAngle[7]=Re_buf[7];
			ucStrAngle[8]=0X54;
			ucStrAngle[9]=0X54;
			ucStrAngle[10]=0X54;
			flag = 1;
			usart_ok = 1;
			CLI();
			break;
			} 
	    }
	 }
}
