#include <header.h>
#include <fridge.h>

// global defines
#define _LCDML_CONTROL_encoder_pin_a 13      // pin encoder b
#define _LCDML_CONTROL_encoder_pin_b 12      // pin encoder a
#define _LCDML_CONTROL_encoder_pin_button 0  // pin taster
#define _LCDML_CONTROL_encoder_high_active 0 // physical pin , use internal pullup

#define _LCDML_CONTROL_encoder_refresh_time 5UL // 5ms
#define _LCDML_CONTROL_encoder_switch_time 75UL // 75 ms

#define _LCDML_CONTROL_encoder_switch_press_short() LCDML.BT_enter()
#define _LCDML_CONTROL_encoder_rotary_a() LCDML.BT_up()
#define _LCDML_CONTROL_encoder_rotary_b() LCDML.BT_down()

#define _LCDML_CONTROL_encoder_advanced_switch 1
#define _LCDML_CONTROL_encoder_switch_press_long() LCDML.BT_quit()

#define _LCDML_CONTROL_encoder_advanced_rotary 0
#define _LCDML_CONTROL_encoder_rotary_a_and_press() LCDML.BT_left()
#define _LCDML_CONTROL_encoder_rotary_b_and_press() LCDML.BT_right()

#define _LCDML_CONTROL_encoder_t_long_press 20000 // maximum is 1275 (5*255)

uint8_t g_LCDML_CONTROL_encoder_t_prev = 0;
uint8_t g_LCDML_CONTROL_encoder_a_prev = 0;
uint8_t g_LCDML_CONTROL_t_pressed = 0;
uint32_t g_LCDML_CONTROL_t_press_time = 0;
long int g_LCDML_DISP_press_time = 0;

// *********************************************************************
void lcdml_menu_control(void)
// *********************************************************************
{
  if (LCDML.BT_setup())
  {
    // runs only once
    // init pins, enable pullups
    if (_LCDML_CONTROL_encoder_high_active == 0)
    {
      pinMode(_LCDML_CONTROL_encoder_pin_a, INPUT_PULLUP);
      pinMode(_LCDML_CONTROL_encoder_pin_b, INPUT_PULLUP);
      pinMode(_LCDML_CONTROL_encoder_pin_button, INPUT_PULLUP);
    }
  }

  unsigned char a = digitalRead(_LCDML_CONTROL_encoder_pin_a);
  unsigned char b = digitalRead(_LCDML_CONTROL_encoder_pin_b);
  unsigned char t = digitalRead(_LCDML_CONTROL_encoder_pin_button);

  // change button status if high and low active are switched
  if (_LCDML_CONTROL_encoder_high_active == 1)
  {
    t = !t;
  }

  // check if the button was pressed and save this state
  if ((millis() - g_LCDML_DISP_press_time) >= _LCDML_CONTROL_encoder_switch_time)
  {
    g_LCDML_DISP_press_time = millis(); // reset button press time

    // press button once
    if (t == false && g_LCDML_CONTROL_encoder_t_prev == 0)
    {

      g_LCDML_CONTROL_t_pressed = 1;
    }
    else
    {
      g_LCDML_CONTROL_encoder_t_prev = 0;
    }
  }

  // check if button is currently pressed
  if (t == false)
  {

    // check if the advanced rotary function is enabled
    if (_LCDML_CONTROL_encoder_advanced_rotary == 1)
    {

      // check if the rotary encoder was moved
      if (a == false && g_LCDML_CONTROL_encoder_a_prev)
      {
        g_LCDML_CONTROL_encoder_t_prev = 1;

        if (b == false)
        {
          // switch active and rotary b moved

          _LCDML_CONTROL_encoder_rotary_b_and_press();
        }
        else
        {

          // switch active and rotary a moved
          _LCDML_CONTROL_encoder_rotary_a_and_press();
        }

        g_LCDML_CONTROL_t_pressed = 0;
        g_LCDML_CONTROL_t_press_time = 0;
      }
    }

    // check advanced mode "long press switch"
    if (_LCDML_CONTROL_encoder_advanced_switch == 1)
    {
      // button was pressed
      if (g_LCDML_CONTROL_t_pressed == 1)
      {

        g_LCDML_CONTROL_t_press_time++;
        // Serial.println(g_LCDML_CONTROL_t_press_time);
      }
    }
  }
  else
  {
    // switch is not active

    // check encoder
    if (a == false && g_LCDML_CONTROL_encoder_a_prev)
    {
      g_LCDML_CONTROL_encoder_t_prev = 1;

      if (b == false)
      {
        _LCDML_CONTROL_encoder_rotary_a();
      }
      else
      {

        _LCDML_CONTROL_encoder_rotary_b();
      }

      g_LCDML_CONTROL_t_pressed = 0;
      g_LCDML_CONTROL_t_press_time = 0;
      g_LCDML_DISP_press_time = millis();
    }

    // check if an button was pressed
    if (g_LCDML_CONTROL_t_pressed == 1)
    {

      if (g_LCDML_CONTROL_t_press_time >= _LCDML_CONTROL_encoder_t_long_press && _LCDML_CONTROL_encoder_advanced_switch == 1)
      {

        _LCDML_CONTROL_encoder_switch_press_long();
      }
      else
      {

        _LCDML_CONTROL_encoder_switch_press_short();
      }

      g_LCDML_CONTROL_t_pressed = 0;
      g_LCDML_CONTROL_t_press_time = 0;
      g_LCDML_DISP_press_time = millis();
    }
  }

  g_LCDML_CONTROL_encoder_a_prev = a; // set new encoder status
}