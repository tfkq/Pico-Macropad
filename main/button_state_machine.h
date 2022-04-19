/**
 * @file button_state_machine.h
 * @author zauberwild
 * @brief class the controls a button of the Neotrellis. complete with input and led controlling (incl. state machine)
 * @version 2.1
 * @date 2022-04-04
 *
 * @copyright MIT license, Arvid Randow, 2022
 *
 */

#ifndef button_state_machine_h
#define button_state_machine_h

class TrellisButton
{
	int trellis_number;

	RGB color;
	LEDStates state;

	bool changed = false;

	uint8_t event;

public:
	TrellisButton();
	TrellisButton(int p_trellis_number);

	void begin();
	void update();

	int get_event();

	void set_color(RGB p_color);
	void set_color(int hue);
	void set_state(LEDStates p_state);
	void set_on_off(bool on);
	void set_flash(bool on);
	void set_blink(bool on);
};

/**
 * @brief Construct a new Trellis Button:: Trellis Button object
 *
 */
TrellisButton::TrellisButton()
{
}

/**
 * @brief Construct a new Trellis Button:: Trellis Button object
 *
 * @param p_trellis_number number of the button on the trellis; 0..15
 */
TrellisButton::TrellisButton(int p_trellis_number)
{
	trellis_number = p_trellis_number;
}

/**
 * @brief begins the macropad. needless for now
 *
 */
void TrellisButton::begin()
{
}

/**
 * @brief updates the button on input and led status. has to be called repetitively and without delay
 *
 */
void TrellisButton::update()
{
	//* update button
	if (state.on)
	{
		event = NeoTrellis::get_event(trellis_number);
	}
	else
	{
		event = 0;
	}
	if (event == SEESAW_KEYPAD_EDGE_RISING)
	{
		state.pulse = true;
	}
	else if (event == SEESAW_KEYPAD_EDGE_FALLING)
	{
		state.pulse = false;
	}

	//* update led
	RGB actual_color = color;
	// state machine
	if (state.on == false) // led is off
	{
		actual_color = RGB(0, 0, 0);
	}
	else if (state.pulse) // led is pressed
	{
		actual_color = RGB(255, 255, 255);
	}
	else if (state.flash) // make it flash
	{
		// einfach Kosinus verwenden
		double mod = (cos(2 * PI * millis() / 2000)+1)*0.5;
		actual_color.r *= mod;
		actual_color.g *= mod;
		actual_color.b *= mod;
	}
	else if (state.blink) // just a blink
	{
		// einfach Kosinus verwenden
		double mod = cos(2 * PI * millis() / 1000);
		if (mod > 0.99) // only for short periods of time
		{
			actual_color.r *= 0.65; // make the brightness a tiny little bit lower
			actual_color.g *= 0.65;
			actual_color.b *= 0.65;
		}
	}

	// writing
	NeoTrellis::set_color(trellis_number, actual_color);
}

/**
 * @brief get an event
 * 
 * @return int SEESAW_KEYPAD_EDGE_RISING or SEESAW_KEYPAD_EDGE_FALLING
 */
int TrellisButton::get_event()
{
	return event;
}



/**
 * @brief set the color of the led
 *
 * @param p_color color
 */
void TrellisButton::set_color(RGB p_color)
{
	color = p_color;
}

/**
 * @brief turn button on or off. also effects button itself
 *
 * @param on
 */
void TrellisButton::set_on_off(bool on)
{
	state.on = on;
}


/**
 * @brief turn on/off flash (fading on-off)
 * 
 * @param on 
 */
void TrellisButton::set_flash(bool on)
{
	state.flash = on;
}

/**
 * @brief turn on/off blink (small, unobtrusive blink)
 * 
 * @param on 
 */
void TrellisButton::set_blink(bool on)
{
	state.blink = on;
}

#endif