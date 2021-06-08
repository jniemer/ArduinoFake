#include "ArduinoFake.h"
#include "SPI.h"

void SPIClass::begin(int8_t sck, int8_t miso, int8_t mosi, int8_t ss)
{
    ArduinoFakeInstance(SPIClass, this)->begin(sck, miso, mosi, ss);
}

void SPIClass::end()
{
    ArduinoFakeInstance(SPIClass, this)->end();
}

void SPIClass::setHwCs(bool use)
{
    ArduinoFakeInstance(SPIClass, this)->setHwCs(use);
}

void SPIClass::setBitOrder(uint8_t bitOrder)
{
    ArduinoFakeInstance(SPIClass, this)->setBitOrder(bitOrder);
}
void SPIClass::setDataMode(uint8_t dataMode)
{
    ArduinoFakeInstance(SPIClass, this)->setDataMode(dataMode);
}
void SPIClass::setFrequency(uint32_t freq)
{
    ArduinoFakeInstance(SPIClass, this)->setFrequency(freq);
}
void SPIClass::setClockDivider(uint32_t clockDiv)
{
    ArduinoFakeInstance(SPIClass, this)->setClockDivider(clockDiv);
}

uint32_t SPIClass::getClockDivider()
{
    return ArduinoFakeInstance(SPIClass, this)->getClockDivider();
}

void SPIClass::beginTransaction(SPISettings settings)
{
    ArduinoFakeInstance(SPIClass, this)->beginTransaction(settings);
}
void SPIClass::endTransaction(void)
{
    ArduinoFakeInstance(SPIClass, this)->endTransaction();
}
void SPIClass::transfer(uint8_t * data, uint32_t size)
{
    ArduinoFakeInstance(SPIClass, this)->transfer(data, size);
}
uint8_t SPIClass::transfer(uint8_t data)
{
    return ArduinoFakeInstance(SPIClass, this)->transfer(data);
}
uint16_t SPIClass::transfer16(uint16_t data)
{
    return ArduinoFakeInstance(SPIClass, this)->transfer16(data);
}
uint32_t SPIClass::transfer32(uint32_t data)
{
    return ArduinoFakeInstance(SPIClass, this)->transfer32(data);
}

void SPIClass::transferBytes(const uint8_t * data, uint8_t * out, uint32_t size)
{
    ArduinoFakeInstance(SPIClass, this)->transferBytes(data, out, size);
}
void SPIClass::transferBits(uint32_t data, uint32_t * out, uint8_t bits)
{
    ArduinoFakeInstance(SPIClass, this)->transferBits(data, out, bits);
}

void SPIClass::write(uint8_t data)
{
    ArduinoFakeInstance(SPIClass, this)->write(data);
}
void SPIClass::write16(uint16_t data)
{
    ArduinoFakeInstance(SPIClass, this)->write16(data);
}
void SPIClass::write32(uint32_t data)
{
    ArduinoFakeInstance(SPIClass, this)->write32(data);
}
void SPIClass::writeBytes(const uint8_t * data, uint32_t size)
{
    ArduinoFakeInstance(SPIClass, this)->writeBytes(data, size);
}
void SPIClass::writePixels(const void * data, uint32_t size)
{
    ArduinoFakeInstance(SPIClass, this)->writePixels(data, size);
}
void SPIClass::writePattern(const uint8_t * data, uint8_t size, uint32_t repeat)
{
    ArduinoFakeInstance(SPIClass, this)->writePattern(data, size, repeat);
}

uint8_t * SPIClass::bus()
{
    return ArduinoFakeInstance(SPIClass, this)->bus();
}




SPIClass SPI = SPIClassFakeProxy(ArduinoFakeInstance(SPIClass));