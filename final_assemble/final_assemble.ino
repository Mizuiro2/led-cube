#include <Adafruit_NeoPixel.h>
#include <dht11.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define NUM_LEDS    256
#define LED_PIN1    11
#define LED_PIN2    12
#define DHT11PIN    4
#define sensorPin   A0

dht11 DHT11;


Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

Adafruit_NeoPixel panel1(NUM_LEDS, LED_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel panel2(NUM_LEDS, LED_PIN2, NEO_GRB + NEO_KHZ800);

const uint8_t numbers[][7] = {
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
const uint8_t letter_C[6] = {
    0x1E,   // 00011110
    0x10,   // 00010000
    0x10,   // 00010000
    0x10,   // 00010000
    0x10,   // 00010000
    0x1E    // 00011110
};
const uint8_t percentSymbol[6] = {
    0x18,   // 00011000
    0x1A,   // 00011010
    0x04,   // 00000100
    0x08,   // 00001000
    0x16,   // 00010110
    0x06    // 00000110
};
const uint8_t letters[][7] = {
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
const uint8_t gasSafe[16][16] = {
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
const uint8_t gasAlert[16][16] = {
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
const uint8_t grass[16][16] = {
    {01, 02, 03, 04, 01, 02, 01, 03, 03, 05, 01, 05, 06, 07, 05, 03},   // line 1
    {01, 04, 01, 02, 06, 08, 01, 07, 06, 03, 01, 09, 01, 04, 01, 10},   // line 2
    {03, 08, 06, 11, 01, 08, 02, 08, 01, 05, 03, 12, 08, 13, 03, 08},   // line 3
    {08, 21, 08, 08, 17, 08, 08, 08, 18, 08, 19, 08, 15, 08, 08, 15},   // line 4
    {14, 15, 14, 20, 08, 14, 15, 15, 08, 08, 08, 16, 15, 14, 08, 15},   // line 5
    {15, 08, 14, 14, 15, 14, 08, 08, 08, 15, 15, 08, 15. 15, 15, 20},   // line 6
    {20, 15, 15, 15, 16, 15, 15, 20, 20, 15, 20, 20, 15, 14, 15, 14},   // line 7
    {15, 15, 20, 20, 14, 14, 15, 15, 14, 08, 14, 14, 15, 15, 14, 14},   // line 8
    {14, 15, 15, 14, 15, 14, 15, 08, 15, 14, 14, 15, 15, 15, 08, 15},   // line 9
    {15, 14, 08, 15, 15, 08, 08, 15, 15, 15, 15, 15, 20, 20, 15, 14},   // line 10
    {15, 14, 15, 20, 20, 15, 20, 14, 08, 20, 20, 08, 14, 14, 21, 15},   // line 11
    {14, 15, 15, 14, 14, 20, 15, 14, 16, 14, 14, 15, 08, 14, 15, 08},   // line 12
    {15, 08, 14, 15, 14, 14, 20, 15, 15, 15, 15, 15, 15, 15, 20, 20},   // line 13
    {15, 14, 15, 15, 22, 15, 14, 14, 15, 08, 20, 08, 15, 20, 14, 14},   // line 14
    {14, 15, 08, 20, 15, 08, 15, 08, 20, 20, 15, 14, 15, 15, 14, 14},   // line 15
    {14, 15, 20, 14, 14, 15, 21, 15, 14, 14, 15, 15, 14, 14, 15, 08}    // line 16
};
const uint8_t glowstone[16][16] = {
    {1, 2, 3, 4, 4, 2, 1, 2, 2, 4, 3, 5, 6, 2, 3, 7},
    {6, 1, 2, 4, 8, 8, 3, 2, 4, 7, 2, 6, 6, 1, 2, 4},
    {3, 2, 4, 7, 3, 3, 4, 8, 8, 7, 8, 4, 1, 2, 4, 7},
    {7, 4, 7, 2, 1, 2, 3, 4, 8, 5, 1, 8, 4, 4, 7, 7},
    {4, 8, 2, 5, 6, 6, 2, 4, 1, 6, 6, 2, 8, 7, 6, 1},
    {4, 3, 1, 6, 6, 1, 1, 3, 2, 1, 2, 3, 7, 6, 5, 1},
    {8, 4, 4, 2, 1, 1, 2, 4, 3, 4, 8, 7, 3, 2, 1, 4},
    {1, 7, 8, 4, 3, 2, 4, 8, 4, 7, 1, 3, 7, 3, 4, 2},
    {6, 1, 3, 7, 4, 3, 8, 7, 3, 5, 6, 1, 4, 8, 1, 5},
    {6, 2, 2, 3, 5, 1, 2, 7, 2, 6, 6, 2, 4, 7, 7, 1},
    {2, 3, 4, 2, 1, 2, 3, 3, 4, 2, 1, 3, 4, 7, 7, 1},
    {4, 4, 7, 3, 4, 7, 1, 6, 7, 4, 2, 4, 8, 3, 7, 8},
    {8, 7, 1, 2, 4, 8, 6, 5, 1, 2, 4, 7, 6, 1, 3, 4},
    {7, 1, 5, 6, 6, 4, 7, 1, 2, 3, 8, 1, 5, 6, 2, 4},
    {7, 2, 6, 1, 2, 3, 4, 8, 4, 4, 7, 3, 2, 3, 4, 8},
    {7, 4, 1, 2, 3, 8, 6, 1, 3, 8, 8, 4, 4, 4, 8, 7}
};
const uint8_t flame1[16][16] = {
{1, 1, 1, 2, 3, 4},
};

int detectMode() {
    int mode = 0;
    if (1) {
        mode = 1;
    }
    else if (0) {
        mode = 2;
    }
    else if (0) {
        mode = 3;
    }
    else if (0) {
        mode = 4;
    }
    return mode;
}

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
                gassafeDisplay();
            }
            else {
                gasalertDisplay();
            }
        break;

        case 3:
            
        break;

        default:
        switchError();
    }

    panel1.show();
}

void setup() {
    panel1.begin();
    panel2.begin();
    Serial.begin(9600);

    if(!accel.begin())
    {
        // Serial.println("No ADXL345 sensor detected.");
        // while(1);
    }
}

void numberPut(int startX, int startY, int num, uint32_t color) {
    int tens = num / 10;
    int ones = num % 10;
    for (int row = 0; row < 7; row++) {
        for (int col = 0; col < 5; col++) {
            if (numbers[tens][row] & (0x10 >> col)) {
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
            if (numbers[ones][row] & (0x10 >> col)) {
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

void celsiusPut(uint32_t color) {
    int startX = 12;
    int startY = 0;
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 4; col++) {
            if (letter_C[row] & (0x10 >> col)) {
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
            if (percentSymbol[row] & (0x10 >> col)) {
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
            switch (gasSafe[row][col]) {
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
            switch (gasAlert[row][col]) {
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

void grass() {
    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 16; col++) {
            switch (grass[row][col]) {
            case 1: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(67, 102, 59)); break;
            case 2: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(57, 87, 49)); break;
            case 3: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(60, 91, 52)); break;
            case 4: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(56, 85, 49)); break;
            case 5: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(63, 96, 55)); break;
            case 6: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(71, 108, 62)); break;
            case 7: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(51, 78, 45)); break;
            case 8: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(73, 50, 34)); break;
            case 9: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(58, 89, 51)); break;
            case 10: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(56, 84, 48)); break;
            case 11: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(52, 80, 45)); break;
            case 12: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(69, 105, 60)); break;
            case 13: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(47, 72, 41)); break;
            case 14: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(123, 88, 61)); break;
            case 15: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(99, 69, 48)); break;
            case 16: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(88, 88, 89)); break;
            case 17: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(58, 87, 50)); break;
            case 18: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(51, 77, 44)); break;
            case 19: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(56, 86, 49)); break;
            case 20: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(151, 109, 76)); break;
            case 21: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(111, 110, 111)); break;
            case 22: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(95, 72, 56)); break;
            default: break;
            }
        }
    } 
}
void glowstone() {
    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 16; col++) {
            switch (glowstone[row][col]) {
                case 1: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(251, 218, 115)); break; 
                case 2: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(204, 134, 83)); break;
                case 3: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(133, 79, 41)); break;
                case 4: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(112, 69, 34)); break;
                case 5: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(255, 255, 255)); break;
                case 6: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(255, 240, 217)); break;
                case 7: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(136, 104, 57)); break;
                case 8: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(116, 78, 39)); break;
                default: break;
            }
        }
    }
}
void flame1() {
    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 16; col++) {
            switch (flame1[row][col]) {
                case 1: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(255, 255, 255)); break; 
                case 2: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(228, 129, 13)); break;
                case 3: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(197, 85, 0)); break;
                case 4: panel1.setPixelColor(xyToIndex(col, row), panel1.Color(243, 185, 41)); break;
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
            if (letters[4][row] & (0x10 >> col)) {
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
            if (letters[17][row] & (0x10 >> col)) {
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

int readMQ2() {
  unsigned int sensorValue = analogRead(sensorPin);  // Read the analog value from sensor
  unsigned int outputValue = map(sensorValue, 0, 1023, 0, 255); // map the 10-bit data to 8-bit data
  return outputValue;             // Return analog moisture value
}

void loop() {
    displaySwitchMode(detectMode());
    
    /* below is code for testing and monitoring*/
    //  Serial.println();
    int chk = DHT11.read(DHT11PIN);
    //  Serial.print("Humidity (%): ");
    //  Serial.println((float)DHT11.humidity, 2);
    //  Serial.print("Temperature  (C): ");
    //  Serial.println((float)DHT11.temperature, 2);
    //  Serial.print("Analog output: ");
    //  Serial.println(readMQ2());
    //  not needed for actual project

    delay(3000);
}