/* 
  SPI.h - SPI library for esp32

  Copyright (c) 2015 Hristo Gochkov. All rights reserved.
  This file is part of the esp8266 core for Arduino environment.
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <stdlib.h>
#include "ArduinoFake.h"
#include "StreamFake.h"

#define SPI_HAS_TRANSACTION

#define FSPI  1 //SPI bus attached to the flash (can use the same data lines but different SS)
#define HSPI  2 //SPI bus normally mapped to pins 12 - 15, but can be matrixed to any pins
#define VSPI  3 //SPI bus normally attached to pins 5, 18, 19 and 23, but can be matrixed to any pins

// This defines are not representing the real Divider of the ESP32
// the Defines match to an AVR Arduino on 16MHz for better compatibility
#define SPI_CLOCK_DIV2    0x00101001 //8 MHz
#define SPI_CLOCK_DIV4    0x00241001 //4 MHz
#define SPI_CLOCK_DIV8    0x004c1001 //2 MHz
#define SPI_CLOCK_DIV16   0x009c1001 //1 MHz
#define SPI_CLOCK_DIV32   0x013c1001 //500 KHz
#define SPI_CLOCK_DIV64   0x027c1001 //250 KHz
#define SPI_CLOCK_DIV128  0x04fc1001 //125 KHz

#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2
#define SPI_MODE3 3

#define SPI_CS0 0
#define SPI_CS1 1
#define SPI_CS2 2
#define SPI_CS_MASK_ALL 0x7

#define SPI_LSBFIRST 0
#define SPI_MSBFIRST 1

typedef enum _BitOrder {
  MSBFIRST,
  LSBFIRST
} BitOrder;

class SPISettings
{
public:
    SPISettings() :_clock(1000000), _bitOrder(0), _dataMode(0) {}
    SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) :_clock(clock), _bitOrder(bitOrder), _dataMode(dataMode) {}
    uint32_t _clock;
    uint8_t  _bitOrder;
    uint8_t  _dataMode;
};

class SPIClass
{
private:
    int8_t _spi_num;
    //spi_t * _spi;
    bool _use_hw_ss;
    int8_t _sck;
    int8_t _miso;
    int8_t _mosi;
    int8_t _ss;
    uint32_t _div;
    uint32_t _freq;
    bool _inTransaction;
    void writePattern_(const uint8_t * data, uint8_t size, uint8_t repeat);

public:
    SPIClass(uint8_t spi_id = 0) {};
    void begin(int8_t sck=-1, int8_t miso=-1, int8_t mosi=-1, int8_t ss=-1);
    void end();

    void setHwCs(bool use);
    void setBitOrder(uint8_t bitOrder);
    void setDataMode(uint8_t dataMode);
    void setFrequency(uint32_t freq);
    void setClockDivider(uint32_t clockDiv);
    
    uint32_t getClockDivider();

    void beginTransaction(SPISettings settings);
    void endTransaction(void);
    void transfer(uint8_t * data, uint32_t size);
    uint8_t transfer(uint8_t data);
    uint16_t transfer16(uint16_t data);
    uint32_t transfer32(uint32_t data);
  
    void transferBytes(const uint8_t * data, uint8_t * out, uint32_t size);
    void transferBits(uint32_t data, uint32_t * out, uint8_t bits);

    virtual void write(uint8_t data);
    virtual void write16(uint16_t data);
    virtual void write32(uint32_t data);
    virtual void writeBytes(const uint8_t * data, uint32_t size);
    virtual void writePixels(const void * data, uint32_t size);//ili9341 compatible
    virtual void writePattern(const uint8_t * data, uint8_t size, uint32_t repeat);

    uint8_t * bus();
};

struct SPIClassFake
{
    virtual void begin(int8_t sck=-1, int8_t miso=-1, int8_t mosi=-1, int8_t ss=-1) = 0;
    virtual void end() = 0;

    virtual void setHwCs(bool use) = 0;
    virtual void setBitOrder(uint8_t bitOrder) = 0;
    virtual void setDataMode(uint8_t dataMode) = 0;
    virtual void setFrequency(uint32_t freq) = 0;
    virtual void setClockDivider(uint32_t clockDiv) = 0;
    
    virtual uint32_t getClockDivider() = 0;

    virtual void beginTransaction(SPISettings settings) = 0;
    virtual void endTransaction(void) = 0;
    virtual void transfer(uint8_t * data, uint32_t size) = 0;
    virtual uint8_t transfer(uint8_t data) = 0;
    virtual uint16_t transfer16(uint16_t data) = 0;
    virtual uint32_t transfer32(uint32_t data) = 0;
  
    virtual void transferBytes(const uint8_t * data, uint8_t * out, uint32_t size) = 0;
    virtual void transferBits(uint32_t data, uint32_t * out, uint8_t bits) = 0;

    virtual void write(uint8_t data) = 0;
    virtual void write16(uint16_t data) = 0;
    virtual void write32(uint32_t data) = 0;
    virtual void writeBytes(const uint8_t * data, uint32_t size) = 0;
    virtual void writePixels(const void * data, uint32_t size) = 0;//ili9341 compatible
    virtual void writePattern(const uint8_t * data, uint8_t size, uint32_t repeat) = 0;

    virtual uint8_t * bus() = 0;
};

class SPIClassFakeProxy : public SPIClass
{
    private:
        SPIClassFake* spiFake;

    public:
        SPIClassFakeProxy(SPIClassFake* fake)
        {
            spiFake = fake;
        }

        SPIClassFake* getSPIClassFake()
        {
            return spiFake;
        }
};

extern SPIClass SPI;

#endif
