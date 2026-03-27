
 #define _XTAL_FREQ 16000000

#include <xc.h>
#include <stdio.h>
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define RS  RB0
#define EN  RB1
#define LCD_PORT PORTD 

void lcd_cmd(unsigned char cmd)
{
    RS = 0;
    LCD_PORT = cmd;
    EN = 1;
    __delay_ms(2);
    EN = 0;
}
void lcd_data(unsigned char data)
{
    RS = 1;
    LCD_PORT = data;
    EN = 1;
    __delay_ms(2);
    EN = 0;
}
void lcd_string(const char *c)
{
    while(*c)
        lcd_data(*c++);
}
void lcd_init()
{
    __delay_ms(20);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}
void adc_init()
{
    ADCON0 = 0x81;
    ADCON1 = 0x80; 
}
unsigned int adc_read(unsigned char channel)
{
    if(channel > 7)
        return 0;
    ADCON0 &= 0xC5;
    ADCON0 |= (channel << 3);  
    __delay_us(20);
    GO_nDONE = 1;
    while(GO_nDONE);
    return ((ADRESH << 8) + ADRESL);
}

void main()
{
    TRISA = 0xFF;  
    TRISB = 0x00;
    TRISD = 0x00;
    TRISC = 0x00;
    lcd_init();
    adc_init();
    PORTC=0;
    PORTD=0;
    PORTB=0;
    
    unsigned int a0,a1;
    float v0,v1; 
    char buffer[16];

    while(1)
    {
        a0 = adc_read(0);
        a1 = adc_read(1);
        v0 = (a0*5.0/1023.0)*100;
        lcd_cmd(0x80);
        sprintf(buffer, "Temp: %.2f C",v0);
        lcd_string(buffer);
        v1=(a1*5.0/1023.0)*100;
        lcd_cmd(0x0C);
        sprintf(buffer, "Temp: %.2f C",v1);
        lcd_string(buffer);
        if(v0 > v1)
         {
             PORTCbits.RC0 = 1;
             PORTCbits.RC1 = 0;
         }
        else if(v1 > v0)
         {
             PORTCbits.RC0 = 0;
             PORTCbits.RC1 = 1;
         }
        else
         {
              PORTCbits.RC0 = 0;
              PORTCbits.RC1 = 0;
         }
        __delay_ms(50);
    }
}
