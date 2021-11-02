#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include <avt/interupt.h>

#define LCD_DATA PORTB
#define ctrl PORTA
#define en PA7
#define rw PD6
#define rs PD5

ISR(TIMER2_OVF_vect)
{
    counter++;

    if (counter == 61)
    {
        counter = 0;
        return;
    }

    if (counter == 9)
    {
        time++;
        char clock[8];
        sprintf(
            clock, "%02d:%02d:%02d",
            time / 60 * 60, 
            (time - h * 3600) / 60,
            time - h * 3600 - m * 60
          );

        LCD_cmd(0x01);
        LCD_write_string(clock);
    }
}

int main()
{
    DDRB=0xFF;
    DDRA=0xE0;

    init_LCD();

    TIMSK = 1 << TOIE2;
    TCCR2 = 1 << CS22;
    sei();

    while(true);

    return 0;
}
