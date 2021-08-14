#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef int32_t esp_err_t;

typedef const char*  esp_event_base_t; /**< unique pointer to a subsystem that exposes events */
typedef void*        esp_event_loop_handle_t; /**< a number that identifies an event with respect to a base */
typedef void         (*esp_event_handler_t)(void* event_handler_arg, 
                                        esp_event_base_t event_base, 
                                        int32_t event_id, 
                                        void* event_data); /**< function called when an event is posted to the queue */

#define ESP_EVENT_ANY_BASE     NULL             /**< register handler for any event base */
#define ESP_EVENT_ANY_ID       -1               /**< register handler for any event id */

typedef struct esp_mqtt_client *esp_mqtt_client_handle_t;

typedef enum {
    MQTT_EVENT_ANY = -1,
    MQTT_EVENT_ERROR = 0,          /*!< on error event, additional context: connection return code, error handle from esp_tls (if supported) */
    MQTT_EVENT_CONNECTED,          /*!< connected event, additional context: session_present flag */
    MQTT_EVENT_DISCONNECTED,       /*!< disconnected event */
    MQTT_EVENT_SUBSCRIBED,         /*!< subscribed event, additional context: msg_id */
    MQTT_EVENT_UNSUBSCRIBED,       /*!< unsubscribed event */
    MQTT_EVENT_PUBLISHED,          /*!< published event, additional context:  msg_id */
    MQTT_EVENT_DATA,               /*!< data event, additional context:
                                        - msg_id               message id
                                        - topic                pointer to the received topic
                                        - topic_len            length of the topic
                                        - data                 pointer to the received data
                                        - data_len             length of the data for this event
                                        - current_data_offset  offset of the current data for this event
                                        - total_data_len       total length of the data received
                                        Note: Multiple MQTT_EVENT_DATA could be fired for one message, if it is
                                        longer than internal buffer. In that case only first event contains topic
                                        pointer and length, other contain data only with current data length
                                        and current data offset updating.
                                         */
    MQTT_EVENT_BEFORE_CONNECT,     /*!< The event occurs before connecting */
} esp_mqtt_event_id_t;

typedef enum {
    MQTT_CONNECTION_ACCEPTED = 0,                   /*!< Connection accepted  */
    MQTT_CONNECTION_REFUSE_PROTOCOL,                /*!< MQTT connection refused reason: Wrong protocol */
    MQTT_CONNECTION_REFUSE_ID_REJECTED,             /*!< MQTT connection refused reason: ID rejected */
    MQTT_CONNECTION_REFUSE_SERVER_UNAVAILABLE,      /*!< MQTT connection refused reason: Server unavailable */
    MQTT_CONNECTION_REFUSE_BAD_USERNAME,            /*!< MQTT connection refused reason: Wrong user */
    MQTT_CONNECTION_REFUSE_NOT_AUTHORIZED           /*!< MQTT connection refused reason: Wrong username or password */
} esp_mqtt_connect_return_code_t;

typedef enum {
    MQTT_ERROR_TYPE_NONE = 0,
    MQTT_ERROR_TYPE_TCP_TRANSPORT,
    MQTT_ERROR_TYPE_CONNECTION_REFUSED,
} esp_mqtt_error_type_t;

#define MQTT_ERROR_TYPE_ESP_TLS MQTT_ERROR_TYPE_TCP_TRANSPORT

typedef enum {
    MQTT_TRANSPORT_UNKNOWN = 0x0,
    MQTT_TRANSPORT_OVER_TCP,      /*!< MQTT over TCP, using scheme: ``mqtt`` */
    MQTT_TRANSPORT_OVER_SSL,      /*!< MQTT over SSL, using scheme: ``mqtts`` */
    MQTT_TRANSPORT_OVER_WS,       /*!< MQTT over Websocket, using scheme:: ``ws`` */
    MQTT_TRANSPORT_OVER_WSS       /*!< MQTT over Websocket Secure, using scheme: ``wss`` */
} esp_mqtt_transport_t;

typedef enum {
    MQTT_PROTOCOL_UNDEFINED = 0,
    MQTT_PROTOCOL_V_3_1,
    MQTT_PROTOCOL_V_3_1_1
} esp_mqtt_protocol_ver_t;

typedef struct esp_mqtt_error_codes {
    /* compatible portion of the struct corresponding to struct esp_tls_last_error */
    esp_err_t esp_tls_last_esp_err;              /*!< last esp_err code reported from esp-tls component */
    int       esp_tls_stack_err;                 /*!< tls specific error code reported from underlying tls stack */
    int       esp_tls_cert_verify_flags;         /*!< tls flags reported from underlying tls stack during certificate verification */
    /* esp-mqtt specific structure extension */
    esp_mqtt_error_type_t error_type;            /*!< error type referring to the source of the error */
    esp_mqtt_connect_return_code_t connect_return_code; /*!< connection refused error code reported from MQTT broker on connection */
    /* tcp_transport extension */
    int       esp_transport_sock_errno;         /*!< errno from the underlying socket */

} esp_mqtt_error_codes_t;

typedef struct {
    esp_mqtt_event_id_t event_id;       /*!< MQTT event type */
    esp_mqtt_client_handle_t client;    /*!< MQTT client handle for this event */
    void *user_context;                 /*!< User context passed from MQTT client config */
    char *data;                         /*!< Data associated with this event */
    int data_len;                       /*!< Length of the data for this event */
    int total_data_len;                 /*!< Total length of the data (longer data are supplied with multiple events) */
    int current_data_offset;            /*!< Actual offset for the data associated with this event */
    char *topic;                        /*!< Topic associated with this event */
    int topic_len;                      /*!< Length of the topic for this event associated with this event */
    int msg_id;                         /*!< MQTT messaged id of message */
    int session_present;                /*!< MQTT session_present flag for connection event */
    esp_mqtt_error_codes_t *error_handle; /*!< esp-mqtt error handle including esp-tls errors as well as internal mqtt errors */
} esp_mqtt_event_t;

typedef esp_mqtt_event_t *esp_mqtt_event_handle_t;

typedef esp_err_t (* mqtt_event_callback_t)(esp_mqtt_event_handle_t event);

typedef struct {
    mqtt_event_callback_t event_handle;     /*!< handle for MQTT events as a callback in legacy mode */
    esp_event_loop_handle_t event_loop_handle; /*!< handle for MQTT event loop library */
    const char *host;                       /*!< MQTT server domain (ipv4 as string) */
    const char *uri;                        /*!< Complete MQTT broker URI */
    uint32_t port;                          /*!< MQTT server port */
    const char *client_id;                  /*!< default client id is ``ESP32_%CHIPID%`` where %CHIPID% are last 3 bytes of MAC address in hex format */
    const char *username;                   /*!< MQTT username */
    const char *password;                   /*!< MQTT password */
    const char *lwt_topic;                  /*!< LWT (Last Will and Testament) message topic (NULL by default) */
    const char *lwt_msg;                    /*!< LWT message (NULL by default) */
    int lwt_qos;                            /*!< LWT message qos */
    int lwt_retain;                         /*!< LWT retained message flag */
    int lwt_msg_len;                        /*!< LWT message length */
    int disable_clean_session;              /*!< mqtt clean session, default clean_session is true */
    int keepalive;                          /*!< mqtt keepalive, default is 120 seconds */
    bool disable_auto_reconnect;            /*!< this mqtt client will reconnect to server (when errors/disconnect). Set disable_auto_reconnect=true to disable */
    void *user_context;                     /*!< pass user context to this option, then can receive that context in ``event->user_context`` */
    int task_prio;                          /*!< MQTT task priority, default is 5, can be changed in ``make menuconfig`` */
    int task_stack;                         /*!< MQTT task stack size, default is 6144 bytes, can be changed in ``make menuconfig`` */
    int buffer_size;                        /*!< size of MQTT send/receive buffer, default is 1024 (only receive buffer size if ``out_buffer_size`` defined) */
    const char *cert_pem;                   /*!< Pointer to certificate data in PEM or DER format for server verify (with SSL), default is NULL, not required to verify the server. PEM-format must have a terminating NULL-character. DER-format requires the length to be passed in cert_len. */
    size_t cert_len;                        /*!< Length of the buffer pointed to by cert_pem. May be 0 for null-terminated pem */
    const char *client_cert_pem;            /*!< Pointer to certificate data in PEM or DER format for SSL mutual authentication, default is NULL, not required if mutual authentication is not needed. If it is not NULL, also `client_key_pem` has to be provided. PEM-format must have a terminating NULL-character. DER-format requires the length to be passed in client_cert_len. */
    size_t client_cert_len;                 /*!< Length of the buffer pointed to by client_cert_pem. May be 0 for null-terminated pem */
    const char *client_key_pem;             /*!< Pointer to private key data in PEM or DER format for SSL mutual authentication, default is NULL, not required if mutual authentication is not needed. If it is not NULL, also `client_cert_pem` has to be provided. PEM-format must have a terminating NULL-character. DER-format requires the length to be passed in client_key_len */
    size_t client_key_len;                  /*!< Length of the buffer pointed to by client_key_pem. May be 0 for null-terminated pem */
    esp_mqtt_transport_t transport;         /*!< overrides URI transport */
    int refresh_connection_after_ms;        /*!< Refresh connection after this value (in milliseconds) */
    const struct psk_key_hint* psk_hint_key;     /*!< Pointer to PSK struct defined in esp_tls.h to enable PSK authentication (as alternative to certificate verification). If not NULL and server/client certificates are NULL, PSK is enabled */
    bool          use_global_ca_store;      /*!< Use a global ca_store for all the connections in which this bool is set. */
    int reconnect_timeout_ms;               /*!< Reconnect to the broker after this value in miliseconds if auto reconnect is not disabled (defaults to 10s) */
    const char **alpn_protos;               /*!< NULL-terminated list of supported application protocols to be used for ALPN */
    const char *clientkey_password;         /*!< Client key decryption password string */
    int clientkey_password_len;             /*!< String length of the password pointed to by clientkey_password */
    esp_mqtt_protocol_ver_t protocol_ver;   /*!< MQTT protocol version used for connection, defaults to value from menuconfig*/
    int out_buffer_size;                    /*!< size of MQTT output buffer. If not defined, both output and input buffers have the same size defined as ``buffer_size`` */
    bool skip_cert_common_name_check;       /*!< Skip any validation of server certificate CN field, this reduces the security of TLS and makes the mqtt client susceptible to MITM attacks  */
    bool use_secure_element;                /*!< enable secure element for enabling SSL connection */
    void *ds_data;                          /*!< carrier of handle for digital signature parameters */
    int network_timeout_ms;                 /*!< Abort network operation if it is not completed after this value, in milliseconds (defaults to 10s) */
    bool disable_keepalive;                 /*!< Set disable_keepalive=true to turn off keep-alive mechanism, false by default (keepalive is active by default). Note: setting the config value `keepalive` to `0` doesn't disable keepalive feature, but uses a default keepalive period */
} esp_mqtt_client_config_t;

esp_mqtt_client_handle_t esp_mqtt_client_init(const esp_mqtt_client_config_t *config);
esp_err_t esp_mqtt_client_set_uri(esp_mqtt_client_handle_t client, const char *uri);
esp_err_t esp_mqtt_client_start(esp_mqtt_client_handle_t client);
esp_err_t esp_mqtt_client_reconnect(esp_mqtt_client_handle_t client);
esp_err_t esp_mqtt_client_disconnect(esp_mqtt_client_handle_t client);
esp_err_t esp_mqtt_client_stop(esp_mqtt_client_handle_t client);
int esp_mqtt_client_subscribe(esp_mqtt_client_handle_t client, const char *topic, int qos);
int esp_mqtt_client_unsubscribe(esp_mqtt_client_handle_t client, const char *topic);
int esp_mqtt_client_publish(esp_mqtt_client_handle_t client, const char *topic, const char *data, int len, int qos, int retain);
esp_err_t esp_mqtt_client_destroy(esp_mqtt_client_handle_t client);
esp_err_t esp_mqtt_set_config(esp_mqtt_client_handle_t client, const esp_mqtt_client_config_t *config);
esp_err_t esp_mqtt_client_register_event(esp_mqtt_client_handle_t client, esp_mqtt_event_id_t event, esp_event_handler_t event_handler, void* event_handler_arg);
int esp_mqtt_client_get_outbox_size(esp_mqtt_client_handle_t client);