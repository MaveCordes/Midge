#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <index.html>
#include <settings.html>
#include <sdcard.html>
#include <about.html>
#include <cam.html>
#include <SD.h>
#include <RTClib.h>
#include <Preferences.h>
#include <ArduinoJson.h>
#include <time.h>
#include <BasicOTA.hpp>
#include <WebSerial.h>
#include <TelnetStream.h>



// NVM Storage
extern Preferences preferences;
void store_value(const char *store_temp, uint8_t store_int);
void store_toggle(const char *store_temp, bool store_bool);

// credentials
extern String http_username;
extern String http_password;
extern String password;
extern String ssid;

// Async Webserver
extern AsyncWebServer server;
extern AsyncWebSocket ws;
// void async_server_on_get();
void async_server_on();
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void initWebSocket();
void onEvent(AsyncWebSocket *server,
             AsyncWebSocketClient *client,
             AwsEventType type,
             void *arg,
             uint8_t *data,
             size_t len);
String processor(const String &var);
void notFound(AsyncWebServerRequest *request);
extern String inputMessage;
extern String inputMessage_2;

// Time
// void printLocalTime();

// timekeeping
extern unsigned long sd_run_time;
extern unsigned long hum_run_time;
extern unsigned long fan_run_time;
extern unsigned long light_run_time;
extern unsigned long temp_run_time;

// JSON
extern StaticJsonDocument<512> doc;
extern char json_data[512];
extern size_t len;

// RTC
extern RTC_DS3231 rtc;
extern DateTime now;
extern bool dis_rtc;

extern uint8_t temperature;
extern uint8_t humidity;
extern uint16_t co2;
// extern uint8_t lighthour;

// NVM
void check_nvm();
void read_nvm_values();
void NVM_read_credentials();
void NVM_store_credentials();

// test 
extern struct tm timeinfo;
// extern bool lgt_toggle;
void toggle_light();
// extern bool new_light;
extern bool toggle_ON_var;