#ifndef __M5_PBHUB__
#define __M5_PBHUB__


#include <Wire.h>


class M5_PbHub {

  private:
    uint8_t _iic_addr = 0x61;
    TwoWire & _wire;

  public:
  

M5_PbHub(TwoWire & wire = Wire, uint8_t iic_addr = 0x61) : _wire(wire) {
    _iic_addr = iic_addr;
}

void begin() {
    // _wire should be started before
    // _wire.begin();
}

int digitalRead(uint8_t channel, uint8_t pin) {
	if (channel == 5) channel++;
	_wire.beginTransmission(_iic_addr);
	_wire.write(((channel+4)<<4) | (0x04+pin));
	_wire.endTransmission();

	uint8_t RegValue = 0;

	_wire.requestFrom(_iic_addr, (uint8_t)1);
	while (_wire.available()) {
		RegValue = _wire.read();
	}
	return RegValue;
}

void digitalWrite(uint8_t channel, uint8_t pin, uint8_t value) {
	if (channel == 5) channel++;
	_wire.beginTransmission(_iic_addr);
	_wire.write(((channel+4)<<4) | (0x00+pin));
	_wire.write(value);
	_wire.endTransmission();
}

int digitalRead(uint8_t channel) {
	// CHANNEL 5 OFFSET BUG/FEATURE IS TREATED IN digitalRead(channel,index)
    return digitalRead(channel,0);
}

void digitalWrite(uint8_t channel, uint8_t  value) {
	// CHANNEL 5 OFFSET BUG/FEATURE IS TREATED IN digitalWrite( channel,  pin,  value)
     digitalWrite(channel,1,value);
}

int analogRead(uint8_t channel) {
	if (channel == 5) channel++;
    _wire.beginTransmission(_iic_addr);
    _wire.write( ((channel+4)<<4) | 0x06);
    _wire.endTransmission();

    uint8_t RegValue_L = 0;
    uint8_t RegValue_H = 0;

    _wire.requestFrom((uint16_t)_iic_addr,(size_t) 2);
    unsigned long millisAtRequest = millis();
    while (_wire.available() < 1 && millis() - millisAtRequest < 500 ) { };
    if ( _wire.available() > 1) {
        RegValue_L = _wire.read();
        RegValue_H = _wire.read();
    }

    return (RegValue_H << 8) | RegValue_L;
}



void analogWrite(uint8_t channel, uint8_t pin, uint8_t  pwm) {
	if (channel == 5) channel++;
    _wire.beginTransmission(_iic_addr);
    _wire.write(((channel+4)<<4) | (0x02+pin));
    _wire.write(pwm);
    _wire.endTransmission();
}


void setPixelCount(uint8_t channel, uint16_t count) {
	if (channel == 5) channel++;
    _wire.beginTransmission(_iic_addr);
    _wire.write(((channel+4)<<4) | 0x08);
    _wire.write(count & 0xff);
    _wire.write(count >> 8);
    _wire.endTransmission();
}

void setPixelColor(uint8_t channel, uint16_t index, uint8_t r,
                                   int8_t g, uint8_t b) {
	if (channel == 5) channel++;									
    _wire.beginTransmission(_iic_addr);
    _wire.write(((channel+4)<<4) | 0x09);
    _wire.write(index & 0xff);
    _wire.write(index >> 8);
    _wire.write(r);
    _wire.write(g);
    _wire.write(b);
    _wire.endTransmission();
}

void fillPixelColor(uint8_t channel, uint16_t index, uint16_t count,
                                  uint8_t r, int8_t g, uint8_t b) {
	if (channel == 5) channel++;									
    _wire.beginTransmission(_iic_addr);
    _wire.write(((channel+4)<<4) | 0x0a);
    _wire.write(index & 0xff);
    _wire.write(index >> 8);

    _wire.write(count & 0xff);
    _wire.write(count >> 8);

    _wire.write(r);
    _wire.write(g);
    _wire.write(b);
    _wire.endTransmission();
}

void setPixelBrightness(uint8_t channel, uint8_t brightness) {
	if (channel == 5) channel++;
    _wire.beginTransmission(_iic_addr);
    _wire.write(((channel+4)<<4) | 0x0b);
    _wire.write(brightness);
    _wire.endTransmission();
}



};

#endif