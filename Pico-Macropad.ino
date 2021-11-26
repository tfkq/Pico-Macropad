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
#define NUMBER_OF_APPS 7

void setup()
{

  // get the config data ready
  Config::begin();

  // get the keyboard connection going
  ShortcutKeyboard::begin();

  // set the trellis board up
  NeoTrellis::begin();

  // start up the display
  delay(500); // wait a second for the display to wake up
  Display::begin();

  // get the encoder spinning
  RotaryEncoderOne::begin();
  RotaryEncoderTwo::begin();

  // fancy startup animation (notes 8-A)

  LedController::resetTimer();
  float luminanceTrellis = LedController::updateForNeoTrellis();
  float luminanceRotary = LedController::updateForRotaryEncoder();

  int step = 0;
  int steps_per_part = 1000;
  while (step < steps_per_part * 3)
  {
    // first on stage: second rotary encoder
    if (step < steps_per_part)
    {
      RotaryEncoderTwo::startupAnim(step, steps_per_part, luminanceRotary);
    }
    // then the other one
    else if (step >= steps_per_part && step < steps_per_part * 2)
    {
      RotaryEncoderOne::startupAnim(step - steps_per_part, steps_per_part, luminanceRotary);
    }
    // and (for now last) the neotrellis board
    else if (step >= steps_per_part * 2 && step < steps_per_part * 3)
    {
      NeoTrellis::startupAnim(step - steps_per_part * 2, steps_per_part, luminanceTrellis);
    }

    // abort anim
    if (NeoTrellis::changed()) //TODO bug: prevent any action when you abort the startup anim
    {
      break;
    }

    step++;
    delay(1);
  }

  LedController::resetTimer();
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
