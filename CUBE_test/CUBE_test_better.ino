#include <Adafruit_NeoPixel.h>
#include <dht11.h>

#define NUM_LEDS 256
#define LED_PIN 11
#define DHT11PIN 4

dht11 DHT11;

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
const uint8_t letter_C[5] = {
  0x1E, // 1111
  0x10, // 1000
  0x10, // 1000
  0x10, // 1000
  0x1E  // 1111
};
const uint8_t percentSymbol[6] = {
  0b1100,
  0b1101,
  0b0010,
  0b0100,
  0b1011,
  0b0011
};



void setup() {
    pixels.begin();
    Serial.begin(9600);
}

void displayNumber_t1(int num, uint32_t color) {
    
    int startX = 0;
    int startY = 0;
    
    for (int row = 0; row < 7; row++) {
        for (int col = 0; col < 5; col++) {
            if (numbers[num][row] & (0x10 >> col)) {
                int pixelIndex;
                int y = startY + row;
                int x = startX + col;
                
                // 修正扫描方向：奇数行从右到左，偶数行从左到右
                if (y % 2 == 0) {
                    pixelIndex = y * 16 + (15 - x);
                } else {
                    pixelIndex = y * 16 + x;
                }
                
                pixels.setPixelColor(pixelIndex, color);
            }
        }
    }
    pixels.show();
}
void displayNumber_t2(int num, uint32_t color) {
    // pixels.clear();
    
    int startX = 6;
    int startY = 0;
    
    for (int row = 0; row < 7; row++) {
        for (int col = 0; col < 5; col++) {
            if (numbers[num][row] & (0x10 >> col)) {
                int pixelIndex;
                int y = startY + row;
                int x = startX + col;
                
                // 修正扫描方向：奇数行从右到左，偶数行从左到右
                if (y % 2 == 0) {
                    pixelIndex = y * 16 + (15 - x);
                } else {
                    pixelIndex = y * 16 + x;
                }
                
                pixels.setPixelColor(pixelIndex, color);
            }
        }
    }
    pixels.show();
}
void displayLetterC(uint32_t color) {
  int startX = 12; // top-right (X:11-15)
  int startY = 0;  // top row

  for (int row = 0; row < 5; row++) {
    for (int col = 0; col < 5; col++) {
      if (letter_C[row] & (0x10 >> col)) {
        int x = startX + col;
        int y = startY + row;
        int pixelIndex;

        if (y % 2 == 0) {
          pixelIndex = y * 16 + (15 - x); // Even rows: right to left
        } else {
          pixelIndex = y * 16 + x;        // Odd rows: left to right
        }

        pixels.setPixelColor(pixelIndex, color);
      }
    }
  }
  pixels.show();
}

void displayNumber_h1(int num, uint32_t color) {
    // pixels.clear();
    
    int startX = 0;
    int startY = 9;
    
    for (int row = 0; row < 7; row++) {
        for (int col = 0; col < 5; col++) {
            if (numbers[num][row] & (0x10 >> col)) {
                int pixelIndex;
                int y = startY + row;
                int x = startX + col;
                
                // 修正扫描方向：奇数行从右到左，偶数行从左到右
                if (y % 2 == 0) {
                    pixelIndex = y * 16 + (15 - x);
                } else {
                    pixelIndex = y * 16 + x;
                }
                
                pixels.setPixelColor(pixelIndex, color);
            }
        }
    }
    pixels.show();
}
void displayNumber_h2(int num, uint32_t color) {
    // pixels.clear();
    
    int startX = 6;
    int startY = 9;
    
    for (int row = 0; row < 7; row++) {
        for (int col = 0; col < 5; col++) {
            if (numbers[num][row] & (0x10 >> col)) {
                int pixelIndex;
                int y = startY + row;
                int x = startX + col;
                
                // 修正扫描方向：奇数行从右到左，偶数行从左到右
                if (y % 2 == 0) {
                    pixelIndex = y * 16 + (15 - x);
                } else {
                    pixelIndex = y * 16 + x;
                }
                
                pixels.setPixelColor(pixelIndex, color);
            }
        }
    }
    pixels.show();
}
void displayPercentSymbol(uint32_t colorhumidity) {
  int startX = 12; // top-right (X:11-15)
  int startY = 9;  // top row

  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 5; col++) {
      if (percentSymbol[row] & (0x10 >> col)) {
        int x = startX + col;
        int y = startY + row;
        int pixelIndex;

        if (y % 2 == 0) {
          pixelIndex = y * 16 + (15 - x); // Even rows: right to left
        } else {
          pixelIndex = y * 16 + x;        // Odd rows: left to right
        }

        pixels.setPixelColor(pixelIndex, colorhumidity);
      }
    }
  }
  pixels.show();
}

void loop() {
  Serial.println();
  int chk = DHT11.read(DHT11PIN);
  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);
  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);

  int temp = 69;
  temp = DHT11.temperature;
  int k = temp % 10;
  int j = temp / 10;
  uint32_t color_temperature = pixels.Color(255,255,255);
  int rt = 255;
  int gt = 102;
  int bt = 153;
  if (temp <= -10) {
    rt = 127;
    gt = 0;
    bt = 255;
  }
  else if (-10 < temp && temp <= -4) {
    rt = 127 + (temp + 10) * (-127 / 6);
    gt = 0;
    bt = 255;
  }
  else if (-4 < temp && temp <= 8) {
    rt = 0;
    gt = (temp + 4) * (255 / 12);
    bt = 255;
  }
  else if (8 < temp && temp <= 20) {
    rt = 0;
    gt = 255;
    bt = 255 + (temp - 8) * (-255 / 12);
  }
  else if (20 < temp && temp <= 32) {
    rt = (temp - 20) * (255 / 12);
    gt = 255;
    bt = 0;
  }
  else if (32 < temp && temp <= 44) {
    rt = 255;
    gt = 255 + (temp - 32) * (-255 / 12);
    bt = 0;
  }
  else {
    rt = 255;
    gt = 0;
    bt = 0;
  }
  color_temperature = pixels.Color(rt,gt,bt);
  pixels.clear();
  displayNumber_t1(j,color_temperature);
  displayNumber_t2(k,color_temperature);
  displayLetterC(color_temperature);

  int hum = DHT11.humidity;
  uint32_t color_humidity = pixels.Color(255,102,153);
  int rh = 255;
  int gh = 102;
  int bh = 153;
  if (hum = 0) {
    rh = 255;
    gh = 255;
    bh = 0;
  }
  else if (hum = 100) {
    rh = 0;
    gh = 0;
    bh = 255;
  }
  else if (hum > 0 && hum <= 33) {
    rh = 255 - (hum / 33) * 255;
    gh = 255;
    bh = 0;
  }
  else if (hum > 33 && hum <= 66) {
    rh = 0;
    gh = 255;
    bh = 0 + (hum - 33) * 255 / 33;
  }
  else if (hum > 66 && hum < 100) {
    rh = 0;
    gh = 255 - (255 * (hum - 66) / 34);
    bh = 255;
  }
  int tens = hum / 10;
  int ones = hum % 10;
  displayNumber_h1(tens, colorhumidity);
  displayNumber_h2(ones, colorhumidity);
  displayPercentSymbol(colorhumidity);

  delay(5000);
}