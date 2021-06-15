#pragma once

/**
 * HTTPClient.h
 *
 * Created on: 02.11.2015
 *
 * Copyright (c) 2015 Markus Sattler. All rights reserved.
 * This file is part of the HTTPClient for Arduino.
 * Port to ESP32 by Evandro Luis Copercini (2017), 
 * changed fingerprints to CA verification. 	
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <ArduinoFake.h>

/// HTTP client errors
#define HTTPC_ERROR_CONNECTION_REFUSED  (-1)
#define HTTPC_ERROR_SEND_HEADER_FAILED  (-2)
#define HTTPC_ERROR_SEND_PAYLOAD_FAILED (-3)
#define HTTPC_ERROR_NOT_CONNECTED       (-4)
#define HTTPC_ERROR_CONNECTION_LOST     (-5)
#define HTTPC_ERROR_NO_STREAM           (-6)
#define HTTPC_ERROR_NO_HTTP_SERVER      (-7)
#define HTTPC_ERROR_TOO_LESS_RAM        (-8)
#define HTTPC_ERROR_ENCODING            (-9)
#define HTTPC_ERROR_STREAM_WRITE        (-10)
#define HTTPC_ERROR_READ_TIMEOUT        (-11)

/// size for the stream handling
#define HTTP_TCP_BUFFER_SIZE (1460)

/// HTTP codes see RFC7231
typedef enum {
    HTTP_CODE_CONTINUE = 100,
    HTTP_CODE_SWITCHING_PROTOCOLS = 101,
    HTTP_CODE_PROCESSING = 102,
    HTTP_CODE_OK = 200,
    HTTP_CODE_CREATED = 201,
    HTTP_CODE_ACCEPTED = 202,
    HTTP_CODE_NON_AUTHORITATIVE_INFORMATION = 203,
    HTTP_CODE_NO_CONTENT = 204,
    HTTP_CODE_RESET_CONTENT = 205,
    HTTP_CODE_PARTIAL_CONTENT = 206,
    HTTP_CODE_MULTI_STATUS = 207,
    HTTP_CODE_ALREADY_REPORTED = 208,
    HTTP_CODE_IM_USED = 226,
    HTTP_CODE_MULTIPLE_CHOICES = 300,
    HTTP_CODE_MOVED_PERMANENTLY = 301,
    HTTP_CODE_FOUND = 302,
    HTTP_CODE_SEE_OTHER = 303,
    HTTP_CODE_NOT_MODIFIED = 304,
    HTTP_CODE_USE_PROXY = 305,
    HTTP_CODE_TEMPORARY_REDIRECT = 307,
    HTTP_CODE_PERMANENT_REDIRECT = 308,
    HTTP_CODE_BAD_REQUEST = 400,
    HTTP_CODE_UNAUTHORIZED = 401,
    HTTP_CODE_PAYMENT_REQUIRED = 402,
    HTTP_CODE_FORBIDDEN = 403,
    HTTP_CODE_NOT_FOUND = 404,
    HTTP_CODE_METHOD_NOT_ALLOWED = 405,
    HTTP_CODE_NOT_ACCEPTABLE = 406,
    HTTP_CODE_PROXY_AUTHENTICATION_REQUIRED = 407,
    HTTP_CODE_REQUEST_TIMEOUT = 408,
    HTTP_CODE_CONFLICT = 409,
    HTTP_CODE_GONE = 410,
    HTTP_CODE_LENGTH_REQUIRED = 411,
    HTTP_CODE_PRECONDITION_FAILED = 412,
    HTTP_CODE_PAYLOAD_TOO_LARGE = 413,
    HTTP_CODE_URI_TOO_LONG = 414,
    HTTP_CODE_UNSUPPORTED_MEDIA_TYPE = 415,
    HTTP_CODE_RANGE_NOT_SATISFIABLE = 416,
    HTTP_CODE_EXPECTATION_FAILED = 417,
    HTTP_CODE_MISDIRECTED_REQUEST = 421,
    HTTP_CODE_UNPROCESSABLE_ENTITY = 422,
    HTTP_CODE_LOCKED = 423,
    HTTP_CODE_FAILED_DEPENDENCY = 424,
    HTTP_CODE_UPGRADE_REQUIRED = 426,
    HTTP_CODE_PRECONDITION_REQUIRED = 428,
    HTTP_CODE_TOO_MANY_REQUESTS = 429,
    HTTP_CODE_REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
    HTTP_CODE_INTERNAL_SERVER_ERROR = 500,
    HTTP_CODE_NOT_IMPLEMENTED = 501,
    HTTP_CODE_BAD_GATEWAY = 502,
    HTTP_CODE_SERVICE_UNAVAILABLE = 503,
    HTTP_CODE_GATEWAY_TIMEOUT = 504,
    HTTP_CODE_HTTP_VERSION_NOT_SUPPORTED = 505,
    HTTP_CODE_VARIANT_ALSO_NEGOTIATES = 506,
    HTTP_CODE_INSUFFICIENT_STORAGE = 507,
    HTTP_CODE_LOOP_DETECTED = 508,
    HTTP_CODE_NOT_EXTENDED = 510,
    HTTP_CODE_NETWORK_AUTHENTICATION_REQUIRED = 511
} t_http_codes;

typedef enum {
    HTTPC_TE_IDENTITY,
    HTTPC_TE_CHUNKED
} transferEncoding_t;

/**
 * redirection follow mode.
 * + `HTTPC_DISABLE_FOLLOW_REDIRECTS` - no redirection will be followed.
 * + `HTTPC_STRICT_FOLLOW_REDIRECTS` - strict RFC2616, only requests using
 *      GET or HEAD methods will be redirected (using the same method),
 *      since the RFC requires end-user confirmation in other cases.
 * + `HTTPC_FORCE_FOLLOW_REDIRECTS` - all redirections will be followed,
 *      regardless of a used method. New request will use the same method,
 *      and they will include the same body data and the same headers.
 *      In the sense of the RFC, it's just like every redirection is confirmed.
 */
typedef enum {
    HTTPC_DISABLE_FOLLOW_REDIRECTS,
    HTTPC_STRICT_FOLLOW_REDIRECTS,
    HTTPC_FORCE_FOLLOW_REDIRECTS
} followRedirects_t;

class HTTPClient
{
public:
/*
 * Since both begin() functions take a reference to client as a parameter, you need to 
 * ensure the client object lives the entire time of the HTTPClient
 */
    //bool begin(WiFiClient &client, String url);
    //bool begin(WiFiClient &client, String host, uint16_t port, String uri = "/", bool https = false);
    virtual bool begin(String url);
    virtual bool begin(String url, const char* CAcert);
    virtual bool begin(String host, uint16_t port, String uri = "/");
    virtual bool begin(String host, uint16_t port, String uri, const char* CAcert);
    virtual bool begin(String host, uint16_t port, String uri, const char* CAcert, const char* cli_cert, const char* cli_key);
    
    virtual void end(void);

    virtual bool connected(void);

    virtual void setReuse(bool reuse); /// keep-alive
    virtual void setUserAgent(const String& userAgent);
    virtual void setAuthorization(const char * user, const char * password);
    virtual void setAuthorization(const char * auth);
    virtual void setConnectTimeout(int32_t connectTimeout);
    virtual void setTimeout(uint16_t timeout);

    // Redirections
    virtual void setFollowRedirects(followRedirects_t follow);
    virtual void setRedirectLimit(uint16_t limit); // max redirects to follow for a single request

    virtual bool setURL(const String &url);
    virtual void useHTTP10(bool usehttp10 = true);

    /// request handling
    virtual int GET();
    virtual int PATCH(uint8_t * payload, size_t size);
    virtual int PATCH(String payload);
    virtual int POST(uint8_t * payload, size_t size);
    virtual int POST(String payload);
    virtual int PUT(uint8_t * payload, size_t size);
    virtual int PUT(String payload);
    virtual int sendRequest(const char * type, String payload);
    virtual int sendRequest(const char * type, uint8_t * payload = NULL, size_t size = 0);
    virtual int sendRequest(const char * type, Stream * stream, size_t size = 0);

    virtual void addHeader(const String& name, const String& value, bool first = false, bool replace = true);

    /// Response handling
    virtual void collectHeaders(const char* headerKeys[], const size_t headerKeysCount);
    virtual String header(const char* name);   // get request header value by name
    virtual String header(size_t i);              // get request header value by number
    virtual String headerName(size_t i);          // get request header name by number
    virtual int headers();                     // get header count
    virtual bool hasHeader(const char* name);  // check if header exists


    virtual int getSize(void);
    virtual const String &getLocation(void);

    virtual int writeToStream(Stream* stream);
    virtual String getString(void);

    virtual String errorToString(int error);
};

struct HTTPClientFake
{

/*
 * Since both begin() functions take a reference to client as a parameter, you need to 
 * ensure the client object lives the entire time of the HTTPClient
 */
    //bool begin(WiFiClient &client, String url);
    //bool begin(WiFiClient &client, String host, uint16_t port, String uri = "/", bool https = false);
    virtual bool begin(String url) = 0;
    virtual bool begin(String url, const char* CAcert) = 0;
    virtual bool begin(String host, uint16_t port, String uri = "/") = 0;
    virtual bool begin(String host, uint16_t port, String uri, const char* CAcert) = 0;
    virtual bool begin(String host, uint16_t port, String uri, const char* CAcert, const char* cli_cert, const char* cli_key) = 0;
    
    virtual void end(void) = 0;

    virtual bool connected(void) = 0;

    virtual void setReuse(bool reuse) = 0; /// keep-alive
    virtual void setUserAgent(const String& userAgent) = 0;
    virtual void setAuthorization(const char * user, const char * password) = 0;
    virtual void setAuthorization(const char * auth) = 0;
    virtual void setConnectTimeout(int32_t connectTimeout) = 0;
    virtual void setTimeout(uint16_t timeout) = 0;

    // Redirections
    virtual void setFollowRedirects(followRedirects_t follow) = 0;
    virtual void setRedirectLimit(uint16_t limit) = 0; // max redirects to follow for a single request

    virtual bool setURL(const String &url) = 0;
    virtual void useHTTP10(bool usehttp10 = true) = 0;

    /// request handling
    virtual int GET() = 0;
    virtual int PATCH(uint8_t * payload, size_t size) = 0;
    virtual int PATCH(String payload) = 0;
    virtual int POST(uint8_t * payload, size_t size) = 0;
    virtual int POST(String payload) = 0;
    virtual int PUT(uint8_t * payload, size_t size) = 0;
    virtual int PUT(String payload) = 0;
    virtual int sendRequest(const char * type, String payload) = 0;
    virtual int sendRequest(const char * type, uint8_t * payload = NULL, size_t size = 0) = 0;
    virtual int sendRequest(const char * type, Stream * stream, size_t size = 0) = 0;

    virtual void addHeader(const String& name, const String& value, bool first = false, bool replace = true) = 0;

    /// Response handling
    virtual void collectHeaders(const char* headerKeys[], const size_t headerKeysCount) = 0;
    virtual String header(const char* name) = 0;   // get request header value by name
    virtual String header(size_t i) = 0;              // get request header value by number
    virtual String headerName(size_t i) = 0;          // get request header name by number
    virtual int headers() = 0;                     // get header count
    virtual bool hasHeader(const char* name) = 0;  // check if header exists


    virtual int getSize(void) = 0;
    virtual const String &getLocation(void) = 0;

    //virtual WiFiClient& getStream(void);
    //virtual WiFiClient* getStreamPtr(void);
    virtual int writeToStream(Stream* stream) = 0;
    virtual String getString(void) = 0;

    virtual String errorToString(int error) = 0;
};

class HTTPClientFakeProxy : public HTTPClient
{
    private:
        HTTPClientFake* httpFake;

    public:
        HTTPClientFakeProxy(HTTPClientFake* fake)
        {
            httpFake = fake;
        }

        HTTPClientFake* getHTTPClientFake()
        {
            return httpFake;
        }
};
