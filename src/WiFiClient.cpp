#include "ArduinoFake.h"
#include "WiFiClient.h"

int  WiFiClient::connect(IPAddress ip, uint16_t port)
{
    return ArduinoFakeInstance(WiFiClient, this)->connect(ip, port);
}

int  WiFiClient::connect(IPAddress ip, uint16_t port, int32_t timeout)
{
    return ArduinoFakeInstance(WiFiClient, this)->connect(ip, port, timeout);
}

int  WiFiClient::connect(const char *host, uint16_t port)
{
    return ArduinoFakeInstance(WiFiClient, this)->connect(host, port);
}

int  WiFiClient::connect(const char *host, uint16_t port, int32_t timeout)
{
    return ArduinoFakeInstance(WiFiClient, this)->connect(host, port, timeout);
}

size_t  WiFiClient::write(uint8_t data)
{
    return ArduinoFakeInstance(WiFiClient, this)->write(data);
}

size_t  WiFiClient::write(const uint8_t *buf, size_t size)
{
    return ArduinoFakeInstance(WiFiClient, this)->write(buf, size);
}

size_t  WiFiClient::write_P(PGM_P buf, size_t size)
{
    return ArduinoFakeInstance(WiFiClient, this)->write_P(buf, size);
}

size_t  WiFiClient::write(Stream &stream)
{
    return ArduinoFakeInstance(WiFiClient, this)->write(stream);
}

int  WiFiClient::available()
{
    return ArduinoFakeInstance(WiFiClient, this)->available();
}

int  WiFiClient::read()
{
    return ArduinoFakeInstance(WiFiClient, this)->read();
}

int  WiFiClient::read(uint8_t *buf, size_t size)
{
    return ArduinoFakeInstance( WiFiClient, this)->read(buf, size);
}

int  WiFiClient::peek()
{
    return ArduinoFakeInstance( WiFiClient, this)->peek();
}

void  WiFiClient::flush()
{
    ArduinoFakeInstance( WiFiClient, this)->flush();
}

void  WiFiClient::stop()
{
    ArduinoFakeInstance( WiFiClient, this)->stop();
}

uint8_t  WiFiClient::connected()
{
    return ArduinoFakeInstance( WiFiClient, this)->connected();
}

int  WiFiClient::fd()
{
    return ArduinoFakeInstance( WiFiClient, this)->fd();
}


int  WiFiClient::setSocketOption(int option, char* value, size_t len)
{
    return ArduinoFakeInstance( WiFiClient, this)->setSocketOption(option, value, len);
}

int  WiFiClient::setOption(int option, int *value)
{
    return ArduinoFakeInstance( WiFiClient, this)->setOption(option, value);
}

int  WiFiClient::getOption(int option, int *value)
{
    return ArduinoFakeInstance( WiFiClient, this)->getOption(option, value);
}

int  WiFiClient::setTimeout(uint32_t seconds)
{
    return ArduinoFakeInstance( WiFiClient, this)->setTimeout(seconds);
}

int  WiFiClient::setNoDelay(bool nodelay)
{
    return ArduinoFakeInstance( WiFiClient, this)->setNoDelay(nodelay);
}

bool  WiFiClient::getNoDelay()
{
    return ArduinoFakeInstance( WiFiClient, this)->getNoDelay();
}


IPAddress  WiFiClient::remoteIP()
{
    return ArduinoFakeInstance( WiFiClient, this)->remoteIP();
}

IPAddress  WiFiClient::remoteIP(int fd)
{
    return ArduinoFakeInstance( WiFiClient, this)->remoteIP(fd);
}

uint16_t  WiFiClient::remotePort()
{
    return ArduinoFakeInstance( WiFiClient, this)->remotePort();
}

uint16_t  WiFiClient::remotePort(int fd)
{
    return ArduinoFakeInstance( WiFiClient, this)->remotePort(fd);
}

IPAddress  WiFiClient::localIP()
{
    return ArduinoFakeInstance( WiFiClient, this)->localIP();
}

IPAddress  WiFiClient::localIP(int fd)
{
    return ArduinoFakeInstance( WiFiClient, this)->localIP(fd);
}

uint16_t  WiFiClient::localPort()
{
    return ArduinoFakeInstance( WiFiClient, this)->localPort();
}

uint16_t  WiFiClient::localPort(int fd)
{
    return ArduinoFakeInstance( WiFiClient, this)->localPort(fd);
}
