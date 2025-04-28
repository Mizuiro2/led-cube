#include <Adafruit_NeoPixel.h>

#define PIN 6
#define WIDTH 16
#define HEIGHT 16
#define NUMPIXELS (WIDTH * HEIGHT)

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t image[16][16] = {
  {pixels.Color(109,158,68), pixels.Color(111,154,72), pixels.Color(119,170,74), pixels.Color(112,157,71), pixels.Color(120,168,75), pixels.Color(116,176,75), pixels.Color(111,162,71), pixels.Color(112,153,71), pixels.Color(116,164,74), pixels.Color(109,161,73), pixels.Color(116,159,74), pixels.Color(116,165,72), pixels.Color(107,156,69), pixels.Color(110,153,72), pixels.Color(117,164,75), pixels.Color(109,155,72)},
  {pixels.Color(116,164,71), pixels.Color(112,155,71), pixels.Color(115,160,74), pixels.Color(113,166,73), pixels.Color(118,169,77), pixels.Color(114,163,73), pixels.Color(111,165,72), pixels.Color(111,156,70), pixels.Color(119,164,75), pixels.Color(118,158,73), pixels.Color(106,97,58), pixels.Color(106,149,67), pixels.Color(119,166,75), pixels.Color(121,168,78), pixels.Color(115,164,75), pixels.Color(120,165,76)},
  {pixels.Color(107,160,68), pixels.Color(115,157,74), pixels.Color(106,96,59), pixels.Color(107,154,68), pixels.Color(111,153,68), pixels.Color(106,95,58), pixels.Color(112,150,69), pixels.Color(115,161,73), pixels.Color(112,143,69), pixels.Color(107,88,57), pixels.Color(108,84,58), pixels.Color(107,142,70), pixels.Color(110,151,70), pixels.Color(112,158,72), pixels.Color(114,164,73), pixels.Color(118,168,76)},
  {pixels.Color(113,168,73), pixels.Color(114,149,71), pixels.Color(113,94,61), pixels.Color(111,146,67), pixels.Color(116,151,68), pixels.Color(112,85,61), pixels.Color(111,93,60), pixels.Color(114,150,71), pixels.Color(109,92,59), pixels.Color(114,81,60), pixels.Color(147,108,79), pixels.Color(117,91,63), pixels.Color(105,83,56), pixels.Color(109,86,58), pixels.Color(114,97,62), pixels.Color(116,155,71)},
  {pixels.Color(110,150,72), pixels.Color(118,98,65), pixels.Color(182,136,97), pixels.Color(121,95,64), pixels.Color(109,86,58), pixels.Color(154,113,83), pixels.Color(149,109,80), pixels.Color(118,92,63), pixels.Color(153,112,82), pixels.Color(151,111,81), pixels.Color(167,123,89), pixels.Color(189,140,101), pixels.Color(123,88,66), pixels.Color(158,114,84), pixels.Color(188,139,100), pixels.Color(114,89,60)},
  {pixels.Color(121,154,78), pixels.Color(151,116,82), pixels.Color(163,118,88), pixels.Color(185,136,98), pixels.Color(131,94,71), pixels.Color(191,141,102), pixels.Color(148,109,83), pixels.Color(157,114,84), pixels.Color(187,139,101), pixels.Color(131,95,70), pixels.Color(188,139,101), pixels.Color(196,146,105), pixels.Color(165,122,89), pixels.Color(201,149,107), pixels.Color(193,143,103), pixels.Color(121,88,64)},
  {pixels.Color(159,122,86), pixels.Color(151,111,82), pixels.Color(122,88,67), pixels.Color(160,117,86), pixels.Color(195,145,105), pixels.Color(203,151,108), pixels.Color(157,115,85), pixels.Color(156,114,84), pixels.Color(142,105,81), pixels.Color(147,112,86), pixels.Color(122,89,67), pixels.Color(127,93,69), pixels.Color(199,148,107), pixels.Color(197,146,105), pixels.Color(134,98,73), pixels.Color(188,139,100)},
  {pixels.Color(197,145,105), pixels.Color(128,93,70), pixels.Color(152,111,82), pixels.Color(143,105,81), pixels.Color(166,122,89), pixels.Color(194,143,103), pixels.Color(132,96,72), pixels.Color(152,110,81), pixels.Color(124,94,75), pixels.Color(141,143,138), pixels.Color(156,118,91), pixels.Color(157,114,84), pixels.Color(193,144,103), pixels.Color(170,124,91), pixels.Color(154,112,83), pixels.Color(158,115,85)},
  {pixels.Color(194,144,104), pixels.Color(162,119,87), pixels.Color(192,141,102), pixels.Color(156,114,84), pixels.Color(157,115,85), pixels.Color(164,120,88), pixels.Color(188,139,101), pixels.Color(160,117,86), pixels.Color(192,142,103), pixels.Color(198,151,113), pixels.Color(194,144,105), pixels.Color(143,104,80), pixels.Color(124,90,68), pixels.Color(186,138,100), pixels.Color(163,119,88), pixels.Color(124,90,68)},
  {pixels.Color(123,89,67), pixels.Color(156,114,85), pixels.Color(157,120,92), pixels.Color(127,92,70), pixels.Color(148,109,81), pixels.Color(140,103,79), pixels.Color(157,115,85), pixels.Color(128,92,69), pixels.Color(156,114,84), pixels.Color(161,117,86), pixels.Color(147,108,83), pixels.Color(151,110,82), pixels.Color(114,82,62), pixels.Color(122,89,67), pixels.Color(192,143,103), pixels.Color(192,142,103)},
  {pixels.Color(158,114,83), pixels.Color(156,118,90), pixels.Color(144,146,139), pixels.Color(187,143,107), pixels.Color(123,89,66), pixels.Color(116,84,64), pixels.Color(158,116,85), pixels.Color(188,140,101), pixels.Color(127,92,69), pixels.Color(157,115,85), pixels.Color(161,118,87), pixels.Color(163,119,87), pixels.Color(156,114,84), pixels.Color(123,89,67), pixels.Color(150,110,81), pixels.Color(123,89,68)},
  {pixels.Color(201,149,107), pixels.Color(160,118,87), pixels.Color(160,122,93), pixels.Color(200,149,107), pixels.Color(159,116,85), pixels.Color(158,115,85), pixels.Color(167,123,90), pixels.Color(201,149,107), pixels.Color(162,119,87), pixels.Color(195,145,104), pixels.Color(205,153,109), pixels.Color(204,151,109), pixels.Color(198,147,106), pixels.Color(193,143,103), pixels.Color(129,94,71), pixels.Color(137,100,77)},
  {pixels.Color(196,145,105), pixels.Color(145,107,82), pixels.Color(161,117,86), pixels.Color(200,148,106), pixels.Color(167,122,89), pixels.Color(194,143,104), pixels.Color(200,149,107), pixels.Color(196,145,105), pixels.Color(165,121,89), pixels.Color(165,121,89), pixels.Color(196,146,105), pixels.Color(192,142,103), pixels.Color(131,95,71), pixels.Color(195,145,104), pixels.Color(195,145,105), pixels.Color(197,146,106)},
  {pixels.Color(147,108,83), pixels.Color(137,100,78), pixels.Color(159,116,86), pixels.Color(195,144,104), pixels.Color(161,118,87), pixels.Color(151,111,85), pixels.Color(153,112,83), pixels.Color(131,95,71), pixels.Color(193,143,103), pixels.Color(160,117,86), pixels.Color(127,92,69), pixels.Color(116,84,63), pixels.Color(117,84,64), pixels.Color(156,114,84), pixels.Color(145,107,82), pixels.Color(161,118,87)},
  {pixels.Color(186,138,100), pixels.Color(121,88,67), pixels.Color(136,100,77), pixels.Color(145,106,82), pixels.Color(162,118,87), pixels.Color(186,138,100), pixels.Color(126,91,69), pixels.Color(154,112,83), pixels.Color(195,145,104), pixels.Color(166,123,90), pixels.Color(181,138,104), pixels.Color(118,86,65), pixels.Color(147,107,79), pixels.Color(157,115,85), pixels.Color(122,89,67), pixels.Color(154,112,83)},
  {pixels.Color(140,103,80), pixels.Color(114,82,63), pixels.Color(135,100,77), pixels.Color(154,113,84), pixels.Color(159,116,85), pixels.Color(162,119,87), pixels.Color(155,113,84), pixels.Color(159,116,85), pixels.Color(162,118,87), pixels.Color(158,120,92), pixels.Color(140,146,142), pixels.Color(110,85,68), pixels.Color(121,87,65), pixels.Color(192,142,102), pixels.Color(159,117,86), pixels.Color(157,115,84)}
};


void setup() {
  pixels.begin();
  pixels.clear();

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      int pixelIndex = y * WIDTH + x;
      pixels.setPixelColor(pixelIndex, image[y][x]);
    }
  }
  
  pixels.show();
}

void loop() {
  // Static display
}
