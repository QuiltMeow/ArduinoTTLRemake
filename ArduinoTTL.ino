#include "ArduinoTTL.h"

#define RX_PIN 2
#define TX_PIN 3
#define ARDUINO_BIT_RATE 9600

// 如果是樹莓派 位元速率可以於 /boot/cmdline.txt 進行修改
#define RASPBERRY_PI_BIT_RATE 9600

ArduinoTTL ttl(RX_PIN, TX_PIN, ARDUINO_BIT_RATE, RASPBERRY_PI_BIT_RATE);

void setup() {
  ttl.begin();
}

void loop() {
  ttl.run();
}
