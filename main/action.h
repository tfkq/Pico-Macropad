
//! DEPRECATED


/** ACTION
 *
 * this part takes the input from the trellis and
 * executes the shortcuts and navigates the menus and
 * controls the led
 *
 * created by zauberwild on 22.3.22
 * licensed under MIT license
 */
/*
namespace Action
{
	Layout active_layout;

	// saved layouts
	Layout all_layouts[MAX_NUMBER_LAYOUTS]; // list of all saved layouts
	int selected_layouts[4];				// the four selected layouts (index to all_layouts)

	//* FUNCTIONS
	void begin();
	void update();

	bool event(int num);

	LEDMap get_led_map();

	void start_reprogramming();

}

void Action::begin()
{
	LittleFS.begin();
	Serial.println("[Action::begin] ### ### ###");
	//* LOAD ALL LAYOUTS
	for (int i = 0; i < MAX_NUMBER_LAYOUTS; i++)
	{
		// search for file
		char filename[32];

		itoa(i, filename, 10);
		Serial.print("LOOKING FOR FILE: ");
		Serial.print(filename);

		if (LittleFS.exists(filename))
		{
			// open file
			Serial.println(" ... found");
			File file = LittleFS.open(filename, "r");
			// create and clean prefab
			Layout new_l = get_clean_layout();

			//* getting data
			String line = file.readStringUntil('\n');
			// name
			int tab = line.indexOf('\t');
			String s = line.substring(0, tab);
			s.toCharArray(new_l.name, MAX_NAME_LENGTH + 1);
			line.remove(0, tab + 1);

			// color
			tab = line.indexOf('\t');
			new_l.color.r = line.substring(0, tab).toInt();
			line.remove(0, tab + 1);
			tab = line.indexOf('\t');
			new_l.color.g = line.substring(0, tab).toInt();
			line.remove(0, tab + 1);
			tab = line.indexOf('\t');
			new_l.color.b = line.substring(0, tab).toInt();

			Serial.print("\tname: ");
			Serial.print(new_l.name);
			Serial.print("\tmenu color: ");
			Serial.print(new_l.color.r);
			Serial.print(", ");
			Serial.print(new_l.color.g);
			Serial.print(", ");
			Serial.println(new_l.color.b);

			//* getting data of the buttons
			for (int btn = 0; btn < 12; btn++)
			{
				line = file.readStringUntil('\n');
				// cover special cases
				if (line[0] == '-') // unassigned button
				{
					// nothing to do here actually
				}
				else if (line[0] == '~') // reprogramming button
				{
					new_l.buttons[btn].use_macro = false;
					new_l.buttons[btn].press = &start_reprogramming;

					// name
					tab = line.indexOf('\t');
					s = line.substring(0, tab);
					s.toCharArray(new_l.buttons[btn].name, MAX_NAME_LENGTH + 1);
					line.remove(0, tab + 1);

					// color
					tab = line.indexOf('\t');
					new_l.buttons[btn].color.r = line.substring(0, tab).toInt();
					line.remove(0, tab + 1);
					tab = line.indexOf('\t');
					new_l.buttons[btn].color.g = line.substring(0, tab).toInt();
					line.remove(0, tab + 1);
					tab = line.indexOf('\t');
					new_l.buttons[btn].color.b = line.substring(0, tab).toInt();
				}
				else
				{

					// name
					tab = line.indexOf('\t');
					s = line.substring(0, tab);
					s.toCharArray(new_l.buttons[btn].name, MAX_NAME_LENGTH + 1);
					line.remove(0, tab + 1);

					// name
					tab = line.indexOf('\t');
					s = line.substring(0, tab);
					s.toCharArray(new_l.buttons[btn].macro, MAX_MACRO_LENGTH + 1);
					line.remove(0, tab + 1);

					// color
					tab = line.indexOf('\t');
					new_l.buttons[btn].color.r = line.substring(0, tab).toInt();
					line.remove(0, tab + 1);
					tab = line.indexOf('\t');
					new_l.buttons[btn].color.g = line.substring(0, tab).toInt();
					line.remove(0, tab + 1);
					tab = line.indexOf('\t');
					new_l.buttons[btn].color.b = line.substring(0, tab).toInt();
				}

				Serial.print("\t\tnumber: ");
				Serial.print(btn);
				Serial.print("\tname: ");
				Serial.print(new_l.buttons[btn].name);
				Serial.print("\tmacro: ");
				Serial.print(new_l.buttons[btn].macro);
				Serial.print("\tcolor: ");
				Serial.print(new_l.buttons[btn].color.r);
				Serial.print(", ");
				Serial.print(new_l.buttons[btn].color.g);
				Serial.print(", ");
				Serial.println(new_l.buttons[btn].color.b);
			}

			file.close();
			all_layouts[i] = new_l;
		}

		Serial.println();
	}

	Serial.println("[Action::begin] reading config files done");
	Serial.println("[Action::begin] set selected layouts");
	//* SET SELECTED LAYOUTS
	if (LittleFS.exists("sel"))
	{
		File file = LittleFS.open("/sel", "r");
		String s = file.readStringUntil('\n');

		int t = s.indexOf(' ');
		selected_layouts[0] = s.substring(0, t).toInt();
		s.remove(0, t + 1);

		t = s.indexOf(' ');
		selected_layouts[1] = s.substring(0, t).toInt();
		s.remove(0, t + 1);

		t = s.indexOf(' ');
		selected_layouts[2] = s.substring(0, t).toInt();

		Serial.println("\tselected layouts are:");
		Serial.print("\t\t0: ");
		Serial.println(all_layouts[selected_layouts[0]].name);
		Serial.print("\t\t1: ");
		Serial.println(all_layouts[selected_layouts[1]].name);
		Serial.print("\t\t2: ");
		Serial.println(all_layouts[selected_layouts[2]].name);

		file.close();
	}
	else
	{
		Serial.println("\tcouldn't find file 'sel', setting standard values");
		selected_layouts[0] = 1;
		selected_layouts[1] = 2;
		selected_layouts[2] = 3;
	}

	Serial.println("[Action::begin] DONE");

	LittleFS.end();
}

void Action::update()
{
	// do we need that?
}

void Action::start_reprogramming()
{
}

/**
 * @brief performs the action based on current layout and button pressed
 *
 * @param num number of the button pressed. From original Trellis layout, not cleaned from Layout Selectors
 * @return true leds have changed
 * @return false leds did not change
 *
bool Action::event(int num)
{
	//* DOC
	/**
	 * Button Layout:
	 *  0  1  2  3
	 *  4  5  6  7
	 *  8  9 10 11
	 * 12 13 14 15
	 *
	 * struct Layout:
	 *  -  0  1  2
	 *  -  3  4  5
	 *  -  6  7  8
	 *  -  9 10 11
	 *
	 * LEFT COLUMN:
	 * the left-most column changes between the menus. The first one (btn 0) will always be for the main menu with
	 * system controls. the remaining three buttons (4, 8, 12) can be remapped to different layers
	 *

	//* CODE
	//* action for the left column (navigation)
	if (num == 0)
	{
		active_layout = all_layouts[0];
		return true;
	}
	if (num == 4 || num == 8 || num == 12)
	{
		active_layout = all_layouts[selected_layouts[num / 4]];
		return true;
	}

	//* action for all the other keys
	// get the button index for layout (button num -> layout index)
	int layout_index = 0;
	if (num <= 3)
	{
		layout_index = num - 1;
	}
	else if (num <= 7)
	{
		layout_index = num - 2;
	}
	else if (num <= 11)
	{
		layout_index = num - 3;
	}
	else
	{
		layout_index = num - 4;
	}

	// perform the action
	Button button = active_layout.buttons[layout_index];
	if (button.use_macro)
	{

		// Macro::print(button.macro);
		Serial.println("### [Action::event] ###");
		Serial.print("\t");
		Serial.println(button.macro);
	}
	else
	{
		// this would probably be the reprogramming button
		button.press();
		return true;
	}

	return false;
}

/**
 * @brief creates an led map for the NeoTrellis
 *
 * @return LEDMap the finished map
 *
LEDMap Action::get_led_map()
{
	LEDMap map;

	// set the left column
	map.colors[0] = all_layouts[selected_layouts[0]].color;
	map.colors[4] = all_layouts[selected_layouts[1]].color;
	map.colors[8] = all_layouts[selected_layouts[2]].color;
	map.colors[12] = all_layouts[selected_layouts[3]].color;
	map.states[0] = all_layouts[selected_layouts[0]].state;
	map.states[4] = all_layouts[selected_layouts[1]].state;
	map.states[8] = all_layouts[selected_layouts[2]].state;
	map.states[12] = all_layouts[selected_layouts[3]].state;


	// set the action area
	int translation_map[] = {1, 2, 3, 5, 6, 7, 9, 10, 11, 13, 14, 15};	// translates the Layout index to the led index

	for (int i = 0; i < 12; i++)
	{
		RGB color = active_layout.buttons[i].color;
		LEDStates state = active_layout.buttons[i].state;
		map.colors[translation_map[i]] = color;
		map.states[translation_map[i]] = state;
	}


	return map;
}
*/