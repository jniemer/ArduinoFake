#include "ArduinoFake.h"
#include "WiFiClient.h"

void DNSServer::processNextRequest() 
{
    ArduinoFakeInstance(DNSServer, this)->processNextRequest();
}

void DNSServer::setErrorReplyCode(const DNSReplyCode &replyCode)
{
    ArduinoFakeInstance(DNSServer, this)->setErrorReplyCode(replyCode);
}

void DNSServer::setTTL(const uint32_t &ttl)
{
    ArduinoFakeInstance(DNSServer, this)->setTTL(ttl);
}

bool DNSServer::start(const uint16_t &port, const String &domainName, const IPAddress &resolvedIP)
{
    return ArduinoFakeInstance(DNSServer, this)->start(port, domainName, resolvedIP);
}

void DNSServer::stop()
{
    ArduinoFakeInstance(DNSServer, this)->stop();
}