#define F_CPU 8000000UL

#define __DELAY_BACKWARD_COMPATIBLE__

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "keypad.c"

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

int main() {
    char keypad_input[16] = "";
    unsigned char i;

    LCD_Init();
    keypad_init();

    PORTC &= ~(1UL << 0);
    PORTC &= ~(1UL << 1);

    while (1) {
        i = key_scan();
        if (i != 255) {
            if ( i == 10 ) {
                strncpy(keypad_input,keypad_input,strlen(keypad_input)-1);
            } else {
                char str[2];
                sprintf(str,"%d",i);
                strcat(keypad_input,str);
            }
            LCD_Clear();
            LCD_String(keypad_input);
        }
    }

    return 0;
}