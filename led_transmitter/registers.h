#define SYSCTL_RCGUART 	(*((volatile unsigned long *)0x400FE618))
#define SYSCTL_PRUART 	(*((volatile unsigned long *)0x400FEA18))
#define SYSCTL_RCGCGPIO 	(*((volatile unsigned long *)0x400FE608))
#define SYSCTL_PRGPIO 	(*((volatile unsigned long *)0x400FEA08))

#define NVIC_ST_CTRL 	  (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD 	(*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT	(*((volatile unsigned long *)0xE000E018))

#define NVIC_EN0 	(*((volatile unsigned long *)0xE000E100))
#define NVIC_EN1 	(*((volatile unsigned long *)0xE000E104))

#define GPIO_PORTF_UNLOCK 	(*((volatile unsigned long *)0x4C4F434B))

#define GPIOA_DATA	(*((unsigned long *)0x400043FC))
#define GPIOA_DIR 	(*((volatile unsigned long *)0x40004400))
#define GPIOA_AFSEL 	(*((volatile unsigned long *)0x40004420))
#define GPIOA_PCTL 	(*((volatile unsigned long *)0x4000452C))
#define GPIOA_AMSEL 	(*((volatile unsigned long *)0x40004528))
#define GPIOA_PUR 	(*((volatile unsigned long *)0x40004510))
#define GPIOA_PDR 	(*((volatile unsigned long *)0x40004514))
#define GPIOA_DR8R 	(*((volatile unsigned long *)0x40004508))
#define GPIOA_DEN 	(*((volatile unsigned long *)0x4000451C))
#define GPIOA_ICR  	(*((unsigned long *)0x4000441C))

#define GPIOF_DATA	(*((unsigned long *)0x400253FC))
#define GPIOF_DIR 	(*((volatile unsigned long *)0x40025400))
#define GPIOF_AFSEL 	(*((volatile unsigned long *)0x40025420))
#define GPIOF_PCTL 	(*((volatile unsigned long *)0x4002552C))
#define GPIOF_AMSEL 	(*((volatile unsigned long *)0x40025528))
#define GPIOF_PUR 	(*((volatile unsigned long *)0x40025510))
#define GPIOF_PDR 	(*((volatile unsigned long *)0x40025514))
#define GPIOF_DR8R 	(*((volatile unsigned long *)0x40025508))
#define GPIOF_DEN 	(*((volatile unsigned long *)0x4002551C))
#define GPIOF_ICR  	(*((unsigned long *)0x4002541C))

#define UART0_DR 	(*((volatile unsigned long *)0x4000C000))
#define UART0_FR 	(*((volatile unsigned long *)0x4000C018))
#define UART0_IBRD 	(*((volatile unsigned long *)0x4000C024))
#define UART0_FBRD 	(*((volatile unsigned long *)0x4000C028))
#define UART0_LCRH 	(*((volatile unsigned long *)0x4000C02C))
#define UART0_CTL 	(*((volatile unsigned long *)0x4000C030))


