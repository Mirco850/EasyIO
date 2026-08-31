#ifndef EASYIO_H
#define EASYIO_H

#include <Arduino.h>
#include <Wire.h>

#define EASYIO_TYPE_NONE   0   // None
#define EASYIO_TYPE_8       1   // PCF8574A (8 Bit: 4 Outputs + 4 Inputs)
#define EASYIO_TYPE_16      2   // PCF8575PWR (16 Bit: 8 Outputs + 8 Inputs)

class EasyIO {
  public:
    EasyIO();

    // Initializes the module and sets all pins to HIGH (0xFF / 0xFFFF).
    // Returns Wire error code: 0 = OK, 2 = Module not found, 99 = Invalid type
    int begin(uint8_t type, uint8_t address);

    // --- SINGLE BIT COMMANDS ---
    // Writes the state of a single bit.
    // Blocks write operations if attempting to set an input pin to LOW!
    bool write(uint8_t pin, bool state);

    // Reads the state of a single bit
    bool read(uint8_t pin);

    // --- BULK COMMANDS (BINARY) ---
    // Writes all output bits at once.
    // Automatically maintains input bits set to 1 (HIGH).
    bool writeBin(uint16_t binaryValue);

    // Reads the state of all bits (outputs + inputs)
    uint16_t readBin();

    // Module info
    uint8_t getType() const { return _type; }
    uint8_t getAddress() const { return _address; }

  private:
    uint8_t  _type;
    uint8_t  _address;
    uint16_t _pinState;
    uint16_t _inputMask; // Automatically calculated inside begin()

    int sendI2C(uint16_t value);
    uint16_t readI2C();
};

#endif