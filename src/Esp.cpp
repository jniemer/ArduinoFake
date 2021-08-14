#include "ArduinoFake.h"
#include "Esp.h"

void EspClass::restart() {
    ArduinoFakeInstance(EspClass, this)->restart();
}

uint32_t EspClass::getHeapSize() {
    return ArduinoFakeInstance(EspClass, this)->getHeapSize();
}

uint32_t EspClass::getFreeHeap() {
    return ArduinoFakeInstance(EspClass, this)->getFreeHeap();
}

uint32_t EspClass::getMinFreeHeap() {
    return ArduinoFakeInstance(EspClass, this)->getMinFreeHeap();
}

uint32_t EspClass::getMaxAllocHeap() {
    return ArduinoFakeInstance(EspClass, this)->getMaxAllocHeap();
}

uint32_t EspClass::getPsramSize() {
    return ArduinoFakeInstance(EspClass, this)->getPsramSize();
}

uint32_t EspClass::getFreePsram() {
    return ArduinoFakeInstance(EspClass, this)->getFreePsram();
}

uint32_t EspClass::getMinFreePsram() {
    return ArduinoFakeInstance(EspClass, this)->getMinFreePsram();
}

uint32_t EspClass::getMaxAllocPsram() {
    return ArduinoFakeInstance(EspClass, this)->getMaxAllocPsram();
}

uint8_t EspClass::getChipRevision() {
    return ArduinoFakeInstance(EspClass, this)->getChipRevision();
}

const char * EspClass::getChipModel() {
    return ArduinoFakeInstance(EspClass, this)->getChipModel();
}

uint8_t EspClass::getChipCores() {
    return ArduinoFakeInstance(EspClass, this)->getChipCores();
}

uint32_t EspClass::getCpuFreqMHz() {
    return ArduinoFakeInstance(EspClass, this)->getCpuFreqMHz();
}

uint32_t EspClass::getCycleCount() {
    return ArduinoFakeInstance(EspClass, this)->getCycleCount();
}

const char * EspClass::getSdkVersion() {
    return ArduinoFakeInstance(EspClass, this)->getSdkVersion();
}

void EspClass::deepSleep(uint32_t time_us) {
    ArduinoFakeInstance(EspClass, this)->deepSleep(time_us);
}

uint32_t EspClass::getFlashChipSize() {
    return ArduinoFakeInstance(EspClass, this)->getFlashChipSize();
}

uint32_t EspClass::getFlashChipSpeed() {
    return ArduinoFakeInstance(EspClass, this)->getFlashChipSpeed();
}

FlashMode_t EspClass::getFlashChipMode() {
    return ArduinoFakeInstance(EspClass, this)->getFlashChipMode();
}

uint32_t EspClass::magicFlashChipSize(uint8_t byte) {
    return ArduinoFakeInstance(EspClass, this)->magicFlashChipSize(byte);
}

uint32_t EspClass::magicFlashChipSpeed(uint8_t byte) {
    return ArduinoFakeInstance(EspClass, this)->magicFlashChipSpeed(byte);
}

FlashMode_t EspClass::magicFlashChipMode(uint8_t byte) {
    return ArduinoFakeInstance(EspClass, this)->magicFlashChipMode(byte);
}

uint32_t EspClass::getSketchSize() {
    return ArduinoFakeInstance(EspClass, this)->getSketchSize();
}

String EspClass::getSketchMD5() {
    return ArduinoFakeInstance(EspClass, this)->getSketchMD5();
}

uint32_t EspClass::getFreeSketchSpace() {
    return ArduinoFakeInstance(EspClass, this)->getFreeSketchSpace();
}

bool EspClass::flashEraseSector(uint32_t sector) {
    return ArduinoFakeInstance(EspClass, this)->flashEraseSector(sector);
}

bool EspClass::flashWrite(uint32_t offset, uint32_t *data, size_t size) {
    return ArduinoFakeInstance(EspClass, this)->flashWrite(offset, data, size);
}

bool EspClass::flashRead(uint32_t offset, uint32_t *data, size_t size) {
    return ArduinoFakeInstance(EspClass, this)->flashRead(offset, data, size);
}

bool EspClass::partitionEraseRange(const esp_partition_t *partition, uint32_t offset, size_t size) {
    return ArduinoFakeInstance(EspClass, this)->partitionEraseRange(partition, offset, size);
}

bool EspClass::partitionWrite(const esp_partition_t *partition, uint32_t offset, uint32_t *data, size_t size) {
    return ArduinoFakeInstance(EspClass, this)->partitionWrite(partition, offset, data, size);
}

bool EspClass::partitionRead(const esp_partition_t *partition, uint32_t offset, uint32_t *data, size_t size) {
    return ArduinoFakeInstance(EspClass, this)->partitionRead(partition, offset, data, size);
}

uint64_t EspClass::getEfuseMac() {
    return ArduinoFakeInstance(EspClass, this)->getEfuseMac();
}

EspClass ESP = EspClassFakeProxy(ArduinoFakeInstance(EspClass));
