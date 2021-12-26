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

  //* fancy startup animation
  // originally, there were no delay allowed during the startup animation (i wanted to be able to interrupt it).
  // Later I simplified it (and did use delay), but there are still some parts left, which is why there so many steps
  LedController::resetTimer();
  float luminanceTrellis = LedController::updateForNeoTrellis();

  int steps_per_part = 1000;

  // let the trellis board do a little blinky-blinky (stolen from the neotrellis examples by Adafruit)
  for (int i = 0; i < steps_per_part; i++)
  {
    NeoTrellis::startupAnim(i, steps_per_part, luminanceTrellis);

    delay(1500 / steps_per_part);
  }

  // show random status lines like a linux booting up
  steps_per_part = 24;
  for (int i = 0; i < steps_per_part; i++)
  {
    Display::startupAnim();
    int rand = random(300);
    delay(rand);
  }

  // now reset timer and activate keys to prepare for battle
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
