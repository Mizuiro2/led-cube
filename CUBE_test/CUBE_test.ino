#include <Adafruit_NeoPixel.h>
#include <dht11.h>

#define NUM_LEDS 256

#define LED_PIN 11

#define DHT11PIN 4

dht11 DHT11;

Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// 定义0-9的5x7点阵数据
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

void setup() {
    pixels.begin();
    Serial.begin(9600);
}
// ... 其他代码保持不变 ...

// first digit of temperature reading from dht11
void displayNumber_t1(int num, uint32_t color) {
    // pixels.clear();
    
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
// Second digit of temperature reading
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

void temp_color() {

}

// ... 其他代码保持不变 ...
void loop() {
  // dht11 loop part
  Serial.println();

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);


    // 循环显示0-9
    // for (int i = 0; i < 10; i++) {
    //     uint32_t color = pixels.Color(255, 102, 153);
    //     displayNumber_t1(i, color);
    //     delay(2000);  // 每个数字显示2秒
    // }
    int temp = 88;

    temp = DHT11.temperature;
    int k = temp % 10;
    int j = (temp - k) / 10;
    
    // color initialize as all white
    uint32_t color = pixels.Color(255,255,255);

    // rgb value initialize as bili pink
    int r = 255;
    int g = 102;
    int b = 153;

    // color change according to temp
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
    color = pixels.Color(r,g,b);

    // pixels.clear();

    displayNumber_t1(j, color);
    displayNumber_t2(k, color);

    // pixels.show();

    // delay(5000);

}