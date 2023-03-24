#include <header.h>
#include <fridge.h>

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
    {
        data[len] = 0;
        String message = (char *)data;

        if (message.indexOf("hum_target") >= 0)
        {
            // String input_target = message.substring(0, message.indexOf("&"));
            String input_value = message.substring(message.indexOf("&") + 1, message.length());

            if (input_value.toInt() > 0)
            {
                set_hum = input_value.toInt();
                store_value("set_hum", set_hum);
            }
            check_nvm();
            set_function();
            return;
        }
        else if (message.indexOf("temp_target") >= 0)
        {
            String input_value = message.substring(message.indexOf("&") + 1, message.length());

            if (input_value.toInt() > 0)
            {
                set_temp = input_value.toInt();
                store_value("set_temp", set_temp);
            }
            check_nvm();
            set_function();
            return;
        }
        else if (message.indexOf("co2_target") >= 0)
        {
            String input_value = message.substring(message.indexOf("&") + 1, message.length());

            if (input_value.toInt() > 0)
            {
                set_co2 = input_value.toInt();
                preferences.begin("stored_values", false);
                preferences.putShort("set_co2", set_co2);
                preferences.end();
            }
            check_nvm();
            set_function();
            return;
        }
        else if (message.indexOf("sd_time_target") >= 0)
        {
            String input_value = message.substring(message.indexOf("&") + 1, message.length());

            if (input_value.toInt() > 0)
            {
                SD_time = input_value.toInt();
                store_value("SD_time", SD_time);
                sd_target_time = millis();
                SD_ON_var = true;
                SD_OFF_var = false;
            }
            check_nvm();
            set_function();
            return;
        }
        else if (message.indexOf("hum_on_input") >= 0)
        {
            String input_value = message.substring(message.indexOf("&1") + 2, message.indexOf("%"));
            String input_value2 = message.substring(message.indexOf("&2") + 2, message.length());

            if (input_value.toInt() > 0)
            {
                set_water_ON = input_value.toInt();
                store_value("set_water_ON", set_water_ON);
            };
            if (input_value2.toInt() > 0)
            {
                set_water_OFF = input_value2.toInt();
                store_value("set_water_OFF", set_water_OFF);
            };
            water_target_time = millis();
            water_ON_var = true;
            water_OFF_var = true;
            check_nvm();
            set_function();
            return;
        }
        else if (message.indexOf("temp_on_input") >= 0)
        {
            String input_value = message.substring(message.indexOf("&1") + 2, message.indexOf("%"));
            String input_value2 = message.substring(message.indexOf("&2") + 2, message.length());

            if (input_value.toInt() > 0)
            {
                set_temp_ON = input_value.toInt();
                store_value("set_temp_ON", set_temp_ON);
            };
            if (input_value2.toInt() > 0)
            {
                set_temp_OFF = input_value2.toInt();
                store_value("set_temp_OFF", set_temp_OFF);
            };
            temp_target_time = millis();
            temp_ON_var = true;
            temp_OFF_var = true;
            check_nvm();
            set_function();
            return;
        }
        else if (message.indexOf("fan_on_input") >= 0)
        {
            String input_value = message.substring(message.indexOf("&1") + 2, message.indexOf("%"));
            String input_value2 = message.substring(message.indexOf("&2") + 2, message.length());

            if (input_value.toInt() > 0)
            {
                set_fan_ON = input_value.toInt();
                store_value("set_fan_ON", set_fan_ON);
            };
            if (input_value2.toInt() > 0)
            {
                set_fan_OFF = input_value2.toInt();
                store_value("set_fan_OFF", set_fan_OFF);
            };
            fan_target_time = millis();
            fan_ON_var = true;
            fan_OFF_var = true;
            check_nvm();
            set_function();
            return;
        }
        else if (message.indexOf("light_on_input") >= 0)
        {
            String input_value = message.substring(message.indexOf("&1") + 2, message.indexOf("%"));
            String input_value2 = message.substring(message.indexOf("&2") + 2, message.length());

            if (input_value.toInt() > 0)
            {
                set_light_ON = input_value.toInt();
                store_value("set_light_ON", set_light_ON);
            };
            if (input_value2.toInt() > 0)
            {
                set_light_OFF = input_value2.toInt();
                store_value("set_light_OFF", set_light_OFF);
            };
            light_target_time = millis();
            light_ON_var = true;
            light_OFF_var = false;
            check_nvm();
            set_function();
            return;
        }
        else if (strcmp((char *)data, "toogle_hum") == 0)
        {
            if (hum_control_var == true)
            {
                hum_control_var = false;
                digitalWrite(waterPIN, false);
                spraying(digitalRead(waterPIN));
                doc["m"] = true;
                doc["h_man"] = false;
                hum_man_var = false; 

                water_target_time = millis();
                water_ON_var = true;
                water_OFF_var = true;
            }
            else
            {
                hum_control_var = true;
                digitalWrite(waterPIN, false);
                spraying(digitalRead(waterPIN));
                doc["m"] = true;
                doc["h_man"] = true;
            }
        }
        else if (strcmp((char *)data, "hum_button_toggle") == 0)
        {
            if (hum_man_var == true)
            {
                digitalWrite(waterPIN, false);
                spraying(digitalRead(waterPIN));
                doc["m"] = true;
                hum_man_var = false;
                doc["h_en"] = false;
            }
            else
            {
                digitalWrite(waterPIN, true);
                spraying(digitalRead(waterPIN));
                doc["m"] = true;
                hum_man_var = true;
                doc["h_en"] = true;
            }
        }

        if (strcmp((char *)data, "toogle_fan") == 0)
        {
            if (fan_control_var == true)
            {
                fan_control_var = false;
                digitalWrite(fanPIN, false);
                fanning(digitalRead(fanPIN));
                doc["m"] = true;
                doc["f_man"] = false;
                fan_man_var = false; 

                fan_target_time = millis();
                fan_ON_var = true;
                fan_OFF_var = true;
            }
            else
            {
                fan_control_var = true;
                digitalWrite(fanPIN, false);
                fanning(digitalRead(fanPIN));
                doc["m"] = true;
                doc["f_man"] = true;
            }
        }
        else if (strcmp((char *)data, "fan_button_toggle") == 0)
        {
            if (fan_man_var == true)
            {
                digitalWrite(fanPIN, false);
                fanning(digitalRead(fanPIN));
                doc["m"] = true;
                fan_man_var = false;
                doc["f_en"] = false;
            }
            else
            {
                digitalWrite(fanPIN, true);
                fanning(digitalRead(fanPIN));
                doc["m"] = true;
                fan_man_var = true;
                doc["f_en"] = true;
            }
        }

        if (strcmp((char *)data, "toogle_temp") == 0)
        {
            if (temp_control_var == true)
            {
                temp_control_var = false;
                digitalWrite(heatingPIN, false);
                heating(digitalRead(heatingPIN));
                doc["m"] = true;
                doc["t_man"] = false;
                temp_man_var = false;

                temp_target_time = millis();
                temp_ON_var = true;
                temp_OFF_var = true;
            }
            else
            {
                temp_control_var = true;
                digitalWrite(heatingPIN, false);
                heating(digitalRead(heatingPIN));
                doc["m"] = true;
                doc["t_man"] = true;
            }
        }
        else if (strcmp((char *)data, "temp_button_toggle") == 0)
        {
            if (temp_man_var == true)
            {
                digitalWrite(heatingPIN, false);
                heating(digitalRead(heatingPIN));
                doc["m"] = true;
                temp_man_var = false;
                doc["t_en"] = false;
            }
            else
            {
                digitalWrite(heatingPIN, true);
                heating(digitalRead(heatingPIN));
                doc["m"] = true;
                temp_man_var = true;
                doc["t_en"] = true;
            }
        }

        if (strcmp((char *)data, "toogle_light") == 0)
        {
            if (light_control_var == true)
            {
                light_control_var = false;
                digitalWrite(lightPIN, false);
                lighting(digitalRead(lightPIN));
                doc["m"] = true;
                doc["l_man"] = false;
                light_man_var = false;

                light_ON_var = true;
                light_OFF_var = false;

                light_target_time = millis();
            }
            else
            {
                light_control_var = true;
                digitalWrite(lightPIN, false);
                lighting(digitalRead(lightPIN));
                doc["m"] = true;
                doc["l_man"] = true;
            }
        }
        else if (strcmp((char *)data, "light_button_toggle") == 0)
        {
            if (light_man_var)
            {
                digitalWrite(lightPIN, false);
                lighting(digitalRead(lightPIN));
                doc["m"] = true;
                light_man_var = false;
                doc["l_en"] = false;
            }
            else
            {
                digitalWrite(lightPIN, true);
                lighting(digitalRead(lightPIN));
                doc["m"] = true;
                light_man_var = true;
                doc["l_en"] = true;
            }
        }

        else if (strcmp((char *)data, "RESET") == 0)
        {
            ESP.restart();
        }
        else if (strcmp((char *)data, "OTA") == 0)
        {
            OTA_var = !OTA_var;
            store_toggle("OTA", OTA_var);
            ESP.restart();
        }
        else if (strcmp((char *)data, "calibration") == 0)
        {
            fast_calibration = !fast_calibration;
            store_toggle("calibration", fast_calibration);
            ESP.restart();
        }
        else if (strcmp((char *)data, "toggle_heat") == 0)
        {
            enable_heating = !enable_heating;
            store_toggle("enable_heating", enable_heating);
            ESP.restart();
        }
        else if (strcmp((char *)data, "toggle_humidifyer") == 0)
        {
            enable_humidify = !enable_humidify;
            store_toggle("enable_humidify", enable_humidify);
            ESP.restart();
        }
        else if (strcmp((char *)data, "toggle_lamp") == 0)
        {
            enable_light = !enable_light;
            store_toggle("enable_light", enable_light);
            ESP.restart();
        }
        else if (strcmp((char *)data, "toggle_ventilator") == 0)
        {
            enable_fan = !enable_fan;
            store_toggle("enable_fan", enable_fan);
            ESP.restart();
        }
        else if (strcmp((char *)data, "toggle_bme") == 0)
        {
            sensor = !sensor;
            store_toggle("sensor", sensor);
            ESP.restart();
        }
        else if (strcmp((char *)data, "toggle_co2") == 0)
        {
            mhz = !mhz;
            store_toggle("mhz", mhz);
            ESP.restart();
        }
         else if (strcmp((char *)data, "toggle_sd") == 0)
        {
            sd = !sd;
            store_toggle("sd", sd);
            ESP.restart();
        }
        size_t len = serializeJson(doc, json_data);
        ws.textAll(json_data, len);
        doc.clear();
    }
}