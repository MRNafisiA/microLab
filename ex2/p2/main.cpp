#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/delay.h>

int main()
{
    DDRA = 0x00;
    DDRB = 0xFF;

    while (true)
    {
        PORTB = 0x00;
        _delay_ms(500);
        PORTB = 0xFF;
        _delay_ms(500);
    }
    
    return 0;
}