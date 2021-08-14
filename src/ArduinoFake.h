#pragma once

#if !defined(UBRRH) && !defined(UBRR0H) && !defined(USBCON)
    #define USBCON
#endif

#include <map>
#include <cstring>
#include <cstdint>
#include <stdexcept>
#include "fakeit/fakeit.hpp"

#include "arduino/Arduino.h"
#include "mqtt_client.h"

#include "FunctionFake.h"
#include "StreamFake.h"
#include "SerialFake.h"
#include "ClientFake.h"
#include "PrintFake.h"
#include "Wire.h"
#include "SPI.h"
#include "WiFi.h"
#include "HTTPClient.h"
#include "AsyncMqttClient.h"
#include "WiFiClient.h"
#include "Esp.h"
#include "DNSServer.h"
//#include "WiFiClientSecure.h"
#include "WebServer.h"

#define ArduinoFake(mock) _ArduinoFakeGet##mock()

#define ArduinoFakeReset() \
    getArduinoFakeContext()->reset()

#define ArduinoFakeInstance(mock, ...) \
    getArduinoFakeContext()->mock(__VA_ARGS__)

#define ArduinoFakeMock(mock) \
    new mock##FakeProxy(ArduinoFakeInstance(mock))

#define _ArduinoFakeGetMock(mock) \
    getArduinoFakeContext()->Mocks->mock

#define _ArduinoFakeGetFunction() _ArduinoFakeGetMock(Function)
#define _ArduinoFakeGetSerial() _ArduinoFakeGetMock(Serial)
#define _ArduinoFakeGetStream() _ArduinoFakeGetMock(Stream)
#define _ArduinoFakeGetClient() _ArduinoFakeGetMock(Client)
#define _ArduinoFakeGetPrint() _ArduinoFakeGetMock(Print)
#define _ArduinoFakeGetSPIClass() _ArduinoFakeGetMock(SPIClass)
#define _ArduinoFakeGetTwoWire() _ArduinoFakeGetMock(TwoWire)
#define _ArduinoFakeGetEspClass() _ArduinoFakeGetMock(EspClass)
#define _ArduinoFakeGetHTTPClient() _ArduinoFakeGetMock(HTTPClient)
#define _ArduinoFakeGetAsyncMqttClient() _ArduinoFakeGetMock(AsyncMqttClient)
#define _ArduinoFakeGetWiFiClient() _ArduinoFakeGetMock(WiFiClient)
//#define _ArduinoFakeGetWiFiClientSecure() _ArduinoFakeGetMock(WiFiClientSecure)
#define _ArduinoFakeGetWebServer() _ArduinoFakeGetMock(WebServer)
#define _ArduinoFakeGetDNSServer() _ArduinoFakeGetMock(DNSServer)
#define _ArduinoFakeGetWiFiClass() _ArduinoFakeGetMock(WiFiClass)
#define _ArduinoFakeGet() _ArduinoFakeGetMock(Function)

#define _ArduinoFakeInstanceGetter1(mock) \
    mock##Fake* mock() \
    { \
        if (!this->Instances->mock){ \
            this->Instances->mock = &this->Mocks->mock.get(); \
        } \
        return this->Instances->mock; \
    }

#define _ArduinoFakeInstanceGetter2(name, clazz) \
    name##Fake* name(class clazz* instance) \
    { \
        if (Mapping[instance]) { \
            return (name##Fake*) Mapping[instance]; \
        } \
        if (dynamic_cast<name##FakeProxy*>(instance)) { \
            return dynamic_cast<name##FakeProxy*>(instance)->get##name##Fake(); \
        } \
        throw std::runtime_error("Unknown instance"); \
    }

struct ArduinoFakeMocks
{
    fakeit::Mock<FunctionFake> Function;
    fakeit::Mock<SerialFake> Serial;
    fakeit::Mock<StreamFake> Stream;
    fakeit::Mock<ClientFake> Client;
    fakeit::Mock<PrintFake> Print;
    fakeit::Mock<TwoWireFake> TwoWire;
    fakeit::Mock<SPIClassFake> SPIClass;
    fakeit::Mock<EspClassFake> EspClass;
    fakeit::Mock<HTTPClientFake> HTTPClient;
    fakeit::Mock<AsyncMqttClientFake> AsyncMqttClient;
    fakeit::Mock<WiFiClientFake> WiFiClient;
    //fakeit::Mock<WiFiClientSecureFake> WiFiClientSecure;
    fakeit::Mock<WebServerFake> WebServer;
    fakeit::Mock<DNSServerFake> DNSServer;
    fakeit::Mock<WiFiClassFake> WiFiClass;
};

struct ArduinoFakeInstances
{
    FunctionFake* Function;
    SerialFake* Serial;
    StreamFake* Stream;
    ClientFake* Client;
    PrintFake* Print;
    TwoWireFake* TwoWire;
    SPIClassFake* SPIClass;
    EspClassFake* EspClass;
    HTTPClientFake* HTTPClient;
    AsyncMqttClientFake* AsyncMqttClient;
    WiFiClientFake* WiFiClient;
    //WiFiClientSecureFake* WiFiClientSecure;
    WebServerFake* WebServer;
    DNSServerFake* DNSServer;
    WiFiClassFake* WiFiClass;
};

class ArduinoFakeContext
{
    public:
        ArduinoFakeInstances* Instances = new ArduinoFakeInstances();
        ArduinoFakeMocks* Mocks = new ArduinoFakeMocks();
        std::map<void*, void*> Mapping;

        _ArduinoFakeInstanceGetter1(Print)
        _ArduinoFakeInstanceGetter1(Stream)
        _ArduinoFakeInstanceGetter1(Serial)
        _ArduinoFakeInstanceGetter1(Client)
        _ArduinoFakeInstanceGetter1(Function)
        _ArduinoFakeInstanceGetter1(TwoWire)
        _ArduinoFakeInstanceGetter1(SPIClass)
        _ArduinoFakeInstanceGetter1(EspClass)
        _ArduinoFakeInstanceGetter1(HTTPClient)
        _ArduinoFakeInstanceGetter1(AsyncMqttClient)
        _ArduinoFakeInstanceGetter1(WiFiClient)
        //_ArduinoFakeInstanceGetter1(WiFiClientSecure)
        _ArduinoFakeInstanceGetter1(WebServer)
        _ArduinoFakeInstanceGetter1(DNSServer)
        _ArduinoFakeInstanceGetter1(WiFiClass)

        _ArduinoFakeInstanceGetter2(Print, Print)
        _ArduinoFakeInstanceGetter2(Client, Client)
        _ArduinoFakeInstanceGetter2(Stream, Stream)
        _ArduinoFakeInstanceGetter2(Serial, Serial_)
        _ArduinoFakeInstanceGetter2(TwoWire, TwoWire)
        _ArduinoFakeInstanceGetter2(SPIClass, SPIClass)
        _ArduinoFakeInstanceGetter2(EspClass, EspClass)
        _ArduinoFakeInstanceGetter2(HTTPClient, HTTPClient)
        _ArduinoFakeInstanceGetter2(AsyncMqttClient, AsyncMqttClient)
        _ArduinoFakeInstanceGetter2(WiFiClient, WiFiClient)
        //_ArduinoFakeInstanceGetter2(WiFiClientSecure, WiFiClientSecure)
        _ArduinoFakeInstanceGetter2(WebServer, WebServer)
        _ArduinoFakeInstanceGetter2(DNSServer, DNSServer)
        _ArduinoFakeInstanceGetter2(WiFiClass, WiFiClass)

        ArduinoFakeContext()
        {
            this->reset();
        }

        void reset(void)
        {
            this->Instances = new ArduinoFakeInstances();

            this->Mocks->Function.Reset();
            this->Mocks->Stream.Reset();
            this->Mocks->Serial.Reset();
            this->Mocks->Client.Reset();
            this->Mocks->Print.Reset();
            this->Mocks->TwoWire.Reset();
            this->Mocks->SPIClass.Reset();
            this->Mocks->EspClass.Reset();
            this->Mocks->WiFiClass.Reset();

            Mapping[&::Serial] = this->Serial();
            Mapping[&::Wire] = this->TwoWire();
            Mapping[&::SPI] = this->SPIClass();
            Mapping[&::ESP] = this->EspClass();
            Mapping[&::WiFi] = this->WiFiClass();

        }
};

ArduinoFakeContext* getArduinoFakeContext();
