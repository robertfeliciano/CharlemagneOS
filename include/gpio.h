#include <stdint.h>

//basically just a loop that the compiler's optimization won't get rid of
static inline void delay(int32_t count){
    asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
                :"=r"(count)
                :[count]"0"(count)
                :"cc");
}

enum{
    //the offsets for each register.
    GPIO_BASE = 0x200000,
 
    //controls actuation of pull up/down to ALL GPIO pins.
    GPPUD = (GPIO_BASE + 0x94),
  
    //controls actuation of pull up/down for specific GPIO pin.
    GPPUDCLK0 = (GPIO_BASE + 0x98),
 
    //the base address for UART.
    //for raspi4 0xFE201000, raspi2 & 3 0x3F201000, and 0x20201000 for raspi1
    UART0_BASE = (GPIO_BASE + 0x1000), 

    //the offsets for reach register for the UART.
    UART0_DR     = (UART0_BASE + 0x00),
    UART0_RSRECR = (UART0_BASE + 0x04),
    UART0_FR     = (UART0_BASE + 0x18),
    UART0_ILPR   = (UART0_BASE + 0x20),
    UART0_IBRD   = (UART0_BASE + 0x24),
    UART0_FBRD   = (UART0_BASE + 0x28),
    UART0_LCRH   = (UART0_BASE + 0x2C),
    UART0_CR     = (UART0_BASE + 0x30),
    UART0_IFLS   = (UART0_BASE + 0x34),
    UART0_IMSC   = (UART0_BASE + 0x38),
    UART0_RIS    = (UART0_BASE + 0x3C),
    UART0_MIS    = (UART0_BASE + 0x40),
    UART0_ICR    = (UART0_BASE + 0x44),
    UART0_DMACR  = (UART0_BASE + 0x48),
    UART0_ITCR   = (UART0_BASE + 0x80),
    UART0_ITIP   = (UART0_BASE + 0x84),
    UART0_ITOP   = (UART0_BASE + 0x88),
    UART0_TDR    = (UART0_BASE + 0x8C),
 
    //the offsets for Mailbox registers
    MBOX_BASE    = 0xB880,
    MBOX_READ    = (MBOX_BASE + 0x00),
    MBOX_STATUS  = (MBOX_BASE + 0x18),
    MBOX_WRITE   = (MBOX_BASE + 0x20)
};

//Mailbox message with clock rate of PL011 to #MHz tag
volatile unsigned int __attribute__((aligned(16))) mbox[9] = {
    9*4, 0, 0x38002, 12, 8, 3000000, 0, 0
};