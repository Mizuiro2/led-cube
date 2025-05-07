#include <Arduino.h>
#include <WiFi.h>
#include <BLEDevice.h>

#define LED_PIN 48  // 根据你的开发板修改LED引脚
#define BUTTON_PIN 0  // 常用Boot按钮引脚

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // WiFi测试
  WiFi.mode(WIFI_MODE_STA);
  WiFi.disconnect();
  delay(100);

  // BLE测试
  BLEDevice::init("ESP32-S3-Test");

  Serial.println("\nESP32-S3 test begin");
  Serial.printf("chipset: %s\n", ESP.getChipModel());
  Serial.printf("chip version: %d\n", ESP.getChipRevision());
  Serial.printf("cpu core no.: %d\n", ESP.getChipCores());
  Serial.printf("flashdrive: %d MB\n", ESP.getFlashChipSize() / (1024 * 1024));
}

void loop() {
  // LED闪烁测试
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED on");
  delay(500);
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED off");
  delay(500);

  // 按钮测试
  if(digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("button pressed!");
    delay(200);  // 消抖
  }

  // WiFi扫描测试
  Serial.println("scan wifi...");
  int n = WiFi.scanNetworks();
  Serial.printf("find %d wifi\n", n);
  for(int i=0; i<n; i++) {
    Serial.printf("%d: %s (%d dBm)\n", i+1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
  }

  // 内存信息
  Serial.printf("spare ram: %d bytes\n", esp_get_free_heap_size());
}