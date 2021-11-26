/** ROTARY ENCODER

   this file reads the rotary-encoder and controls the builtin rgb-leds

   created by zauberwild: 21.08.2021

*/

#ifndef rotary_encoder_h
#define rotary_encoder_h
#include "Arduino.h"
#include "shortcut.h"
#include "led_controller.h"
#include "Bounce2.h"
#include "Keyboard.h"

//* defining constants
const int COLOR_RESET_TIMEOUT = 2500;
const int DEBOUNCE_TIME = 5;

//* the one on the right (weirdly), responsible for volume
namespace RotaryEncoderOne
{

  //* variables
  // pins
  int a = 27;
  int b = 26;
  int sw = 17;
  int led_r = 18;
  int led_g = 19;
  int led_b = 20;

  Bounce bounce_a = Bounce(); // Bounce for all inputs (makes the debouncing a lot easier)
  Bounce bounce_b = Bounce();
  Bounce bounce_sw = Bounce();

  // values
  int led_r_val, led_g_val, led_b_val; // saves the values of the rgb-led
  bool pulse_off = true;               // saves if the encoder is being pressed and should glow white
  // (pulse_OFF because the switch input is inverted; false == pressed)
  //NOTE: update on that one: for some reason the switch isn't inverted (be it the bounce2 library or sth else)
  //NOTE: so the reading will be inverted to accommodate "false equals pressed" statement.
  //TODO: should change that to boe logical at some point

  const volatile int STEPS_PER_VOLUME = 1; // how many steps you need to turn the knob for one command

  volatile int counter_volume; // keeps track of how far the encoder has been turned
  volatile int counter_led;

  unsigned long last_change; // saves the last update, to reset the led on time

  //* functions
  /** @brief starts the first rotary encoder; sets pinmodes and attaches bouncers
*/
  void begin()
  {
    // set the inputs
    bounce_a.attach(a, INPUT_PULLUP);
    bounce_a.interval(DEBOUNCE_TIME);
    bounce_b.attach(b, INPUT_PULLUP);
    bounce_b.interval(DEBOUNCE_TIME);
    bounce_sw.attach(sw, INPUT);
    bounce_sw.interval(DEBOUNCE_TIME);

    // set the leds
    pinMode(led_r, OUTPUT);
    pinMode(led_g, OUTPUT);
    pinMode(led_b, OUTPUT);
  }

  /** @brief plays a fast startup animation
   * @param step current step
   * @param n_steps number of steps this animation will perform
   * @param luminance luminance of the led (%)
   * documentation: notes 8-C
   */
  void startupAnim(int step, int n_steps, int luminance)
  {
    if (step <= n_steps / 2)
    {
      led_r_val = map(step, 0, n_steps / 2, 0, 255);
      led_g_val = map(step, 0, n_steps / 2, 255, 0);
      led_b_val = 0;
    }
    else
    {
      led_r_val = map(step, n_steps / 2, n_steps, 255, 0);
      led_g_val = map(step, n_steps / 2, n_steps, 0, 255);
      led_b_val = 0;
    }

    analogWrite(led_r, 255 - (led_r_val * (luminance / 100)));
    analogWrite(led_g, 255 - (led_g_val * (luminance / 100)));
    analogWrite(led_b, 255 - (led_b_val * (luminance / 100)));
  }

  /** @brief gets input and sends commands
*/
  void update()
  {
    //* rotating fun
    // get input
    bounce_a.update();
    bounce_b.update();
    if (bounce_a.changed() && bounce_a.read() == LOW)
    {

      last_change = millis();
      LedController::resetTimer();

      if (bounce_b.read() == HIGH)
      {
        //Serial.println("[ROT1::update] up");
        counter_led++;
        counter_volume++;
      }
      else
      {
        //Serial.println("[ROT1::update] down");
        counter_led--;
        counter_volume--;
      }
    }

    // send volume command
    if (counter_volume == STEPS_PER_VOLUME)
    {
      ShortcutKeyboard::press(KEY_F24);
      counter_volume = 0;
    }
    else if (counter_volume == -STEPS_PER_VOLUME)
    {
      ShortcutKeyboard::press(KEY_F23);
      counter_volume = 0;
    }

    //* clicking fun
    bounce_sw.update();

    if (bounce_sw.changed())
    {
      pulse_off = !bounce_sw.read();
      if (bounce_sw.read() == HIGH)
      {
        // Serial.println("[ROT1::update] sw, sending -pause-");
        LedController::resetTimer();
        ShortcutKeyboard::press(KEY_F22);
      }
    }
  }

  /** @brief sets the led
   @param luminance	the brightness of the led
*/
  void setLed(float luminance)
  {
    // set the led values (notes 2-D)
    const float C = 42.5; // multiplier for converting the counter to pwm range -> `* C` makes ist go from 0 to 255
                          //NOTE: why exactly 42.5 was chosen is unknown

    // set boundaries
    counter_led = constrain(counter_led, -255 / C, 255 / C);

    // set rgb-values
    if (pulse_off)
    {
      if (counter_led == 0)
      {
        led_r_val = 255;
        led_g_val = 255;
        led_b_val = 0;
      }
      else if (counter_led > 0)
      {
        led_r_val = 255 - (counter_led * C);
        led_g_val = 255;
        led_b_val = 0;
      }
      else if (counter_led < 0)
      {
        led_r_val = 255;
        led_g_val = 255 - (-counter_led * C);
        led_b_val = 0;
      }
    }
    else
    {
      led_r_val = 255;
      led_g_val = 255;
      led_b_val = 255;
    }

    // reset the leds
    if (last_change + COLOR_RESET_TIMEOUT <= millis())
    {
      counter_led = 0;
    }

    // write the value to the led, but with a few modifications:
    // 1. `255 - `: this is a led with common anode, so a value of 0 corresponds to full power, and a value of 255 to off
    //              the main calculations above are done with normal 0->off and 255->full power, so we need to invert it here
    // 2. `* (luminance/100)`: - the luminance is a value of how bright the led should be deppending on the mode (calc. in led_controller)
    //              - it ranges from 0 to 100 (as a percentage), thats why we divide by 100
    //              - then it is multiplied to apply the dimming on to the value
    analogWrite(led_r, 255 - (led_r_val * (luminance / 100)));
    analogWrite(led_g, 255 - (led_g_val * (luminance / 100)));
    analogWrite(led_b, 255 - (led_b_val * (luminance / 100)));
  }

}

//* controlls the one on the left (weirdly), is responsible for switching between the apps
namespace RotaryEncoderTwo
{

  //* variables
  // pins
  int a = 9;
  int b = 8;
  int sw = 14;
  int led_r = 13;
  int led_g = 12;
  int led_b = 11;

  Bounce bounce_a = Bounce(); // Bounce for all inputs (makes the debouncing a lot easier)
  Bounce bounce_b = Bounce();
  Bounce bounce_sw = Bounce();

  // values
  int led_r_val, led_g_val, led_b_val;
  bool pulse_on;

  const volatile int STEPS_PER_VOLUME = 1; // how many steps you need to turn the knob for one command

  volatile int counter_volume; // keeps track of how the encoder has been turned
  volatile int counter_led;

  unsigned long last_change; // saves the last update, to reset the led on time

  bool jumped_to_main; // handling the whole quick-jump to main thing
  int app;
  int prev_app;

  //* functions
  /** @brief starts the first rotary encoder; sets pinmodes and attaches bouncers
*/
  void begin()
  {
    // set the inputs
    bounce_a.attach(a, INPUT_PULLUP);
    bounce_a.interval(DEBOUNCE_TIME);
    bounce_b.attach(b, INPUT_PULLUP);
    bounce_b.interval(DEBOUNCE_TIME);
    bounce_sw.attach(sw, INPUT);
    bounce_sw.interval(DEBOUNCE_TIME);

    // set the leds
    pinMode(led_r, OUTPUT);
    pinMode(led_g, OUTPUT);
    pinMode(led_b, OUTPUT);
  }

  /** @brief plays a fast startup animation
   * @param step current step
   * @param n_steps number of steps this animation will perform
   * @param luminance luminance of the led (%)
   * documentation: notes 8-B
   */
  void startupAnim(int step, int n_steps, int luminance)
  {
    if (step <= n_steps / 2)
    {
      led_r_val = 0;
      led_g_val = map(step, 0, n_steps / 2, 0, 255);
      led_b_val = map(step, 0, n_steps / 2, 255, 0);
    }
    else
    {
      led_r_val = 0;
      led_g_val = map(step, n_steps / 2, n_steps, 255, 0);
      led_b_val = map(step, n_steps / 2, n_steps, 0, 255);
    }

    analogWrite(led_r, 255 - (led_r_val * (luminance / 100)));
    analogWrite(led_g, 255 - (led_g_val * (luminance / 100)));
    analogWrite(led_b, 255 - (led_b_val * (luminance / 100)));
  }

  /** @brief gets input and returns the now active app
   @return the selected app index
*/
  int update(int number_of_apps)
  {
    //* rotating fun
    // get input
    bounce_a.update();
    bounce_b.update();
    if (bounce_a.changed() && bounce_a.read() == LOW)
    {

      last_change = millis();
      LedController::resetTimer();

      if (bounce_b.read() == HIGH)
      {
        app++;
      }
      else
      {
        app--;
      }
    }

    if (app < 0)
    {
      app = number_of_apps - 1;
    }
    else if (app >= number_of_apps)
    {
      app = 0;
    }

    //* clicking fun
    bounce_sw.update();

    if (bounce_sw.changed())
    {
      if (bounce_sw.read() == HIGH)
      {
        //Serial.println("[ROT2::update] sw, jumping between apps");
        LedController::resetTimer();
        jumped_to_main = !jumped_to_main;
        if (jumped_to_main)
        {
          prev_app = app;
          app = 0;
        }
        else
        {
          app = prev_app;
        }
      }
    }

    return app;
  }

  /** @brief sets the led
   @param luminance	the brightness of the led
*/
  void setLed(float luminance, int number_of_apps)
  {
    // calculate the led values (notes 4-B)
    led_r_val = 255;
    led_g_val = map(app, 0, (number_of_apps - 1) / 2, 0, 255);
    led_g_val = constrain(led_g_val, 0, 255);
    led_b_val = map(app, (number_of_apps - 1) / 2, number_of_apps - 1, 255, 0);
    led_b_val = constrain(led_b_val, 0, 255);

    // write the value to the led, but with a few modifications:
    // 1. `255 - `: this is a led with common anode, so a value of 0 corresponds to full power, and a value of 255 to off
    //              the main calculations above are done with normal 0->off and 255->full power, so we need to invert it here
    // 2. `* (luminance/100)`: - the luminance is a value of how bright the led should be deppending on the mode (calc. in led_controller)
    //              - it ranges from 0 to 100 (as a percentage), thats why we divide by 100
    //              - then it is multiplied to apply the dimming on to the value
    analogWrite(led_r, 255 - (led_r_val * (luminance / 100)));
    analogWrite(led_g, 255 - (led_g_val * (luminance / 100)));
    analogWrite(led_b, 255 - (led_b_val * (luminance / 100)));
  }

}

#endif
