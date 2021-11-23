#define KEY_PORT    PORTB
#define KEY_DDR     DDRB
#define KEY_PIN     PINB

unsigned char table[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 11};
unsigned int DELAY = 3;

void keypad_init(void) {
    KEY_DDR = 0x0F;
    KEY_PORT = 0xFF;
}

unsigned char key_released(void) {
    KEY_PORT = 0x70;
    _delay_ms(DELAY);
    if ((KEY_PIN & 0x70) == 0x70)
        return 1;
    else
        return 0;
}

unsigned char key_pressed(void) {
    KEY_PORT = 0x70;
    _delay_ms(DELAY);
    if ((KEY_PIN & 0x70) != 0x70) {
        _delay_ms(20);
        if ((KEY_PIN & 0x70) != 0x70)
            return 1;
    }
    return 0;
}

unsigned char key_scan(void) {
    unsigned char i, key;
    if (key_pressed()) {
        key = 0;
        for (i = 0; i < 4; i++) {
            KEY_PORT = ~(1 << i);
            _delay_ms(DELAY);
            if (((KEY_PIN >> 4) & 1U)==0) {
                key = table[i * 3];
            }
            if (((KEY_PIN >> 5) & 1U)==0) {
                key = table[i * 3 + 1];
            }
            if (((KEY_PIN >> 6) & 1U)==0) {
                key = table[i * 3 + 2];
            }
        }
        while (!key_released());
        return key;
    } else
        return 255;
}