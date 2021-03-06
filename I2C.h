#include <intrins.h>
#include <reg52.h>

sbit I2C_SDA=P1^0;
sbit I2C_SCL=P1^1;

#define	SMPLRT_DIV		0x19	//??????,???:0x07(125Hz)
#define	CONFIG			0x1A	//??????,???:0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//??????????,???:0x18(???,2000deg/s)
#define	ACCEL_CONFIG	0x1C	//?????????????????,???:0x01(???,2G,5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//????,???:0x00(????)
#define	WHO_AM_I			0x68	//IIC?????(????0x68,??)
#define	SlaveAddress	0xD0

void delay();
void i2c_start();
void i2c_stop();
void send_0(void);
void send_1(void);
void i2c_ack();
bit check_ack(void);
bit i2c_send_byte(unsigned char c);
unsigned char i2c_recv_byte();		
