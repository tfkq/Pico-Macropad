/** ARDUINO-MACROPAD


   created by zauberwild in 16.08.2021
   licensed under //TODO
*/

//* local source files
#include "config.h"
#include "shortcut.h"
#include "led_controller.h"
#include "display.h"
#include "neotrellis.h"
#include "rotary_encoder.h"

//* DEFINING CONSTANTS
int NUMBER_OF_APPS = 7;

void setup()
{
  //* start all devices
  Config::begin();
  ShortcutKeyboard::begin();
  NeoTrellis::begin();
  delay(500); // wait a second for the display to wake up
  Display::begin();
  RotaryEncoderOne::begin();
  RotaryEncoderTwo::begin();

  //* fancy startup animation (notes 8-A)
  LedController::resetTimer();
  float luminanceTrellis = LedController::updateForNeoTrellis();
  float luminanceRotary = LedController::updateForRotaryEncoder();

  int step = 0;
  int steps_per_part = 1000;

  while (step < steps_per_part * 3)
  {
    // save start time at loop
    unsigned long t_start = micros();

    // first on stage: second rotary encoder and the neotrellis
    if (step < steps_per_part)
    {
      RotaryEncoderTwo::startupAnim(step, steps_per_part, luminanceRotary);
      NeoTrellis::startupAnim(step, steps_per_part, luminanceTrellis);
    }
    // then the other rotary encoder and the display
    else if (step >= steps_per_part && step < steps_per_part * 2)
    {
      RotaryEncoderOne::startupAnim(step - steps_per_part, steps_per_part, luminanceRotary);
      Display::startupAnim(step - steps_per_part, steps_per_part);
    }

    // abort animation
    if (NeoTrellis::changed()) //TODO bug: prevent any action when you abort the startup anim
    {
      delay(500);
      break;
    }

    // go on as soon one millisecond has passed
    while (true)
    {
      unsigned long t_now = micros();
      if (t_now - t_start >= 1000)
      {
        break;
      }
    }
    step++;
  }

  LedController::resetTimer();
  NeoTrellis::engageKeys();

  //* quickly find the number of Apps
  NUMBER_OF_APPS = 0;
  char empty_name[21];
  for (int i = 0; i < 24; i++)
  {
    if (strcmp(Config::apps[i].name, empty_name) == 0)
    {
      break;
    }
    NUMBER_OF_APPS++;
  }
}

void loop()
{
  // notes 5-A

  RotaryEncoderOne::update();
  int app = RotaryEncoderTwo::update(NUMBER_OF_APPS);

  float luminanceTrellis = LedController::updateForNeoTrellis();
  float luminanceRotary = LedController::updateForRotaryEncoder();

  NeoTrellis::update(app, luminanceTrellis);

  Display::update(app, LedController::getDisplayState());

  RotaryEncoderOne::setLed(luminanceRotary);
  RotaryEncoderTwo::setLed(luminanceRotary, NUMBER_OF_APPS);
}
