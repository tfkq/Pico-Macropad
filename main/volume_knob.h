/**
 * @file volume_knob.h
 * @author zauberwild
 * @brief high level management of the volume knob
 * @version 2.1
 * @date 2022-04-04
 * 
 * @copyright MIT license, Arvid Randow, 2022
 * 
 */


/*

#ifndef volume_knob_h
#define volume_knob_h

// only here to keep my linter happy ￣へ￣
// #include <Bounce2.h>
//TODO remove if i really dont need it

//* SETTINGS
#define DEBOUNCE_TIME 5

namespace VolumeKnob
{

	//* DEFINING VARIABLES
	// pins
	int a = 27;
	int b = 26;
	int sw = 17;
	int led_r = 18;
	int led_g = 19;
	int led_b = 20;
	// bouncing objects
	Bounce bounce_a = Bounce(); // Bounce for all inputs (makes the debouncing a lot easier)
	Bounce bounce_b = Bounce();
	Bounce bounce_sw = Bounce();
	// led object (will fade between hue 0 to 120, middle position 60)
	LED led = LED(led_r, led_g, led_b);

	// values
	bool pulse = false; // saves the button press, to make the led white

	const int STEPS_PER_VOLUME = 1; // how many steps you need to turn the knob for one command send

	int counter_volume; // keeps track of how far the encoder has been turned
	int counter_led;

	unsigned long last_change; // saves the last update, to reset the led on time
	int reset_timer = 2500;	   // [ms] after what time shall the light be resetted?

	//* METHODS

	void begin();
	void update();

}

/** @brief start of the volume knob
 *
void VolumeKnob::begin()
{
	// set the inputs
	bounce_a.attach(a, INPUT_PULLUP);
	bounce_a.interval(DEBOUNCE_TIME);
	bounce_b.attach(b, INPUT_PULLUP);
	bounce_b.interval(DEBOUNCE_TIME);
	bounce_sw.attach(sw, INPUT);
	bounce_sw.interval(DEBOUNCE_TIME);

	// set the led
	led.begin();
	led.set_color(60);

	Serial.println("[VolumeKnob::begin] Volume Knob is spinning!");
}

/** @brief gets the input from the right rotary encoder and spits out volume control
 *
void VolumeKnob::update()
{
	//* rotating fun
	bounce_a.update();
	bounce_b.update();
	if (bounce_a.changed() && bounce_a.read() == LOW)
	{

		last_change = millis();

		if (bounce_b.read() == HIGH)
		{
			counter_volume++;
			counter_led++;
		}
		else
		{
			counter_volume--;
			counter_led--;
		}
	}

	//* sends commands according to the rotating fun
	if (counter_volume == STEPS_PER_VOLUME)
	{
		// volume up
		Macro::press(KEY_F22);
		counter_volume = 0;
	}
	else if (counter_volume == -STEPS_PER_VOLUME)
	{
		Macro::press(KEY_F21);
		counter_volume = 0;
	}

	//* clicking fun
	bounce_sw.update();

	if (bounce_sw.changed())
	{
		pulse = bounce_sw.read();
		if (bounce_sw.read() == HIGH)
		{
			Macro::press(KEY_F20);
		}
	}

	//* led-disco
	// check for time
	if (millis() - reset_timer >= last_change)
	{
		counter_led = 0;
	}

	// calculate hue out of the counter
	float hue = 4 * counter_led + 60;

	// boundary checks
	if (hue < 0)
		hue = 0;
	if (hue > 120)
		hue = 120;

	led.set_color(hue);
	// overwrite if pressed
	led.set_pulse(pulse);
	led.update();
}

#endif
*/