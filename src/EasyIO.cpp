#include "EasyIO.h"

EasyIO::EasyIO() {
  _type = EASYIO_TYPE_NONE;
  _address = 0x00;
  _pinState = 0xFFFF;
  _inputMask = 0x0000;
}

int EasyIO::begin(uint8_t type, uint8_t address) {
  _type = type;
  _address = address;
  
  Wire.begin();

  if (_type == EASYIO_TYPE_8) {
    _inputMask = 0xF0;     // Bits 0-3 Outputs, Bits 4-7 Inputs
    _pinState = 0xFF;      // All set to HIGH at startup (Outputs off, Inputs floating HIGH)
  } 
  else if (_type == EASYIO_TYPE_16) {
    _inputMask = 0xFF00;   // Bits 0-7 Outputs, Bits 8-15 Inputs
    _pinState = 0xFFFF;    // All set to HIGH at startup
  } 
  else {
    _type = EASYIO_TYPE_NONE;
    return 99; // Invalid module type
  }

  // Verify module presence on I2C bus
  Wire.beginTransmission(_address);
  int errorCode = Wire.endTransmission();

  // If chip responds (0), write initial default state
  if (errorCode == 0) {
    sendI2C(_pinState);
  }

  return errorCode;
}

// SINGLE BIT WRITE
bool EasyIO::write(uint8_t pin, bool state) {
  uint8_t maxOutputs = (_type == EASYIO_TYPE_8) ? 4 : 8;
  if (pin >= maxOutputs) return false;

  if (_type == EASYIO_TYPE_8) {
    // 8-bit handling: isolate output bits (0..3)
    uint8_t currentByte = (uint8_t)(_pinState & 0xFF);
    
    // Active-LOW logic: HIGH -> bit to 0 (ON), LOW -> bit to 1 (OFF)
    if (state == HIGH) {
      currentByte &= ~(1 << pin);
    } else {
      currentByte |= (1 << pin);
    }

    // Always enforce input bits (4..7) to HIGH (1) to prevent pin contention
    currentByte |= 0xF0;
    _pinState = currentByte;
  } 
  else { 
    // 16-bit handling
    if (state == HIGH) {
      _pinState &= ~(1 << pin);
    } else {
      _pinState |= (1 << pin);
    }
    _pinState |= _inputMask;
  }

  return (sendI2C(_pinState) == 0);
}

// SINGLE BIT READ
bool EasyIO::read(uint8_t pin) {
  uint8_t shift = (_type == EASYIO_TYPE_8) ? 4 : 8;
  uint8_t totalPins = (_type == EASYIO_TYPE_8) ? 8 : 16;

  // Handle both relative pin index (0..3) and absolute chip pin index (4..7)
  uint8_t bitToRead = pin;
  if (bitToRead < shift) {
    bitToRead += shift;
  }

  if (bitToRead >= totalPins) return false;

  uint16_t readData = readI2C();
  
  // Returns true when active LOW (e.g., button pressed to GND)
  return (readData & (1 << bitToRead)) == 0;
}

// BULK WRITE (BINARY)
bool EasyIO::writeBin(uint16_t binaryValue) {
  if (_type == EASYIO_TYPE_8) {
    uint8_t outputs = (uint8_t)(binaryValue & 0x0F);
    _pinState = ((~outputs) & 0x0F) | 0xF0;
  } else {
    uint16_t outputs = binaryValue & 0x00FF;
    _pinState = ((~outputs) & 0x00FF) | 0xFF00;
  }

  return (sendI2C(_pinState) == 0);
}

// BULK READ (BINARY)
uint16_t EasyIO::readBin() {
  uint8_t shift = (_type == EASYIO_TYPE_8) ? 4 : 8;
  return (((~readI2C()) & _inputMask) >> shift);
}

// PRIVATE: Send data over I2C bus
int EasyIO::sendI2C(uint16_t value) {
  Wire.beginTransmission(_address);

  if (_type == EASYIO_TYPE_8) {
    Wire.write((uint8_t)(value & 0xFF));
  } else if (_type == EASYIO_TYPE_16) {
    Wire.write((uint8_t)(value & 0xFF));        // Low byte (Outputs P00-P07)
    Wire.write((uint8_t)((value >> 8) & 0xFF)); // High byte (Inputs P10-P17)
  } else {
    return 99;
  }

  return Wire.endTransmission();
}

// PRIVATE: Read data from I2C bus
uint16_t EasyIO::readI2C() {
  uint16_t data = 0xFFFF;
  uint8_t bytesToRead = (_type == EASYIO_TYPE_8) ? 1 : 2;

  if (Wire.requestFrom((int)_address, (int)bytesToRead) == bytesToRead) {
    uint8_t lowByte = Wire.read();
    if (_type == EASYIO_TYPE_8) {
      data = lowByte;
    } else {
      uint8_t highByte = Wire.read();
      data = lowByte | (highByte << 8);
    }
  }

  return data;
}