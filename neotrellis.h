/** NEOTRELLIS
 * 
 * this file drives the NeoTrellis board
 * 
 * created by zauberwild on 16.08.2021
 * 
 */

#ifndef neotrellis_h
#define neotrellis_h
#include "Arduino.h"
#include "Adafruit_NeoTrellis.h"
#include "shortcut.h"
#include "config.h"
#include "led_controller.h"

//* DEFINING CONSTANTS
#define INT_PIN 6

namespace NeoTrellis
{

	//* variables
	// NeoTrellis object
	Adafruit_NeoTrellis trellis;

	bool action_pending; // saves, if action needs to be taken
	int callback_num;	 // saves the last pressed key

	int prev_app = -1;		   // saves the previous app
	float prev_luminance = -1; // saves the previous luminance

	bool pulse_on[16]; // saves, where the pulse is activated on press
	bool prev_pulse_on[16];

	//* functions
	/** @brief this function will be called by the NeoTrellis library to process the input on the trellis
	 * @param evt (keyEvent) contains information about the input
	 * @return has to return 0 for some weird reason
	 */
	TrellisCallback callback(keyEvent evt)
	{

		int edge = evt.bit.EDGE;
		int num = evt.bit.NUM;

		if (edge == SEESAW_KEYPAD_EDGE_RISING)
		{

			pulse_on[num] = true;

			if (LedController::resetTimer())
			{
				action_pending = true;
				callback_num = num;
			}
		}
		else
		{

			pulse_on[num] = false;
		}

		return 0;
	}

	/** @brief starts amd sets everything for the trellis module
	 */
	void begin()
	{

		// set pin-mode
		pinMode(INT_PIN, INPUT);

		if (!trellis.begin())
		{
			// Serial.println("could not start trellis");
			while (1)
				;
		}

		//activate all keys and set callbacks
		for (int i = 0; i < NEO_TRELLIS_NUM_KEYS; i++)
		{
			trellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
			trellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
			trellis.registerCallback(i, callback);
		}

		// Serial.println("[neotrellis::begin] Trellis board ready");
	}

	//* shamelessely stolen from Adafruit (seesaw->neotrellis->basic example)
	// Input a value 0 to 255 to get a color value.
	// The colors are a transition r - g - b - back to r.
	uint32_t Wheel(byte WheelPos)
	{
		if (WheelPos < 85)
		{
			return trellis.pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
		}
		else if (WheelPos < 170)
		{
			WheelPos -= 85;
			return trellis.pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
		}
		else
		{
			WheelPos -= 170;
			return trellis.pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
		}
		return 0;
	}

	/** @brief plays a fast startup animation
   * @param step current step
   * @param n_steps number of steps this animation will perform
   * @param luminance luminance of the led (%)
   * documentation: notes 8-C
   */
	void startupAnim(int step, int n_steps, int luminance)
	{
		if (step < n_steps / 2)
		{
			int i = map(step, 0, n_steps / 2, 0, trellis.pixels.numPixels());
			trellis.pixels.setPixelColor(i, Wheel(map(i, 0, trellis.pixels.numPixels(), 0, 255)));
			trellis.pixels.show();
		}
		else
		{
			int i = map(step, n_steps / 2, n_steps, 0, trellis.pixels.numPixels());
			trellis.pixels.setPixelColor(i, 0x000000);
			trellis.pixels.show();
		}
	}

	/** @brief reads the interrupt pin and tells if something has changed
	* @return true, when something changed
	*/
	bool changed()
	{
		return !digitalRead(INT_PIN);
	}

	/** @brief reads the input and sets the leds
	 * @param cur_app	the current app (to get the colors)
	 * @param luminance	the current brightness of the leds
	 */
	void update(int cur_app, float luminance)
	{

		Config::App app = Config::apps[cur_app];

		//* input
		// check for updates

		if (!digitalRead(INT_PIN))
		{
			trellis.read(false);
		}

		//check for pending action
		if (action_pending)
		{
			action_pending = false;

			ShortcutKeyboard::print(app.buttons[callback_num].shortcut);
		}

		//* set leds
		// loop through all leds
		for (int i = 0; i < 16; i++)
		{

			// if app, pulse or luminance have changed
			if (cur_app != prev_app || pulse_on[i] != prev_pulse_on[i] || prev_luminance != luminance)
			{

				float rgb[3]; // saves the color values seperately

				// if pulse is on: make color white
				if (pulse_on[i] && app.buttons[i].color != 0)
				{
					rgb[0] = 255;
					rgb[1] = 255;
					rgb[2] = 255;
				}
				else
				{ // else: set the color taken from config
					rgb[0] = color_table[app.buttons[i].color][0];
					rgb[1] = color_table[app.buttons[i].color][1];
					rgb[2] = color_table[app.buttons[i].color][2];
				}

				// there used to be some brightness balancing here, however it didn't worked.
				// maybe i'll revisit it in the future, maybe not

				// apply the luminance value
				rgb[0] *= luminance / 100;
				rgb[1] *= luminance / 100;
				rgb[2] *= luminance / 100;

				// round to make 'integers'
				rgb[0] = round(rgb[0]);
				rgb[1] = round(rgb[1]);
				rgb[2] = round(rgb[2]);

				int color = trellis.pixels.Color(rgb[0], rgb[1], rgb[2]); // save the color in packed 32-bit format

				trellis.pixels.setPixelColor(i, color);
			}
		}

		trellis.pixels.show();

		//* save previous values
		prev_app = cur_app;
		prev_luminance = luminance;
		for (int i = 0; i < 16; i++)
		{
			prev_pulse_on[i] = pulse_on[i];
		}
	}

}

#endif
