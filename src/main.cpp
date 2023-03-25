#include <header.h>
#include <fridge.h>


// NVM Storage
Preferences preferences;

// JSON
StaticJsonDocument<512> doc;
char json_data[512];
size_t len;

// Time
const char *ntpServer = "europe.pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;
struct tm timeinfo;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

//wSerial
// class iSerialClass : public Stream {
// public:
//   size_t write(uint8_t c) {
//     char buffer[2] = {(char)c, '\0'};
//     sendJsonMessage(buffer);
//     return 1;
//   }

//   int available() {
//     return 0; // Not needed for this implementation
//   }

//   int read() {
//     return -1; // Not needed for this implementation
//   }

//   int peek() {
//     return -1; // Not needed for this implementation
//   }

//   void flush() {
//     // Not needed for this implementation
//   }

// private:
//   void sendJsonMessage(const char* message) {
//     DynamicJsonDocument doc(1024);
//     char json_data[1024];
//     doc["p"] = true;
//     doc["mssg"] = message;
//     size_t len = serializeJson(doc, json_data);
//     ws.textAll(json_data, len);
//     doc.clear();
//   }
// };

iSerialClass iSerial;

//wSerial

//BasicOTA 
BasicOTA OTA;

// LCD Menu Lib
uint8_t _LCDML_DISP_cols = 20;
uint8_t _LCDML_DISP_rows = 4;
uint8_t _LCDML_DSIP_use_header = 0;
uint8_t _LCDML_DISP_cfg_cursor = 0x3e; // cursor Symbol
uint8_t _LCDML_DISP_cfg_scrollbar = 0; // enable a scrollbar

// LiquidCrystal_I2C
LiquidCrystal_I2C lcd(0x27, _LCDML_DISP_cols, _LCDML_DISP_rows);

// LCDMenuLib2
LCDMenuLib2_menu LCDML_0(255, 0, 0, NULL, NULL); // root menu element (do not change)
LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

// Average Float Declarations
Average<uint16_t> avg_co2_10(10);
Average<float> avg_temp_10(10);
Average<float> avg_hum_10(10);
Average<float> avg_bar_10(10);
Average<float> avg_air_10(10);
uint16_t avg_co2_test;

// MHZ-19b
#define MHZ19BAUDRATE 9600; // Device to MH-Z19 Serial baudrate (should not be changed)
MHZ19 myMHZ19;              // Constructor for library
uint8_t RXD2 = 15;
uint8_t TXD2 = 54; //14 on board

// BME680
uint8_t BME_SCK = 33;  // SCL - Grey (33)
uint8_t BME_MISO = 34; // SDO - White (34)
uint8_t BME_MOSI = 32; // SDA - Pink (32)
uint8_t BME_CS = 25;   // CS - Brown
uint8_t BME_CS_1 = 26; // CS - Brown
Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);
Adafruit_BME680 bme_1(BME_CS_1, BME_MOSI, BME_MISO, BME_SCK);

// PINs
uint8_t waterPIN = 27; // -> interal SD Card PIN 4, change to PIN 2 internal LED, old pin 27
uint8_t fanforwaterPIN = 14; // -> interal SD Card PIN 4, change to PIN 2 internal LED, old pin 27

uint8_t fanPIN = 2; // conneted to PIN 4 = SD Pin, change!
uint8_t heatingPIN = 40;
uint8_t lightPIN = 41; // PIN 5 HIGH at Boot

// sort out later
bool spray = true;
// bool heating = true;
// sort out later
uint16_t count;

// timing variable
uint8_t set_temp; // Set Target Temperature
uint8_t set_hum;  // Set Target Humidity
uint16_t set_co2; // Set Target Humidity

uint8_t SD_time; // Write to SD_Card every X Minutes

uint8_t set_light_ON;  // Set turn on time of the Light (00:00 - 24:00)
uint8_t set_light_OFF; // Set turn off time of the Light

uint8_t set_fan_ON;  // Set fan on Time in X Minutes
uint8_t set_fan_OFF; // Set fan off Time in X Minutes

uint8_t set_water_ON;  // Set water on time in X Minutes
uint8_t set_water_OFF; // Set water off time to X Minutes

uint8_t set_temp_ON;  // Set heating on time in X Minutes
uint8_t set_temp_OFF; // Set heating off time in X Minutes

// manual control variables
bool hum_control_var = false;
bool fan_control_var = false;
bool temp_control_var = false;
bool light_control_var = false;

bool hum_man_var = false;
bool fan_man_var = false;
bool temp_man_var = false;
bool light_man_var = false;

// time keeping
unsigned long sd_run_time;
unsigned long hum_run_time;
unsigned long fan_run_time;
unsigned long light_run_time;
unsigned long temp_run_time;
char timer[8];
char timer_hour_min[7];

// SD Card Var
String response = "";

// SD Card File
File data_file_main;
String sd_directory = "";
bool sd_directory_bool = false;
bool dis_sd = false; // true to disable SD Card

// RTC Constructor
DateTime now;
RTC_DS3231 rtc;
bool dis_rtc = false; // true to disable RTC

// test
uint8_t temperature = 0;
uint8_t humidity = 0;
uint16_t co2 = 0;
unsigned long loop_timer_short = 0;
unsigned long loop_timer_long = 0;

// fridge disable function ON/OFF
bool OTA_var = true;
bool fast_calibration = false;
bool enable_heating = true;
bool enable_humidify = true;
bool enable_light = true;
bool enable_fan = true;
bool sensor = true;
bool mhz = true;
bool sd = true;

// timing variables
bool SD_ON_var = true;
bool SD_OFF_var = false;

bool light_ON_var = true;
bool light_OFF_var = false;

bool fan_ON_var = true;
bool fan_OFF_var = true;

bool sensor_ON_var = true;
bool sensor_OFF_var = true;

bool water_ON_var = true;
bool water_OFF_var = true;

bool temp_ON_var = true;
bool temp_OFF_var = true;

bool ppm_ON_var = true;
bool ppm_OFF_var = true;

// For beginners
// LCDML_add(id, prev_layer, new_num, lang_char_array, callback_function)

LCDML_add(0, LCDML_0, 1, "Datascreen", mFunc_datascreen);
LCDML_add(1, LCDML_0, 2, "Programm", NULL);
LCDML_add(2, LCDML_0_2, 1, "Back", mFunc_back);
LCDML_add(3, LCDML_0_2, 2, "Kraeuterseitlinge", NULL);
LCDML_add(4, LCDML_0_2_2, 1, "Back", mFunc_back);
LCDML_add(5, LCDML_0_2_2, 2, "Prepare", NULL);
LCDML_add(6, LCDML_0_2_2, 3, "Fruit", NULL);
LCDML_add(7, LCDML_0_2, 3, "Austernpilze", NULL);
LCDML_add(8, LCDML_0_2_3, 1, "Back", mFunc_back);
LCDML_add(9, LCDML_0_2_3, 2, "Prepare", NULL);
LCDML_add(10, LCDML_0_2_3, 3, "Fruit", NULL);
LCDML_add(11, LCDML_0_2, 4, "Lions Mane", NULL);
LCDML_add(12, LCDML_0_2_4, 1, "Back", mFunc_back);
LCDML_add(13, LCDML_0, 3, "Settings", NULL);
LCDML_add(14, LCDML_0_3, 1, "Back", mFunc_back);
LCDML_add(15, LCDML_0_3, 2, "Temperature", NULL);
LCDML_add(16, LCDML_0_3_2, 1, "Back", mFunc_back);
LCDML_addAdvanced(17, LCDML_0_3_2, 2, NULL, "", mDyn_set_temp, 2, _LCDML_TYPE_dynParam);
LCDML_add(18, LCDML_0_3_2, 3, "permanent heating", NULL); //
LCDML_add(19, LCDML_0_3_2, 4, "enable heating", NULL); 
LCDML_add(20, LCDML_0_3_2, 5, "disable heating", NULL); 
LCDML_add(21, LCDML_0_3, 3, "Humidity", NULL);
LCDML_add(22, LCDML_0_3_3, 1, "Back", mFunc_back);
LCDML_addAdvanced(23, LCDML_0_3_3, 2, NULL, "", mDyn_set_hum, 2, _LCDML_TYPE_dynParam);
LCDML_add(24, LCDML_0_3_3, 3, "spray", mFunc_spray); 
LCDML_add(25, LCDML_0_3_3_3, 1, "Back", mFunc_back);
LCDML_addAdvanced(26, LCDML_0_3_3_3, 2, NULL, "spray 10s", mFunc_spray, 1, _LCDML_TYPE_default);
LCDML_addAdvanced(27, LCDML_0_3_3_3, 3, NULL, "spray 30s", mFunc_spray, 2, _LCDML_TYPE_default);
LCDML_addAdvanced(28, LCDML_0_3_3_3, 4, NULL, "spray 60s", mFunc_spray, 3, _LCDML_TYPE_default);
LCDML_addAdvanced(29, LCDML_0_3_3, 4, NULL, "", mDyn_set_water_ON, 4, _LCDML_TYPE_dynParam);
LCDML_addAdvanced(30, LCDML_0_3_3, 5, NULL, "", mDyn_set_water_OFF, 5, _LCDML_TYPE_dynParam);
LCDML_addAdvanced(31, LCDML_0_3_3, 6, NULL, "enable spraying", mFunc_status_spray, 1, _LCDML_TYPE_default);
LCDML_addAdvanced(32, LCDML_0_3_3, 7, NULL, "disable spraying", mFunc_status_spray, 2, _LCDML_TYPE_default);
LCDML_add(33, LCDML_0_3, 4, "Light", NULL);
LCDML_add(34, LCDML_0_3_4, 1, "Back", mFunc_back);
LCDML_addAdvanced(35, LCDML_0_3_4, 2, NULL, "", mDyn_set_light_ON, 2, _LCDML_TYPE_dynParam);
LCDML_addAdvanced(36, LCDML_0_3_4, 3, NULL, "", mDyn_set_light_OFF, 3, _LCDML_TYPE_dynParam);
LCDML_addAdvanced(37, LCDML_0_3_4, 4, NULL, "Light On", mFunc_led, 1, _LCDML_TYPE_default);
LCDML_addAdvanced(38, LCDML_0_3_4, 5, NULL, "Light Off", mFunc_led, 2, _LCDML_TYPE_default);
LCDML_add(39, LCDML_0_3, 5, "Air", NULL);
LCDML_add(40, LCDML_0_3_5, 1, "Back", mFunc_back);
LCDML_addAdvanced(41, LCDML_0_3_5, 2, NULL, "", mDyn_set_fan_ON, 2, _LCDML_TYPE_dynParam);
LCDML_addAdvanced(42, LCDML_0_3_5, 3, NULL, "", mDyn_set_fan_OFF, 3, _LCDML_TYPE_dynParam);
LCDML_add(43, LCDML_0, 4, "Data", NULL); //
LCDML_add(44, LCDML_0_4, 1, "Back", mFunc_back); //
LCDML_add(45, LCDML_0_4, 2, "Show mean temp", NULL); //
LCDML_add(46, LCDML_0_4, 3, "show mean hum", NULL); //
LCDML_add(47, LCDML_0_4, 4, "show mean co2", NULL); //
LCDML_add(48, LCDML_0_4, 5, "SD card", NULL); //
LCDML_add(49, LCDML_0_4_5, 1, "Back", mFunc_back); //
LCDML_add(50, LCDML_0_4_5, 2, "read SD card", NULL); //
LCDML_add(51, LCDML_0_4_5, 3, "write SD card", NULL); //
LCDML_addAdvanced(52, LCDML_0_4_5, 4, NULL, "", mDyn_set_SD_time, 4, _LCDML_TYPE_dynParam); //
LCDML_add(53, LCDML_0_4, 6, "show mean wattage", NULL); //
LCDML_add(54, LCDML_0, 5, "Information", mFunc_information);

// Example for conditions (for example for a screensaver)
// 1. define a condition as a function of a boolean type -> return false = not displayed, return true = displayed
// 2. set the function name as callback (remove the braces '()' it gives bad errors)
// LCDMenuLib_add(id, prev_layer,     new_num, condition,   lang_char_array, callback_function, parameter (0-255), menu function type  )
LCDML_addAdvanced(55, LCDML_0, 6, COND_hide, "screensaver", mFunc_datascreen, 0, _LCDML_TYPE_default); // this menu function can be found on "LCDML_display_menuFunction" tab

// ***TIP*** Try to update _LCDML_DISP_cnt when you add a menu element.

// You can jump to a menu function from anywhere with
// LCDML.OTHER_jumpToFunc(mFunc_p2); // the parameter is the function name

// menu element count - last element id
// this value must be the same as the last menu element
#define _LCDML_DISP_cnt 55

// create menu
LCDML_createMenu(_LCDML_DISP_cnt);

void setup()
{

  // Start Serial
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // NVM store credentials, read credentials.cpp documentation
  // NVM_store_credentials();

  // NVM read credentials
  NVM_read_credentials();

  // Start Wifi
  WiFi.begin(ssid.c_str(), password.c_str());

  // WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  // Print ESP32 Local IP Address
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("");

  // Route for data_file_main / web page
  async_server_on();
  Serial.println("AsyncWebserver started");

  // WebSerial
  WebSerial.begin(&server);

  // Start server
  initWebSocket();
  server.begin();
  Serial.println("WebSocket inizialized");

  // config NTP time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // config OTA
  OTA.begin(); 


  // Set PINs
  pinMode(waterPIN, OUTPUT);
  pinMode(fanforwaterPIN, OUTPUT);
  pinMode(fanPIN, OUTPUT);
  pinMode(heatingPIN, OUTPUT);
  pinMode(lightPIN, OUTPUT);

  digitalWrite(waterPIN, false);
  digitalWrite(fanPIN, false);
  digitalWrite(heatingPIN, false);
  digitalWrite(lightPIN, false);
  Serial.println("Output pins set");

  // Start SD Card
  if (sd)
  {
  if (!SD.begin()) // 27
  {
    Serial.println("Card Mount Failed");
    dis_sd = true;
    sprintf(filename, "err");
  }
  Serial.println("SD Card inizialized");
  }

  // Start MHZ
  if (mhz)
  {
    myMHZ19.begin(Serial2);
    myMHZ19.autoCalibration(true);
    if (fast_calibration)
    {
      fast_calibrate_mhz();
    }
    Serial.println("MHZ-19B initialized");
  }

  //  BME680 start inizialisation 
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

  if (!bme_1.begin()) {
    Serial.println("Could not find a valid BME680_1 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization for BME680
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

  bme_1.setTemperatureOversampling(BME680_OS_8X);
  bme_1.setHumidityOversampling(BME680_OS_2X);
  bme_1.setPressureOversampling(BME680_OS_4X);
  bme_1.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme_1.setGasHeater(320, 150); // 320*C for 150 ms
  Serial.println("BME6801/2 initialised");

  //Initialize LCD
  lcd.init();
  lcd.backlight();
  Serial.println("LCD initialised");

  LCDML_setup(_LCDML_DISP_cnt);
  LCDML.SCREEN_enable(mFunc_datascreen, 20000); // set to 10 seconds

  read_nvm_values();
  check_nvm();

  // Start RTC
  if (!rtc.begin())
  {
    Serial.println(F("Couldn't find RTC"));
    dis_rtc = true;
  }

  if (rtc.lostPower())
  {
    Serial.println("RTC lost power, let's set the time!");
    getLocalTime(&timeinfo);
    rtc.adjust(DateTime(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec));
  }
  Serial.println("RTC inizialized");
  
  Serial.println(OTA_var ? "OTA loaded" : "OTA deactivated");
  Serial.println(fast_calibration ? "MHZ calibration" : "MHZ calibration deactivated");
  Serial.println(enable_heating ? "Heating inizialized" : "Heating deactivated");
  Serial.println(enable_light ? "Light inizialized" : "Light deactivated");
  Serial.println(enable_humidify ? "Humidify inizialized" : "Humidify deactivated");
  Serial.println(enable_fan ? "Fan inizialized" : "Fan deactivated");
  Serial.println(sensor ? "Sensors inizialized" : "Sensors deactivated");
  Serial.println(mhz ? "MHZ loaded" : "MHZ deactivated");
  Serial.println(sd ? "SD loaded" : "SD deactivated");
  Serial.println("");

  sensor_control();

  TelnetStream.begin();

  Serial.println("Setup finished");
}

void loop()
{

  LCDML.loop_control();
  LCDML.loop_menu();
  OTA.handle();  

  //Telnet v0.4
    // if (TelnetStream.available() > 0) {
    // String message = "";
    // while (TelnetStream.available() > 0) {
    //   char c = TelnetStream.read();
    //   message += c;
    //   delay(1);
    // }
    //   ws.textAll(message);
    //   message.clear();  
    //   }
  //Telnet v0.4

  if (millis() >= loop_timer_short + 300)
  {
    // FAN CONTROL
    ventilation_control();

    // HUM CONTROL
    water_control();

    // HEAT CONTROL
    temperature_control();

    //  SD Control
    SD_control();

    //send_timer_value();

    //send_sensor_value();

    loop_timer_short = millis();
  }

  if (millis() >= loop_timer_long + 25000)
  {
    ws.cleanupClients();

    // light_timer();

    sensor_control();

    // co2_control();

    set_function();

    loop_timer_long = millis();
  }
}