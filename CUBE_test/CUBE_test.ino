#include <Adafruit_NeoPixel.h>
#define NUM_LEDS 256
 
Adafruit_NeoPixel pixels(NUM_LEDS, 11, NEO_GRB + NEO_KHZ800);
 
#define LED_PIN 11
 
#define STR_NUM 2
 
 
const unsigned char table[][16] = {
  // 桃(0) 叶(1) 芳(2) 游(3) 梦(4) 未(5) 忘(6) ，(7) 廿(8) 年(9) 回(10) 首(11) 叹(12) 流(13) 光(14) 。(15)
  {0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x19, 0xFF, 0x19, 0x83, 0x3B, 0x06, 0x3E, 0x30, 0x78, 0x30},
  {0xD9, 0xBC, 0x19, 0xB6, 0x1B, 0x36, 0x1B, 0x33, 0x1E, 0x33, 0x18, 0x30, 0x18, 0xF0, 0x18, 0x60} /*"你",0*/
  /* (16 X 16 , 宋体, 加粗 )*/
};
 
  const unsigned char wo[][16] = {
  {0x04, 0x80, 0x0E, 0xA0, 0x78, 0x90, 0x08, 0x90, 0x08, 0x84, 0xFF, 0xFE, 0x08, 0x80, 0x08, 0x90},
  {0x0A, 0x90, 0x0C, 0x60, 0x18, 0x40, 0x68, 0xA0, 0x09, 0x20, 0x0A, 0x14, 0x28, 0x14, 0x10, 0x0C}
  // 显示我
};

  const unsigned char tempzero[1][1] = {};


void setup() {
  Serial.begin(9600);
  pixels.begin();
}
 
//把16进制转化成2进制的16位数组
int* getBin(int Dec, int Dec2 ) {
  //  Dec=128;
  static int a[16];
  for (int i = 7 ; i >= 0 ; i--) {
    if (pow(2, i) <= Dec) {
      Dec = Dec - pow(2, i);
      a[7 - i] = 1;
    } else {
      a[7 - i] = 0;
    }
  }
  for (int i = 7 ; i >= 0 ; i--) {
    if (pow(2, i) <= Dec2) {
      Dec2 = Dec2 - pow(2, i);
      a[15 - i] = 1;
    } else {
      a[15 - i] = 0;
    }
  }
  return a;
}
 
void loop() {
  //  pixels.clear();
  // put your main code here, to run repeatedly:
  int *lines;
  uint32_t  hsv;
  int count = 0;
  int r = 255, g = 255, b = 255;
 
  for (int k = 0; k < STR_NUM; k++) {
    if (k % 2 == 0) {
      r = random(10, 255);
      g = random(10, 255);
      b = random(10, 255);
    }
    for (int m = 0; m < 16; m++) {
      //对于每个16进制的数组，进行两个数字的组合成16位编码
      lines = getBin(wo[k][m], wo[k][m + 1]);
   
      if (m % 4 == 2 || m % 4 == 3)//0,1 代表偶数行，2，3代表技术行，奇数行从左到右输出，偶数行从右到左输出
      {
        for (int i = 0; i < 16; i++) {
          if (lines[i] == 1)pixels.setPixelColor(count, r, g, b);
          count++;
        }
      }
      else {
        for (int i = 15; i >= 0 ; i--) {
          if (lines[i] == 1)  pixels.setPixelColor(count,  r, g, b);
          count++;
        }
      }
      m++;
      pixels.show();
    }
    if (k % 2 == 1) {//由于使用了默认字模，所以每个汉字是两个16进制数组，所以在这里进行了处理
      pixels.show();
      delay(2000);
      pixels.clear();
      pixels.show();
      count = 0;
    }
  }
 
  //    delay(500);
 
}