#include <mpu.h>

void send_str(unsigned char str_[]){ // 传送字串
	    unsigned char ii = 0;
	    while(str_[ii] != '\0') {
				SBUF = str_[ii];
				while(!TI);				// 等特数据传送
				TI = 0;					// 清除数据传送标志
				ii++;					// 下一个字符
	   }	
 }

void mpu_write_byte(unsigned char addr,unsigned char dat){
	i2c_start();
	if(i2c_send_byte(SlaveAddress)){ //Address for mpu6050
		send_str("i2c_send_byte(SlaveAddress) success!");
	}  
	i2c_send_byte(addr);  //Address for register
	i2c_send_byte(dat);   //write data to rigister
	i2c_stop();
}
unsigned char mpu_read_byte(unsigned char addr){
	unsigned char dat;
	i2c_start();
	i2c_send_byte(SlaveAddress);  //Address for mpu6050
	i2c_send_byte(addr);  //Address for register
	i2c_start();
	i2c_send_byte(SlaveAddress+1);  //Address for mpu6050
	dat=i2c_recv_byte();
	i2c_ack();
	i2c_stop();
	return dat;
}
void mpu_init(){
	int i,j;
	for(i=0;i<1000;i++){
		for(j=0;j<1000;j++)
		_nop_();
	}
	mpu_write_byte(PWR_MGMT_1, 0x00); 
	mpu_write_byte(SMPLRT_DIV, 0x07);
	mpu_write_byte(CONFIG, 0x06);
	mpu_write_byte(GYRO_CONFIG, 0x08);  //不自检，量程+-500
	mpu_write_byte(ACCEL_CONFIG, 0x00);   //不自检，量程+-2g
}
int get_data(unsigned char addr){
	unsigned char h,l;
	h=mpu_read_byte(addr);
	l=mpu_read_byte(addr+1);
	return (h<<8)+l;
}