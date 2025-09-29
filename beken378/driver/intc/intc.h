/**
 ****************************************************************************************
 *
 * @file intc.h
 *
 * @brief Declaration of the Reference Interrupt Controller (INTC) API.
 *
 * Copyright (C) RivieraWaves 2011-2016
 *
 ****************************************************************************************
 */

#ifndef _INTC_H_
#define _INTC_H_

#include "compiler.h"
#include "doubly_list.h"
#include "generic.h"

//#define INTC_DEBUG

#ifdef INTC_DEBUG
#define INTC_PRT       os_printf
#define INTC_WPRT      warning_prf
#else
#define INTC_PRT       os_null_printf
#define INTC_WPRT      os_null_printf
#endif

#define INTC_MAX_COUNT                    32


struct arm_registers
{
    uint32 r0;
    uint32 r1;
    uint32 r2;
    uint32 r3;
    uint32 r4;
    uint32 r5;
    uint32 r6;
    uint32 r7;
    uint32 r8;
    uint32 r9;
    uint32 r10;
    uint32 fp;
    uint32 ip;
    uint32 sp;
    uint32 lr;
    uint32 pc;
    uint32 spsr;
    uint32 cpsr;
};

typedef struct
{
    LIST_HEADER_T list;

    FUNCPTR isr_func;

    UINT8  pri;            // priority
    UINT8  int_num;
    UINT16 resv;
} ISR_T;

typedef struct
{
    LIST_HEADER_T isr;

    UINT8 max;     // maximum interrupt number
    UINT8 min;     // minum interrupt number
} ISR_LIST_T;
/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief Initialize and configure the reference INTCTRL.
 * This function configures the INTC according to the system needs.
 ****************************************************************************************
 */
extern void intc_init(void);
extern void intc_irq(void);
extern void intc_fiq(void);
extern void do_irq( void );
extern void do_fiq( void );
extern void do_swi( void );
extern void do_undefined( void );
extern void do_pabort( void );
extern void do_dabort( void );
extern void do_reserved( void );

#endif // _INTC_H_
