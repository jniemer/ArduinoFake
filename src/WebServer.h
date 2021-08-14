/*
  WebServer.h - Dead simple web-server.
  Supports only one simultaneous client, knows how to handle GET and POST.

  Copyright (c) 2014 Ivan Grokhotkov. All rights reserved.

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
  Modified 8 May 2015 by Hristo Gochkov (proper post and file upload handling)
*/


#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <functional>
#include <memory>
#include "webserver/HTTP_Method.h"
#include "webserver/Uri.h"

enum HTTPUploadStatus { UPLOAD_FILE_START, UPLOAD_FILE_WRITE, UPLOAD_FILE_END,
                        UPLOAD_FILE_ABORTED };
enum HTTPClientStatus { HC_NONE, HC_WAIT_READ, HC_WAIT_CLOSE };
enum HTTPAuthMethod { BASIC_AUTH, DIGEST_AUTH };

#define HTTP_DOWNLOAD_UNIT_SIZE 1436

#ifndef HTTP_UPLOAD_BUFLEN
#define HTTP_UPLOAD_BUFLEN 1436
#endif

#define HTTP_MAX_DATA_WAIT 5000 //ms to wait for the client to send the request
#define HTTP_MAX_POST_WAIT 5000 //ms to wait for POST data to arrive
#define HTTP_MAX_SEND_WAIT 5000 //ms to wait for data chunk to be ACKed
#define HTTP_MAX_CLOSE_WAIT 2000 //ms to wait for the client to close the connection

#define CONTENT_LENGTH_UNKNOWN ((size_t) -1)
#define CONTENT_LENGTH_NOT_SET ((size_t) -2)

class WebServer;

typedef struct {
  HTTPUploadStatus status;
  String  filename;
  String  name;
  String  type;
  size_t  totalSize;    // file size
  size_t  currentSize;  // size of data currently in buf
  uint8_t buf[HTTP_UPLOAD_BUFLEN];
} HTTPUpload;

#include "webserver/RequestHandler.h"

namespace fs {
class FS;
}

class WebServer
{
public:
  WebServer(IPAddress addr, int port = 80);
  WebServer(int port = 80);
  virtual ~WebServer();

  virtual void begin();
  virtual void begin(uint16_t port);
  virtual void handleClient();

  virtual void close();
  virtual void stop();

  virtual bool authenticate(const char * username, const char * password);
  virtual void requestAuthentication(HTTPAuthMethod mode = BASIC_AUTH, const char* realm = NULL, const String& authFailMsg = String("") );

  typedef std::function<void(void)> THandlerFunction;
  virtual void on(const Uri &uri, THandlerFunction handler);
  virtual void on(const Uri &uri, HTTPMethod method, THandlerFunction fn);
  virtual void on(const Uri &uri, HTTPMethod method, THandlerFunction fn, THandlerFunction ufn);
  virtual void addHandler(RequestHandler* handler);
  virtual void serveStatic(const char* uri, fs::FS& fs, const char* path, const char* cache_header = NULL );
  virtual void onNotFound(THandlerFunction fn);  //called when handler is not assigned
  virtual void onFileUpload(THandlerFunction fn); //handle file uploads

  virtual String uri();
  virtual HTTPMethod method();
  virtual WiFiClient client();
  virtual HTTPUpload& upload();

  virtual String pathArg(unsigned int i); // get request path argument by number
  virtual String arg(String name);        // get request argument value by name
  virtual String arg(int i);              // get request argument value by number
  virtual String argName(int i);          // get request argument name by number
  virtual int args();                     // get arguments count
  virtual bool hasArg(String name);       // check if argument exists
  virtual void collectHeaders(const char* headerKeys[], const size_t headerKeysCount); // set the request headers to collect
  virtual String header(String name);      // get request header value by name
  virtual String header(int i);              // get request header value by number
  virtual String headerName(int i);          // get request header name by number
  virtual int headers();                     // get header count
  virtual bool hasHeader(String name);       // check if header exists

  virtual String hostHeader();            // get request host header if available or empty String if not

  // send response to the client
  // code - HTTP response code, can be 200 or 404
  // content_type - HTTP content type, like "text/plain" or "image/png"
  // content - actual content body
  virtual void send(int code, const char* content_type = NULL, const String& content = String(""));
  virtual void send(int code, char* content_type, const String& content);
  virtual void send(int code, const String& content_type, const String& content);
  virtual void send_P(int code, PGM_P content_type, PGM_P content);
  virtual void send_P(int code, PGM_P content_type, PGM_P content, size_t contentLength);

  virtual void enableDelay(boolean value);
  virtual void enableCORS(boolean value = true);
  virtual void enableCrossOrigin(boolean value = true);

  virtual void setContentLength(const size_t contentLength);
  virtual void sendHeader(const String& name, const String& value, bool first = false);
  virtual void sendContent(const String& content);
  virtual void sendContent(const char* content, size_t contentLength);
  virtual void sendContent_P(PGM_P content);
  virtual void sendContent_P(PGM_P content, size_t size);

  virtual String urlDecode(const String& text);

/*  template<typename T>
  size_t streamFile(T &file, const String& contentType) {
    _streamFileCore(file.size(), file.name(), contentType);
    return _currentClient.write(file);
  }*/
};

class WebServerFake
{
public:

  virtual void begin() = 0;
  virtual void begin(uint16_t port) = 0;
  virtual void handleClient() = 0;

  virtual void close() = 0;
  virtual void stop() = 0;

  virtual bool authenticate(const char * username, const char * password) = 0;
  virtual void requestAuthentication(HTTPAuthMethod mode = BASIC_AUTH, const char* realm = NULL, const String& authFailMsg = String("") ) = 0;

  typedef std::function<void(void)> THandlerFunction;
  virtual void on(const Uri &uri, THandlerFunction handler) = 0;
  virtual void on(const Uri &uri, HTTPMethod method, THandlerFunction fn) = 0;
  virtual void on(const Uri &uri, HTTPMethod method, THandlerFunction fn, THandlerFunction ufn) = 0;
  virtual void addHandler(RequestHandler* handler) = 0;
  virtual void serveStatic(const char* uri, fs::FS& fs, const char* path, const char* cache_header = NULL ) = 0;
  virtual void onNotFound(THandlerFunction fn) = 0;  //called when handler is not assigned
  virtual void onFileUpload(THandlerFunction fn) = 0; //handle file uploads

  virtual String uri() = 0;
  virtual HTTPMethod method() = 0;
  virtual WiFiClient client()= 0;
  virtual HTTPUpload& upload() = 0;

  virtual String pathArg(unsigned int i) = 0; // get request path argument by number
  virtual String arg(String name) = 0;        // get request argument value by name
  virtual String arg(int i) = 0;              // get request argument value by number
  virtual String argName(int i) = 0;          // get request argument name by number
  virtual int args() = 0;                     // get arguments count
  virtual bool hasArg(String name) = 0;       // check if argument exists
  virtual void collectHeaders(const char* headerKeys[], const size_t headerKeysCount) = 0; // set the request headers to collect
  virtual String header(String name) = 0;      // get request header value by name
  virtual String header(int i) = 0;              // get request header value by number
  virtual String headerName(int i) = 0;          // get request header name by number
  virtual int headers() = 0;                     // get header count
  virtual bool hasHeader(String name) = 0;       // check if header exists

  virtual String hostHeader() = 0;            // get request host header if available or empty String if not

  // send response to the client
  // code - HTTP response code, can be 200 or 404
  // content_type - HTTP content type, like "text/plain" or "image/png"
  // content - actual content body
  virtual void send(int code, const char* content_type = NULL, const String& content = String("")) = 0;
  virtual void send(int code, char* content_type, const String& content) = 0;
  virtual void send(int code, const String& content_type, const String& content) = 0;
  virtual void send_P(int code, PGM_P content_type, PGM_P content) = 0;
  virtual void send_P(int code, PGM_P content_type, PGM_P content, size_t contentLength) = 0;

  virtual void enableDelay(boolean value) = 0;
  virtual void enableCORS(boolean value = true) = 0;
  virtual void enableCrossOrigin(boolean value = true) = 0;

  virtual void setContentLength(const size_t contentLength) = 0;
  virtual void sendHeader(const String& name, const String& value, bool first = false) = 0;
  virtual void sendContent(const String& content) = 0;
  virtual void sendContent(const char* content, size_t contentLength) = 0;
  virtual void sendContent_P(PGM_P content) = 0;
  virtual void sendContent_P(PGM_P content, size_t size) = 0;

  virtual String urlDecode(const String& text) = 0;

/*  template<typename T>
  size_t streamFile(T &file, const String& contentType) {
    _streamFileCore(file.size(), file.name(), contentType);
    return _currentClient.write(file);
  }*/
};



class WebServerFakeProxy : public WebServer
{
    private:
        WebServerFake* wsFake;

    public:
        WebServerFakeProxy(WebServerFake* fake)
        {
            wsFake = fake;
        }

        WebServerFake* getWebServerFake()
        {
            return wsFake;
        }
};


#endif /* WEBSERVER_H */
