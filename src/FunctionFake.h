#pragma once

#include "fakeit/fakeit.hpp"
#include "mqtt_client.h"

struct FunctionFake
{
    virtual void init(void) = 0;
    virtual void loop(void) = 0;
    virtual void setup(void) = 0;

    virtual void pinMode(uint8_t, uint8_t) = 0;
    virtual void digitalWrite(uint8_t, uint8_t) = 0;
    virtual int digitalRead(uint8_t) = 0;

    virtual int analogRead(uint8_t) = 0;
    virtual void analogReference(uint8_t) = 0;
    virtual void analogWrite(uint8_t, int) = 0;


    virtual unsigned long millis(void) = 0;
    virtual unsigned long micros(void) = 0;

    virtual void delay(unsigned long) = 0;
    virtual void delayMicroseconds(unsigned int) = 0;

    virtual unsigned long pulseIn(uint8_t, uint8_t, unsigned long) = 0;
    virtual unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout) = 0;

    virtual void shiftOut(uint8_t, uint8_t, uint8_t, uint8_t) = 0;
    virtual uint8_t shiftIn(uint8_t, uint8_t, uint8_t) = 0;

    virtual void detachInterrupt(uint8_t) = 0;
    virtual void attachInterrupt(uint8_t, void (*)(void), int mode) = 0;
    virtual void cli() = 0;
    virtual void sei() = 0;

    virtual void tone(uint8_t _pin, unsigned int frequency, unsigned long duration) = 0;
    virtual void noTone(uint8_t _pin) = 0;

    virtual long random(long) = 0;
    virtual long random(long, long) = 0;
    virtual void randomSeed(unsigned long) = 0;

    virtual long map(long, long, long, long, long) = 0;

    virtual void yield() = 0;

    //ESP functions
    virtual double ledcSetup(uint8_t chan, double freq, uint8_t bit_num) = 0;
    virtual void ledcAttachPin(uint8_t pin, uint8_t chan) = 0;
    virtual void ledcDetachPin(uint8_t pin) = 0;
    virtual void ledcWrite(uint8_t chan, uint32_t duty) = 0;

    //ESP-IDF functions
    virtual esp_mqtt_client_handle_t esp_mqtt_client_init(const esp_mqtt_client_config_t *config) = 0;
    virtual esp_err_t esp_mqtt_client_set_uri(esp_mqtt_client_handle_t client, const char *uri) = 0;
    virtual esp_err_t esp_mqtt_client_start(esp_mqtt_client_handle_t client) = 0;
    virtual esp_err_t esp_mqtt_client_reconnect(esp_mqtt_client_handle_t client) = 0;
    virtual esp_err_t esp_mqtt_client_disconnect(esp_mqtt_client_handle_t client) = 0;
    virtual esp_err_t esp_mqtt_client_stop(esp_mqtt_client_handle_t client) = 0;
    virtual int esp_mqtt_client_subscribe(esp_mqtt_client_handle_t client, const char *topic, int qos) = 0;
    virtual int esp_mqtt_client_unsubscribe(esp_mqtt_client_handle_t client, const char *topic) = 0;
    virtual int esp_mqtt_client_publish(esp_mqtt_client_handle_t client, const char *topic, const char *data, int len, int qos, int retain) = 0;
    virtual esp_err_t esp_mqtt_client_destroy(esp_mqtt_client_handle_t client) = 0;
    virtual esp_err_t esp_mqtt_set_config(esp_mqtt_client_handle_t client, const esp_mqtt_client_config_t *config) = 0;
    virtual esp_err_t esp_mqtt_client_register_event(esp_mqtt_client_handle_t client, esp_mqtt_event_id_t event, esp_event_handler_t event_handler, void* event_handler_arg) = 0;
    virtual int esp_mqtt_client_get_outbox_size(esp_mqtt_client_handle_t client) = 0;
};
