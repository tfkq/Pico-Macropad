/**
 * @file brightness_knob.h
 * @author zauberwild
 * @brief high level management of the brightness knob
 * @version 0.1
 * @date 2022-04-04
 *
 * @copyright MIT license, Arvid Randow, 2022
 *
 */

#ifndef brightness_knob_h
#define brightness_knob_h

namespace BrightnessKnob
{
	RotaryEncoder encoder = RotaryEncoder(9, 8, 14, RGB(13, 12, 11));

	void begin();
	void update();

	void correct_brightness();

}

/**
 * @brief initialize the brightness knob; call one 
 * 
 */
void BrightnessKnob::begin()
{
	encoder.begin();
	encoder.set_color(60);
}

/**
 * @brief update the input and led of the brightness knob; must be called repeatedly without delay
 * 
 */
void BrightnessKnob::update()
{
	encoder.update();

	//* get rotating events
	int event = encoder.get_rot_event();
	if (event != 0)
	{
		if (event == ROTARY_ENCODER_CW)
		{
			raw_brightness += BRIGHTNESS_STEPS_PER_STEPS;
		}
		else if (event == ROTARY_ENCODER_CCW)
		{
			raw_brightness -= BRIGHTNESS_STEPS_PER_STEPS;
		}
		if (raw_brightness < 0)
			raw_brightness = 0;
		else if (raw_brightness > 50) // see "/doc/code documentation/Brightness Correction.md" -> EDIT about this
			raw_brightness = 50;

		correct_brightness();
	}

	//* get clicking events
	//?
	// event = encoder.get_sw_event();
	// if (event == ROTARY_ENCODER_SW_RISING)
	// {
	// }

	//* led management
	// linear function, converts 0..100 to 240..120
	float hue = -1.2 * brightness + 240;
	encoder.set_color(hue);
}

/**
 * @brief calculates the correct brightness out of the raw input
 * 
 */
void BrightnessKnob::correct_brightness()
{
	// see "/doc/code documentation/Brightness Correction.md" about this
	brightness = 1 / (100 * pow(2.718, -0.184 * raw_brightness));
	if (brightness < 0)
		brightness = 0;
	else if (brightness > 100)
		brightness = 100;
}

#endif