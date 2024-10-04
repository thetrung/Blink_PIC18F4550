//
//
// 'C' source line config statements
#include <xc.h>

//////////////////////////////////////////////////////////////////////////////////
// How to Display the Configuration Bits Window :
// From the main menu, select Window > Target Memory Views > Configuration Bits. 
//
// * Good news : It's still working fine with 18F4550.

// PIC18F4550 Configuration Bit Settings
//
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
//
#pragma config FOSC = INTOSCIO_EC        // Oscillator Selection bits (RC oscillator)
#pragma config PLLDIV = 2                // PLL prescaler set to divide by 2
#pragma config CPUDIV = OSC1_PLL2        // CPU system clock divide by 2
#pragma config USBDIV = 2                // USB clock source from 96Mhz 
#pragma config FCMEN = OFF               // Fail-Safe Clock Monitor
#pragma config IESO = OFF                // Oscillator Selection bits (RC oscillator)
#pragma config PWRT = OFF                // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON                  // Brown-out Reset Enable
#pragma config BORV = 3                  // Brown-out Reset Enable bit (BOR enabled)
#pragma config VREGEN = ON               // USB Voltage-REGulator Enabled.
#pragma config WDT = OFF                 // Watchdog Timer Enable bit (WDT enabled)
#pragma config MCLRE = ON                // pin MCLR enabled.
#pragma config LVP = ON                  // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config XINST = OFF               // Extended Instruction Set Enable Bit ( Legacy Mode )

#define _XTAL_FREQ 8000000     // 16-48Mhz but doesn't matter if config below.

#define PERIOD 100 // x2 (us)

/////////////////////////
//                     //
// Arduino-like Macros //
// ( As a Demo on how )//
//                     //
/////////////////////////

// MODE
#define LOW 0
#define HIGH 1

// I/O
#define INPUT 1
#define OUTPUT 0

// PORT-A
#define RA0 LATA0
#define RA1 LATA1
#define RA2 LATA2
#define RA3 LATA3
#define RA4 LATA4
#define RA5 LATA5
#define RA6 LATA6
#define RA7 LATA7

// PINMODE
#define PIN_RA0 TRISA0

// FUNCTIONS 
#define pinMode(PIN, MODE) (PIN = MODE)
#define digitalWrite(PORT, STATE) (PORT = STATE)
#define delay __delay_ms

void main(void) {
    //
    // Config Clock :
    //
    // - Without IRCF/SCS, 18F4550 will auto-select slower clock @ 31Khz~125kHz.
    // - IRCF : select clock speed, default (lowest) 0b000 -> 31KHz, 0b111 -> 8Mhz
    // - SCS : has 4 modes : 
    //   00 = primary clock source (FOSC config), which could be external.
    //   01 = Timer-1 oscillator : a low-power clock source.
    //   10 = internal oscillator block (8MHz || IRCF bit)
    //   11 = internal 31kHz oscillator, used for low-power mode.
    // 
    //
    OSCCONbits.IRCF = 0b111;
    OSCCONbits.SCS = 0b10;
    
    // Config I/O by TRIS-A/B/C/D/E register :
//    TRISA0 = 0;   // Set RA0 as output:
    pinMode(PIN_RA0, OUTPUT);
    
    while(1){
        // Set HIGH/LOW
//        LATAbits.LATA0 = HIGH; __delay_ms(PERIOD);
//        LATAbits.LATA0 = LOW; __delay_ms(PERIOD); 
        
        digitalWrite(RA0, HIGH); 
        delay(PERIOD);
        
        digitalWrite(RA0, LOW); 
        delay(PERIOD);
    }
    return;
}
