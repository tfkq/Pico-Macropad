/**
 * @file menu.h
 * @author zauberwild
 * @brief menu namespace, which manages everything that makes ths thing interactive
 * @version 0.1
 * @date 2022-04-04
 *
 * @copyright MIT license, Arvid Randow, 2022
 *
 */

namespace Menu
{
	//* TYPEDEFS

	struct Layer
	{
		bool used = true;
		char title[MAX_NAME_LENGTH + 1];
		RGB color;
		char btn_names[12][MAX_NAME_LENGTH + 1];
		RGB btn_colors[12];
		char btn_commands[12][MAX_MACRO_LENGTH + 1];
	};

	//* VARIABLES AND OBJECTS

	Layer layers[13]; // saves all layers

	int selected_layers[] = {-1, -1, -1, -1}; // saves the selected layers in the menu; -1 means unused spot
	int active_layer = 0;					  // saves the active layer
	int prev_active_layer = 0;

	bool output_changed = true;
	bool layer_key_has_been_pressed = false; // saves whether a layer key was pressed while a menu kay was holded

	TrellisButton btn_menu[4];
	TrellisButton btn_layer[12];

	int translation_map_layer[] = {1, 2, 3, 5, 6, 7, 9, 10, 11, 13, 14, 15};
	int translation_map_menu[] = {0, 4, 8, 12};

	// [PROG]
	int prog_phase = 0;
	int prog_selection = 0;

	//* FUNCTIONS

	int begin();

	void update();

	void write_sel_to_file();

}

/**
 * @brief loads the config files
 *
 * @return int 0 if successful or error code:
 * 1: unable to mount file system
 * 2: unable to open file
 */
int Menu::begin()
{
	Serial.println("### [menu] READING CONFIG FILES ###");
	//* mount file system
	if (!LittleFS.begin())
	{
		Serial.println("[ERROR] couldn't mount file system");
		return 1;
	}

	//* read "sel" file
	Serial.println("#1 reading standard config");
	File sel = LittleFS.open("sel", "r");

	if (!sel)
	{
		Serial.println("[ERROR] file couldn't be opened");
		return 2;
	}

	for (int i = 0; i < 4; i++)
	{
		selected_layers[i] = sel.parseInt();
		Serial.print(selected_layers[i]);
		Serial.print(", ");
	}
	Serial.println("finished.");
	sel.close();

	//* read other config files
	Serial.println("#2 reading layer files");

	for (int i = 0; i <= 12; i++)
	{
		String filename = String(i);
		if (LittleFS.exists(filename))
		{
			// getting essential layer data
			Serial.println("-> file " + filename + " exists");

			File file = LittleFS.open(filename, "r");
			if (!file)
			{
				Serial.println("[ERROR] file couldn't be opened");
				return 2;
			}

			file.readStringUntil('\t').toCharArray(layers[i].title, MAX_NAME_LENGTH + 1);
			layers[i].color.r = file.readStringUntil('\t').toInt();
			layers[i].color.g = file.readStringUntil('\t').toInt();
			layers[i].color.b = file.readStringUntil('\n').toInt();

			Serial.print("\tLayer name: ");
			Serial.println(layers[i].title);
			Serial.print("\tLayer Color: ");
			Serial.print(layers[i].color.r);
			Serial.print(", ");
			Serial.print(layers[i].color.g);
			Serial.print(", ");
			Serial.println(layers[i].color.b);

			// getting button data
			for (int j = 0; j < 12; j++)
			{
				file.readStringUntil('\t').toCharArray(layers[i].btn_names[j], MAX_NAME_LENGTH + 1);
				file.readStringUntil('\t').toCharArray(layers[i].btn_commands[j], MAX_MACRO_LENGTH + 1);
				layers[i].btn_colors[j].r = file.readStringUntil('\t').toInt();
				layers[i].btn_colors[j].g = file.readStringUntil('\t').toInt();
				layers[i].btn_colors[j].b = file.readStringUntil('\n').toInt();

				Serial.print("\t\tButton #");
				Serial.println(j);
				Serial.print("\t\t\tbutton name:\t");
				Serial.println(layers[i].btn_names[j]);
				Serial.print("\t\t\tbutton command:\t");
				Serial.println(layers[i].btn_commands[j]);
				Serial.print("\t\t\tbutton Color:\t");
				Serial.print(layers[i].btn_colors[j].r);
				Serial.print(", ");
				Serial.print(layers[i].btn_colors[j].r);
				Serial.print(", ");
				Serial.println(layers[i].btn_colors[j].r);
			}

			file.close();
		}
		else
		{
			Serial.println("-> file " + filename + " does not exist");
			layers[i].used = false;
		}
	}

	Serial.println("### [menu] READING DONE ### ###");

	//* prepare objects and variables
	// menu buttons
	for (int i = 0; i < 4; i++)
	{
		btn_menu[i] = TrellisButton(translation_map_menu[i]);
	}
	for (int i = 0; i < 12; i++)
	{
		btn_layer[i] = TrellisButton(translation_map_layer[i]);
	}

	return 0;
}

/**
 * @brief updates the menu; must be called repeatedly and without delay
 * 
 */
void Menu::update()
{
	//* UPDATE
	// neotrellis
	for (int i = 0; i < 4; i++)
	{
		btn_menu[i].update();
	}
	for (int i = 0; i < 12; i++)
	{
		btn_layer[i].update();
	}

	//* ### ### NORMAL MODE ### ###
	if (prog_phase == 0)
	{
		//* INPUT AND PROCESSING
		//* menu
		for (int i = 0; i < 4; i++)
		{
			if (btn_menu[i].get_event() == SEESAW_KEYPAD_EDGE_RISING)
			{
				if (selected_layers[i] != -1) // if layer is not unused
				{
					prev_active_layer = active_layer;
					active_layer = selected_layers[i];
					output_changed = true;
					layer_key_has_been_pressed = false;
				}
			}
			if (btn_menu[i].get_event() == SEESAW_KEYPAD_EDGE_FALLING && layer_key_has_been_pressed)
			{
				if (selected_layers[i] != -1) // if layer is not unused
				{
					layer_key_has_been_pressed = false;

					active_layer = prev_active_layer;
					output_changed = true;
				}
			}
		}

		//* layer
		for (int i = 0; i < 12; i++)
		{
			if (btn_layer[i].get_event() == SEESAW_KEYPAD_EDGE_RISING)
			{
				// check for programming button
				if (strcmp(layers[active_layer].btn_names[i], "[PROG]") == 0)
				{
					// start programming mode
					prog_phase = 1;
				}
				else
				{
					Macro::print(layers[active_layer].btn_commands[i]);
					layer_key_has_been_pressed = true;
				}
			}
		}

		//* OUTPUT
		if (output_changed)
		{
			output_changed = false;

			for (int i = 0; i < 4; i++)
			{
				if (selected_layers[i] != -1) // if layer is not unused
				{
					// neotrellis leds
					btn_menu[i].set_color(layers[selected_layers[i]].color);
					btn_menu[i].set_on_off(true);

					// set blink if active layer
					btn_menu[i].set_blink(layers[selected_layers[i]].title == layers[active_layer].title);
				}
				else
				{
					btn_menu[i].set_on_off(false);
					btn_menu[i].set_color(RGB(127,127,127));
				}
			}
			for (int i = 0; i < 12; i++)
			{
				// neotrellis leds
				btn_layer[i].set_color(layers[active_layer].btn_colors[i]);

				// turn leds off, when button unused
				btn_layer[i].set_on_off(!(layers[active_layer].btn_names[i][0] == 0));

				// display
				Display::set_text(i, layers[active_layer].btn_names[i]);
			}

			// display
			Display::set_title(layers[active_layer].title);
		}
	}
	else
	{
		//* ### ### PROG MODE ### ###
		switch (prog_phase)
		{
		case 1:
			//* STARTING UP PROG MODE - SETTING UP LAYER SELECTION
			// turn the menu off
			for (int i = 0; i < 4; i++)
				btn_menu[i].set_on_off(false);

			Display::set_title("[PROG] select layer");
			for (int i = 0; i < 12; i++)
			{
				// check if layer is used
				if (layers[i + 1].used)
				{
					// set display
					Display::set_text(i, layers[i + 1].title);

					// set trellis -> layer
					btn_layer[i].set_color(layers[i + 1].color);
					btn_layer[i].set_flash(true);
				}
				else
				{
					// set display
					Display::set_text(i, "");

					// set trellis -> layer
					btn_layer[i].set_on_off(false);
				}
			}

			prog_phase = 2;

		case 2:
			//* WAITING FOR INPUT - SELECT A LAYER
			for (int i = 0; i < 12; i++)
			{
				if (btn_layer[i].get_event() == SEESAW_KEYPAD_EDGE_RISING)
				{
					prog_selection = i + 1;
					prog_phase = 3;
				}
			}

			break;

		case 3: //* SETTING UP MENU SPOT SELECTION
			// clear layer area
			for (int i = 0; i < 12; i++)
			{
				// display
				Display::set_text(i, "");

				// trellis
				btn_layer[i].set_on_off(false);
			}

			for (int i = 1; i < 4; i++)
			{
				// set menu
				btn_menu[i].set_on_off(true);
				btn_menu[i].set_flash(true);
				// set display
				Display::set_text(0, i, layers[selected_layers[i]].title);
			}
			Display::set_title("[PROG] select menu spot");

			prog_phase = 4;

		case 4:

			//* WAITING FOR INPUT - SELECT A MENU SPOT
			for (int i = 1; i < 4; i++)
			{
				if (btn_menu[i].get_event() == SEESAW_KEYPAD_EDGE_RISING)
				{
					// make sure we don't place the same layer two times
					for (int j = 1; j < 4; j++)
					{
						if (selected_layers[j] == prog_selection)
						{
							selected_layers[j] = -1;
						}
					}
					// set layer
					selected_layers[i] = prog_selection;

					// write to file
					write_sel_to_file();

					// exit prog mode
					prog_phase = 0;
					for (int j = 0; j < 4; j++)
					{
						btn_menu[j].set_on_off(true);
						btn_menu[j].set_flash(false);
					}
					for (int j = 0; j < 12; j++)
					{
						btn_layer[j].set_on_off(true);
						btn_layer[j].set_flash(false);
					}
					output_changed = true;
				}
			}

			break;

		default:
			break;
		}
	}
}

/**
 * @brief writes the current selection of layouts to the 'sel' file on the file system
 *
 */
void Menu::write_sel_to_file()
{
	File sel = LittleFS.open("sel", "w");
	for (int i = 0; i < 4; i++)
	{
		// char t[7];
		// sprintf(t,"%d",i);
		sel.print(i);
		sel.print('\n');
	}
	sel.close();
}