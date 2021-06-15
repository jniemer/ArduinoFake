#pragma once

#include "Arduino.h"
#include "asyncMQTT/Flags.hpp"
#include "asyncMQTT/ParsingInformation.hpp"
#include "asyncMQTT/MessageProperties.hpp"
#include "asyncMQTT/Helpers.hpp"
#include "asyncMQTT/Callbacks.hpp"
#include "asyncMQTT/DisconnectReasons.hpp"
#include "asyncMQTT/Storage.hpp"

#include "asyncMQTT/Packets/Packet.hpp"
#include "asyncMQTT/Packets/ConnAckPacket.hpp"
#include "asyncMQTT/Packets/PingRespPacket.hpp"
#include "asyncMQTT/Packets/SubAckPacket.hpp"
#include "asyncMQTT/Packets/UnsubAckPacket.hpp"
#include "asyncMQTT/Packets/PublishPacket.hpp"
#include "asyncMQTT/Packets/PubRelPacket.hpp"
#include "asyncMQTT/Packets/PubAckPacket.hpp"
#include "asyncMQTT/Packets/PubRecPacket.hpp"
#include "asyncMQTT/Packets/PubCompPacket.hpp"

#define SEMAPHORE_TAKE(X) void()
#define SEMAPHORE_GIVE() void()

class AsyncMqttClient {
 public:
  AsyncMqttClient();

  virtual AsyncMqttClient& setKeepAlive(uint16_t keepAlive);
  virtual AsyncMqttClient& setClientId(const char* clientId);
  virtual AsyncMqttClient& setCleanSession(bool cleanSession);
  virtual AsyncMqttClient& setMaxTopicLength(uint16_t maxTopicLength);
  virtual AsyncMqttClient& setCredentials(const char* username, const char* password = nullptr);
  virtual AsyncMqttClient& setWill(const char* topic, uint8_t qos, bool retain, const char* payload = nullptr, size_t length = 0);
  virtual AsyncMqttClient& setServer(IPAddress ip, uint16_t port);
  virtual AsyncMqttClient& setServer(const char* host, uint16_t port);

  virtual AsyncMqttClient& onConnect(AsyncMqttClientInternals::OnConnectUserCallback callback);
  virtual AsyncMqttClient& onDisconnect(AsyncMqttClientInternals::OnDisconnectUserCallback callback);
  virtual AsyncMqttClient& onSubscribe(AsyncMqttClientInternals::OnSubscribeUserCallback callback);
  virtual AsyncMqttClient& onUnsubscribe(AsyncMqttClientInternals::OnUnsubscribeUserCallback callback);
  virtual AsyncMqttClient& onMessage(AsyncMqttClientInternals::OnMessageUserCallback callback);
  virtual AsyncMqttClient& onPublish(AsyncMqttClientInternals::OnPublishUserCallback callback);

  virtual bool connected() const;
  virtual void connect();
  virtual void disconnect(bool force = false);
  virtual uint16_t subscribe(const char* topic, uint8_t qos);
  virtual uint16_t unsubscribe(const char* topic);
  virtual uint16_t publish(const char* topic, uint8_t qos, bool retain, const char* payload = nullptr, size_t length = 0, bool dup = false, uint16_t message_id = 0);

  virtual const char* getClientId();
};

struct AsyncMqttClientFake {
 public:

  virtual AsyncMqttClient& setKeepAlive(uint16_t keepAlive) = 0;
  virtual AsyncMqttClient& setClientId(const char* clientId) = 0;
  virtual AsyncMqttClient& setCleanSession(bool cleanSession) = 0;
  virtual AsyncMqttClient& setMaxTopicLength(uint16_t maxTopicLength) = 0;
  virtual AsyncMqttClient& setCredentials(const char* username, const char* password = nullptr) = 0;
  virtual AsyncMqttClient& setWill(const char* topic, uint8_t qos, bool retain, const char* payload = nullptr, size_t length = 0) = 0;
  virtual AsyncMqttClient& setServer(IPAddress ip, uint16_t port) = 0;
  virtual AsyncMqttClient& setServer(const char* host, uint16_t port) = 0;

  virtual AsyncMqttClient& onConnect(AsyncMqttClientInternals::OnConnectUserCallback callback) = 0;
  virtual AsyncMqttClient& onDisconnect(AsyncMqttClientInternals::OnDisconnectUserCallback callback) = 0;
  virtual AsyncMqttClient& onSubscribe(AsyncMqttClientInternals::OnSubscribeUserCallback callback) = 0;
  virtual AsyncMqttClient& onUnsubscribe(AsyncMqttClientInternals::OnUnsubscribeUserCallback callback) = 0;
  virtual AsyncMqttClient& onMessage(AsyncMqttClientInternals::OnMessageUserCallback callback) = 0;
  virtual AsyncMqttClient& onPublish(AsyncMqttClientInternals::OnPublishUserCallback callback) = 0;

  virtual bool connected() const = 0;
  virtual void connect() = 0;
  virtual void disconnect(bool force = false) = 0;
  virtual uint16_t subscribe(const char* topic, uint8_t qos) = 0;
  virtual uint16_t unsubscribe(const char* topic) = 0;
  virtual uint16_t publish(const char* topic, uint8_t qos, bool retain, const char* payload = nullptr, size_t length = 0, bool dup = false, uint16_t message_id = 0) = 0;

  virtual const char* getClientId() = 0;
};

class AsyncMqttClientFakeProxy : public AsyncMqttClient
{
    private:
        AsyncMqttClientFake* amqttFake;

    public:
        AsyncMqttClientFakeProxy(AsyncMqttClientFake* fake)
        {
            amqttFake = fake;
        }

        AsyncMqttClientFake* getAsyncMqttClientFake()
        {
            return amqttFake;
        }
};
