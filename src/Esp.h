/*
 Esp.h - ESP31B-specific APIs
 Copyright (c) 2015 Ivan Grokhotkov. All rights reserved.

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

#ifndef ESP_H
#define ESP_H

#include <ArduinoFake.h>
#include "esp/esp_partition.h"

/**
 * AVR macros for WDT managment
 */
typedef enum {
    WDTO_0MS    = 0,   //!< WDTO_0MS
    WDTO_15MS   = 15,  //!< WDTO_15MS
    WDTO_30MS   = 30,  //!< WDTO_30MS
    WDTO_60MS   = 60,  //!< WDTO_60MS
    WDTO_120MS  = 120, //!< WDTO_120MS
    WDTO_250MS  = 250, //!< WDTO_250MS
    WDTO_500MS  = 500, //!< WDTO_500MS
    WDTO_1S     = 1000,//!< WDTO_1S
    WDTO_2S     = 2000,//!< WDTO_2S
    WDTO_4S     = 4000,//!< WDTO_4S
    WDTO_8S     = 8000 //!< WDTO_8S
} WDTO_t;


typedef enum {
    FM_QIO = 0x00,
    FM_QOUT = 0x01,
    FM_DIO = 0x02,
    FM_DOUT = 0x03,
    FM_FAST_READ = 0x04,
    FM_SLOW_READ = 0x05,
    FM_UNKNOWN = 0xff
} FlashMode_t;

typedef enum {
    SKETCH_SIZE_TOTAL = 0,
    SKETCH_SIZE_FREE = 1
} sketchSize_t;


class EspClass
{
public:
    EspClass() {}
    ~EspClass() {}
    virtual void restart();

    //Internal RAM
    virtual uint32_t getHeapSize(); //total heap size
    virtual uint32_t getFreeHeap(); //available heap
    virtual uint32_t getMinFreeHeap(); //lowest level of free heap since boot
    virtual uint32_t getMaxAllocHeap(); //largest block of heap that can be allocated at once

    //SPI RAM
    virtual uint32_t getPsramSize();
    virtual uint32_t getFreePsram();
    virtual uint32_t getMinFreePsram();
    virtual uint32_t getMaxAllocPsram();

    virtual uint8_t getChipRevision();
    virtual const char * getChipModel();
    virtual uint8_t getChipCores();
    virtual uint32_t getCpuFreqMHz();
    virtual uint32_t getCycleCount();
    virtual const char * getSdkVersion();

    virtual void deepSleep(uint32_t time_us);

    virtual uint32_t getFlashChipSize();
    virtual uint32_t getFlashChipSpeed();
    virtual FlashMode_t getFlashChipMode();

    virtual uint32_t magicFlashChipSize(uint8_t byte);
    virtual uint32_t magicFlashChipSpeed(uint8_t byte);
    virtual FlashMode_t magicFlashChipMode(uint8_t byte);

    virtual uint32_t getSketchSize();
    virtual String getSketchMD5();
    virtual uint32_t getFreeSketchSpace();

    virtual bool flashEraseSector(uint32_t sector);
    virtual bool flashWrite(uint32_t offset, uint32_t *data, size_t size);
    virtual bool flashRead(uint32_t offset, uint32_t *data, size_t size);

    virtual bool partitionEraseRange(const esp_partition_t *partition, uint32_t offset, size_t size);
    virtual bool partitionWrite(const esp_partition_t *partition, uint32_t offset, uint32_t *data, size_t size);
    virtual bool partitionRead(const esp_partition_t *partition, uint32_t offset, uint32_t *data, size_t size);

    virtual uint64_t getEfuseMac();
};

struct EspClassFake
{
    virtual void restart() = 0;

    //Internal RAM
    virtual uint32_t getHeapSize() = 0; //total heap size
    virtual uint32_t getFreeHeap() = 0; //available heap
    virtual uint32_t getMinFreeHeap() = 0; //lowest level of free heap since boot
    virtual uint32_t getMaxAllocHeap() = 0; //largest block of heap that can be allocated at once

    //SPI RAM
    virtual uint32_t getPsramSize() = 0;
    virtual uint32_t getFreePsram() = 0;
    virtual uint32_t getMinFreePsram() = 0;
    virtual uint32_t getMaxAllocPsram() = 0;

    virtual uint8_t getChipRevision() = 0;
    virtual const char * getChipModel() = 0;
    virtual uint8_t getChipCores() = 0;
    virtual uint32_t getCpuFreqMHz() = 0;
    virtual uint32_t getCycleCount() = 0;
    virtual const char * getSdkVersion() = 0;

    virtual void deepSleep(uint32_t time_us) = 0;

    virtual uint32_t getFlashChipSize() = 0;
    virtual uint32_t getFlashChipSpeed() = 0;
    virtual FlashMode_t getFlashChipMode() = 0;

    virtual uint32_t magicFlashChipSize(uint8_t byte) = 0;
    virtual uint32_t magicFlashChipSpeed(uint8_t byte) = 0;
    virtual FlashMode_t magicFlashChipMode(uint8_t byte) = 0;

    virtual uint32_t getSketchSize() = 0;
    virtual String getSketchMD5() = 0;
    virtual uint32_t getFreeSketchSpace() = 0;

    virtual bool flashEraseSector(uint32_t sector) = 0;
    virtual bool flashWrite(uint32_t offset, uint32_t *data, size_t size) = 0;
    virtual bool flashRead(uint32_t offset, uint32_t *data, size_t size) = 0;

    virtual bool partitionEraseRange(const esp_partition_t *partition, uint32_t offset, size_t size) = 0;
    virtual bool partitionWrite(const esp_partition_t *partition, uint32_t offset, uint32_t *data, size_t size) = 0;
    virtual bool partitionRead(const esp_partition_t *partition, uint32_t offset, uint32_t *data, size_t size) = 0;

    virtual uint64_t getEfuseMac() = 0;
};

class EspClassFakeProxy : public EspClass
{
    private:
        EspClassFake* espFake;

    public:
        EspClassFakeProxy(EspClassFake* fake)
        {
            espFake = fake;
        }

        EspClassFake* getEspClassFake()
        {
            return espFake;
        }
};

extern EspClass ESP;

#endif //ESP_H
