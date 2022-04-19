/**
 * @file rotary_encoder.h
 * @author zauberwild
 * @brief low-level communication with a rotary encoder
 * @version 2.1
 * @date 2022-04-04
 *
 * @copyright MIT license, Arvid, Randow 2022
 *
 */

#ifndef rotary_encoder_h
#define rotary_encoder_h

#define ROTARY_ENCODER_SW_RISING 3
#define ROTARY_ENCODER_SW_FALLING 2
#define ROTARY_ENCODER_CCW 13
#define ROTARY_ENCODER_CW 12

class RotaryEncoder
{
	// button / encoder
	int a, b, sw;
	Bounce bounce_a = Bounce(); // Bounce for all inputs (makes the debouncing a lot easier)
	Bounce bounce_b = Bounce();
	Bounce bounce_sw = Bounce();
	u_int8_t rot_event;
	u_int8_t sw_event;
	// led
	RGB pins;
	RGB color;
	bool changed = true;
	bool pulse;

public:
	RotaryEncoder();
	RotaryEncoder(int p_a, int p_b, int p_sw, RGB p_pins);
	void begin();
	void update();

	void set_color(RGB p_color);
	void set_color(int hue);
	int get_rot_event();
	int get_sw_event();
};

/**
 * @brief Construct a new Rotary Encoder:: Rotary Encoder object
 * 
 */
RotaryEncoder::RotaryEncoder() {}

/**
 * @brief Construct a new Rotary Encoder:: Rotary Encoder object
 * 
 * @param p_a pin for encoder switch A (or CLK)
 * @param p_b pin for encoder switch B (or Data or Signal)
 * @param p_sw pin for built-in button
 * @param p_pins pins of the rgb-led as RGB(r, g, b)
 */
RotaryEncoder::RotaryEncoder(int p_a, int p_b, int p_sw, RGB p_pins)
{
	a = p_a;
	b = p_b;
	sw = p_sw;
	pins = p_pins;
}

/**
 * @brief initializes the encoder; call once on startup
 * 
 */
void RotaryEncoder::begin()
{
	// set the inputs
	bounce_a.attach(a, INPUT_PULLUP);
	bounce_a.interval(DEBOUNCE_TIME);
	bounce_b.attach(b, INPUT_PULLUP);
	bounce_b.interval(DEBOUNCE_TIME);
	bounce_sw.attach(sw, INPUT);
	bounce_sw.interval(DEBOUNCE_TIME);

	// set the leds
	pinMode(pins.r, OUTPUT);
	pinMode(pins.g, OUTPUT);
	pinMode(pins.b, OUTPUT);
}

/**
 * @brief update the encoder; must be called repeatedly without delay
 * 
 */
void RotaryEncoder::update()
{
	//* rotating fun
	bounce_a.update();
	bounce_b.update();
	rot_event = 0;
	if (bounce_a.changed() && bounce_a.read() == LOW)
	{
		last_input = millis();
		if (bounce_b.read() == HIGH)
		{
			rot_event = ROTARY_ENCODER_CW;
		}
		else
		{
			rot_event = ROTARY_ENCODER_CCW;
		}
	}

	//* clicking fun
	bounce_sw.update();
	sw_event = 0;
	if (bounce_sw.changed())
	{
		last_input = millis();
		Display::announce_change();
		pulse = bounce_sw.read();
		changed = true;
		if (bounce_sw.read() == HIGH)
		{
			sw_event = ROTARY_ENCODER_SW_RISING;
		}
		else
		{
			sw_event = ROTARY_ENCODER_SW_FALLING;
		}
	}

	//* blinky-blinky fun
	if (changed)
	{
		changed = false;
		RGB actual_color = color;
		if (pulse)
		{
			actual_color = RGB(255, 255, 255);
		}

		float enc_brightness = brightness * 2;
		if (enc_brightness < 0)
			enc_brightness = 0;
		else if (enc_brightness > 100)
			enc_brightness = 100;
		
		enc_brightness /= 100;

		analogWrite(pins.r, 255 - (actual_color.r * enc_brightness));
		analogWrite(pins.g, 255 - (actual_color.g * enc_brightness));
		analogWrite(pins.b, 255 - (actual_color.b * enc_brightness));
	}
}

/**
 * @brief set the color of the encoder
 * 
 * @param p_color color as RGB
 */
void RotaryEncoder::set_color(RGB p_color)
{
	color = p_color;
	changed = true;
}

/**
 * @brief set the color of the encoder
 * 
 * @param hue hue of the color (saturation and value are assumed to be 100%)
 */
void RotaryEncoder::set_color(int hue)
{
	color = hue_to_rgb(hue);
	changed = true;
}

/**
 * @brief get any event from the rotating bit
 * 
 * @return int 0: no event; ROTARY_ENCODER_CW when turning clockwise; ROTARY_ENCODER_CCW when turning counterclockwise
 */
int RotaryEncoder::get_rot_event()
{
	return rot_event;
}

/**
 * @brief get any event from the clicky bit
 * 
 * @return int 0: no event; ROTARY_ENCODER_SW_RISING or ROTARY_ENCODER_SW_FALLING when value changed
 */
int RotaryEncoder::get_sw_event()
{
	return sw_event;
}

#endif