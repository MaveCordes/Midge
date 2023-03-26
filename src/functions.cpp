#include <header.h>
#include <fridge.h>

// SD Card Variables
char filename[16];

// target time holding var
unsigned long sd_target_time = 0;
unsigned long water_target_time = 0;
unsigned long temp_target_time = 0;
unsigned long fan_target_time = 0;
unsigned long light_target_time = 0;
uint8_t light_store;

void SD_control()
{
  if (sd)
  {
    if (SD_ON_var == true && SD_OFF_var == false)
    {
      char foldername[9];
      if (!getLocalTime(&timeinfo))
      {
        if (!dis_rtc)
        {
          now = rtc.now();
          sprintf(foldername, "/%i", now.year());
          SD.mkdir(foldername);
          sprintf(foldername, "%s/%02i", foldername, now.month());
          SD.mkdir(foldername);
          sprintf(filename, "%s/%02i.txt", foldername, now.day());
        }
        else
        {
          SD.mkdir("/emergency_saves");
          sprintf(filename, "/emergency_saves/data.txt");
        }
      }
      else
      {
        strftime(foldername, 9, "/%Y", &timeinfo);
        SD.mkdir(foldername);
        strftime(foldername, 9, "/%Y/%02m", &timeinfo);
        SD.mkdir(foldername);
        strftime(filename, 16, "/%Y/%02m/%02d.txt", &timeinfo);
      }

      sd_target_time += SD_time * 60000;
      SD_ON_var = false;
      SD_OFF_var = true;
    }

    if (millis() >= sd_target_time && SD_OFF_var == true)
    {
      SD_write_data();
      sd_target_time = millis();

      SD_ON_var = true;
      SD_OFF_var = false;
    }
  }
}

void SD_write_data()
{
  data_file_main = SD.open(filename, FILE_APPEND);
  if (data_file_main)
  {
    if (!getLocalTime(&timeinfo))
    {
      if (!dis_rtc)
      {
        now = rtc.now();
        char buf[] = "DD.MM.YY,hh:mm:ss";
        data_file_main.print(buf);
      }
      else
      {
        data_file_main.print("NOTIME");
      }
    }
    data_file_main.print(&timeinfo, "%d.%m.%Y,%H:%M:%S");
    data_file_main.print(String(",") + String(avg_hum_10.mean()));
    data_file_main.print(String(",") + String(avg_temp_10.mean()));
    data_file_main.print(String(",") + String(avg_bar_10.mean()));
    data_file_main.print(String(",") + String(avg_air_10.mean()));
    data_file_main.print(String(",") + String(rtc.getTemperature()));
    data_file_main.print(String(",") + String(myMHZ19.getTemperature()));
    data_file_main.print(String(",") + String(avg_co2_test));
    data_file_main.print(String(",") + String(set_fan_ON) + String(";") + String(set_fan_OFF));
    data_file_main.print(String(",") + String(set_water_ON) + String(";") + String(set_water_OFF));
    data_file_main.print(String(",") + String(set_light_ON) + String(";") + String(set_light_OFF));
    data_file_main.print(String(",") + String(set_temp_ON) + String(";") + String(set_temp_OFF));
    data_file_main.print(String(",") + String(set_hum));
    data_file_main.print(String(",") + String(set_temp));
    data_file_main.print(String(",") + String(set_co2));
    data_file_main.println("");
    data_file_main.close();
  }
}

void water_control()
{
  if (enable_humidify)
  {
    if (!hum_control_var)
    {
      if (water_ON_var == true && water_OFF_var == true && humidity < set_hum)
      {
        digitalWrite(waterPIN, true);
        digitalWrite(fanforwaterPIN, true);
        spraying(digitalRead(waterPIN));
        water_target_time += set_water_ON * 60000;
        water_ON_var = false;
        water_OFF_var = false;

        //test mit nur einem Lüfter
        // digitalWrite(fanPIN, true);
        // fanning(digitalRead(fanPIN));
        // fan_control_var = true;
        //test Ende
      }
       if (millis() >= water_target_time || humidity >= set_hum)
      {
        if (water_ON_var == false)
        {
          digitalWrite(waterPIN, false);
          digitalWrite(fanforwaterPIN, false);
          spraying(digitalRead(waterPIN));
          water_target_time = millis();
          water_target_time += set_water_OFF * 60000;
          water_ON_var = true;

          //test mit nur einem Lüfter
          // digitalWrite(fanPIN, false);
          // fanning(digitalRead(fanPIN));
          // fan_control_var = false;
          //test Ende
        }
        else
        {
          water_OFF_var = true;
        }
      }
    }
  }
}

void temperature_control()
{
  if (enable_heating)
  {
    if (!temp_control_var)
    {
      if (temp_ON_var == true && temp_OFF_var == true)
      {
        digitalWrite(heatingPIN, true);
        heating(digitalRead(heatingPIN));
        temp_target_time += set_temp_ON * 60000;
        temp_ON_var = false;
        temp_OFF_var = false;
      }

      if (millis() >= temp_target_time)
      {
        if (temp_ON_var == false)
        {
          digitalWrite(heatingPIN, false);
          heating(digitalRead(heatingPIN));
          temp_target_time = millis();
          temp_target_time += set_temp_OFF * 60000;
          temp_ON_var = true;
        }
        else
        {
          temp_OFF_var = true;
        }
      }
    }
  }
}

void ventilation_control()
{
  if (enable_fan)
  {
    if (!fan_control_var)
    {
      if (fan_ON_var == true && fan_OFF_var == true)
      {
        digitalWrite(fanPIN, true);
        fanning(digitalRead(fanPIN));
        fan_target_time += set_fan_ON * 60000;
        fan_ON_var = false;
        fan_OFF_var = false;
      }

      if (millis() >= fan_target_time)
      {
        if (fan_ON_var == false)
        {
          digitalWrite(fanPIN, false);
          fanning(digitalRead(fanPIN));
          fan_target_time = millis();
          fan_target_time += set_fan_OFF * 60000;
          fan_ON_var = true;
        }
        else
        {
          fan_OFF_var = true;
        }
      }
    }
  }
}

void check_nvm()
{
  if ((SD_time == 0) || (set_hum == 0) || (set_temp == 0) ||
      (set_water_ON == 0) || (set_water_OFF == 0) || (set_fan_ON == 0) ||
      (set_fan_OFF == 0))
  {
    Serial.println("NVM failed, resetting all variables");
    SD_time = 10;
    set_hum = 90;
    set_temp = 15;
    set_co2 = 1000;
    set_water_ON = 1;
    set_water_OFF = 10;
    set_fan_ON = 5;
    set_fan_OFF = 5;
    set_light_ON = 8;
    set_light_OFF = 16;
  }
  else
  {
    Serial.println("NVM inizialized");
  }
}

void read_nvm_values()
{
  preferences.begin("stored_values", true);
  SD_time = preferences.getUChar("SD_time", SD_time);
  set_hum = preferences.getUChar("set_hum", set_hum);
  set_temp = preferences.getUChar("set_temp", set_temp);
  set_co2 = preferences.getShort("set_co2", set_co2);
  set_water_ON = preferences.getUChar("set_water_ON", set_water_ON);
  set_water_OFF = preferences.getUChar("set_water_OFF", set_water_OFF);
  set_fan_ON = preferences.getUChar("set_fan_ON", set_fan_ON);
  set_fan_OFF = preferences.getUChar("set_fan_OFF", set_fan_OFF);
  set_light_ON = preferences.getUChar("set_light_ON", set_light_ON);
  set_light_OFF = preferences.getUChar("set_light_OFF", set_light_OFF);
  set_temp_ON = preferences.getUChar("set_temp_ON", set_temp_ON);
  set_temp_OFF = preferences.getUChar("set_temp_OFF", set_temp_OFF);

  OTA_var = preferences.getBool("OTA", OTA_var);
  fast_calibration = preferences.getBool("calibration", fast_calibration);
  enable_heating = preferences.getBool("enable_heating", enable_heating);
  enable_humidify = preferences.getBool("enable_humidify", enable_humidify);
  enable_light = preferences.getBool("enable_light", enable_light);
  enable_fan = preferences.getBool("enable_fan", enable_fan);
  sensor = preferences.getBool("sensor", sensor);
  mhz = preferences.getBool("mhz", mhz);
  sd = preferences.getBool("sd", sd);
  preferences.end();
}

void NVM_store_credentials()
{
  preferences.begin("credentials", false);
  preferences.putString("ssid", ssid);
  preferences.putString("password", password);
  preferences.putString("http_username", http_username);
  preferences.putString("http_password", http_password);
  Serial.println("Network Credentials Saved using Preferences");
  preferences.end();
}

void NVM_read_credentials()
{
  preferences.begin("credentials", true);
  ssid = preferences.getString("ssid", "");
  password = preferences.getString("password", "");
  http_username = preferences.getString("http_username", "");
  http_password = preferences.getString("http_password", "");
  preferences.end();
}

void light_timer()
{
  if (enable_light)
  {
    if (!light_control_var)
    {
      if (!getLocalTime(&timeinfo))
      {
        if (!dis_rtc)
        {
          now = rtc.now();
          light_store = now.hour();
          light_control();
        }
        else
        {
          light_offline_control();
        }
      }
      else
      {
        char hour[3];
        strftime(hour, 3, "%H", &timeinfo);
        light_store = atoi(hour);
        light_control();
      }
    }
  }
}

void light_control()
{
  if (light_ON_var == false || light_OFF_var == false)
  {
    if (light_store >= set_light_ON && light_store < set_light_OFF)
    {
      digitalWrite(lightPIN, true);
      lighting(digitalRead(lightPIN));
      light_ON_var = true;
      light_OFF_var = true;
    }
  }

  if (light_ON_var == true || light_OFF_var == true)
  {
    if (light_store >= set_light_OFF || light_store < set_light_ON)
    {
      digitalWrite(lightPIN, false);
      lighting(digitalRead(lightPIN));
      light_ON_var = false;
      light_OFF_var = false;
    }
  }
}

void light_offline_control()
{

  if (light_ON_var == true && light_OFF_var == true)
  {
    Serial.println("light on");
    digitalWrite(lightPIN, true);
    lighting(digitalRead(lightPIN));
    light_target_time += set_light_ON * 3600000;
    light_ON_var = false;
    light_OFF_var = false;
  }

  if (millis() >= light_target_time)
  {
    if (light_ON_var == false)
    {
      Serial.println("light off");
      digitalWrite(lightPIN, false);
      lighting(digitalRead(lightPIN));
      light_target_time = millis();
      light_target_time += set_light_OFF * 3600000;
      light_ON_var = true;
    }
    else
    {
      light_OFF_var = true;
    }
  }
}

void spraying(bool val)
{
  doc["b"] = true;
  doc["h_btn"] = val;
  size_t len = serializeJson(doc, json_data);
  ws.textAll(json_data, len);
  doc.clear();

  doc["i"] = true;
  if (humidity <= 50)
  {
    doc["h_ico"] = 1;
  }
  else if (humidity > 50 && humidity <= 85)
  {
    doc["h_ico"] = 2;
  }
  else
  {
    doc["h_ico"] = 3;
  };
  len = serializeJson(doc, json_data);
  ws.textAll(json_data, len);
  doc.clear();
}

void fanning(bool val)
{
  doc["p1"] = true;
  if (val)
  {
    doc["f"] = "ON";
  }
  else
  {
    doc["f"] = "OFF";
  };
  size_t len = serializeJson(doc, json_data);
  ws.textAll(json_data, len);
  doc.clear();

  doc["i"] = true;
  doc["f_ico"] = val;
  if (co2 <= 1000)
  {
    doc["c_ico"] = true;
  }
  else
  {
    doc["h_ico"] = false;
  };
  len = serializeJson(doc, json_data);
  ws.textAll(json_data, len);
  doc.clear();

  doc["b"] = true;
  doc["f_btn"] = val;
  len = serializeJson(doc, json_data);
  ws.textAll(json_data, len);
  doc.clear();
}

void heating(bool val)
{
  doc["b"] = true;

  doc["t_btn"] = val;

  size_t len = serializeJson(doc, json_data);
  ws.textAll(json_data, len);
  doc.clear();

  doc["i"] = true;
  if (temperature <= 10)
  {
    doc["t_ico"] = 1;
  }
  else if (temperature > 10 && temperature <= 15)
  {
    doc["t_ico"] = 2;
  }
  else if (temperature > 15 && temperature <= 20)
  {
    doc["t_ico"] = 3;
  }
  else
  {
    doc["t_ico"] = 4;
  };
  len = serializeJson(doc, json_data);
  ws.textAll(json_data, len);
  doc.clear();
}

void lighting(bool val)
{
  doc["b"] = true;

  doc["l_btn"] = val;

  size_t len = serializeJson(doc, json_data);
  ws.textAll(json_data, len);
  doc.clear();

  doc["p1"] = true;
  ntp_hour_min();
  if (val)
  {
    doc["l"] = "ON " + String(timer_hour_min);
  }
  else
  {
    doc["l"] = "OFF " + String(timer_hour_min);
  };

  len = serializeJson(doc, json_data);
  ws.textAll(json_data, len);
  doc.clear();

  doc["i"] = true;

  doc["l_ico"] = val;

  len = serializeJson(doc, json_data);
  ws.textAll(json_data, len);
  doc.clear();
}

String run_time(unsigned long var)
{

  unsigned long val;
  val = (var - millis());
  // val = var;
  uint8_t running_hr = val / 3600000;
  val = val - 3600000 * running_hr;
  uint8_t running_min = val / 60000;
  val = val - 60000 * running_min;
  uint8_t running_sec = val / 1000;
  sprintf(timer, "%02im %02is", running_min, running_sec);

  return timer;
}

String ntp_hour_min()
{
  if (!getLocalTime(&timeinfo))
  {
    if (!dis_rtc)
    {
      now = rtc.now();
      sprintf(timer_hour_min, "%02i:%02i", now.hour(), now.minute());
    }
    else
    {
      sprintf(timer_hour_min, "err");
    }
  }
  else
  {
    char chart[6];
    strftime(chart, 6, "%R", &timeinfo);
    sprintf(timer_hour_min, "%s", chart);
  }

  return timer_hour_min;
}

void set_function()
{
  doc["p2"] = true;

  doc["h_t"] = set_hum;
  doc["t_t"] = set_temp;
  doc["c_t"] = set_co2;
  doc["sd_t"] = SD_time;

  doc["on_h"] = set_water_ON;
  doc["on_t"] = set_temp_ON;
  doc["on_f"] = set_fan_ON;
  doc["on_l"] = set_light_ON;

  doc["off_h"] = set_water_OFF;
  doc["off_t"] = set_temp_OFF;
  doc["off_f"] = set_fan_OFF;
  doc["off_l"] = set_light_OFF;

  len = serializeJson(doc, json_data);
  ws.textAll(json_data, len);
  doc.clear();
}

void send_timer_value()
{
  doc["p2"] = true;
  run_time(water_target_time);
  doc["h_r"] = timer;
  run_time(temp_target_time);
  doc["t_r"] = timer;
  run_time(fan_target_time);
  doc["f_r"] = timer;
  ntp_hour_min();
  doc["l_r"] = timer_hour_min;
  if (sd)
  {
    run_time(sd_target_time);
    doc["sd_r"] = timer;
  }
  else
  {
    doc["sd_r"] = "disabled";
  }
  len = serializeJson(doc, json_data);
  ws.textAll(json_data, len);
  doc.clear();
}

void send_sensor_value()
{
  doc["s"] = true;
  doc["h"] = humidity;
  doc["t"] = temperature;
  doc["c"] = co2;
  doc["sd"] = filename;
  len = serializeJson(doc, json_data);
  ws.textAll(json_data, len);
  doc.clear();
}

// MHZ Calibration
void fast_calibrate_mhz()
{
  Serial.print("ABC Status: ");
  myMHZ19.getABC() ? Serial.println("ON") : Serial.println("OFF");
  Serial.println("Calibrating..");
  myMHZ19.calibrate();
}

void sensor_control()
{

  // sensor_ON_var = false;
  // sensor_OFF_var = true;

  // may cause problem
  if (!bme.performReading())
  {
    Serial.println("Failed to perform reading :(");
    return;
  }

  float bme_temperature = bme.temperature;
  float bme_humidity = bme.humidity;
  float bme_pressure = bme.pressure;
  bme_pressure /= 100;
  float bme_air = bme.gas_resistance;
  bme_air /= 1000;

  if (!bme_1.performReading())
  {
    Serial.println("Failed to perform reading :(");
    return;
  }

  float bme_temperature2 = bme_1.temperature;
  float bme_humidity2 = bme_1.humidity;
  float bme_pressure2 = bme_1.pressure;
  bme_pressure2 /= 100;
  float bme_air2 = bme_1.gas_resistance;
  bme_air2 /= 1000;

  float temp10 = ((bme_temperature + bme_temperature2) / 2);
  float hum10 = ((bme_humidity + bme_humidity2) / 2);

  temperature = temp10;
  humidity = hum10;

  float bar10 = ((bme_pressure + bme_pressure2) / 2);
  float air10 = ((bme_air + bme_air2) / 2);

  avg_temp_10.push(temp10);
  avg_hum_10.push(hum10);
  avg_bar_10.push(bar10);
  avg_air_10.push(air10);

  // Serial.println((now.timestamp(DateTime::TIMESTAMP_FULL)));
  Serial.println("SENSOR MEASUREMENT");
  
  iSerial.print("BME_1_hum:");
  iSerial.println(bme_humidity);
  iSerial.print("BME_2_hum:");
  iSerial.println(bme_humidity2);
  iSerial.print("BME_hum10:");
  iSerial.println(hum10);

  // Serial.println();
}

void co2_control()
{

  // if (ppm_ON_var == true) {

  int co2_ppm;

  // ppm_ON_var = false;
  // ppm_OFF_var = true;

  // take co2 and temp measurement from MH-Z19B and average it over 10 and 50 measurements
  co2_ppm = myMHZ19.getCO2();
  uint8_t MH_Z19_Temp_int = myMHZ19.getTemperature();
  avg_co2_10.push(co2_ppm);
  avg_co2_test = avg_co2_10.mean();
  co2 = co2_ppm;

  // Serial.println((now.timestamp(DateTime::TIMESTAMP_FULL)));
  Serial.println("CO2 MEASUREMENT");
  Serial.print("CO2: ");
  Serial.println(co2_ppm);
  Serial.print("CO2 avg: ");
  Serial.println(avg_co2_test);
  Serial.print("CO2 temp: ");
  Serial.println(MH_Z19_Temp_int);
  Serial.println();
}

void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void printHeapInfo() {
  uint32_t freeHeap = ESP.getFreeHeap();
  uint32_t totalHeap = ESP.getHeapSize();
  iSerial.println("");
  iSerial.print("Free heap memory, total heap: ");
  iSerial.print(freeHeap);
  iSerial.print(",");
  iSerial.println(totalHeap);
  iSerial.println("");
}
