#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/delay.h>

int main()
{
    DDRA = 0xFF;

    while (true)
    {
        PORTA ^= 1UL << 0;
        _delay_ms(500);
    }
    
    return 0;
}