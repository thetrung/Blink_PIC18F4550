Blink on PIC18F4550
=====================
Not just a blink demo to verify my dozen of 4550, but also Arduino-like Macros to make it ease on eyes. Microchip really need to think about this, not just slapping MCC into it to hide.

### Configuration Bits
This is most-important stuff that I have documented inside the `main.c` code, as it make sure the code work.
```
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

#define _XTAL_FREQ 8000000               // Using internal oscillator @ 8Mhz but doesn't matter if config below.
```

### Clock Config
Although, you may have configured above, it still need to config in code.
- Without IRCF/SCS, 18F4550 will auto-select slower clock @ 31Khz~125kHz.

### OSCCONbits.IRCF 
Select clock speed, default (lowest) 0b000 -> 31KHz, 0b111 -> 8Mhz

### OSCCONbits.SCS 
Has 4 modes : 
- 00 = primary clock source (FOSC config), which could be external.
- 01 = Timer-1 oscillator : a low-power clock source.
- 10 = internal oscillator block (8MHz || IRCF bit)
- 11 = internal 31kHz oscillator, used for low-power mode.
```
//
// Config Clock :
//
OSCCONbits.IRCF = 0b111;
OSCCONbits.SCS = 0b10;
```
