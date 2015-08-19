
#include <mpu.h>
#include <visualScope.h>
sbit p11=P1^1;
sbit p10=P1^0;
sbit p12=P1^2;
sbit p13=P1^3;
sbit p14=P1^4;
sbit p15=P1^5;
sbit p16=P1^6;
sbit p17=P1^7;
bit  flag_REC=0; 
bit  flag=0;  

double a[3],w[3],Angle[3],T;

unsigned char str[] ="test code!";
char code str1[] = "收到指令，向后!\n";
char code str2[] = "收到指令，向左!\n";
char code str3[] = "收到指令，向右!\n";
char code str4[] = "收到指令，停止!\n";
unsigned char check[3]={0xAA,0xAB,0xAC};

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
uchar  i=0;
uchar  dat=0;
uchar  buff[5]=0;
sbit    SCL=P2^0;			//IIC
sbit    SDA=P2^1;			//IIC

void init_uart(void);
void send_str(char code str_[]);
void send_massage();
void DecodeIMUData(unsigned char chrTemp[]);
void send_double(double a);
void send_doubleStr(double a[]);

int main(){
	init_uart();
	mpu_init();
	send_str("init success!\n");
	while(1){
//		int Gx,Gy,Gz,t;
//		Gx=(int)mpu_read_byte(GYRO_XOUT_H)<<8|(int)mpu_read_byte(GYRO_XOUT_L);
//		Gy=(int)mpu_read_byte(GYRO_YOUT_H)<<8|(int)mpu_read_byte(GYRO_YOUT_L);
//		Gz=(int)mpu_read_byte(GYRO_ZOUT_H)<<8|(int)mpu_read_byte(GYRO_ZOUT_L);
//		t=(int)mpu_read_byte(TEMP_OUT_H)<<8|(int)mpu_read_byte(TEMP_OUT_L);
//		if(Gx>32768){
//			Gx=65535-Gx;
//		}
//		if(Gx<32768){
//			Gx=-Gx;
//		}
//		if(Gy>32768){
//			Gy=65535-Gy;
//		}
//		if(Gy<32768){
//			Gy=-Gy;
//		}
//		if(Gx>32768){
//			Gz=65535-Gz;
//		}
//		if(Gz<32768){
//			Gz=-Gz;
//		}
//		VisualScope(t,Gx,Gy,Gz);
		unsigned char temp=0,i,j;
		for(i=0;i<3;i++){
			SBUF=check[i];
			while(!TI);
			TI=0;
		}
		//send_str("read again!!!\n");
//		SBUF=0xAA;
//		while(!TI);
//		TI=0;
		for(i=0;i<14;i++){
			j=ACCEL_XOUT_H+i;
			temp|=SBUF=mpu_read_byte(j);
		  while(!TI);
			TI = 0;
		 }
		SBUF=temp;
		while(!TI);
			TI = 0;
		//send_massage();
	}
	return 0;
}



void init_uart(void){
	TMOD=0x20;
	TH1=0xfd;  //9600
	TL1=0xfd;
	SCON=0x50;
	TR1=1;
	ES=1;
	EA=1;
}
void isr_uart(void) interrupt 4{
//	if(RI){	                 //是否接收中断
//		RI=0;
//    dat=SBUF;
//    if(dat=='O'&&(i==0)) //接收数据第一帧
//      {
//        buff[i]=dat;
//        flag=1;        //开始接收数据
//      }
//      else
//      if(flag==1)
//     {
//       i++;
//       buff[i]=dat;
//       if(i>=2){
//				i=0;
//				flag=0;
//				flag_REC=1;
//			 }  // 停止接收
//     }
//	 }
}
 void send_massage(){
	 unsigned char temp[11],i;
	 temp[1]=0x51;
	 for(i=2;i<10;i++){
			 temp[i]=mpu_read_byte(ACCEL_XOUT_H+i-2);
		 }
	 DecodeIMUData(temp);
	 send_doubleStr(a);
	 //send_doubleStr(w);
	 //send_doubleStr(Angle);
	 //send_double(T);
 }
 
	void send_double(double d){
		unsigned long a=d;
		unsigned char b;
		char t=4;
		while(t>0) {
			t--;
			b=a&0x000000ff;
			SBUF = b;
			while(!TI);				// 等特数据传送
				TI = 0;					// 清除数据传送标志
			a>>8;
	   }	
	}
	
	void send_doubleStr(double a[]){
		int i;
		SBUF=0xAA;				//开始标志位
		while(!TI);				// 等特数据传送
				TI = 0;					// 清除数据传送标志
		for(i=0;i<3;i++){
			send_double(a[i]);
		}
	}
	
	
		/*while(1){
		if(flag_REC==1){
			if(buff[0]=='O'&&buff[1]=='N')	//第一个字节为O，第二个字节为N，第三个字节为控制码
			switch(buff[2]){
				case 'C':
					P1=0xFF;
					p12=0;
					p16=1;
				  send_str(str2);
					break;
				case 'A':
					P1=0xFF;
					p10=0;
					p14=1;
				  send_str(str);
					break;
				case 'D':
					P1=0xFF;
					p13=0;
					p17=1;
				  send_str(str3);
					break;
				case 'B':
					P1=0xFF;
					p11=0;
					p15=1;
				  send_str(str1);
					break;
				case 'F':
					P1=0x00;
				  send_str(str4);
					break;
				}
		}
	}*/