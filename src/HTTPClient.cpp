#include "ArduinoFake.h"
#include "HTTPClient.h"

bool HTTPClient::begin(String url)
{
    return ArduinoFakeInstance(HTTPClient, this)->begin(url);
}

bool HTTPClient::begin(String url, const char* CAcert)
{
    return ArduinoFakeInstance(HTTPClient, this)->begin(url, CAcert);
}

bool HTTPClient::begin(String host, uint16_t port, String uri)
{
    return ArduinoFakeInstance(HTTPClient, this)->begin(host, port, uri);
}

bool HTTPClient::begin(String host, uint16_t port, String uri, const char* CAcert)
{
    return ArduinoFakeInstance(HTTPClient, this)->begin(host, port, uri, CAcert);
}

bool HTTPClient::begin(String host, uint16_t port, String uri, const char* CAcert, const char* cli_cert, const char* cli_key)
{
    return ArduinoFakeInstance(HTTPClient, this)->begin(host, port, uri, CAcert, cli_cert, cli_key);
}
    
void HTTPClient::end(void)
{
    ArduinoFakeInstance(HTTPClient, this)->end();
}

bool HTTPClient::connected(void)
{
    return ArduinoFakeInstance(HTTPClient, this)->connected();
}

void HTTPClient::setReuse(bool reuse)
{
    ArduinoFakeInstance(HTTPClient, this)->setReuse(reuse);
}

void HTTPClient::setUserAgent(const String& userAgent)
{
    ArduinoFakeInstance(HTTPClient, this)->setUserAgent(userAgent);
}

void HTTPClient::setAuthorization(const char * user, const char * password)
{
    ArduinoFakeInstance(HTTPClient, this)->setAuthorization(user, password);
}

void HTTPClient::setAuthorization(const char * auth)
{
    ArduinoFakeInstance(HTTPClient, this)->setAuthorization(auth);
}

void HTTPClient::setConnectTimeout(int32_t connectTimeout)
{
    ArduinoFakeInstance(HTTPClient, this)->setConnectTimeout(connectTimeout);
}

void HTTPClient::setTimeout(uint16_t timeout)
{
    ArduinoFakeInstance(HTTPClient, this)->setTimeout(timeout);
}

void HTTPClient::setFollowRedirects(followRedirects_t follow)
{
    ArduinoFakeInstance(HTTPClient, this)->setFollowRedirects(follow);
}

void HTTPClient::setRedirectLimit(uint16_t limit)
{
    ArduinoFakeInstance(HTTPClient, this)->setRedirectLimit(limit);
}

bool HTTPClient::setURL(const String &url){
    return ArduinoFakeInstance(HTTPClient, this)->setURL(url);
}

void HTTPClient::useHTTP10(bool usehttp10)
{
    ArduinoFakeInstance(HTTPClient, this)->useHTTP10(usehttp10);
}

int HTTPClient::GET()
{
    return ArduinoFakeInstance(HTTPClient, this)->GET();
}

int HTTPClient::PATCH(uint8_t * payload, size_t size)
{
    return ArduinoFakeInstance(HTTPClient, this)->PATCH(payload, size);
}

int HTTPClient::PATCH(String payload)
{
    return ArduinoFakeInstance(HTTPClient, this)->PATCH(payload);
}

int HTTPClient::POST(uint8_t * payload, size_t size)
{
    return ArduinoFakeInstance(HTTPClient, this)->POST(payload, size);
}

int HTTPClient::POST(String payload)
{
    return ArduinoFakeInstance(HTTPClient, this)->POST(payload);
}

int HTTPClient::PUT(uint8_t * payload, size_t size)
{
    return ArduinoFakeInstance(HTTPClient, this)->PUT(payload, size);
}

int HTTPClient::PUT(String payload)
{
    return ArduinoFakeInstance(HTTPClient, this)->PUT(payload);
}

int HTTPClient::sendRequest(const char * type, String payload)
{
    return ArduinoFakeInstance(HTTPClient, this)->sendRequest(type, payload);
}

int HTTPClient::sendRequest(const char * type, uint8_t * payload, size_t size)
{
   return ArduinoFakeInstance(HTTPClient, this)->sendRequest(type, payload, size);
}

int HTTPClient::sendRequest(const char * type, Stream * stream, size_t size)
{
    return ArduinoFakeInstance(HTTPClient, this)->sendRequest(type, stream, size);
}

void HTTPClient::addHeader(const String& name, const String& value, bool first, bool replace)
{
    ArduinoFakeInstance(HTTPClient, this)->addHeader(name, value, first, replace);
}

void HTTPClient::collectHeaders(const char* headerKeys[], const size_t headerKeysCount)
{
    ArduinoFakeInstance(HTTPClient, this)->collectHeaders(headerKeys, headerKeysCount);
}

String HTTPClient::header(const char* name)
{
    return ArduinoFakeInstance(HTTPClient, this)->header(name);
}

String HTTPClient::header(size_t i)
{
    return ArduinoFakeInstance(HTTPClient, this)->header(i);
}

String HTTPClient::headerName(size_t i)
{
    return ArduinoFakeInstance(HTTPClient, this)->headerName(i);
}

int HTTPClient::headers()
{
    return ArduinoFakeInstance(HTTPClient, this)->headers();
}

bool HTTPClient::hasHeader(const char* name)
{
    return ArduinoFakeInstance(HTTPClient, this)->hasHeader(name);
}


int HTTPClient::getSize(void)
{
    return ArduinoFakeInstance(HTTPClient, this)->getSize();
}

const String &HTTPClient::getLocation(void)
{
    return ArduinoFakeInstance(HTTPClient, this)->getLocation();
}

int HTTPClient::writeToStream(Stream* stream)
{
    return ArduinoFakeInstance(HTTPClient, this)->writeToStream(stream);
}

String HTTPClient::getString(void)
{
    return ArduinoFakeInstance(HTTPClient, this)->getString();
}

String HTTPClient::errorToString(int error)
{
    return ArduinoFakeInstance(HTTPClient, this)->errorToString(error);
}
