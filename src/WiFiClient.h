/*
  Client.h - Base class that provides Client
  Copyright (c) 2011 Adrian McEwen.  All right reserved.

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

#pragma once


#include "Arduino.h"

class WiFiClientSocketHandle;
class WiFiClientRxBuffer;

class WiFiClient
{

public:
    WiFiClient();
    virtual int connect(IPAddress ip, uint16_t port);
    virtual int connect(IPAddress ip, uint16_t port, int32_t timeout);
    virtual int connect(const char *host, uint16_t port);
    virtual int connect(const char *host, uint16_t port, int32_t timeout);
    virtual size_t write(uint8_t data);
    virtual size_t write(const uint8_t *buf, size_t size);
    virtual size_t write_P(PGM_P buf, size_t size);
    virtual size_t write(Stream &stream);
    virtual int available();
    virtual int read();
    virtual int read(uint8_t *buf, size_t size);
    virtual int peek();
    virtual void flush();
    virtual void stop();
    virtual uint8_t connected();

    virtual int fd();

    virtual int setSocketOption(int option, char* value, size_t len);
    virtual int setOption(int option, int *value);
    virtual int getOption(int option, int *value);
    virtual int setTimeout(uint32_t seconds);
    virtual int setNoDelay(bool nodelay);
    virtual bool getNoDelay();

    virtual IPAddress remoteIP();
    virtual IPAddress remoteIP(int fd);
    virtual uint16_t remotePort();
    virtual uint16_t remotePort(int fd);
    virtual IPAddress localIP();
    virtual IPAddress localIP(int fd);
    virtual uint16_t localPort();
    virtual uint16_t localPort(int fd);

    //friend class WiFiServer;
    //using Print::write;
};

struct WiFiClientFake
{

public:
    virtual int connect(IPAddress ip, uint16_t port) = 0;
    virtual int connect(IPAddress ip, uint16_t port, int32_t timeout) = 0;
    virtual int connect(const char *host, uint16_t port) = 0;
    virtual int connect(const char *host, uint16_t port, int32_t timeout) = 0;
    virtual size_t write(uint8_t data) = 0;
    virtual size_t write(const uint8_t *buf, size_t size) = 0;
    virtual size_t write_P(PGM_P buf, size_t size) = 0;
    virtual size_t write(Stream &stream) = 0;
    virtual int available() = 0;
    virtual int read() = 0;
    virtual int read(uint8_t *buf, size_t size) = 0;
    virtual int peek() = 0;
    virtual void flush() = 0;
    virtual void stop() = 0;
    virtual uint8_t connected() = 0;

    virtual int fd() = 0;

    virtual int setSocketOption(int option, char* value, size_t len) = 0;
    virtual int setOption(int option, int *value) = 0;
    virtual int getOption(int option, int *value) = 0;
    virtual int setTimeout(uint32_t seconds) = 0;
    virtual int setNoDelay(bool nodelay) = 0;
    virtual bool getNoDelay() = 0;

    virtual IPAddress remoteIP() = 0;
    virtual IPAddress remoteIP(int fd) = 0;
    virtual uint16_t remotePort() = 0;
    virtual uint16_t remotePort(int fd) = 0;
    virtual IPAddress localIP() = 0;
    virtual IPAddress localIP(int fd) = 0;
    virtual uint16_t localPort() = 0;
    virtual uint16_t localPort(int fd) = 0;

    //using PrintFake::write;
};

class WiFiClientFakeProxy : public WiFiClient
{
    private:
        WiFiClientFake* wcFake;

    public:
        WiFiClientFakeProxy(WiFiClientFake* fake)
        {
            wcFake = fake;
        }

        WiFiClientFake* getWiFiClientFake()
        {
            return wcFake;
        }
};
