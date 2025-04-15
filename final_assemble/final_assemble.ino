#include <Adafruit_NeoPixel.h>
#include <dht11.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define NUM_LEDS    256
#define LED_PIN     11
#define DHT11PIN    4

dht11 DHT11;


Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

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
    pixels.clear();

    int temp = DHT11.temperature;
    int hum = DHT11.humidity;

    switch(mode) {
        case 1:
        numberPut(0, 0, temp, tempColor(temp));
        celsiusPut(tempColor(temp));
        numberPut(0, 9, hum, humColor(hum));
        percentPut(humColor(hum));
        break;
        case 2:

        break;
        case 3:

        break;
    }

    pixels.show();
}

void setup() {
    pixels.begin();
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
                pixels.setPixelColor(pixelIndex, color);
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
                pixels.setPixelColor(pixelIndex, color);
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
                pixels.setPixelColor(pixelIndex, color);
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
                pixels.setPixelColor(pixelIndex, color);
            }
        }
    }
}

int tempColor(int temp) {
    uint32_t color = pixels.Color(255,255,255);
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
    color = pixels.Color(r, g, b);
    return color;
    // return pixels.Color(255, 0, 0); // Always red, just for test
}

int humColor(int hum) {
    uint32_t color = pixels.Color(255,255,255);
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
    color = pixels.Color(r, g, b);
    return color;
    // return pixels.Color(255, 0, 0); // Always red, just for test
}

void loop() {
    displaySwitchMode(detectMode());
    
    /* below is code for testing and monitoring*/
    Serial.println();
    int chk = DHT11.read(DHT11PIN);
    Serial.print("Humidity (%): ");
    Serial.println((float)DHT11.humidity, 2);
    Serial.print("Temperature  (C): ");
    Serial.println((float)DHT11.temperature, 2);

    

    delay(5000);
}