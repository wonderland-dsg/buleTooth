#include <reg52.h>
#define u8 unsigned char
#define u16 unsigned int
#define int16_t signed int
#define uint16_t  u16 
#define uint8_t  u8 
	

static u16 RS232_VisualScope_CRC16( u8 *Array, u16 Len );
static u8 RS232_VisualScope_CHKSUM(u8 *Array,u16 Len);
void VisualScope(int16_t CH1,int16_t CH2,int16_t CH3,int16_t CH4);