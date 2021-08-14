#include "FunctionFake.h"
#include "ArduinoFake.h"

void pinMode(uint8_t pin, uint8_t mode)
{
    ArduinoFakeInstance(Function)->pinMode(pin, mode);
}

void digitalWrite(uint8_t pin, uint8_t val)
{
    ArduinoFakeInstance(Function)->digitalWrite(pin, val);
}

int digitalRead(uint8_t pin)
{
    return ArduinoFakeInstance(Function)->digitalRead(pin);
}

int analogRead(uint8_t pin)
{
    return ArduinoFakeInstance(Function)->analogRead(pin);
}

void analogWrite(uint8_t pin, int val)
{
    ArduinoFakeInstance(Function)->analogWrite(pin, val);
}

void analogReference(uint8_t mode)
{
    ArduinoFakeInstance(Function)->analogReference(mode);
}

unsigned long millis(void)
{
    return ArduinoFakeInstance(Function)->millis();
}

unsigned long micros(void)
{
    return ArduinoFakeInstance(Function)->micros();
}

void delay(unsigned long value)
{
    ArduinoFakeInstance(Function)->delay(value);
}

void delayMicroseconds(unsigned int us)
{
    ArduinoFakeInstance(Function)->delayMicroseconds(us);
}

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
    return ArduinoFakeInstance(Function)->pulseIn(pin, state, timeout);
}

unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout)
{
    return ArduinoFakeInstance(Function)->pulseInLong(pin, state, timeout);
}

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
    ArduinoFakeInstance(Function)->shiftOut(dataPin, clockPin, bitOrder, val);
}

uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
    return ArduinoFakeInstance(Function)->shiftIn(dataPin, clockPin, bitOrder);
}

void detachInterrupt(uint8_t interruptNum) {
    ArduinoFakeInstance(Function)->detachInterrupt(interruptNum);
}

void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode) {
	ArduinoFakeInstance(Function)->attachInterrupt(interruptNum, userFunc, mode);
}

void cli(void) {
    ArduinoFakeInstance(Function)->cli();
}

void sei(void) {
    ArduinoFakeInstance(Function)->sei();
}

void tone(uint8_t pin, unsigned int frequency, unsigned long duration)
{
    ArduinoFakeInstance(Function)->tone(pin, frequency, duration);
}

void noTone(uint8_t pin)
{
    ArduinoFakeInstance(Function)->noTone(pin);
}

long random(long max)
{
    return ArduinoFakeInstance(Function)->random(max);
}

long random(long min, long max)
{
    return ArduinoFakeInstance(Function)->random(min, max);
}

void randomSeed(unsigned long seed)
{
    return ArduinoFakeInstance(Function)->randomSeed(seed);
}

long map(long value, long fromLow, long fromHigh, long toLow, long toHigh)
{
    return ArduinoFakeInstance(Function)->map(value, fromLow, fromHigh, toLow, toHigh);
}

void yield()
{
    ArduinoFakeInstance(Function)->yield();
}


// ESP functions

double ledcSetup(uint8_t chan, double freq, uint8_t bit_num)
{
    return ArduinoFakeInstance(Function)->ledcSetup(chan, freq, bit_num);
}

void ledcAttachPin(uint8_t pin, uint8_t chan)
{
    ArduinoFakeInstance(Function)->ledcAttachPin(pin, chan);
}

void ledcDetachPin(uint8_t pin)
{
    ArduinoFakeInstance(Function)->ledcDetachPin(pin);
}

void ledcWrite(uint8_t chan, uint32_t duty)
{
    ArduinoFakeInstance(Function)->ledcWrite(chan, duty);
}



// ESP-IDF functions

esp_mqtt_client_handle_t esp_mqtt_client_init(const esp_mqtt_client_config_t *config)
{
    return ArduinoFakeInstance(Function)->esp_mqtt_client_init(config);
}

esp_err_t esp_mqtt_client_set_uri(esp_mqtt_client_handle_t client, const char *uri)
{
    return ArduinoFakeInstance(Function)->esp_mqtt_client_set_uri(client, uri);
}

esp_err_t esp_mqtt_client_start(esp_mqtt_client_handle_t client)
{
    return ArduinoFakeInstance(Function)->esp_mqtt_client_start(client);
}

esp_err_t esp_mqtt_client_reconnect(esp_mqtt_client_handle_t client)
{
    return ArduinoFakeInstance(Function)->esp_mqtt_client_reconnect(client);
}

esp_err_t esp_mqtt_client_disconnect(esp_mqtt_client_handle_t client)
{
    return ArduinoFakeInstance(Function)->esp_mqtt_client_disconnect(client);
}

esp_err_t esp_mqtt_client_stop(esp_mqtt_client_handle_t client)
{
    return ArduinoFakeInstance(Function)->esp_mqtt_client_stop(client);
}

int esp_mqtt_client_subscribe(esp_mqtt_client_handle_t client, const char *topic, int qos)
{
    return ArduinoFakeInstance(Function)->esp_mqtt_client_subscribe(client, topic, qos);
}

int esp_mqtt_client_unsubscribe(esp_mqtt_client_handle_t client, const char *topic)
{
    return ArduinoFakeInstance(Function)->esp_mqtt_client_unsubscribe(client, topic);
}

int esp_mqtt_client_publish(esp_mqtt_client_handle_t client, const char *topic, const char *data, int len, int qos, int retain)
{
    return ArduinoFakeInstance(Function)->esp_mqtt_client_publish(client, topic, data, len, qos, retain);
}

esp_err_t esp_mqtt_client_destroy(esp_mqtt_client_handle_t client)
{
    return ArduinoFakeInstance(Function)->esp_mqtt_client_destroy(client);
}

esp_err_t esp_mqtt_set_config(esp_mqtt_client_handle_t client, const esp_mqtt_client_config_t *config)
{
    return ArduinoFakeInstance(Function)->esp_mqtt_set_config(client, config);
}

esp_err_t esp_mqtt_client_register_event(esp_mqtt_client_handle_t client, esp_mqtt_event_id_t event, esp_event_handler_t event_handler, void* event_handler_arg)
{
    return ArduinoFakeInstance(Function)->esp_mqtt_client_register_event(client, event, event_handler, event_handler_arg);
}

int esp_mqtt_client_get_outbox_size(esp_mqtt_client_handle_t client)
{
    return ArduinoFakeInstance(Function)->esp_mqtt_client_get_outbox_size(client);
}
