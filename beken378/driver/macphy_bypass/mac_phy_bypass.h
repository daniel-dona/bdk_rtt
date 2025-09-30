#include <stdint.h>
#ifndef _MAC_PHY_BYPASSH_
#define _MAC_PHY_BYPASS_H_

#define MPB_ADDR_BASE                (0x01060000)

typedef union
{
	struct {
		volatile uint32_t bypass_en:1;
		volatile uint32_t resv0:3;
		volatile uint32_t mode:2;
		volatile uint32_t resv1:2;
		volatile uint32_t single_txen:1;
		volatile uint32_t resv2:23;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x0_TypeDef;

typedef union
{
	struct {
		volatile uint32_t pre_rxdelay:20;
		volatile uint32_t resv2:12;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x1_TypeDef;

typedef union
{
	struct {
		volatile uint32_t rxdelay:20;
		volatile uint32_t resv2:12;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x2_TypeDef;

typedef union
{
	struct {
		volatile uint32_t pre_txdelay:20;
		volatile uint32_t resv2:12;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x3_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txdelay:20;
		volatile uint32_t resv2:12;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x4_TypeDef;

typedef union
{
	struct {
		volatile uint32_t rxstat:20;
		volatile uint32_t resv2:12;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x8_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txstat:20;
		volatile uint32_t resv2:12;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x9_TypeDef;

typedef union
{
	struct {
		volatile uint32_t rxerrstat:20;
		volatile uint32_t resv2:12;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0xA_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txerrstat:20;
		volatile uint32_t resv2:12;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0xB_TypeDef;


typedef union
{
	struct {
		volatile uint32_t txvector0:8;
		volatile uint32_t resv1:24;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x80_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txvector1:8;
		volatile uint32_t resv1:24;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x81_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txvector2:8;
		volatile uint32_t resv1:24;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x82_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txvector3:8;
		volatile uint32_t resv1:24;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x83_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txvector4:8;
		volatile uint32_t resv1:24;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x84_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txvector5:8;
		volatile uint32_t resv1:24;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x85_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txvector6:8;
		volatile uint32_t resv1:24;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x86_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txvector7:8;
		volatile uint32_t resv1:24;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x87_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txvector8:8;
		volatile uint32_t resv1:24;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x88_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txvector9:8;
		volatile uint32_t resv1:24;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x89_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txvector10:8;
		volatile uint32_t resv1:24;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x8A_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txvector11:8;
		volatile uint32_t resv1:24;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x8B_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txvector12:8;
		volatile uint32_t resv1:24;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x8C_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txvector13:8;
		volatile uint32_t resv1:24;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x8D_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txvector14:8;
		volatile uint32_t resv1:24;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x8E_TypeDef;

typedef union
{
	struct {
		volatile uint32_t txvector15:8;
		volatile uint32_t resv1:24;		
	}bits;
	
	volatile uint32_t value;
}MPB_REG0x8F_TypeDef;

struct MPB_TypeDef {
    volatile MPB_REG0x0_TypeDef  *r0;
    volatile MPB_REG0x1_TypeDef  *r1;
    volatile MPB_REG0x2_TypeDef  *r2;
    volatile MPB_REG0x3_TypeDef  *r3;
    volatile MPB_REG0x4_TypeDef  *r4;
    volatile MPB_REG0x8_TypeDef  *r8;
    volatile MPB_REG0x9_TypeDef  *r9;
    volatile MPB_REG0xA_TypeDef  *r10;    
    volatile MPB_REG0xB_TypeDef  *r11;
    
    volatile MPB_REG0x80_TypeDef  *r128;
    volatile MPB_REG0x81_TypeDef  *r129;
    volatile MPB_REG0x82_TypeDef  *r130;
    volatile MPB_REG0x83_TypeDef  *r131;
    volatile MPB_REG0x84_TypeDef  *r132;
    volatile MPB_REG0x85_TypeDef  *r133;
    volatile MPB_REG0x86_TypeDef  *r134;
    volatile MPB_REG0x87_TypeDef  *r135;
    volatile MPB_REG0x88_TypeDef  *r136;
    volatile MPB_REG0x89_TypeDef  *r137;
    volatile MPB_REG0x8A_TypeDef  *r138;
    volatile MPB_REG0x8B_TypeDef  *r139;
    volatile MPB_REG0x8C_TypeDef  *r140;
    volatile MPB_REG0x8D_TypeDef  *r141;
    volatile MPB_REG0x8E_TypeDef  *r142;
    volatile MPB_REG0x8F_TypeDef  *r143;
};

extern uint32_t mpb_ctrl(uint32_t cmd, void *param);
#endif // _MAC_PHY_BYPASS_H_

// eof
