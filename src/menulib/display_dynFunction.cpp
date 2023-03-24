#include <header.h>
#include <fridge.h>

void mDyn_set_hum(uint8_t line) {
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if (LCDML.BT_checkAny())
    {
      if (LCDML.BT_checkEnter())
      {
        // this function checks returns the scroll disable status (0 = menu scrolling enabled, 1 = menu scrolling disabled)
        if (LCDML.MENU_getScrollDisableStatus() == 0)
        {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          LCDML.MENU_disScroll();
        }
        else
        {
          // enable the normal menu scroll function
          LCDML.MENU_enScroll();
          // EEPROM.update(1, set_hum);
        }

        // do something
        // ...
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkUp()) {
        if (set_hum < 100) {
          set_hum++;
        }
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkDown()) {
        if (set_hum > 0) {
          set_hum--;
        }
      }
    }
  }

  char buf[20];
  sprintf (buf, "set hum: %d", set_hum);

  // use the line from function parameters
  lcd.setCursor(1, line);
  lcd.print(buf);  lcd.print(" "); lcd.print("%");


}


void mDyn_set_SD_time(uint8_t line) {
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if (LCDML.BT_checkAny())
    {
      if (LCDML.BT_checkEnter())
      {
        // this function checks returns the scroll disable status (0 = menu scrolling enabled, 1 = menu scrolling disabled)
        if (LCDML.MENU_getScrollDisableStatus() == 0)
        {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          LCDML.MENU_disScroll();
        }
        else
        {
          // enable the normal menu scroll function
          LCDML.MENU_enScroll();
          // EEPROM.update(2, SD_time);
          SD_ON_var = true;
        }

        // do something
        // ...
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkUp()) {
        if (SD_time < 60) {
          SD_time++;
        }
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkDown()) {
        if (SD_time > 1) {
          SD_time--;
        }
      }
    }
  }

  char buf[20];
  sprintf (buf, "SD time: %d", SD_time);

  // use the line from function parameters
  lcd.setCursor(1, line);
  lcd.print(buf); lcd.print(" min");

}


void mDyn_set_temp(uint8_t line) {
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if (LCDML.BT_checkAny())
    {
      if (LCDML.BT_checkEnter())
      {
        // this function checks returns the scroll disable status (0 = menu scrolling enabled, 1 = menu scrolling disabled)
        if (LCDML.MENU_getScrollDisableStatus() == 0)
        {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          LCDML.MENU_disScroll();
        }
        else
        {
          // enable the normal menu scroll function
          LCDML.MENU_enScroll();
          // EEPROM.update(3, set_temp);
        }

        // do something
        // ...
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkUp()) {
        if (set_temp < 25) {
          set_temp++;
        }
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkDown()) {
        if (set_temp > 10) {
          set_temp--;
        }
      }
    }
  }

  char buf[20];
  sprintf (buf, "set temp: %d", set_temp);

  // use the line from function parameters
  lcd.setCursor(1, line);
  lcd.print(buf);  lcd.print(" ");  lcd.print((char) 223); lcd.print("C");


}


void mDyn_set_light_ON(uint8_t line) {
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if (LCDML.BT_checkAny())
    {
      if (LCDML.BT_checkEnter())
      {
        // this function checks returns the scroll disable status (0 = menu scrolling enabled, 1 = menu scrolling disabled)
        if (LCDML.MENU_getScrollDisableStatus() == 0)
        {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          LCDML.MENU_disScroll();
        }
        else
        {
          // enable the normal menu scroll function
          LCDML.MENU_enScroll();
          // EEPROM.update(4, set_light_ON);
        }

        // do something
        // ...
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkUp()) {
        if (set_light_ON < 12 && set_light_ON < set_light_OFF) {
          set_light_ON++;
        }
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkDown()) {
        if (set_light_ON > 1) {
          set_light_ON--;
        }
      }
    }
  }

  char buf[20];
  sprintf (buf, "start: %d", set_light_ON);

  // use the line from function parameters
  lcd.setCursor(1, line);
  lcd.print(buf);
}


void mDyn_set_light_OFF(uint8_t line) {
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if (LCDML.BT_checkAny())
    {
      if (LCDML.BT_checkEnter())
      {
        // this function checks returns the scroll disable status (0 = menu scrolling enabled, 1 = menu scrolling disabled)
        if (LCDML.MENU_getScrollDisableStatus() == 0)
        {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          LCDML.MENU_disScroll();
        }
        else
        {
          // enable the normal menu scroll function
          LCDML.MENU_enScroll();
          // EEPROM.update(5, set_light_OFF);
        }

        // do something
        // ...
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkUp()) {
        if (set_light_OFF < 20 && set_light_OFF > set_light_ON) {
          set_light_OFF++;
        }
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkDown()) {
        if (set_light_OFF > 12) {
          set_light_OFF--;
        }
      }
    }
  }

  char buf[20];
  sprintf (buf, "stop: %d", set_light_OFF);

  // use the line from function parameters
  lcd.setCursor(1, line);
  lcd.print(buf);
}


void mDyn_set_fan_ON(uint8_t line) {
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if (LCDML.BT_checkAny())
    {
      if (LCDML.BT_checkEnter())
      {
        // this function checks returns the scroll disable status (0 = menu scrolling enabled, 1 = menu scrolling disabled)
        if (LCDML.MENU_getScrollDisableStatus() == 0)
        {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          LCDML.MENU_disScroll();
        }
        else
        {
          // enable the normal menu scroll function
          LCDML.MENU_enScroll();
          // EEPROM.update(6, set_fan_ON);
        }

        // do something
        // ...
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkUp()) {
        if (set_fan_ON < 60) {
          set_fan_ON++;
        }
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkDown()) {
        if (set_fan_ON > 1) {
          set_fan_ON--;
        }
      }
    }
  }

  char buf[20];
  sprintf (buf, "fan on: %d min", set_fan_ON);

  // use the line from function parameters
  lcd.setCursor(1, line);
  lcd.print(buf);
}


void mDyn_set_fan_OFF(uint8_t line) {
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if (LCDML.BT_checkAny())
    {
      if (LCDML.BT_checkEnter())
      {
        // this function checks returns the scroll disable status (0 = menu scrolling enabled, 1 = menu scrolling disabled)
        if (LCDML.MENU_getScrollDisableStatus() == 0)
        {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          LCDML.MENU_disScroll();
        }
        else
        {
          // enable the normal menu scroll function
          LCDML.MENU_enScroll();
          // EEPROM.update(7, set_fan_OFF);
        }

        // do something
        // ...
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkUp()) {
        if (set_fan_OFF < 60) {
          set_fan_OFF++;
        }
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkDown()) {
        if (set_fan_OFF > 1) {
          set_fan_OFF--;
        }
      }
    }
  }

  char buf[20];
  sprintf (buf, "fan off: %d min", set_fan_OFF);

  // use the line from function parameters
  lcd.setCursor(1, line);
  lcd.print(buf);
}


void mDyn_set_water_ON(uint8_t line) {
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if (LCDML.BT_checkAny())
    {
      if (LCDML.BT_checkEnter())
      {
        // this function checks returns the scroll disable status (0 = menu scrolling enabled, 1 = menu scrolling disabled)
        if (LCDML.MENU_getScrollDisableStatus() == 0)
        {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          LCDML.MENU_disScroll();
        }
        else
        {
          // enable the normal menu scroll function
          LCDML.MENU_enScroll();
          // EEPROM.update(8, set_water_ON);
        }

        // do something
        // ...
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkUp()) {
        if (set_water_ON < 30) {
          set_water_ON++;
        }
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkDown()) {
        if (set_water_ON > 1) {
          set_water_ON--;
        }
      }
    }
  }

  char buf[20];
  sprintf (buf, "water on: %d min", set_water_ON);

  // use the line from function parameters
  lcd.setCursor(1, line);
  lcd.print(buf);
}


void mDyn_set_water_OFF(uint8_t line) {
  // check if this function is active (cursor stands on this line)
  if (line == LCDML.MENU_getCursorPos())
  {
    // make only an action when the cursor stands on this menu item
    //check Button
    if (LCDML.BT_checkAny())
    {
      if (LCDML.BT_checkEnter())
      {
        // this function checks returns the scroll disable status (0 = menu scrolling enabled, 1 = menu scrolling disabled)
        if (LCDML.MENU_getScrollDisableStatus() == 0)
        {
          // disable the menu scroll function to catch the cursor on this point
          // now it is possible to work with BT_checkUp and BT_checkDown in this function
          // this function can only be called in a menu, not in a menu function
          LCDML.MENU_disScroll();
        }
        else
        {
          // enable the normal menu scroll function
          LCDML.MENU_enScroll();
          // EEPROM.update(9, set_water_OFF);
        }

        // do something
        // ...
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkUp()) {
        if (set_water_OFF < 60) {
          set_water_OFF++;
        }
      }

      // This check have only an effect when MENU_disScroll is set
      if (LCDML.BT_checkDown()) {
        if (set_water_OFF > 1) {
          set_water_OFF--;
        }
      }
    }
  }

  char buf[20];
  sprintf (buf, "water off: %d min", set_water_OFF);

  // use the line from function parameters
  lcd.setCursor(1, line);
  lcd.print(buf);
}

//// *********************************************************************
//void mDyn_time(uint8_t line)
//// *********************************************************************
//{
//  char buf[20];
//  // http://www.c-howto.de/tutorial/benutzerinteraktion/bildschirmausgaben/
//  sprintf (buf, "%02d:%02d:%02d", dyn_hour, dyn_min, dyn_sec);
//
//  // use the line from function parameters
//  lcd.setCursor(1, line);
//  lcd.print(buf);
//
//  // reset initscreen timer when this function is displayed
//  LCDML.SCREEN_resetTimer();
//
//  // check if this function is active (cursor stands on this line)
//  if (line == LCDML.MENU_getCursorPos())
//  {
//    // ...
//
//
//
//  }
//}