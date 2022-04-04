
//* SETTINGS
#define MAX_NAME_LENGTH 6
#define MAX_MACRO_LENGTH 63
#define MAX_NUMBER_LAYOUTS 12



//* INCLUDES
// Arduino libraries
#include <Bounce2.h>
#include <Adafruit_NeoTrellis.h>
#include <Keyboard.h>
// Pico specific library
#include <LittleFS.h>
// local files

//* SETTINGS
#define DEBOUNCE_TIME 5

void setup()
{
  Serial.begin(9600);
  delay(500);
  while (!Serial)
  {
  }


  Macro::begin();
  VolumeKnob::begin();
  NeoTrellis::begin();
  delay(500);

  Action::begin();
  Serial.println("MACROPAD READY!");
}

void loop()
{
  VolumeKnob::update();
  NeoTrellis::update();
}