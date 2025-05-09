#include <Adafruit_NeoPixel.h>
#include <dht11.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

#define NUM_LEDS    256
#define LED_PIN1    13

#define DHT11PIN    4
#define sensorPin   10

int buzzerPin = 8;

#define touchPin  2     // Pin connected to OUT of touch sensor
int currentMode = 1;
const int numModes = 7;

bool lastTouchState = LOW;

int mode = 0;

int period = 200;
int refreshPeriod = 1000;
unsigned long time_now = 0;
int mainrefreshPeriod = 1000;
int MQrefreshPeriod = 2000;

int num = 0;
int numR = 99;

dht11 DHT11;


Adafruit_NeoPixel panel1(NUM_LEDS, LED_PIN1, NEO_GRB + NEO_KHZ800);


const uint8_t numbers [10][7] PROGMEM = {
    {0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F}, // 0
    {0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E}, // 1
    {0x1F, 0x01, 0x01, 0x1F, 0x10, 0x10, 0x1F}, // 2
    {0x1F, 0x01, 0x01, 0x1F, 0x01, 0x01, 0x1F}, // 3
    {0x11, 0x11, 0x11, 0x1F, 0x01, 0x01, 0x01}, // 4
    {0x1F, 0x10, 0x10, 0x1F, 0x01, 0x01, 0x1F}, // 5
    {0x1F, 0x10, 0x10, 0x1F, 0x11, 0x11, 0x1F}, // 6
    {0x1F, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08}, // 7
    {0x1F, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x1F}, // 8
    {0x1F, 0x11, 0x11, 0x1F, 0x01, 0x01, 0x1F}  // 9
};
const uint8_t  letter_C[6] PROGMEM = {
    0x1E,   // 00011110
    0x10,   // 00010000
    0x10,   // 00010000
    0x10,   // 00010000
    0x10,   // 00010000
    0x1E    // 00011110
};
const uint8_t percentSymbol[6] PROGMEM = {
    0x18,   // 00011000
    0x1A,   // 00011010
    0x04,   // 00000100
    0x08,   // 00001000
    0x16,   // 00010110
    0x06    // 00000110
};
const uint8_t letters[26][7] PROGMEM = {
    {0x0E, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11}, // A
    {0x1E, 0x11, 0x11, 0x1E, 0x11, 0x11, 0x1E}, // B
    {0x0E, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0E}, // C
    {0x1E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1E}, // D
    {0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x1F}, // E
    {0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x10}, // F
    {0x0E, 0x11, 0x10, 0x17, 0x11, 0x11, 0x0E}, // G
    {0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11}, // H
    {0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E}, // I
    {0x0F, 0x01, 0x01, 0x01, 0x01, 0x11, 0x0E}, // J
    {0x11, 0x11, 0x12, 0x1C, 0x12, 0x11, 0x11}, // K
    {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F}, // L
    {0x11, 0x1B, 0x15, 0x11, 0x11, 0x11, 0x11}, // M
    {0x11, 0x11, 0x19, 0x15, 0x13, 0x11, 0x11}, // N
    {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, // O
    {0x1E, 0x11, 0x11, 0x1E, 0x10, 0x10, 0x10}, // P
    {0x0E, 0x11, 0x11, 0x11, 0x15, 0x13, 0x0F}, // Q
    {0x1E, 0x11, 0x11, 0x1E, 0x11, 0x11, 0x11}, // R
    {0x0E, 0x11, 0x10, 0x0E, 0x01, 0x11, 0x0E}, // S
    {0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}, // T
    {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, // U
    {0x11, 0x11, 0x11, 0x11, 0x11, 0x0A, 0x04}, // V
    {0x11, 0x11, 0x11, 0x11, 0x15, 0x1B, 0x11}, // W
    {0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11}, // X
    {0x11, 0x11, 0x0A, 0x04, 0x04, 0x04, 0x04}, // Y
    {0x1F, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1F}  // Z
};
const uint8_t gasSafe[16][16] PROGMEM = {
    {0, 1, 1, 0, 0, 2, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0},   // line 1
    {1, 0, 0, 0, 2, 0, 0, 2, 1, 0, 0, 0, 0, 2, 0, 0},   // line 2
    {1, 0, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0},   // line 3
    {1, 0, 0, 1, 2, 0, 0, 2, 0, 0, 0, 1, 0, 2, 0, 0},   // line 4
    {0, 1, 1, 0, 2, 0, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0},   // line 5
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // line 6
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // line 7
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // line 8
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // line 9
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // line 10
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // line 11
    {0, 3, 3, 0, 0, 4, 4, 0, 0, 3, 3, 0, 4, 4, 4, 4},   // line 12
    {3, 0, 0, 0, 4, 0, 0, 4, 3, 0, 0, 0, 4, 0, 0, 0},   // line 13
    {3, 3, 3, 3, 4, 4, 4, 4, 3, 3, 3, 3, 4, 4, 4, 0},   // line 14
    {0, 0, 0, 3, 4, 0, 0, 4, 3, 0, 0, 0, 4, 0, 0, 0},   // line 15
    {0, 3, 3, 0, 4, 0, 0, 4, 3, 0, 0, 0, 4, 4, 4, 4},   // line 16
};
const uint8_t gasAlert[16][16] PROGMEM = {
    {0, 1, 1, 0, 0, 2, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0},   // line 1
    {1, 0, 0, 0, 2, 0, 0, 2, 1, 0, 0, 0, 0, 2, 0, 0},   // line 2
    {1, 0, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0},   // line 3
    {1, 0, 0, 1, 2, 0, 0, 2, 0, 0, 0, 1, 0, 2, 0, 0},   // line 4
    {0, 1, 1, 0, 2, 0, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0},   // line 5
    {5, 0, 0, 5, 0, 0, 5, 5, 5, 5, 0, 0, 5, 5, 5, 5},   // line 6
    {5, 5, 0, 5, 0, 5, 5, 0, 0, 5, 5, 0, 5, 5, 5, 5},   // line 7
    {5, 5, 5, 5, 0, 5, 5, 0, 0, 5, 5, 0, 0, 5, 5, 0},   // line 8
    {5, 0, 5, 5, 0, 5, 5, 0, 0, 5, 5, 0, 0, 5, 5, 0},   // line 9
    {5, 0, 0, 5, 0, 0, 5, 5, 5, 5, 0, 0, 0, 5, 5, 0},   // line 10
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // line 11
    {0, 3, 3, 0, 0, 4, 4, 0, 0, 3, 3, 0, 4, 4, 4, 4},   // line 12
    {3, 0, 0, 0, 4, 0, 0, 4, 3, 0, 0, 0, 4, 0, 0, 0},   // line 13
    {3, 3, 3, 3, 4, 4, 4, 4, 3, 3, 3, 3, 4, 4, 4, 0},   // line 14
    {0, 0, 0, 3, 4, 0, 0, 4, 3, 0, 0, 0, 4, 0, 0, 0},   // line 15
    {0, 3, 3, 0, 4, 0, 0, 4, 3, 0, 0, 0, 4, 4, 4, 4},   // line 16
};

const uint8_t glowstone[16][16] PROGMEM = {
    {1, 2, 3, 4, 4, 2, 1, 2, 2, 4, 3, 5, 6, 2, 3, 7},
    {6, 1, 2, 4, 10, 10, 3, 2, 4, 7, 2, 6, 6, 1, 2, 4},
    {3, 2, 4, 7, 3, 3, 4, 10, 10, 7, 10, 4, 1, 2, 4, 7},
    {7, 4, 7, 2, 1, 2, 3, 4, 10, 5, 1, 10, 4, 4, 7, 7},
    {4, 10, 2, 5, 6, 6, 2, 4, 1, 6, 6, 2, 10, 7, 6, 1},
    {4, 3, 1, 6, 6, 1, 1, 3, 2, 1, 2, 3, 7, 6, 5, 1},
    {10, 4, 4, 2, 1, 1, 2, 4, 3, 4, 10, 7, 3, 2, 1, 4},
    {1, 7, 10, 4, 3, 2, 4, 10, 4, 7, 1, 3, 7, 3, 4, 2},
    {6, 1, 3, 7, 4, 3, 10, 7, 3, 5, 6, 1, 4, 10, 1, 5},
    {6, 2, 2, 3, 5, 1, 2, 7, 2, 6, 6, 2, 4, 7, 7, 1},
    {2, 3, 4, 2, 1, 2, 3, 3, 4, 2, 1, 3, 4, 7, 7, 1},
    {4, 4, 7, 3, 4, 7, 1, 6, 7, 4, 2, 4, 10, 3, 7, 10},
    {10, 7, 1, 2, 4, 10, 6, 5, 1, 2, 4, 7, 6, 1, 3, 4},
    {7, 1, 5, 6, 6, 4, 7, 1, 2, 3, 10, 1, 5, 6, 2, 4},
    {7, 2, 6, 1, 2, 3, 4, 10, 4, 4, 7, 3, 2, 3, 4, 10},
    {7, 4, 1, 2, 3, 10, 6, 1, 3, 10, 10, 4, 4, 4, 10, 7}
};

const uint8_t grass[16][16] PROGMEM = {
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 2, 2, 2, 2, 2 },
    { 2, 2, 5, 2, 2, 5, 2, 2, 2, 5, 5, 2, 2, 2, 2, 2 },
    { 2, 2, 5, 2, 2, 5, 5, 2, 5, 5, 3, 5, 5, 5, 5, 2 },
    { 2, 5, 1, 5, 5, 3, 3, 5, 3, 3, 3, 1, 5, 3, 1, 5 },
    { 2, 3, 3, 1, 5, 1, 3, 3, 1, 5, 1, 1, 3, 1, 1, 5 },
    { 3, 3, 5, 3, 1, 1, 3, 3, 3, 3, 5, 5, 1, 1, 5, 1 },
    { 1, 5, 3, 3, 3, 1, 5, 3, 5, 4, 3, 3, 1, 3, 3, 3 },
    { 1, 3, 1, 3, 3, 3, 1, 3, 1, 1, 1, 3, 5, 1, 3, 5 },
    { 5, 3, 3, 5, 3, 3, 3, 5, 3, 3, 3, 3, 5, 5, 1, 1 },
    { 3, 3, 4, 1, 5, 5, 3, 1, 5, 3, 3, 3, 3, 5, 3, 5 },
    { 1, 3, 3, 1, 3, 3, 3, 1, 3, 1, 1, 1, 1, 1, 5, 3 },
    { 1, 3, 3, 1, 3, 1, 1, 1, 3, 3, 1, 1, 5, 1, 1, 1 },
    { 3, 3, 3, 1, 3, 3, 3, 5, 1, 3, 5, 5, 5, 3, 3, 3 },
    { 1, 5, 3, 3, 3, 1, 5, 3, 1, 3, 1, 5, 3, 3, 5, 3 },
    { 3, 5, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, 5, 1, 3, 3 }
};


// int detectMode() {
//     int mode = 2;
//     if (0) {
//         mode = 1;
//     }
//     else if (0) {
//         mode = 2;
//     }
//     else if (0) {
//         mode = 3;
//     }
//     else if (0) {
//         mode = 4;
//     }
//     return mode;
// }

void displaySwitchMode(int mode) {
    panel1.clear();

    int temp = DHT11.temperature;
    int hum = DHT11.humidity;
    int gas = readMQ2();
    switch(mode) {
        case 1:
            numberPut(0, 0, temp, tempColor(temp));
            celsiusPut(tempColor(temp));
            numberPut(0, 9, hum, humColor(hum));
            percentPut(humColor(hum));

        break;

        case 2:
                if (gas < 65) {
                    noTone(8);
                    gassafeDisplay();
                }
                else {
                    pinMode(8,OUTPUT);
                    tone(8,1000);
                    gasalertDisplay();
                }
        break;

        case 3:
            noTone(8);
            displayGlowstone();
        break;
            
        case 4:
            numberLoop();
        break;

        case 5:
            numberLoopR();
            num = 0;
        break;

        case 6:
            numR = 99;
            displayGrass();
        break;

        default:
            switchError();
    }

    panel1.show();
}

void setup() {
    pinMode(touchPin, INPUT);

    panel1.begin();
    panel1.setBrightness(80);
    panel1.show(); // Initialize with all LEDs off
    Serial.begin(9600);

}

void numberPut(int startX, int startY, int num, uint32_t color) {
    int tens = num / 10;
    int ones = num % 10;
    if (num > 9) {
        for (int row = 0; row < 7; row++) {
            for (int col = 0; col < 5; col++) {
                if (pgm_read_byte(&(numbers[tens][row])) & (0x10 >> col)) {
                    int pixelIndex;
                    int y = startY + row;
                    int x = startX + col;
                    if (y % 2 == 0) {
                        pixelIndex = y * 16 + (15 - x);
                    }
                    else {
                        pixelIndex = y * 16 + x;
                    }
                    panel1.setPixelColor(pixelIndex, color);
                }
            }
        }
        for (int row = 0; row < 7; row++) {
            for (int col = 0; col < 5; col++) {
                if (pgm_read_byte(&(numbers[ones][row])) & (0x10 >> col)) {
                    int pixelIndex;
                    int y = startY + row;
                    int x = startX + 6 + col;
                    if (y % 2 == 0) {
                        pixelIndex = y * 16 + (15 - x);
                    }
                    else {
                        pixelIndex = y * 16 + x;
                    }
                    panel1.setPixelColor(pixelIndex, color);
                }
            }
        }
    }
    else {
        for (int row = 0; row < 7; row++) {
            for (int col = 0; col < 5; col++) {
                if (pgm_read_byte(&(numbers[ones][row])) & (0x10 >> col)) {
                    int pixelIndex;
                    int y = startY + row;
                    int x = startX + 3 + col;
                    if (y % 2 == 0) {
                        pixelIndex = y * 16 + (15 - x);
                    }
                    else {
                        pixelIndex = y * 16 + x;
                    }
                    panel1.setPixelColor(pixelIndex, color);
                }
            }
        }
    }
}

void numberPut2(int startX, int startY, int num, uint32_t color) {
    int tens = num / 10;
    int ones = num % 10;
    if (num > 9) {
        for (int row = 0; row < 7; row++) {
            for (int col = 0; col < 5; col++) {
                if (pgm_read_byte(&(numbers[tens][row])) & (0x10 >> col)) {
                    int pixelIndex;
                    int y = startY + row;
                    int x = startX + col;
                    if (y % 2 == 0) {
                        pixelIndex = y * 16 + (15 - x);
                    }
                    else {
                        pixelIndex = y * 16 + x;
                    }
                    panel1.setPixelColor(pixelIndex, color);
                }
            }
        }
        for (int row = 0; row < 7; row++) {
            for (int col = 0; col < 5; col++) {
                if (pgm_read_byte(&(numbers[ones][row])) & (0x10 >> col)) {
                    int pixelIndex;
                    int y = startY + row;
                    int x = startX + 7 + col;
                    if (y % 2 == 0) {
                        pixelIndex = y * 16 + (15 - x);
                    }
                    else {
                        pixelIndex = y * 16 + x;
                    }
                    panel1.setPixelColor(pixelIndex, color);
                }
            }
        }
    }
    else {
        for (int row = 0; row < 7; row++) {
            for (int col = 0; col < 5; col++) {
                if (pgm_read_byte(&(numbers[ones][row])) & (0x10 >> col)) {
                    int pixelIndex;
                    int y = startY + row;
                    int x = startX + 3 + col;
                    if (y % 2 == 0) {
                        pixelIndex = y * 16 + (15 - x);
                    }
                    else {
                        pixelIndex = y * 16 + x;
                    }
                    panel1.setPixelColor(pixelIndex, color);
                }
            }
        }
    }
}


void celsiusPut(uint32_t color) {
    int startX = 12;
    int startY = 0;
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 4; col++) {
            if (pgm_read_byte(&(letter_C[row])) & (0x10 >> col)) {
                int x = startX + col;
                int y = startY + row;
                int pixelIndex;
                if(y % 2 == 0) {
                    pixelIndex = y * 16 + (15 - x);
                }
                else {
                    pixelIndex = y * 16 + x;
                }
                panel1.setPixelColor(pixelIndex, color);
            }
        }
    }
}


void percentPut(uint32_t color) {
    int startX = 12;
    int startY = 9;
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 4; col++) {
            if (pgm_read_byte(&(percentSymbol[row])) & (0x10 >> col)) {
                int x = startX + col;
                int y = startY + row;
                int pixelIndex;
                if(y % 2 == 0) {
                    pixelIndex = y * 16 + (15 - x);
                }
                else {
                    pixelIndex = y * 16 + x;
                }
                panel1.setPixelColor(pixelIndex, color);
            }
        }
    }
}


int tempColor(int temp) {
    uint32_t color = panel1.Color(255,255,255);
    int r = 255;
    int g = 102;
    int b = 153;
    if (temp <= -10) {
        r = 127;
        g = 0;
        b = 255;
    }
    else if (-10 < temp && temp <= -4) {
        r = 127 + (temp + 10) * (-127 / 6);
        g = 0;
        b = 255;
    }
    else if (-4 < temp && temp <= 8) {
        r = 0;
        g = (temp + 4) * (255 / 12);
        b = 255;
    }
    else if (8 < temp && temp <= 20) {
        r = 0;
        g = 255;
        b = 255 + (temp - 8) * (-255 / 12);
    }
    else if (20 < temp && temp <= 32) {
        r = (temp - 20) * (255 / 12);
        g = 255;
        b = 0;
    }
    else if (32 < temp && temp <= 44) {
        r = 255;
        g = 255 + (temp - 32) * (-255 / 12);
        b = 0;
    }
    else {
        r = 255;
        g = 0;
        b = 0;
    }
    color = panel1.Color(r, g, b);
    return color;
    // return panel1.Color(255, 0, 0); // Always red, just for test
}


int humColor(int hum) {
    uint32_t color = panel1.Color(255,255,255);
    int r = 255;
    int g = 102;
    int b = 253;
    if (hum == 0) {
        r = 255;
        g = 255;
        b = 0;
    }
    else if (hum > 0 && hum <= 33) {
        r = 255 - (hum / 33) * 255;
        g = 255;
        b  = 0;
    }
    else if (hum > 33 && hum <= 66) {
        r = 0;
        g = 255;
        b = 0 + (hum - 33) * 255 / 33;
    }
    else {
        r = 0;
        g = 255 - (255 * (hum - 66) / 34);
        b = 255;
    }
    color = panel1.Color(r, g, b);
    return color;
    // return panel1.Color(255, 0, 0); // Always red, just for test
}


void gassafeDisplay() {
    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 16; col++) {
            switch (pgm_read_byte(&(gasSafe[row][col]))) {
            case 1: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(0, 128, 255)); break;
            case 2: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(0, 255, 255)); break;
            case 3: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(0, 204, 0)); break;
            case 4: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(51, 255, 51)); break;
            default: break;
            }
        }
    }
}


void gasalertDisplay() {
    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 16; col++) {
            switch (pgm_read_byte(&(gasAlert[row][col]))) {
            case 1: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(0, 128, 255)); break;
            case 2: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(0, 255, 255)); break;
            case 3: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(0, 204, 0)); break;
            case 4: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(51, 255, 51)); break;
            case 5: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(255, 0, 0)); break;
            default: break;
            }
        }
    } 
}


void displayGlowstone() {
    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 16; col++) {
            switch (pgm_read_byte(&(glowstone[row][col]))) {
                case 1: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(251, 218, 115));
                break; 
                case 2: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(204, 134, 83));
                break;
                case 3: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(133, 79, 41));
                break;
                case 4: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(112, 69, 34));
                break;
                case 5: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(255, 255, 255));
                break;
                case 6: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(255, 240, 217));
                break;
                case 7: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(136, 104, 57));
                break;
                case 10: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(116, 78, 39));
                break;
                default: break;
            }
        }
    }
}

void displayGrass() {
    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 16; col++) {
            switch (pgm_read_byte(&(grass[row][col]))) {
                case 1: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(207, 154, 110));
                break; 
                case 2: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(204, 134, 83));
                break;
                case 3: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(114, 162, 73));
                break;
                case 4: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(155, 113, 84));
                break;
                case 5: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(108, 78, 58));
                break;
                default: break;
            }
        }
    }
}

int xyToIndex(int x, int y) {
  if (y % 2 == 1) {
    return y * 16 + x;       // even row: left to right
  } else {
    return y * 16 + (15 - x); // odd row: right to left
  }
}

void switchError() {
    for (int row = 0; row < 7; row++) {
        for (int col = 0; col < 5; col++) {
            if (pgm_read_byte(&(letters[4][row])) & (0x10 >> col)) {
                int pixelIndex;
                int y = row;
                int x = col;
                if (y % 2 == 0) {
                    pixelIndex = y * 16 + (15 - x);
                }
                else {
                    pixelIndex = y * 16 + x;
                }
                panel1.setPixelColor(pixelIndex, panel1.Color(255, 0, 0));
            }
        }
    }
    for (int row = 0; row < 7; row++) {
        for (int col = 0; col < 5; col++) {
            if (pgm_read_byte(&(letters[17][row])) & (0x10 >> col)) {
                int pixelIndex;
                int y = row;
                int x = col + 6;
                if (y % 2 == 0) {
                    pixelIndex = y * 16 + (15 - x);
                }
                else {
                    pixelIndex = y * 16 + x;
                }
                panel1.setPixelColor(pixelIndex, panel1.Color(255, 0, 0));
            }
        }
    }
}

void allOn() {
    panel1.fill((0, 127, 0), 20);
    delay(1000);
}

void numberLoop() {
    if (millis() - time_now >= refreshPeriod) {
        time_now = millis();  // update time
        numberPut2(2, 4, num, panel1.Color(255, 0, 0));
        num++;
    if (num >= 100) num = 0;
  }
}
void numberLoopR() {
    if (millis() - time_now >= refreshPeriod) {
        time_now = millis();  // update time
        numberPut2(2, 4, numR, panel1.Color(255, 0, 0));
        numR--;
    if (numR <= 0) numR = 99;
  }
}

// int blinking() {
//     uint32_t color
//     retrun color;   
// }

int readMQ2() {
    if (millis() - time_now >= MQrefreshPeriod) {
        time_now = millis();
        unsigned int sensorValue = analogRead(sensorPin);  // Read the analog value from sensor
        unsigned int outputValue = map(sensorValue, 0, 1023, 0, 255); // map the 10-bit data to 8-bit data
        return outputValue;             // Return analog moisture value
    }
}

void loop() {
    bool touchState = digitalRead(touchPin);

    // Detect rising edge (touch event)
    if (touchState == HIGH && lastTouchState == LOW && millis() >= time_now + period) {
        currentMode++;
        if (currentMode > numModes) currentMode = 1;

        // Serial.print("Mode changed to: ");
        // Serial.println(currentMode);

        mode = currentMode;

        time_now += period;

        delay(200); // Simple debounce
    }
    lastTouchState = touchState;
    if (millis() - time_now >= mainrefreshPeriod) {
        displaySwitchMode(mode);
        panel1.show();
    }
    
    
    /* below is code for testing and monitoring*/
    // Serial.println();
    int chk = DHT11.read(DHT11PIN);
    // Serial.print("Humidity (%): ");
    // Serial.println((float)DHT11.humidity, 2);
    // Serial.print("Temperature  (C): ");
    // Serial.println((float)DHT11.temperature, 2);
    // Serial.print("Analog output: ");
    // Serial.println(readMQ2());
    //  not needed for actual project

    // delay(1000);
}
