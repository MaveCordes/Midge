#include <header.h>
#include <fridge.h>

// HTML Placeholder
String placeholder;

// Replaces placeholder with Webserver Values
String processor(const String &var)
{
  // Values Page 1
  if (var == "TEMPERATURE")
  {
    placeholder = String(temperature);
    return placeholder;
  }
  else if (var == "HUMIDITY")
  {
    placeholder = String(humidity);
    return placeholder;
  }
  else if (var == "CO2")
  {
    placeholder = String(co2);
    return placeholder;
  }
  else if (var == "SD_CARD_NAME")
  {
    placeholder = String(filename);
    return placeholder;
  }
  // Icon Page 1
  else if (var == "FAN")
  {
    if (digitalRead(fanPIN))
    {
      placeholder = "ON";
    }
    else
    {
      placeholder = "OFF";
    }
    return placeholder;
  }
  else if (var == "TEMP_ICON_LOW")
  {
    if (temperature <= 10)
    {
      placeholder = "style='display: block'";
    }
    else if (temperature > 10 && temperature <= 15)
    {
      placeholder = "style='display: none'";
    }
    else if (temperature > 15 && temperature <= 20)
    {
      placeholder = "style='display: none'";
    }
    else
    {
      placeholder = "style='display: none'";
    };
    return placeholder;
  }
  else if (var == "TEMP_ICON_2ND")
  {
    if (temperature <= 10)
    {
      placeholder = "style='display: none'";
    }
    else if (temperature > 10 && temperature <= 15)
    {
      placeholder = "style='display: block'";
    }
    else if (temperature > 15 && temperature <= 20)
    {
      placeholder = "style='display: none'";
    }
    else
    {
      placeholder = "style='display: none'";
    };
    return placeholder;
  }
  else if (var == "TEMP_ICON_3RD")
  {
    if (temperature <= 10)
    {
      placeholder = "style='display: none'";
    }
    else if (temperature > 10 && temperature <= 15)
    {
      placeholder = "style='display: none'";
    }
    else if (temperature > 15 && temperature <= 20)
    {
      placeholder = "style='display: block'";
    }
    else
    {
      placeholder = "style='display: none'";
    };
    return placeholder;
  }
  else if (var == "TEMP_ICON_HIGH")
  {
    if (temperature <= 10)
    {
      placeholder = "style='display: none'";
    }
    else if (temperature > 10 && temperature <= 15)
    {
      placeholder = "style='display: none'";
    }
    else if (temperature > 15 && temperature <= 20)
    {
      placeholder = "style='display: none'";
    }
    else
    {
      placeholder = "style='display: block'";
    };
    return placeholder;
  }
  else if (var == "HUM_ICON_LOW")
  {
    if (humidity <= 50)
    {
      placeholder = "style='display: block'";
    }
    else if (humidity > 50 && humidity <= 85)
    {
      placeholder = "style='display: none'";
    }
    else
    {
      placeholder = "style='display: none'";
    };
    return placeholder;
  }
  else if (var == "HUM_ICON_2ND")
  {
    if (humidity <= 50)
    {
      placeholder = "style='display: none'";
    }
    else if (humidity > 50 && humidity <= 85)
    {
      placeholder = "style='display: block'";
    }
    else
    {
      placeholder = "style='display: none'";
    };
    return placeholder;
  }
  else if (var == "HUM_ICON_HIGH")
  {
    if (humidity <= 50)
    {
      placeholder = "style='display: none'";
    }
    else if (humidity > 50 && humidity <= 85)
    {
      placeholder = "style='display: none'";
    }
    else
    {
      placeholder = "style='display: block'";
    };
    return placeholder;
  }
  else if (var == "CO2_ICON_LOW")
  {
    if (co2 <= 1000)
    {
      placeholder = "style='display: block'";
    }
    else
    {
      placeholder = "style='display: none'";
    };
    return placeholder;
  }
  else if (var == "CO2_ICON_HIGH")
  {
    if (co2 <= 1000)
    {
      placeholder = "style='display: none'";
    }
    else
    {
      placeholder = "style='display: block'";
    };
    return placeholder;
  }
  else if (var == "FAN_ICON_ON")
  {
    if (digitalRead(fanPIN))
    {
      placeholder = "style='display: block'";
    }
    else
    {
      placeholder = "style='display: none'";
    };
    return placeholder;
  }
  else if (var == "FAN_ICON_OFF")
  {
    if (digitalRead(fanPIN))
    {
      placeholder = "style='display: none'";
    }
    else
    {
      placeholder = "style='display: block'";
    };
    return placeholder;
  }
  else if (var == "LIGHT_CLASS")
  {
    if (digitalRead(lightPIN))
    {
      placeholder = "light";
    }
    else
    {
      placeholder = "light_off";
    };
    return placeholder;
  }
  else if (var == "LIGHTTIME")
  {
    ntp_hour_min();
    if (digitalRead(lightPIN))
    {
      placeholder = "ON ";
      placeholder += String(timer_hour_min);
    }
    else
    {
      placeholder = "OFF ";
      placeholder += String(timer_hour_min);
    };
    return placeholder;
  }
  else if (var == "LIGHT_ICON_ON")
  {
    if (digitalRead(lightPIN))
    {
      placeholder = "style='display: block'";
    }
    else
    {
      placeholder = "style='display: none'";
    };
    return placeholder;
  }
  else if (var == "LIGHT_ICON_OFF")
  {
    if (digitalRead(lightPIN))
    {
      placeholder = "style='display: none'";
    }
    else
    {
      placeholder = "style='display: block'";
    };
    return placeholder;
  }

  else if (var == "SD_YEAR")
  {
    if (!getLocalTime(&timeinfo))
    {
      placeholder = "2022";
    }
    char chart[5];
    strftime(chart, 5, "%Y", &timeinfo);
    placeholder = chart;
    return placeholder;
  }
  else if (var == "SD_MONTH")
  {
    if (!getLocalTime(&timeinfo))
    {
      placeholder = "2022/06";
    }
    char chart[9];
    strftime(chart, 9, "%Y/%m", &timeinfo);
    placeholder = chart;
    return placeholder;
  }
  else if (var == "SD_MONTH_DAY")
  {
    if (!getLocalTime(&timeinfo))
    {
      placeholder = "Month";
    }
    char chart[9];
    strftime(chart, 9, "%B", &timeinfo);
    placeholder = chart;
    return placeholder;
  }

  else if (var == "SDPLACEHOLDER")
  {
    if (!dis_sd)
    {
      if (sd_directory_bool)
      {
        data_file_main = SD.open(sd_directory);
      }
      else
      {
        data_file_main = SD.open("/");
      }
      response = "";
      placeholder = printDirectory(data_file_main);
      data_file_main.close();
      placeholder.toLowerCase();
    }
    else
    {
      placeholder = "err";
    }

    return placeholder;
  }

  // Target Page 2
  else if (var == "TARGET_VALUE_HUMIDITY")
  {
    placeholder = String(set_hum);
    return placeholder;
  }
  else if (var == "TARGET_VALUE_TEMPERATURE")
  {
    placeholder = String(set_temp);
    return placeholder;
  }
  else if (var == "TARGET_VALUE_SD_TIME")
  {
    placeholder = String(SD_time);
    return placeholder;
  }
  else if (var == "TARGET_VALUE_CO2")
  {
    placeholder = String(set_co2);
    return placeholder;
  }

  // ON OFF Time Page 2
  else if (var == "ON_TIME_HUMIDITY")
  {
    placeholder = String(set_water_ON);
    return placeholder;
  }
  else if (var == "ON_TIME_TEMPERATURE")
  {
    placeholder = String(set_temp_ON);
    return placeholder;
  }
  else if (var == "ON_TIME_FAN")
  {
    placeholder = String(set_fan_ON);
    return placeholder;
  }
  else if (var == "ON_TIME_LIGHT")
  {
    placeholder = String(set_light_ON);
    return placeholder;
  }
  else if (var == "OFF_TIME_HUMIDITY")
  {
    placeholder = String(set_water_OFF);
    return placeholder;
  }
  else if (var == "OFF_TIME_TEMPERATURE")
  {
    placeholder = String(set_temp_OFF);
    return placeholder;
  }
  else if (var == "OFF_TIME_FAN")
  {
    placeholder = String(set_fan_OFF);
    return placeholder;
  }
  else if (var == "OFF_TIME_LIGHT")
  {
    placeholder = String(set_light_OFF);
    return placeholder;
  }

  // Status Button Page 2
  else if (var == "HUMIDITY_BUTTON_ON")
  {
    if (digitalRead(waterPIN) == true)
    {
      placeholder = "style='display: block'";
    }
    else
    {
      placeholder = "style='display: none'";
    }
    return placeholder;
  }
  else if (var == "HUMIDITY_BUTTON_OFF")
  {
    if (digitalRead(waterPIN) == true)
    {
      placeholder = "style='display: none'";
    }
    else
    {
      placeholder = "style='display: block'";
    }
    return placeholder;
  }
  else if (var == "TEMPERATURE_BUTTON_ON")
  {
    if (digitalRead(heatingPIN) == true)
    {
      placeholder = "style='display: block'";
    }
    else
    {
      placeholder = "style='display: none'";
    }
    return placeholder;
  }
  else if (var == "TEMPERATURE_BUTTON_OFF")
  {
    if (digitalRead(heatingPIN) == true)
    {
      placeholder = "style='display: none'";
    }
    else
    {
      placeholder = "style='display: block'";
    }
    return placeholder;
  }
  else if (var == "FAN_BUTTON_ON")
  {
    if (digitalRead(fanPIN) == true)
    {
      placeholder = "style='display: block'";
    }
    else
    {
      placeholder = "style='display: none'";
    }
    return placeholder;
  }
  else if (var == "FAN_BUTTON_OFF")
  {
    if (digitalRead(fanPIN) == true)
    {
      placeholder = "style='display: none'";
    }
    else
    {
      placeholder = "style='display: block'";
    }
    return placeholder;
  }
  else if (var == "LIGHT_BUTTON_ON")
  {
    if (digitalRead(lightPIN))
    {
      placeholder = "style='display: block'";
    }
    else
    {
      placeholder = "style='display: none'";
    }
    return placeholder;
  }
  else if (var == "LIGHT_BUTTON_OFF")
  {
    if (digitalRead(lightPIN))
    {
      placeholder = "style='display: none'";
    }
    else
    {
      placeholder = "style='display: block'";
    }
    return placeholder;
  }

  // timekeeping page 2
  else if (var == "HUM_RUNNING_TIME")
  {
    placeholder = "calc";
    return placeholder;
  }
  else if (var == "TEMPERATURE_RUNNING_TIME")
  {
    placeholder = "calc";
    return placeholder;
  }
  else if (var == "FAN_RUNNING_TIME")
  {
    placeholder = "calc";
    return placeholder;
  }
  else if (var == "LIGHT_RUNNING_TIME")
  {
    ntp_hour_min();
    placeholder = timer_hour_min;
    return placeholder;
  }
  else if (var == "SD_CARD_TIMER")
  {
    if (!dis_sd)
    {
      run_time(sd_target_time);
      placeholder = timer;
    }
    else
    {
      placeholder = "err";
    }
    return placeholder;
  }

  // Toggle Indicator Page 2 Bottom
  else if (var == "HUM_TOGGLE_INDICATOR")
  {
    if (digitalRead(waterPIN) == true)
    {
      placeholder = "checked= ''";
    }
    else
    {
      placeholder = "";
    }
    return placeholder;
  }
  else if (var == "TEMP_TOGGLE_INDICATOR")
  {
    if (digitalRead(heatingPIN) == HIGH)
    {
      placeholder = "checked= ''";
    }
    else
    {
      placeholder = "";
    }
    return placeholder;
  }
  else if (var == "FAN_TOGGLE_INDICATOR")
  {
    if (digitalRead(fanPIN) == true)
    {
      placeholder = "checked= ''";
    }
    else
    {
      placeholder = "";
    };
    return placeholder;
  }
  else if (var == "LIGHT_TOGGLE_INDICATOR")
  {
    if (digitalRead(lightPIN))
    {
      placeholder = "checked= ''";
    }
    else
    {
      placeholder = "";
    }
    return placeholder;
  }

  // Disable Buttons Page 2
  else if (var == "TOGGLE_OTA")
  {
    if (OTA_var == 1)
    {
      placeholder = "Disable";
    }
    else
    {
      placeholder = "Activate";
    };
    return placeholder;
  }
  else if (var == "CLASS_OTA")
  {
    if (OTA_var == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-secondary'";
    };
    return placeholder;
  }
  else if (var == "TOGGLE_CAL")
  {
    if (fast_calibration == 1)
    {
      placeholder = "Disable";
    }
    else
    {
      placeholder = "Activate";
    };
    return placeholder;
  }
  else if (var == "CLASS_CAL")
  {
    if (fast_calibration == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-secondary'";
    };
    return placeholder;
  }
  else if (var == "TOGGLE_TEMP")
  {
    if (enable_heating == 1)
    {
      placeholder = "Disable";
    }
    else
    {
      placeholder = "Activate";
    };
    return placeholder;
  }
  else if (var == "CLASS_TEMP")
  {
    if (enable_heating == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-secondary'";
    };
    return placeholder;
  }
  else if (var == "TOGGLE_HUM")
  {
    if (enable_humidify == 1)
    {
      placeholder = "Disable";
    }
    else
    {
      placeholder = "Activate";
    };
    return placeholder;
  }
  else if (var == "CLASS_HUM")
  {
    if (enable_humidify == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-secondary'";
    };
    return placeholder;
  }
  else if (var == "TOGGLE_LIGHT")
  {
    if (enable_light == 1)
    {
      placeholder = "Disable";
    }
    else
    {
      placeholder = "Activate";
    };
    return placeholder;
  }
  else if (var == "CLASS_LIGHT")
  {
    if (enable_light == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-secondary'";
    };
    return placeholder;
  }
  else if (var == "TOGGLE_FAN")
  {
    if (enable_fan == 1)
    {
      placeholder = "Disable";
    }
    else
    {
      placeholder = "Activate";
    };
    return placeholder;
  }
  else if (var == "CLASS_FAN")
  {
    if (enable_fan == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-secondary'";
    };
    return placeholder;
  }
  else if (var == "TOGGLE_BME")
  {
    if (sensor == 1)
    {
      placeholder = "Disable";
    }
    else
    {
      placeholder = "Activate";
    };
    return placeholder;
  }
  else if (var == "CLASS_BME")
  {
    if (sensor == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-secondary'";
    };
    return placeholder;
  }
  else if (var == "TOGGLE_MHZ")
  {
    if (mhz == 1)
    {
      placeholder = "Disable";
    }
    else
    {
      placeholder = "Activate";
    };
    return placeholder;
  }
   else if (var == "TOGGLE_SD")
  {
    if (sd == 1)
    {
      placeholder = "Disable";
    }
    else
    {
      placeholder = "Activate";
    };
    return placeholder;
  }
  else if (var == "CLASS_MHZ")
  {
    if (mhz == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-secondary'";
    };
    return placeholder;
  }
    else if (var == "CLASS_SD")
  {
    if (sd == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-secondary'";
    };
    return placeholder;
  }
  else if (var == "CLASS_HUM_CONTROL")
  {
    if (hum_control_var == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-light'";
    };
    return placeholder;
  }
  else if (var == "CLASS_FAN_CONTROL")
  {
    if (fan_control_var == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-light'";
    };
    return placeholder;
  }
  else if (var == "CLASS_TEMP_CONTROL")
  {
    if (temp_control_var == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-light'";
    };
    return placeholder;
  }
  else if (var == "CLASS_LIGHT_CONTROL")
  {
    if (light_control_var == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-light'";
    };
    return placeholder;
  }
  else if (var == "HUM_MAN_TEXT")
  {
    if (hum_man_var == 1)
    {
      placeholder = "on";
    }
    else
    {
      placeholder = "off";
    };
    return placeholder;
  }
  else if (var == "FAN_MAN_TEXT")
  {
    if (fan_man_var == 1)
    {
      placeholder = "on";
    }
    else
    {
      placeholder = "off";
    };
    return placeholder;
  }
  else if (var == "TEMP_MAN_TEXT")
  {
    if (temp_man_var == 1)
    {
      placeholder = "on";
    }
    else
    {
      placeholder = "off";
    };
    return placeholder;
  }
  else if (var == "LIGHT_MAN_TEXT")
  {
    if (light_man_var == 1)
    {
      placeholder = "on";
    }
    else
    {
      placeholder = "off";
    };
    return placeholder;
  }
  else if (var == "CLASS_HUM_MAN")
  {
    if (hum_man_var == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-secondary'";
    };
    return placeholder;
  }
  else if (var == "CLASS_TEMP_MAN")
  {
    if (temp_man_var == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-secondary'";
    };
    return placeholder;
  }
  else if (var == "CLASS_FAN_MAN")
  {
    if (fan_man_var == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-secondary'";
    };
    return placeholder;
  }
  else if (var == "CLASS_LIGHT_MAN")
  {
    if (light_man_var == 1)
    {
      placeholder = "class='btn btn-primary'";
    }
    else
    {
      placeholder = "class='btn btn-secondary'";
    };
    return placeholder;
  }
  else if (var == "HUM_MAN_DIS")
  {
    if (hum_control_var == 1)
    {
      placeholder = "enabled";
    }
    else
    {
      placeholder = "disabled";
    };
    return placeholder;
  }
  else if (var == "FAN_MAN_DIS")
  {
    if (fan_control_var == 1)
    {
      placeholder = "enabled";
    }
    else
    {
      placeholder = "disabled";
    };
    return placeholder;
  }
  else if (var == "TEMP_MAN_DIS")
  {
    if (temp_control_var == 1)
    {
      placeholder = "enabled";
    }
    else
    {
      placeholder = "disabled";
    };
    return placeholder;
  }
  else if (var == "LIGHT_MAN_DIS")
  {
    if (light_control_var == 1)
    {
      placeholder = "enabled";
    }
    else
    {
      placeholder = "disabled";
    };
    return placeholder;
  }
  return String();
}