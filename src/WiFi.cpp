#include "ArduinoFake.h"
#include "WiFi.h"

wl_status_t WiFiClass::begin(const char* ssid, const char *passphrase, int32_t channel, const uint8_t* bssid, bool connect)    
{
    return ArduinoFakeInstance(WiFiClass, this)->begin(ssid, passphrase, channel, bssid, connect);
}

wl_status_t WiFiClass::begin(char* ssid, char *passphrase, int32_t channel, const uint8_t* bssid, bool connect)    
{
    return ArduinoFakeInstance(WiFiClass, this)->begin(ssid, passphrase, channel, bssid, connect);
}

wl_status_t WiFiClass::begin()    
{
    return ArduinoFakeInstance(WiFiClass, this)->begin();
}

bool WiFiClass::disconnect(bool wifioff, bool eraseap)    
{
    return ArduinoFakeInstance(WiFiClass, this)->disconnect(wifioff, eraseap);
}

bool WiFiClass::softAP(const char* ssid, const char* passphrase, int channel, int ssid_hidden, int max_connection)    
{
    return ArduinoFakeInstance(WiFiClass, this)->softAP(ssid, passphrase, channel, ssid_hidden, max_connection);
}
bool WiFiClass::softAPdisconnect(bool wifioff)    
{
    return ArduinoFakeInstance(WiFiClass, this)->softAPdisconnect(wifioff);
}
IPAddress WiFiClass::softAPIP()    
{
    return ArduinoFakeInstance(WiFiClass, this)->softAPIP();
}

bool WiFiClass::setHostname(const char * hostname)   
{
    return ArduinoFakeInstance(WiFiClass, this)->setHostname(hostname);
}

bool WiFiClass::mode(wifi_mode_t mode)    
{
    return ArduinoFakeInstance(WiFiClass, this)->mode(mode);
}

wifi_mode_t WiFiClass::getMode()
{
    return ArduinoFakeInstance(WiFiClass, this)->getMode();
}

bool WiFiClass::setAutoConnect(bool autoConnect)    
{
    return ArduinoFakeInstance(WiFiClass, this)->setAutoConnect(autoConnect);
}

bool WiFiClass::getAutoConnect()    
{
    return ArduinoFakeInstance(WiFiClass, this)->getAutoConnect();
}

IPAddress WiFiClass::localIP()    
{
    return ArduinoFakeInstance(WiFiClass, this)->localIP();
}

void WiFiClass::persistent(bool persistent)    
{
    ArduinoFakeInstance(WiFiClass, this)->persistent(persistent);
}


wifi_event_id_t WiFiClass::onEvent(WiFiEventFuncCb cbEvent, system_event_id_t event)
{
    return ArduinoFakeInstance(WiFiClass, this)->onEvent(cbEvent, event);
}

WiFiClass WiFi = WiFiClassFakeProxy(ArduinoFakeInstance(WiFiClass));