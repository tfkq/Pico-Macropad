/**
 * @file neotrellis.h
 * @author zauberwild
 * @brief (kinda) low level communication with the NeoTrellis board. make me the perfect API i need for the Button state
 * machines
 * @version 2.1
 * @date 2022-04-04
 * 
 * @copyright MIT license, Arvid Randow, 2022
 * 
 */


/*
/** NEOTRELLIS
 *
 * this file drives the NeoTrellis board
 *
 * created by zauberwild on 16.08.2021
 * licensed under MIT license
 *

#ifndef neotrellis_h
#define neotrellis_h

//* DEFINING CONSTANTS
#define INT_PIN 6

namespace NeoTrellis
{

	//* VARIABLES AND OBJECTS
	Adafruit_NeoTrellis trellis;
	LED leds[16];

	// event variables
	volatile bool event_happened = false;
	volatile int event_edge;
	volatile int event_num;

	//* FUNCTIONS
	TrellisCallback callback(keyEvent evt);
	void begin();
	void update();

}

/**
 * @brief callback function. will be called when there's interrupt coming from the trellis.
 * don't call this function on your own!
 *
 * @param evt the event raised by the interrupt
 * @return TrellisCallback 0, if it doesn't you are fucked
 *
TrellisCallback NeoTrellis::callback(keyEvent evt)
{
	event_happened = true;
	event_edge = evt.bit.EDGE;
	event_num = evt.bit.NUM;

	return 0;
}

/**
 * @brief start method for the neotrellis; call once in setup()
 *
 *
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

		leds[i] = LED(i, &trellis);
		leds[i].begin();

		RGB col = hue_to_rgb(map(i, 0, 16, 0, 360));
		leds[i].set_color(col);
	}
	trellis.pixels.setBrightness(50);
	trellis.pixels.show();

	Serial.println("[neotrellis::begin] Trellis board ready");
}

/**
 * @brief updates the NeoTrellis; call repeatedly in loop()
 *
 *
void NeoTrellis::update()
{
	bool change_from_action = false; // stores any led change produced in Action namespace
	//* input
	// check for updates
	if (!digitalRead(INT_PIN)) // this thing is necessary apparently, despite using the interrupt
	{
		trellis.read(false);
	}
	// event detection
	if (event_happened)
	{
		event_happened = false;

		if (event_edge == SEESAW_KEYPAD_EDGE_RISING)
		{
			leds[event_num].set_pulse(true);
			change_from_action = Action::event(event_num);
		}
		else if (event_edge == SEESAW_KEYPAD_EDGE_FALLING)
		{
			leds[event_num].set_pulse(false);
		}
	}

	//* leds
	bool changed = false;
	// change from the Action namespace
	if (change_from_action)
	{
		changed = true;
		LEDMap map = Action::get_led_map();
		// update all leds
		for(int i = 0; i < 16; i++)
		{
			leds[i].set_color(map.colors[i]);
			leds[i].set_state(map.states[i]);
		}
	}
	else
	{
		// change from inside this namespace
		for (int i = 0; i < 16; i++)
		{
			if (leds[i].update())
				changed = true;
		}
	}
	if (changed)
		trellis.pixels.show();
}

#endif
*/