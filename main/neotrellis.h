/**
 * @file neotrellis.h
 * @author zauberwild
 * @brief (kinda) low level communication with the NeoTrellis board. makes me the perfect API i need for the Button state
 * machines. updates can be written continuously, it will automatically only update every few seconds
 * @version 2.1
 * @date 2022-04-04
 *
 * @copyright MIT license, Arvid Randow, 2022
 *
 */

#ifndef neotrellis_h
#define neotrellis_h

#include "utils.h"

//* CONSTANTS // SETTINGS
#define INT_PIN 6

namespace NeoTrellis
{
	//* variables and objects
	Adafruit_NeoTrellis trellis;

	// button / input
	volatile bool event_happened;
	// volatile int event_edge;
	// volatile int event_num;

	volatile uint8_t events[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	// led / output
	unsigned long last_update; // stores the millis of the last led update
	RGB colors[16];			   // saves all colors until the next update

	// functions
	TrellisCallback callback(keyEvent evt);

	void begin();
	void update();
	void set_color(int num, RGB color);
	int get_event(int number);

}

/**
 * @brief callback function to handle input from the neotrellis
 *
 * @param evt event raised by neotrellis
 * @return TrellisCallback 0
 */
TrellisCallback NeoTrellis::callback(keyEvent evt)
{
	event_happened = true;
	// event_edge = evt.bit.EDGE;
	// event_num = evt.bit.NUM;
	events[evt.bit.NUM] = evt.bit.EDGE;

	Display::announce_change();

	return 0;
}

/**
 * @brief starts the neotrellis. configures the keys.
 *
 */
void NeoTrellis::begin()
{
	// set pin-mode
	pinMode(INT_PIN, INPUT);

	if (!trellis.begin())
	{
		Serial.println("could not start trellis");
		while (1)
			;
	}

	// activate all keys and set callbacks
	for (int i = 0; i < NEO_TRELLIS_NUM_KEYS; i++)
	{
		trellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
		trellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
		trellis.registerCallback(i, callback);
	}
	trellis.pixels.setBrightness(255);
	trellis.pixels.show();

	Serial.println("[NeoTrellis::begin] Trellis board ready");
}

/**
 * @brief checks for input, writes to the led
 *
 */
void NeoTrellis::update()
{
	if (!digitalRead(INT_PIN))
	{
		trellis.read(false);
	}

	//* update buttons
	if (event_happened)
	{
		event_happened = false;
		last_input = millis();
	}

	//* update leds
	if (last_update + TRELLIS_LED_UPDATE_TIME < millis())
	{
		last_update = millis();

		for (int i = 0; i < 16; i++)
		{

			uint32_t color_i = trellis.pixels.Color(colors[i].r * brightness / 100,
													colors[i].g * brightness / 100,
													colors[i].b * brightness / 100);
			trellis.pixels.setPixelColor(i, color_i);
		}
		trellis.pixels.show();
	}
}

/**
 * @brief set a specific button to a specific color
 *
 * @param num number of button
 * @param p_color color
 */
void NeoTrellis::set_color(int num, RGB p_color)
{
	colors[num] = p_color;
}

/**
 * @brief checks if there was an event for a specific button
 *
 * @param number number of the button
 * @return int the event or 0, if no event
 */
int NeoTrellis::get_event(int number)
{
	uint8_t ret = events[number];
	events[number] = 0;
	return ret;
}

#endif