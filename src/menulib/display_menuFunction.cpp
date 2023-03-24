#include <header.h>
#include <fridge.h>

void mFunc_information(uint8_t param)
{
  if (LCDML.FUNC_setup())
  {
    LCDML_UNUSED(param);
    lcd.setCursor(0, 0);
    lcd.print(F("  Mushroom Fridge"));
    lcd.setCursor(0, 1);
    lcd.print(F("   Version  esp0.3"));
    lcd.setCursor(0, 2);
    lcd.print(F("     Feb. 2023"));
    lcd.setCursor(0, 3);
    lcd.print(F("  by Marvin Kordis"));
  }

  if (LCDML.FUNC_loop())
  {
    if (LCDML.BT_checkAny())
    {
      LCDML.FUNC_goBackToMenu();
    }
  }

  if (LCDML.FUNC_close())
  {
  }
}

uint8_t g_func_timer_info = 0;
unsigned long g_timer_1 = 0;
void mFunc_spray(uint8_t param)
{
  if (LCDML.FUNC_setup())
  {

    //    LCDML_UNUSED(param);

    if (spray == true)
    {

      if (param == 1)
      {
        lcd.print(F("30 sec spraying")); // print some content on first row
        g_func_timer_info = 30;          // reset and set timer
      }

      if (param == 2)
      {
        lcd.print(F("60 sec spraying")); // print some content on first row
        g_func_timer_info = 60;          // reset and set timer
      }

      if (param == 3)
      {
        lcd.print(F("300 sec spraying")); // print some content on first row
        g_func_timer_info = 120;          // reset and set timer
      }

      digitalWrite(waterPIN, LOW);
      LCDML.FUNC_setLoopInterval(100); // starts a trigger event for the loop function every 100 milliseconds
      LCDML.TIMER_msReset(g_timer_1);
    }
    else
    {
      lcd.print(F("spraying disabled"));
    }
  }

  if (LCDML.FUNC_loop()) // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function

    // reset screensaver timer
    if (spray == true)
    {
      LCDML.SCREEN_resetTimer();

      // this function is called every 100 milliseconds

      // this method checks every 1000 milliseconds if it is called
      if (LCDML.TIMER_ms(g_timer_1, 1000))
      {
        g_func_timer_info--; // increment the value every second
        lcd.setCursor(0, 0); // set cursor pos
        lcd.print(F("  "));
        lcd.setCursor(0, 0);          // set cursor pos
        lcd.print(g_func_timer_info); // print the time counter value
      }

      // this function can only be ended when quit button is pressed or the time is over
      // check if the function ends normally
      if (g_func_timer_info <= 0)
      {
        // leave this function
        digitalWrite(27, LOW);

        LCDML.FUNC_goBackToMenu();
      }
    }
    else
    {

      if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
      {
        LCDML.FUNC_goBackToMenu(); // leave this function
      }
    }
  }

  if (LCDML.FUNC_close())
  {
    digitalWrite(waterPIN, HIGH);
  }
}

void mFunc_led(uint8_t param)
{
  if (LCDML.FUNC_setup())
  {

    //    pinMode(30, OUTPUT);
    if (param == 1)
    {
      digitalWrite(lightPIN, HIGH);
    }
    if (param == 2)
    {
      digitalWrite(lightPIN, LOW);
    }
  }

  if (LCDML.FUNC_loop())
  {

    LCDML.FUNC_goBackToMenu();
  }

  if (LCDML.FUNC_close())
  {
  }
}

void mFunc_status_spray(uint8_t param)
{
  if (LCDML.FUNC_setup())
  {

    if (param == 1)
    {
      spray = true;
    }
    if (param == 2)
    {
      spray = false;
    }
  }

  if (LCDML.FUNC_loop())
  {

    LCDML.FUNC_goBackToMenu();
  }

  if (LCDML.FUNC_close())
  {
  }
}

bool switch_screen = true;
void mFunc_datascreen(uint8_t param)
{
  LCDML_UNUSED(param);

  if (LCDML.FUNC_setup())
  {
    lcd.clear();
    LCDML.FUNC_setLoopInterval(1000);
    //    g_func_timer_info = 10;
  }

  if (LCDML.FUNC_loop())
  {
    LCDML.SCREEN_resetTimer();

    //    if (LCDML.TIMER_ms(g_timer_1, 1000)) {
    //      g_func_timer_info--;
    //    }

    //    if (g_func_timer_info <= 0)  {
    //      switch_screen ^= true;
    //      lcd.clear();
    //      g_func_timer_info = 10;
    //    }

    if (switch_screen)
    {
      lcd.setCursor(0, 0);

      if (!getLocalTime(&timeinfo))
      {
        if (!dis_rtc)
        {
          now = rtc.now();
          char buf[] = "DD.MM.YY hh:mm:ss";
          lcd.print(now.toString(buf));
        }
        else
        {
          lcd.print("no time available");
        }
      }
      lcd.print(&timeinfo, "%d.%m.%Y %H:%M:%S");
      lcd.setCursor(0, 1);
      lcd.print(F("MH:"));
      lcd.print(avg_hum_10.mean());
      lcd.print(F("% MT:"));
      lcd.print(avg_temp_10.mean());
      lcd.print((char)223);
      lcd.print(F("C"));
      lcd.setCursor(0, 2);
      lcd.print(F("H:"));
      lcd.print(humidity);
      lcd.print(F("%"));
      // lcd.print(F("CO2: "));
      // lcd.print(avg_co2_test);
      // lcd.print(F(" ppm"));
      lcd.setCursor(0, 3);
      //      lcd.print(F("CO2_50: ")); lcd.print(avg_co2_50); lcd.print(F(" ppm"));

      //      lcd.print(F("RTC: ")); lcd.print(rtc.getTemperature()); lcd.print((char) 223); lcd.print(F("C SD: "));lcd.print(count);
      lcd.print(F("Target: "));
      lcd.print(set_hum);
      lcd.print("% ");
      lcd.print(F("SD: "));
      lcd.print(count);
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print(F("SD: "));
      lcd.print(filename);
      lcd.setCursor(0, 1);
      lcd.print(F("FAN: "));
      lcd.print(set_fan_ON);
      lcd.print(F(" min | "));
      lcd.print(set_fan_OFF);
      lcd.print(F(" min"));
      lcd.setCursor(0, 2);
      lcd.print(F("HUM: "));
      lcd.print(set_water_ON);
      lcd.print(F(" min | "));
      lcd.print(set_water_OFF);
      lcd.print(F(" min"));
      lcd.setCursor(0, 3);
      lcd.print(F("LGT: "));
      lcd.print(set_light_ON);
      lcd.print(F(":00 - "));
      lcd.print(set_light_OFF);
      lcd.print(F(":00"));
    }
    //          char buf2[20];
    //      sprintf(buf2, "FAN: %d min | %d min", set_fan_ON, set_fan_OFF);
    //      lcd.print(buf2);

    if (LCDML.BT_checkEnter())
    {
      LCDML.FUNC_goBackToMenu(); // leave this function
    }

    if (LCDML.BT_checkAny())
    {
      switch_screen ^= true;
      lcd.clear();
    }
  }

  if (LCDML.FUNC_close())
  {
    LCDML.MENU_goRoot();
  }
}

void mFunc_back(uint8_t param)
{

  if (LCDML.FUNC_setup())
  {
    LCDML_UNUSED(param);

    LCDML.FUNC_goBackToMenu(1);
  }
}

/* ===================mFunc_goToRootMenu================== *
  //void mFunc_goToRootMenu(uint8_t param) {
  //  if (LCDML.FUNC_setup())         // ****** SETUP *********
  //  {
  //    // remmove compiler warnings when the param variable is not used:
  //    LCDML_UNUSED(param);
  //
  //    // go to root and display menu
  //    LCDML.MENU_goRoot();
  //  }
  //}

*/

/* ===================Example========================== *
  void your_function_name(uint8_t param)
  {
  if(LCDML.FUNC_setup())
  {
    LCDML_UNUSED(param);

    LCDML.FUNC_setLoopInterval(100);

    // uncomment this line when the menu should go back to the last called position
    // this could be a cursor position or the an active menu function
    // GBA means => go back advanced
  //    LCDML.FUNC_setGBA()
  }

  if(LCDML.FUNC_loop())
  {
    LCDML.SCREEN_resetTimer();

    if(LCDML.BT_checkAny()) {
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())
  {

  }
  }

*/