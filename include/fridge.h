#include <LCDMenuLib2.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BME680.h>
#include <Average.h>
#include <MHZ19.h> 

// LCDMenulib
void lcdml_menu_display();
void lcdml_menu_clear();
void lcdml_menu_control();

// variable display_menuFunction
extern uint8_t g_func_timer_info;
extern unsigned long g_timer_1;
extern bool switch_screen;

// LCD Menu Display
extern uint8_t _LCDML_DISP_cols;
extern uint8_t _LCDML_DISP_rows;
extern uint8_t _LCDML_DSIP_use_header;
extern uint8_t _LCDML_DISP_cfg_cursor;            
extern uint8_t _LCDML_DISP_cfg_scrollbar;

//LCD
extern LCDMenuLib2_menu LCDML_0;
extern LCDMenuLib2 LCDML;
extern LiquidCrystal_I2C lcd;

//menu_fix
extern char* g_LCDML_DISP_lang_lcdml_table[254];
extern bool COND_hide();

// Encoder
void check_rotary();

// BME680
extern uint8_t BME_SCK;
extern uint8_t BME_MISO;
extern uint8_t BME_MOSI;
extern uint8_t BME_CS;
extern uint8_t BME_CS_1;
extern Adafruit_BME680 bme;
extern Adafruit_BME680 bme_1;

// MHZ19b
void fast_calibrate_mhz();
extern int16_t MHZ19BAUDRATE;
extern int8_t MH_Z19_Temp;
extern MHZ19 myMHZ19;    // Constructor for library
extern uint16_t avg_co2_test;
extern uint8_t RXD2;
extern uint8_t TXD2;

//average
extern Average<uint16_t> avg_co2_10;  
extern Average<float> avg_temp_10;  
extern Average<float> avg_hum_10;  
extern Average<float> avg_bar_10;  
extern Average<float> avg_air_10;  


// Sort out later
extern bool spray;
// extern bool heating;
extern uint16_t count;

void mDyn_set_hum(uint8_t line);
void mDyn_set_SD_time(uint8_t line);
void mDyn_set_temp(uint8_t line);
void mDyn_set_light_ON(uint8_t line);
void mDyn_set_light_OFF(uint8_t line);
void mDyn_set_fan_ON(uint8_t line);
void mDyn_set_fan_OFF(uint8_t line);
void mDyn_set_water_ON(uint8_t line);
void mDyn_set_water_OFF(uint8_t line);

// display_menuFunction
void mFunc_information(uint8_t param);
void mFunc_spray(uint8_t param);
void mFunc_led(uint8_t param);
void mFunc_status_spray(uint8_t param);
void mFunc_datascreen(uint8_t param);
void mFunc_back(uint8_t param);
// void mFunc_SD_read(uint8_t param);
// void mFunc_SD_write(uint8_t param);
void mFunc_status_heating(uint8_t param);
void mFunc_permanent_heating(uint8_t param);

//functions
void SD_control(DateTime now);
void SD_write_data();
void light_control(DateTime now);
void fan_control(DateTime now);
void sensor_control();
void co2_control();
void sensor_measurement(DateTime now);
void water_control(DateTime now);

//folder
extern char filename[];
extern char foldername[];
extern char foldername_sub[];

void mFunc_timer_info(uint8_t param);
void mFunc_p2(uint8_t param);
void mFunc_screensaver(uint8_t param);
void mFunc_goToRootMenu(uint8_t param);
void mFunc_jumpTo_timer_info(uint8_t param);
void mFunc_para(uint8_t param);
void mFunc_exampleEventHandling(uint8_t param);
// sort out later

// global bool variable 
extern bool SD_ON_var;
extern bool SD_OFF_var;

extern bool light_ON_var;
extern bool light_OFF_var;

extern bool fan_ON_var;
extern bool fan_OFF_var;

extern bool sensor_ON_var;
extern bool sensor_OFF_var;

extern bool water_ON_var;
extern bool water_OFF_var;

extern bool ppm_ON_var;
extern bool ppm_OFF_var;

extern bool temp_ON_var;
extern bool temp_OFF_var;

// manual control variable
extern bool hum_control_var;
extern bool fan_control_var;
extern bool temp_control_var;
extern bool light_control_var;

extern bool hum_man_var;
extern bool fan_man_var;
extern bool temp_man_var;
extern bool light_man_var;

// global PIN
extern uint8_t waterPIN;
extern uint8_t fanforwaterPIN;
extern uint8_t fanPIN;
extern uint8_t heatingPIN;
extern uint8_t lightPIN;

//global timing variable
extern uint8_t set_hum;
extern uint8_t SD_time;
extern uint8_t set_temp;
extern uint16_t set_co2;
extern uint8_t set_light_ON;
extern uint8_t set_light_OFF;
extern uint8_t set_fan_ON;
extern uint8_t set_fan_OFF;
extern uint8_t set_water_ON;
extern uint8_t set_water_OFF;
extern uint8_t set_temp_ON;
extern uint8_t set_temp_OFF;

// ON/OFF Functions
extern bool fast_calibration;
extern bool OTA_var;
extern bool enable_heating;
extern bool enable_humidify;
extern bool enable_light;
extern bool sensor;
extern bool mhz;
extern bool sd;
extern bool enable_fan;

// Variables for SD
// extern bool SD_ON_var;
// extern bool SD_OFF_var;
extern bool sd_directory_bool;
extern String sd_directory;
extern String response;
// Folder and Filenames for SD Card
extern char filename[];
// extern char foldername[];
// extern char foldername_sub[];
void SD_write_data();
String printDirectory(File dir);
extern File data_file_main;
extern bool dis_sd;

// send button state
void spraying(bool val);
void fanning(bool val);
void heating(bool val);
void lighting(bool val);

// timing target var store
extern unsigned long sd_target_time;
extern unsigned long water_target_time;
extern unsigned long temp_target_time;
extern unsigned long fan_target_time;
extern unsigned long light_target_time;
extern uint8_t light_store;
// test
extern unsigned long test_time;
extern unsigned long test_time_10;


// control 
void SD_control();
void water_control();
void temperature_control ();
void ventilation_control();
void light_timer();
void light_control();
void light_offline_control();

void set_function();
void send_timer_value();
void send_sensor_value();

// time keeping
String run_time(unsigned long var);
extern char timer[];
extern char timer_hour_min[];
String ntp_hour_min();
void printLocalTime();


