#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/delay.h>

int main()
{
    DDRA = 0x00;
    DDRB = 0xFF;

    int i = 0;
    bool dir = true;
    while (true)
    {
        if ((PINA >> 0) & 1U)
        {
            i = 0;
            PORTB = 0x00;
            dir = true;
        }
        else
        {
            if (dir)
            {
                if (i != 0)
                {
                    PORTB &= ~(1UL << (i - 1));
                }
                PORTB |= 1UL << i;
                if (i == 7)
                {
                    dir = false;
                }
                else
                {
                    i++;
                }
            }
            else
            {
                PORTB |= 1UL << (i - 1);
                PORTB &= ~(1UL << i);
                if (i == 1)
                {
                    dir = true;
                }
                else
                {
                    i--;
                }
            }
            _delay_ms(500);
        }
    }

    return 0;
}