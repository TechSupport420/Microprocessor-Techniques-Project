#include "registers.h"
void Delay(unsigned int);
void setupUARTforUSB(void);
char readUSB(void);
void writeUSB(char c);
void setupUARTforBluetooth(void);
char readBluetooth(void);
void writeBluetooth(char c);
void setupBluetoothInterrupt(void);
void bluetoothISR(void);
void processBluetoothCommand(char command);
void printNum(int num);
void printString(char* str);

extern void DisableInterrupts(void);
extern void EnableInterrupts(void);

void Delay(unsigned int numLoops){
	volatile unsigned int lp;
	volatile unsigned int i;

	for(lp=0; lp<numLoops; lp++)
		for (i=0; i<=0xFFFF; i++) ;
}

char mode = 0;
char speed = 0;
char direction = 0;
char targetHeading = 0;

// configure UART0 on port A pins 0 and 1
void setupUARTforUSB(void){
	
	// enable clock for port A
	SYSCTL_RCGCGPIO |= 0x01;
	while((SYSCTL_PRGPIO & 0x01) != 0x01);
	
	// enable clock for UART0
	SYSCTL_RCGCUART |= 0x01;
	while((SYSCTL_RCGCUART & 0x01) != 0x01);
	
	// diable UART
	UART0_CTL &=~ 0x01;
	
	// set baud rate: 9600, I=104, F=11
	UART0_IBRD = 104;
	UART0_FBRD = 11;
	
	// set line control parameters: 8bits, no parity, 1 stop bit
	UART0_LCRH &=~ 0x0E;
	UART0_LCRH |= 0x60;
	
	// enable UART
	UART0_CTL |= 0x301;
	
	// set GPIO alternate function select
	GPIO_PORTA_AFSEL |= 0x03;
	
	// enable pull down
	GPIO_PORTA_PUR |= 0x03;
	
	// digital enable
	GPIO_PORTA_DEN |= 0x03;
	
	// set GPIO alternate function
	GPIO_PORTA_PCTL &=~ 0x000000FF;
	GPIO_PORTA_PCTL |= 0x00000011;
	
}

// configure UART1 on port C pins 4 and 5
void setupUARTforBluetooth(void){
	
	// enable clock for port C
	SYSCTL_RCGCGPIO |= 0x04;
	while((SYSCTL_PRGPIO & 0x04) != 0x04);
	
	// enable clock for UART1
	SYSCTL_RCGCUART |= 0x02;
	while((SYSCTL_RCGCUART & 0x02) != 0x02);
	
	// diable UART
	UART1_CTL &=~ 0x01;
	
	// set baud rate: 9600, I=104, F=11
	UART1_IBRD = 104;
	UART1_FBRD = 11;
	
	// set line control parameters: 8bits, no parity, 1 stop bit
	UART1_LCRH &=~ 0x0E;
	UART1_LCRH |= 0x60;
	
	// enable UART
	UART1_CTL &=~ 0x20;
	UART1_CTL |= 0x301;
	
	// set GPIO alternate function select
	GPIO_PORTC_AFSEL |= 0x30;
	
	// enable pull down
	GPIO_PORTC_PUR |= 0x30;
	
	// digital enable
	GPIO_PORTC_DEN |= 0x30;
	
	// set GPIO alternate function
	GPIO_PORTC_PCTL &=~ 0x00FF0000;
	GPIO_PORTC_PCTL |= 0x00220000;
	
}

// enable interrupt on bluetooth receive
void setupBluetoothInterrupt(void){
	
	// disable all interrupts
	// CPSID();
	DisableInterrupts();
	
	// set interrupt FIFO level = 1
	UART1_IFLS &=~ 0x28;
	UART1_IFLS |= 0x08;
	
	// enable interrupt
	UART1_IM |= 0x10;
	
	// enable UART1 interrupts
	NVIC_EN0 |= 0x40;
	
	// set priority = 1 (second highest)
	NVIC_PRI1 &=~ (unsigned)(0x7) << 13;
	NVIC_PRI1 |= (unsigned)(0x1) << 13;
	
	// set interrupt service routine
	// done in startup.s
	
	// enable all interrupts
	// CPSIE();
	EnableInterrupts();
	
}

// bluetooth recieve interrupt handler
void bluetoothISR(void){
	
	// read command and process it
	char c = readBluetooth();
	processBluetoothCommand(c);
	
	// clear interrupt status
	UART1_ICR |= 0x10;
	
}

// processes a bluetooth UART command and decodes it
void processBluetoothCommand(char command){
	
	// get mode
	mode = command & 0x80;
	
	if(mode){
		// if direct mode
		
		// get speed
		speed = command >> 3 & 0xF;
		
		// get direction
		direction = command & 0x7;
		
	}else{
		// heading mode
		
		// map from 2 bits to 4 bits
		char speedMap[] = {0, 0x7, 0, 0xF};

		// get speed
		speed = speedMap[command >> 5 & 0x3];
		
		// get heading
		targetHeading = command & 0x1F;
		
	}
	
	printString("m: ");
	printNum((int) mode);
	printString("s: ");
	printNum((int) speed);
	printString("d: ");
	printNum((int) direction);
	printString("h: ");
	printNum((int) targetHeading);
	
}

void printString(char* str){
	
	while(*str != 0){
		writeUSB(*str);
		str++;
	}
	
}

// prints to USB UART the hex representation of given int
void printNum(int num){
	
	char characters[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	
	// for each nibble
	for(int i = 28; i >= 0; i -= 4){
		int n = num >> i & 0xF;
		writeUSB(characters[n]);
	}
	
	// new line
	writeUSB('\r');
	writeUSB('\n');
	
}

// receive a character
char readUSB(void){
	
	// wait for input
	while((UART0_FR & 0x10) == 0x10);
	
	return UART0_DR & 0x000000FF;
	
}

// send a character
void writeUSB(char c){
	
	// wait for output availabiity
	while((UART0_FR & 0x20) == 0x20);
	
	// send data
	UART0_DR = c;
	
}

// receive a character
char readBluetooth(void){
	
	// wait for input
	while((UART1_FR & 0x10) == 0x10);
	
	return UART1_DR & 0x000000FF;
	
}

// send a character
void writeBluetooth(char c){
	
	// wait for output availabiity
	while((UART1_FR & 0x20) == 0x20);
	
	// send data
	UART1_DR &=~ 0xFF;
	UART1_DR = c;
	
}
