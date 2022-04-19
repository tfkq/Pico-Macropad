/**
 * @file display.h
 * @author zauberwild
 * @brief writes the text to the display. takes (kinda) high level instructions, does the math itself and uses the
 * (kinda) low-level functions of the library
 * @version 0.1
 * @date 2022-04-04
 *
 * @copyright MIT license, Arvid Randow, 2022
 *
 */

#ifndef display_h
#define display_h

//* DEFINING CONSTANTS
#define SCREEN_WIDTH 128	// OLED display width, in pixels
#define SCREEN_HEIGHT 64	// OLED display height, in pixels
#define OLED_RESET 28		// Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

namespace Display
{
	//* VARIABLES AND OBJECTS
	Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

	bool change = false;
	bool on = true;
	unsigned long last_update = 0;

	// text / position of text
	char title[MAX_NAME_LENGTH + 1];
	int title_pos[] = {64, 2};											 // --v
	char text[12][MAX_NAME_LENGTH + 1];									 //  --v
	int text_x[] = {19, 64, 109, 19, 64, 109, 19, 64, 109, 19, 64, 109}; // the middle coordinate of every textfield
	int text_y[] = {18, 18, 18, 30, 30, 30, 42, 42, 42, 54, 54, 54};	 // coordinate of the upper edge

	//* FUNCTIONS
	void begin();
	void update();

	int get_x_coordinate(char *text, int middle);

	void write_to_display();

	void announce_change();
	void set_title(char *p_title);
	void set_text(int p_number, char *p_text);
	void set_text(int x, int y, char *p_text);
}

/**
 * @brief initializes the display; call once on startup
 *
 */
void Display::begin()
{
	// start display and test if it works
	if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
	{
		// Serial.println("[display::begin] DISPLAY NO NO WORKING");
		// Serial.println(F("SSD1306 allocation failed"));
		while (true)
		{
		} // Don't proceed, loop forever
	}

	// Serial.println("[display::begin] display ready to go");

	display.clearDisplay();
	display.display();

	// manage settings for displaying text
	display.setTextColor(1, 0);
	display.setTextSize(1);
	display.cp437(true);

	Serial.println("[Display::begin] Display ready");
}

/**
 * @brief update the display; must be called repeatedly without delay
 *
 */
void Display::update()
{
	// check for display update
	if (last_update + DISPLAY_UPDATE_TIME <= millis())
	{
		change = true;
	}

	// check for timeout
	bool pre_on = on;
	on = last_input + DISPLAY_TIMEOUT >= millis();

	if (pre_on != on)
		change = true;

	// draw to display if something changed
	if (change)
	{
		change = false;
		last_update = millis();

		display.clearDisplay();

		if (on)
		{
			// draw title
			display.setCursor(get_x_coordinate(title, title_pos[0]), title_pos[1]);
			display.print(title);
			// draw separating line
			// calculate the left x-postion and length of the line depending on the remaining
			// until the display will turn off (linear function)
			int time_until_off = last_input + DISPLAY_TIMEOUT - millis();
			int pos_x = ((64 * time_until_off) / -DISPLAY_TIMEOUT) + 64;
			int length = (128 * time_until_off) / DISPLAY_TIMEOUT;
			// Serial.println(pos_x);
			display.drawFastHLine(pos_x, 13, length, 1);
			display.drawFastHLine(pos_x, 14, length, 1);
			// draw text
			for (int i = 0; i < 12; i++)
			{
				display.setCursor(get_x_coordinate(text[i], text_x[i]), text_y[i]);
				display.print(text[i]);
			}
		}
		display.display();
	}
}

/**
 * @brief update the display asap
 *
 */
void Display::announce_change()
{
	change = true;
}

/**
 * @brief change the title
 *
 * @param p_title the new title
 */
void Display::set_title(char *p_title)
{
	strcpy(title, p_title);
	change = true;
}

/**
 * @brief change the text on a certain position
 *
 * @param p_number index of the position; layer index: 0..11
 * @param p_text the new text
 */
void Display::set_text(int p_number, char *p_text)
{
	strcpy(text[p_number], p_text);
	change = true;
}

/**
 * @brief change the text on a certain position
 *
 * @param x x postion; 0..2
 * @param y y position; 0..3
 * @param p_text the new text
 */
void Display::set_text(int x, int y, char *p_text)
{
	int number = x + (y * 3);
	set_text(number, p_text);
	change = true;
}

/**
 * @brief calculates the necessary x-coordinate to place text middle-centered
 *
 * @param text the text to place
 * @param middle the middle x-coordinate
 * @return int x-coordinate of the left border
 */
int Display::get_x_coordinate(char *text, int middle)
{

	int number_of_chars = 0; // count the number of characters
	for (int i = 0; i < 24; i++)
	{
		if (text[i] == 0)
			break;

		number_of_chars++;
	}

	int length = number_of_chars * 6; // calculate the length of the text with the width of one character

	return middle - (length / 2); // return the most left coordinate
}

#endif
