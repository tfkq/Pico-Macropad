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

#ifndef volume_knob_h
#define volume_knob_h

namespace VolumeKnob
{
	RotaryEncoder encoder = RotaryEncoder(27, 26, 17, RGB(18, 19, 20));

	int counter_volume; // keeps track of how far the encoder has been turned
	int counter_led;

	unsigned long last_change; // saves the last update, to reset the led on time
	int reset_timer = 2500;	   // [ms] after what time shall the light be resetted?

	void begin();
	void update();

}

/**
 * @brief start the volume knob; call once in setup
 * 
 */
void VolumeKnob::begin()
{
	encoder.begin();
	encoder.set_color(60);
}

/**
 * @brief updates the input and led of the volume knob; call repeatedly without delay
 * 
 */
void VolumeKnob::update()
{
	encoder.update();

	//* get rotating events
	int event = encoder.get_rot_event();
	if (event == ROTARY_ENCODER_CW)
	{
		counter_volume++;
		counter_led++;
		last_change = millis();
	}
	else if (event == ROTARY_ENCODER_CCW)
	{
		counter_volume--;
		counter_led--;
		last_change = millis();
	}

	// send commands
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

	//* get clicking events
	event = encoder.get_sw_event();
	if (event == ROTARY_ENCODER_SW_RISING)
	{
		Macro::press(KEY_F20);
	}

	//* led management
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

	encoder.set_color(hue);
}

#endif