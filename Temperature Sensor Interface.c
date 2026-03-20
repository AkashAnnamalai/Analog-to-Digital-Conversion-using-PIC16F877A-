
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

#define _XTAL_FREQ 16000000 
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <stdio.h>
#include <xc.h>

#define RS RB0
#define E RB2
#define LCD_PORT PORTD

void lcd_cmd(unsigned char cmd)
{
    RS = 0;
    LCD_PORT = cmd;
    E = 1;
    __delay_ms(1);
    E = 0;
}

void lcd_data(unsigned char data){
    RS = 1;
    LCD_PORT = data;
    E =1;
    __delay_ms(1);
    E = 0;
}

void lcd_string(const char *c){
    while(*c){
        lcd_data(*c++);
    }
}

void lcd_init(){
    
    __delay_ms(10);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}

void lcd_clear(){
    lcd_cmd(0x01);
    __delay_ms(2);
}

void adc_init()
{
    ADCON0 = 0x01; 
    ADCON1 = 0x80;   
}

unsigned int adc_read(unsigned int channel)
{
    if(channel > 7) 
        return 0;

    ADCON0 &= 0xC7;             
    ADCON0 |= (channel << 3);    

    __delay_ms(2);               

    GO_nDONE = 1;                
    while(GO_nDONE);             

    return ((unsigned int)(ADRESH << 8) | ADRESL);
}

void main(void) {
    TRISB =0;
    TRISD =0;
    TRISA =1;
    
    PORTB=0;
    PORTD=0;
    
    lcd_init();
    adc_init();
    
    unsigned int adc_val;
    
    float temp;
    char buffer[16];
    
    while(1)
    {
        adc_val = adc_read(0);
        
       temp = (adc_val * 5.0 * 100) / 1023;
       lcd_cmd(0X80);
       lcd_string("Temperature: ");
       
       sprintf(buffer, "%.2f C", temp);
       lcd_cmd(0XC0);
       lcd_string(buffer);
       
       __delay_ms(500);
       
    }
    
    
         
}
