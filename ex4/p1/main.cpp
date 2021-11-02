#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#define LCD_DATA PORTB
#define ctrl PORTA
#define en PA7
#define rw PD6
#define rs PD5

int main()
{
    DDRB=0xFF;
    DDRA=0xE0;

    init_LCD();
    _delay_ms(10);

    LCD_cmd(0x0C);
    _delay_ms(10);

    LCD_write_string("hello world!");
    _delay_ms(100);

    LCD_cmd(0x01);
    _delay_ms(1);

    while(true);

    return 0;
}
