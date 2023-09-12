#ifndef __M5_PBHUB__
#define __M5_PBHUB__


#include <Wire.h>


#define M5_PBHUB_IIC_ADDR1 0x61
#define M5_PBHUB_IIC_ADDR2 0x62
#define M5_PBHUB_IIC_ADDR3 0x63
#define M5_PBHUB_IIC_ADDR4 0x64
#define M5_PBHUB_IIC_ADDR5 0x65
#define M5_PBHUB_IIC_ADDR6 0x66
#define M5_PBHUB_IIC_ADDR7 0x67
#define M5_PBHUB_IIC_ADDR8 0x68


class M5_PbHub {

  private:
    uint8_t _iic_addr = M5_PBHUB_IIC_ADDR1;

  public:
M5_PbHub() {
}

M5_PbHub(uint8_t iic_addr) {
    _iic_addr = iic_addr;
}

void begin() {
    Wire.begin();
}

uint16_t analogRead(uint8_t channel) {
    Wire.beginTransmission(_iic_addr);
    Wire.write((channel<<8) | 0x06);
    Wire.endTransmission();

    uint8_t RegValue_L = 0;
    uint8_t RegValue_H = 0;

    Wire.requestFrom(_iic_addr, (uint8_t)2);
    while (Wire.available()) {
        RegValue_L = Wire.read();
        RegValue_H = Wire.read();
    }

    return (RegValue_H << 8) | RegValue_L;
}

uint8_t digitalRead(uint8_t channel, uint8_t pin) {
    Wire.beginTransmission(_iic_addr);
    Wire.write((channel<<8) | (0x04+pin));
    Wire.endTransmission();

    uint8_t RegValue = 0;

    Wire.requestFrom(_iic_addr, (uint8_t)1);
    while (Wire.available()) {
        RegValue = Wire.read();
    }
    return RegValue;
}

void digitalWrite(uint8_t channel, uint8_t pin, uint8_t value) {
    Wire.beginTransmission(_iic_addr);
    Wire.write((channel<<8) | (0x00+pin));
    Wire.write(value);
    Wire.endTransmission();
}

void analogWrite(uint8_t channel, uint8_t pin, uint8_t  duty) {
    Wire.beginTransmission(_iic_addr);
    Wire.write((channel<<8) | (0x02+pin));
    Wire.write(duty);
    Wire.endTransmission();
}


void setPixelCount(uint8_t channel, uint16_t count) {
    Wire.beginTransmission(_iic_addr);
    Wire.write((channel<<8) | 0x08);
    Wire.write(count & 0xff);
    Wire.write(count >> 8);
    Wire.endTransmission();
}

void setPixelColor(uint8_t channel, uint16_t index, uint8_t r,
                                   int8_t g, uint8_t b) {
    Wire.beginTransmission(_iic_addr);
    Wire.write((channel<<8) | 0x09);
    Wire.write(index & 0xff);
    Wire.write(index >> 8);
    Wire.write(r);
    Wire.write(g);
    Wire.write(b);
    Wire.endTransmission();
}

void fillPixelColor(uint8_t channel, uint16_t first, uint16_t count,
                                  uint8_t r, int8_t g, uint8_t b) {
    Wire.beginTransmission(_iic_addr);
    Wire.write((channel<<8) | 0x0a);
    Wire.write(first & 0xff);
    Wire.write(first >> 8);

    Wire.write(count & 0xff);
    Wire.write(count >> 8);

    Wire.write(r);
    Wire.write(g);
    Wire.write(b);
    Wire.endTransmission();
}

void setPixelBrightness(uint8_t channel, uint8_t brightness) {
    Wire.beginTransmission(_iic_addr);
    Wire.write((channel<<8) | 0x0b);
    Wire.write(brightness);
    Wire.endTransmission();
}



};

#endif