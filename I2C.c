#include <I2C.h>
#define true 1
#define false 0
void delay(){
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();
//	_nop_();_nop_();_nop_();_nop_();
}

void i2c_start(){
	I2C_SDA=1;
	I2C_SCL=1;
	delay();
	I2C_SDA=0;
	delay();
	I2C_SCL=0;
	delay();
}

void i2c_stop(){
	I2C_SDA=0;
	I2C_SCL=1;
	delay();
	I2C_SDA=1;
	delay();
	I2C_SCL=0;
	delay();
}

void send_0(void){
	I2C_SDA=0;
	I2C_SCL=1;
	delay();
	I2C_SCL=0;
	delay();
}

void send_1(void){
	I2C_SDA=1;
	I2C_SCL=1;
	delay();
	I2C_SCL=0;
	delay();
}

bit check_ack(void){
	bit temp;
	I2C_SDA=1;
	I2C_SCL=1;
	delay();
	temp=I2C_SDA;
	delay();
	I2C_SCL=0;
	delay();
	if(temp==1){
		return false;
	}else{
		return true;
	}
}
void i2c_ack(){
	I2C_SDA=0;
	I2C_SCL=1;
	delay();
	I2C_SDA=1;
	I2C_SCL=0;
	delay();
}

bit i2c_send_byte(unsigned char c){
	unsigned char i;
	for(i=8;i>0;i--){
		if(c&0x80){
			send_1();
		}else{
			send_0();
		}
		c=c<<1;
	}
	if(check_ack()){
		return true;
	}
	return false;
}

unsigned char i2c_recv_byte(){
	unsigned char i,r;
	bit temp;
	for(i=8;i>0;i--){
		I2C_SDA=1;
		I2C_SCL=1;
		r=r<<1;
		delay();
		temp=I2C_SDA;
		delay();
		I2C_SCL=0;
		if(temp==1)r=r|0x01;
	}
	send_0();
	return r;
}

