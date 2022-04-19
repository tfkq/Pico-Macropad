
//* SETTINGS
#define MAX_NAME_LENGTH 6
#define MAX_MACRO_LENGTH 63
#define MAX_NUMBER_LAYOUTS 12
#define DISPLAY_TIMEOUT 5000		 // time it takes for the display to turn off [ms]
#define DISPLAY_UPDATE_TIME 500		 // time between the display updates [ms]
#define TRELLIS_LED_UPDATE_TIME 50	 // time between the led updates [ms]
#define DEBOUNCE_TIME 5				 // debounce time for the rotary encoder [ms]
#define STEPS_PER_VOLUME 1			 // steps the volume knob needs to be turned to send a volume command
#define BRIGHTNESS_STEPS_PER_STEPS 2 // how much does the brightness change per encoder step
double raw_brightness = 40;			 // brightness percentage (0%-100%); used to calculate a corrected version
double brightness;					 // brightness percentage (0%-100%); use this one, because it is corrected

unsigned long last_input = 0; // saves the last time any of the inputs had been changed [ms]

//* INCLUDES
// Arduino libraries
#include <Bounce2.h>
#include <Keyboard.h>
#include <Adafruit_NeoTrellis.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Pico specific library
#include <LittleFS.h>
// local files
#include "macro.h"
#include "utils.h"
#include "display.h"
#include "rotary_encoder.h"
#include "brightness_knob.h"
#include "volume_knob.h"
#include "neotrellis.h"
#include "button_state_machine.h"
// #include "layer.h"
#include "menu.h"

void setup()
{
	Serial.begin(9600);
	// while (!Serial)
	// {
	// }

	Menu::begin();

	VolumeKnob::begin();
	BrightnessKnob::begin();
	BrightnessKnob::correct_brightness();
	delay(750);
	NeoTrellis::begin();
	delay(750);
	Display::begin();

	last_input = millis();
}

void loop()
{
	Menu::update();

	Display::update();

	NeoTrellis::update();

	VolumeKnob::update();
	BrightnessKnob::update();
}
