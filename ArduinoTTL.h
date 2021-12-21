#include <SoftwareSerial.h>

class ArduinoTTL {
  protected:
    byte rxPin, txPin;
    int hardwareSerialBitRate, softwareSerialBitRate;

    SoftwareSerial* softwareSerial;
    byte* serialBuffer;
  public:
    ArduinoTTL(byte rxPin, byte txPin, int hardwareSerialBitRate, int softwareSerialBitRate) {
      this->rxPin = rxPin;
      this->txPin = txPin;
      this->hardwareSerialBitRate = hardwareSerialBitRate;
      this->softwareSerialBitRate = softwareSerialBitRate;

      softwareSerial = new SoftwareSerial(rxPin, txPin);
      serialBuffer = new byte[_SS_MAX_RX_BUFF]; // 接收序列埠緩衝區
    }

    ~ArduinoTTL() {
      delete[] serialBuffer;
      delete softwareSerial;
    }

    void begin() {
      Serial.begin(hardwareSerialBitRate);
      while (!Serial) {
      }

      softwareSerial->begin(softwareSerialBitRate);
      while (!*softwareSerial) {
      }
    }

    void run() { // 轉發
      // 嗯 根本不需要多執行緒 ...
      int available = Serial.available();
      if (available) {
        Serial.readBytes(serialBuffer, available);
        softwareSerial->write(serialBuffer, available);
      }

      available = softwareSerial->available();
      if (available) {
        softwareSerial->readBytes(serialBuffer, available);
        Serial.write(serialBuffer, available);
      }
    }
};
