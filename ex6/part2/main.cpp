#define F_CPU 8000000UL

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#define LCD_Data_Dir DDRD
#define LCD_Command_Dir DDRC
#define LCD_Data_Port PORTD
#define LCD_Command_Port PORTC
#define RS PC5
#define RW PC6
#define EN PC7

// lcd interface source: http://www.electronicwings.com
void LCD_Command(unsigned char cmnd) {
    LCD_Data_Port = cmnd;
    LCD_Command_Port &= ~(1 << RS);
    LCD_Command_Port &= ~(1 << RW);
    LCD_Command_Port |= (1 << EN);
    _delay_us(1);
    LCD_Command_Port &= ~(1 << EN);
    _delay_ms(3);
}

void LCD_Init(void) {
    LCD_Command_Dir = 0xFF;
    LCD_Data_Dir = 0xFF;
    _delay_ms(20);

    LCD_Command(0x38);
    LCD_Command(0x0C);
    LCD_Command(0x06);
    LCD_Command(0x01);
    LCD_Command(0x80);
}

void LCD_Char(unsigned char char_data) {
    LCD_Data_Port = char_data;
    LCD_Command_Port |= (1 << RS);
    LCD_Command_Port &= ~(1 << RW);
    LCD_Command_Port |= (1 << EN);
    _delay_us(1);
    LCD_Command_Port &= ~(1 << EN);
    _delay_ms(1);
}

void LCD_String(char *str) {
    int i;
    for (i = 0; str[i] != 0; i++) {
        LCD_Char(str[i]);
    }
}

void LCD_Clear() {
    LCD_Command(0x01);
    LCD_Command(0x80);
}

uint16_t adc_read(uint8_t ch) {
    // select the corresponding channel 0~7
    ch &= 0b00000111;  // AND operation with 7
    ADMUX = (ADMUX & 0xF8) | ch;
    // start single conversion
    // write '1' to ADSC
    ADCSRA |= (1 << ADSC);
    // wait for conversion to complete
    // ADSC becomes '0' again
    while (ADCSRA & (1 << ADSC));
    return (ADC);
}

int main() {
    // init adc
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    
    uint16_t adc_result0;
    int temp;
    int shift, i;
    
    LCD_Init();

    while (1) {
        adc_result0 = adc_read(0);
        temp = adc_result0 / 2.01; // temp in C

        DDRB=0xff;

        char buffer[12];
        sprintf(buffer, "temp: %d", temp);
        LCD_Clear();
        LCD_String(buffer);

        if(temp>30){
            PORTB |= 1UL << 0;
        }else{
            PORTB &= ~(1UL << 0);
        }

        _delay_ms(300);
    }

    return 0;
}