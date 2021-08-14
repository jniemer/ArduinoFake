#pragma once

#include "ArduinoFake.h"

typedef enum {
    WIFI_MODE_NULL = 0,  /**< null mode */
    WIFI_MODE_STA,       /**< WiFi station mode */
    WIFI_MODE_AP,        /**< WiFi soft-AP mode */
    WIFI_MODE_APSTA,     /**< WiFi station + soft-AP mode */
    WIFI_MODE_MAX
} wifi_mode_t;

typedef enum {
    WIFI_POWER_19_5dBm = 78,// 19.5dBm
    WIFI_POWER_19dBm = 76,// 19dBm
    WIFI_POWER_18_5dBm = 74,// 18.5dBm
    WIFI_POWER_17dBm = 68,// 17dBm
    WIFI_POWER_15dBm = 60,// 15dBm
    WIFI_POWER_13dBm = 52,// 13dBm
    WIFI_POWER_11dBm = 44,// 11dBm
    WIFI_POWER_8_5dBm = 34,// 8.5dBm
    WIFI_POWER_7dBm = 28,// 7dBm
    WIFI_POWER_5dBm = 20,// 5dBm
    WIFI_POWER_2dBm = 8,// 2dBm
    WIFI_POWER_MINUS_1dBm = -4// -1dBm
} wifi_power_t;

typedef enum {
    SYSTEM_EVENT_WIFI_READY = 0,           /**< ESP32 WiFi ready */
    SYSTEM_EVENT_SCAN_DONE,                /**< ESP32 finish scanning AP */
    SYSTEM_EVENT_STA_START,                /**< ESP32 station start */
    SYSTEM_EVENT_STA_STOP,                 /**< ESP32 station stop */
    SYSTEM_EVENT_STA_CONNECTED,            /**< ESP32 station connected to AP */
    SYSTEM_EVENT_STA_DISCONNECTED,         /**< ESP32 station disconnected from AP */
    SYSTEM_EVENT_STA_AUTHMODE_CHANGE,      /**< the auth mode of AP connected by ESP32 station changed */
    SYSTEM_EVENT_STA_GOT_IP,               /**< ESP32 station got IP from connected AP */
    SYSTEM_EVENT_STA_LOST_IP,              /**< ESP32 station lost IP and the IP is reset to 0 */
    SYSTEM_EVENT_STA_WPS_ER_SUCCESS,       /**< ESP32 station wps succeeds in enrollee mode */
    SYSTEM_EVENT_STA_WPS_ER_FAILED,        /**< ESP32 station wps fails in enrollee mode */
    SYSTEM_EVENT_STA_WPS_ER_TIMEOUT,       /**< ESP32 station wps timeout in enrollee mode */
    SYSTEM_EVENT_STA_WPS_ER_PIN,           /**< ESP32 station wps pin code in enrollee mode */
    SYSTEM_EVENT_STA_WPS_ER_PBC_OVERLAP,   /*!< ESP32 station wps overlap in enrollee mode */
    SYSTEM_EVENT_AP_START,                 /**< ESP32 soft-AP start */
    SYSTEM_EVENT_AP_STOP,                  /**< ESP32 soft-AP stop */
    SYSTEM_EVENT_AP_STACONNECTED,          /**< a station connected to ESP32 soft-AP */
    SYSTEM_EVENT_AP_STADISCONNECTED,       /**< a station disconnected from ESP32 soft-AP */
    SYSTEM_EVENT_AP_STAIPASSIGNED,         /**< ESP32 soft-AP assign an IP to a connected station */
    SYSTEM_EVENT_AP_PROBEREQRECVED,        /**< Receive probe request packet in soft-AP interface */
    SYSTEM_EVENT_GOT_IP6,                  /**< ESP32 station or ap or ethernet interface v6IP addr is preferred */
    SYSTEM_EVENT_ETH_START,                /**< ESP32 ethernet start */
    SYSTEM_EVENT_ETH_STOP,                 /**< ESP32 ethernet stop */
    SYSTEM_EVENT_ETH_CONNECTED,            /**< ESP32 ethernet phy link up */
    SYSTEM_EVENT_ETH_DISCONNECTED,         /**< ESP32 ethernet phy link down */
    SYSTEM_EVENT_ETH_GOT_IP,               /**< ESP32 ethernet got IP from connected AP */
    SYSTEM_EVENT_MAX
} system_event_id_t;

typedef enum {
    WIFI_AUTH_OPEN = 0,         /**< authenticate mode : open */
    WIFI_AUTH_WEP,              /**< authenticate mode : WEP */
    WIFI_AUTH_WPA_PSK,          /**< authenticate mode : WPA_PSK */
    WIFI_AUTH_WPA2_PSK,         /**< authenticate mode : WPA2_PSK */
    WIFI_AUTH_WPA_WPA2_PSK,     /**< authenticate mode : WPA_WPA2_PSK */
    WIFI_AUTH_WPA2_ENTERPRISE,  /**< authenticate mode : WPA2_ENTERPRISE */
    WIFI_AUTH_MAX
} wifi_auth_mode_t;

struct ip4_addr {
  uint32_t addr;
};

typedef struct ip4_addr ip4_addr_t;

struct ip6_addr {
  uint32_t addr[4];
};

/** IPv6 address */
typedef struct ip6_addr ip6_addr_t;

typedef struct {
    ip6_addr_t ip; /**< Interface IPV6 address */
} tcpip_adapter_ip6_info_t;

typedef struct {
    ip4_addr_t ip;      /**< Interface IPV4 address */
    ip4_addr_t netmask; /**< Interface IPV4 netmask */
    ip4_addr_t gw;      /**< Interface IPV4 gateway address */
} tcpip_adapter_ip_info_t;

typedef enum {
    WPS_FAIL_REASON_NORMAL = 0,                   /**< ESP32 WPS normal fail reason */
    WPS_FAIL_REASON_RECV_M2D,                       /**< ESP32 WPS receive M2D frame */
    WPS_FAIL_REASON_MAX
}system_event_sta_wps_fail_reason_t;
typedef struct {
    uint32_t status;          /**< status of scanning APs */
    uint8_t  number;
    uint8_t  scan_id;
} system_event_sta_scan_done_t;

typedef struct {
    uint8_t ssid[32];         /**< SSID of connected AP */
    uint8_t ssid_len;         /**< SSID length of connected AP */
    uint8_t bssid[6];         /**< BSSID of connected AP*/
    uint8_t channel;          /**< channel of connected AP*/
    wifi_auth_mode_t authmode;
} system_event_sta_connected_t;

typedef struct {
    uint8_t ssid[32];         /**< SSID of disconnected AP */
    uint8_t ssid_len;         /**< SSID length of disconnected AP */
    uint8_t bssid[6];         /**< BSSID of disconnected AP */
    uint8_t reason;           /**< reason of disconnection */
} system_event_sta_disconnected_t;

typedef struct {
    wifi_auth_mode_t old_mode;         /**< the old auth mode of AP */
    wifi_auth_mode_t new_mode;         /**< the new auth mode of AP */
} system_event_sta_authmode_change_t;

typedef struct {
    tcpip_adapter_ip_info_t ip_info;
    bool ip_changed;
} system_event_sta_got_ip_t;

typedef struct {
    uint8_t pin_code[8];         /**< PIN code of station in enrollee mode */
} system_event_sta_wps_er_pin_t;

/* @brief On-chip network interfaces */
typedef enum {
    TCPIP_ADAPTER_IF_STA = 0,     /**< Wi-Fi STA (station) interface */
    TCPIP_ADAPTER_IF_AP,          /**< Wi-Fi soft-AP interface */
    TCPIP_ADAPTER_IF_ETH,         /**< Ethernet interface */
    TCPIP_ADAPTER_IF_MAX
} tcpip_adapter_if_t;

typedef struct {
    tcpip_adapter_if_t if_index;
    tcpip_adapter_ip6_info_t ip6_info;
} system_event_got_ip6_t;

typedef struct {
    uint8_t mac[6];           /**< MAC address of the station connected to ESP32 soft-AP */
    uint8_t aid;              /**< the aid that ESP32 soft-AP gives to the station connected to  */
} system_event_ap_staconnected_t;

typedef struct {
    uint8_t mac[6];           /**< MAC address of the station disconnects to ESP32 soft-AP */
    uint8_t aid;              /**< the aid that ESP32 soft-AP gave to the station disconnects to  */
} system_event_ap_stadisconnected_t;

typedef struct {
    int rssi;                 /**< Received probe request signal strength */
    uint8_t mac[6];           /**< MAC address of the station which send probe request */
} system_event_ap_probe_req_rx_t;

typedef struct {
    ip4_addr_t ip; 
} system_event_ap_staipassigned_t;

typedef union {
    system_event_sta_connected_t               connected;          /**< ESP32 station connected to AP */
    system_event_sta_disconnected_t            disconnected;       /**< ESP32 station disconnected to AP */
    system_event_sta_scan_done_t               scan_done;          /**< ESP32 station scan (APs) done */
    system_event_sta_authmode_change_t         auth_change;        /**< the auth mode of AP ESP32 station connected to changed */
    system_event_sta_got_ip_t                  got_ip;             /**< ESP32 station got IP, first time got IP or when IP is changed */
    system_event_sta_wps_er_pin_t              sta_er_pin;         /**< ESP32 station WPS enrollee mode PIN code received */
    system_event_sta_wps_fail_reason_t         sta_er_fail_reason;/**< ESP32 station WPS enrollee mode failed reason code received */
    system_event_ap_staconnected_t             sta_connected;      /**< a station connected to ESP32 soft-AP */
    system_event_ap_stadisconnected_t          sta_disconnected;   /**< a station disconnected to ESP32 soft-AP */
    system_event_ap_probe_req_rx_t             ap_probereqrecved;  /**< ESP32 soft-AP receive probe request packet */
    system_event_ap_staipassigned_t            ap_staipassigned;   /**< ESP32 soft-AP assign an IP to the station*/
    system_event_got_ip6_t                     got_ip6;            /**< ESP32 station　or ap or ethernet ipv6 addr state change to preferred */
} system_event_info_t;

typedef struct {
    system_event_id_t     event_id;      /**< event ID */
    system_event_info_t   event_info;    /**< event information */
} system_event_t;

typedef enum {
    WIFI_PROV_INIT,
    WIFI_PROV_START,
    WIFI_PROV_CRED_RECV,
    WIFI_PROV_CRED_FAIL,
    WIFI_PROV_CRED_SUCCESS,
    WIFI_PROV_END,
    WIFI_PROV_DEINIT,
} wifi_prov_cb_event_t;

typedef struct
{
     wifi_prov_cb_event_t event;
     void *event_data;
}wifi_prov_event_t;

typedef void (*WiFiEventCb)(system_event_id_t event);
typedef std::function<void(system_event_id_t event, system_event_info_t info)> WiFiEventFuncCb;
typedef void (*WiFiEventSysCb)(system_event_t *event);
typedef void (*WiFiProvEventCb)(system_event_t *sys_event, wifi_prov_event_t *prov_event);

typedef size_t wifi_event_id_t;

typedef enum {
    WL_NO_SHIELD        = 255,   // for compatibility with WiFi Shield library
    WL_IDLE_STATUS      = 0,
    WL_NO_SSID_AVAIL    = 1,
    WL_SCAN_COMPLETED   = 2,
    WL_CONNECTED        = 3,
    WL_CONNECT_FAILED   = 4,
    WL_CONNECTION_LOST  = 5,
    WL_DISCONNECTED     = 6
} wl_status_t;

#define WiFiMode_t   wifi_mode_t
#define WIFI_OFF     WIFI_MODE_NULL
#define WIFI_STA     WIFI_MODE_STA
#define WIFI_AP      WIFI_MODE_AP
#define WIFI_AP_STA  WIFI_MODE_APSTA

class WiFiClass
{
public:
    WiFiClass() {};

    virtual wl_status_t begin(const char* ssid, const char *passphrase = NULL, int32_t channel = 0, const uint8_t* bssid = NULL, bool connect = true);
    virtual wl_status_t begin(char* ssid, char *passphrase = NULL, int32_t channel = 0, const uint8_t* bssid = NULL, bool connect = true);
    virtual wl_status_t begin();
    virtual bool disconnect(bool wifioff = false, bool eraseap = false);

    virtual bool softAP(const char* ssid, const char* passphrase = NULL, int channel = 1, int ssid_hidden = 0, int max_connection = 4);
    virtual bool softAPdisconnect(bool wifioff = false);
    virtual IPAddress softAPIP();

    virtual bool setHostname(const char * hostname);
    virtual bool mode(wifi_mode_t mode);
    virtual wifi_mode_t getMode();
    virtual bool setAutoConnect(bool autoConnect);
    virtual bool getAutoConnect();
    virtual IPAddress localIP();
    virtual void persistent(bool persistent);

    virtual wifi_event_id_t onEvent(WiFiEventFuncCb cbEvent, system_event_id_t event = SYSTEM_EVENT_MAX);
};

struct WiFiClassFake
{
public:
    virtual wl_status_t begin(const char* ssid, const char *passphrase = NULL, int32_t channel = 0, const uint8_t* bssid = NULL, bool connect = true) = 0;
    virtual wl_status_t begin(char* ssid, char *passphrase = NULL, int32_t channel = 0, const uint8_t* bssid = NULL, bool connect = true) = 0;
    virtual wl_status_t begin() = 0;
    virtual bool disconnect(bool wifioff = false, bool eraseap = false) = 0;

    virtual bool softAP(const char* ssid, const char* passphrase = NULL, int channel = 1, int ssid_hidden = 0, int max_connection = 4) = 0;
    virtual bool softAPdisconnect(bool wifioff = false) = 0;
    virtual IPAddress softAPIP() = 0;

    virtual bool setHostname(const char * hostname) = 0;
    virtual bool mode(wifi_mode_t mode) = 0;
    virtual wifi_mode_t getMode() = 0;
    virtual bool setAutoConnect(bool autoConnect) = 0;
    virtual bool getAutoConnect() = 0;
    virtual IPAddress localIP() = 0;
    virtual void persistent(bool persistent) = 0;

    virtual wifi_event_id_t onEvent(WiFiEventFuncCb cbEvent, system_event_id_t event = SYSTEM_EVENT_MAX) = 0;
};

class WiFiClassFakeProxy : public WiFiClass
{
    private:
        WiFiClassFake* wcFake;

    public:
        WiFiClassFakeProxy(WiFiClassFake* fake)
        {
            wcFake = fake;
        }

        WiFiClassFake* getWiFiClassFake()
        {
            return wcFake;
        }
};

extern WiFiClass WiFi;
