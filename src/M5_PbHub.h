#ifndef __M5_PBHUB__
#define __M5_PBHUB__


#include <Wire.h>



class M5_PbHub {

  private:
    uint8_t _iic_addr = 0x61;

    int _digitalRead(uint8_t channel, uint8_t pin) {
        Wire.beginTransmission(_iic_addr);
        Wire.write(((channel+4)<<4) | (0x04+pin));
        Wire.endTransmission();

        uint8_t RegValue = 0;

        Wire.requestFrom(_iic_addr, (uint8_t)1);
        while (Wire.available()) {
            RegValue = Wire.read();
        }
        return RegValue;
    }

    void _digitalWrite(uint8_t channel, uint8_t pin, uint8_t value) {
        Wire.beginTransmission(_iic_addr);
        Wire.write(((channel+4)<<4) | (0x00+pin));
        Wire.write(value);
        Wire.endTransmission();
    }



  public:
M5_PbHub() {
}

M5_PbHub(uint8_t iic_addr) {
    _iic_addr = iic_addr;
}

void begin() {
    Wire.begin();
}

int digitalRead(uint8_t channel) {
    return _digitalRead(channel,0);
}

void digitalWrite(uint8_t channel, uint8_t  value) {
     _digitalWrite(channel,1,value);
}

int analogRead(uint8_t channel) {
    Wire.beginTransmission(_iic_addr);
    Wire.write( ((channel+4)<<4) | 0x06);
    Wire.endTransmission();

    uint8_t RegValue_L = 0;
    uint8_t RegValue_H = 0;

    Wire.requestFrom((uint16_t)_iic_addr,(size_t) 2);
    unsigned long millisAtRequest = millis();
    while (Wire.available() < 1 && millis() - millisAtRequest < 500 ) { };
    if ( Wire.available() > 1) {
        RegValue_L = Wire.read();
        RegValue_H = Wire.read();
    }

    return (RegValue_H << 8) | RegValue_L;
}



void analogWrite(uint8_t channel, uint8_t pin, uint8_t  pwm) {
    Wire.beginTransmission(_iic_addr);
    Wire.write(((channel+4)<<4) | (0x02+pin));
    Wire.write(pwm);
    Wire.endTransmission();
}


void setPixelCount(uint8_t channel, uint16_t count) {
    Wire.beginTransmission(_iic_addr);
    Wire.write(((channel+4)<<4) | 0x08);
    Wire.write(count & 0xff);
    Wire.write(count >> 8);
    Wire.endTransmission();
}

void setPixelColor(uint8_t channel, uint16_t index, uint8_t r,
                                   int8_t g, uint8_t b) {
    Wire.beginTransmission(_iic_addr);
    Wire.write(((channel+4)<<4) | 0x09);
    Wire.write(index & 0xff);
    Wire.write(index >> 8);
    Wire.write(r);
    Wire.write(g);
    Wire.write(b);
    Wire.endTransmission();
}

void fillPixelColor(uint8_t channel, uint16_t index, uint16_t count,
                                  uint8_t r, int8_t g, uint8_t b) {
    Wire.beginTransmission(_iic_addr);
    Wire.write(((channel+4)<<4) | 0x0a);
    Wire.write(index & 0xff);
    Wire.write(index >> 8);

    Wire.write(count & 0xff);
    Wire.write(count >> 8);

    Wire.write(r);
    Wire.write(g);
    Wire.write(b);
    Wire.endTransmission();
}

void setPixelBrightness(uint8_t channel, uint8_t brightness) {
    Wire.beginTransmission(_iic_addr);
    Wire.write(((channel+4)<<4) | 0x0b);
    Wire.write(brightness);
    Wire.endTransmission();
}



};

#endif