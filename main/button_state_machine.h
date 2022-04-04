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




/*
class LED
{
private:
	bool trellis_led;
	int pin_r, pin_g, pin_b;
	int led_number = 0;
	Adafruit_NeoTrellis *trellis;
	RGB value;
	RGB prev_buffer;

	// states
	LEDStates state;

public:
	LED();
	LED(int p_number, Adafruit_NeoTrellis *trellis_p); // constructor for neotrellis LED
	LED(int p_r, int p_g, int p_b);					   // constructor for Encoder LED

	void begin();

	// color
	void set_color(float p_hue);
	void set_color(RGB p_value);

	// states
	void set_state(LEDStates p_state);
	void set_on_off(bool on);
	void set_flash(bool flash);
	void set_pulse(bool pulse);

	bool update();
};

/**
 * @brief Construct a new LED::LED object.
 * I don't know why I need it, but I need it ¯\_(ツ)_/¯
 *
LED::LED()
{
}

/**
 * @brief Construct a new LED::LED object
 *
 * @param p_number number of the button
 * @param trellis_p pointer to the trellis object in control of the led
 *
LED::LED(int p_number, Adafruit_NeoTrellis *trellis_p)
{
	trellis_led = true;
	led_number = p_number;
	trellis = trellis_p;
}

/**
 * @brief Construct a new LED::LED object
 *
 * @param p_r pin of red led
 * @param p_g pin of green led
 * @param p_b pin of blue led
 *
LED::LED(int p_r, int p_g, int p_b)
{
	trellis_led = false;
	pin_r = p_r;
	pin_g = p_g;
	pin_b = p_b;
}

/**
 * @brief start the led object, mainly just sets the pinmode for the encoder leds
 *
 *
void LED::begin()
{
	if (trellis_led)
	{
	}
	else
	{
		pinMode(pin_r, OUTPUT);
		pinMode(pin_g, OUTPUT);
		pinMode(pin_b, OUTPUT);
	}
}

/**
 * @brief set the color via the hue
 *
 * @param p_hue the hue [0;360]
 *
void LED::set_color(float p_hue)
{
	value = hue_to_rgb(p_hue);
}

/**
 * @brief set the color via rgb values
 *
 * @param p_value input them as a rgb-struct
 *
void LED::set_color(RGB p_value)
{
	value = p_value;
}

/**
 * @brief overwrite the complete state
 *
 * @param p_state
 *
void LED::set_state(LEDStates p_state)
{
	state = p_state;
}

/**
 * @brief turn the led off and on
 * (this state has the highest priority)
 * @param on true for on; false for off
 *
void LED::set_on_off(bool on)
{
	state.off = !on;
}

/**
 * @brief set the led to flashing
 * (this state has third priority)
 * @param flash true to turn it on; false to turn it off
 *
void LED::set_flash(bool flash)
{
	state.flash = flash;
}

/**
 * @brief set the led to pulse (white flash)
 * (this state has second priority)
 * @param pulse true to turn it on; false to turn it off
 *
void LED::set_pulse(bool pulse)
{
	state.pulse = pulse;
}

/**
 * @brief update the led
 *
 * @return true values have changed
 * @return false values did not change
 *
bool LED::update()
{
	RGB buffer = value;

	//* modifications

	if (state.off)
	{
		buffer.r = 0;
		buffer.r = 0;
		buffer.r = 0;
	}
	else if (state.pulse)
	{
		buffer.r = 255;
		buffer.g = 255;
		buffer.b = 255;
	}
	else if (state.flash)
	{
		// TODO make it go blinky blinky
	}

	// check if something changed from the last time
	bool changed = false;
	if (buffer.r != prev_buffer.r ||
		buffer.g != prev_buffer.g ||
		buffer.b != prev_buffer.b)
		changed = true;

	//* write to the leds
	if (changed)
	{
		if (trellis_led)
		{
			trellis->pixels.setPixelColor(led_number,
										  trellis->pixels.Color(
											  buffer.r, buffer.g, buffer.b));
		}
		else
		{
			analogWrite(pin_r, 255 - buffer.r);
			analogWrite(pin_g, 255 - buffer.g);
			analogWrite(pin_b, 255 - buffer.b);
		}
	}

	prev_buffer = buffer;

	return changed;
}
*/