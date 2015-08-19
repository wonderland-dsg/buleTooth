#include <I2C.h>
#include <reg52.h>

void send_str(unsigned char str_[]);
void mpu_write_byte(unsigned char addr,unsigned char dat);
unsigned char mpu_read_byte(unsigned char addr);
void mpu_init();
int get_data(unsigned char addr);