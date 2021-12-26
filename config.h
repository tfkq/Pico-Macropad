/** CONFIG
 * 
 * this file saves the different shortcuts, saving them in structs
 * 
 * created by zauberwild on 16.08.2021
 * 
 */

#ifndef config_h
#define config_h
#include "Arduino.h"

//* define colors here
// when defining colors you can either just use the index or
// use #define to give each index a name
const int color_table[][3] = {
	{0, 0, 0},
	{255, 0, 0},
	{255, 64, 0},
	{255, 127, 0},
	{255, 191, 0},
	{255, 255, 0},
	{191, 255, 0},
	{127, 255, 0},
	{64, 255, 0},
	{0, 255, 0},
	{0, 255, 64},
	{0, 255, 127},
	{0, 255, 191},
	{0, 255, 255},
	{0, 191, 255},
	{0, 127, 255},
	{0, 64, 255},
	{0, 0, 255},
	{64, 0, 255},
	{127, 0, 255},
	{191, 0, 255},
	{255, 0, 255},
	{255, 0, 191},
	{255, 0, 127},
	{255, 0, 64},
};

namespace Config
{

	//* data structures
	/** Button Struct
	 * saves name, shortcut and color of an Button
	 */
	struct Button
	{
		char name[5];
		char shortcut[64];
		int color;
	};

	/** App Struct
	 * saves a name of the app and Button(struct) for all the 16 buttons
	 */
	struct App
	{
		char name[21];
		Button buttons[16];
	};

	//* variables

	App apps[24];

	//* functions
	/** @brief set up all the config data. Apps and their shortcuts are hardcoded in here
	 */
	void begin()
	{

		// struct Button emptyButton = {"-", "", 0};

		//* CREATE APPS AND SHORTCUTS HERE
		//--SOF_ShortcutDefintion--

		// MAIN
		struct App MAIN = {"MAIN",
						   {
							   {"MIC", "$F240#0.", 5},
							   {"Lock", "$F240#1.", 3},
							   {"StBy", "$F240#2.", 2},
							   {"Off", "$F240#3.", 1},
							   {"Min", "$F240#4.", 14},
							   {"Max", "$F240#5.", 14},
							   {"Prev", "$F240#6.", 4},
							   {"Next", "$F240#7.", 4},
							   {"", "", 0},
							   {"", "", 0},
							   {"", "", 0},
							   {"", "", 0},
							   {"Win1", "$F240#12.", 17},
							   {"Win2", "$F240#13.", 17},
							   {"Win3", "$F240#14.", 17},
							   {"Win4", "$F240#15.", 17},

						   }};

		// QuickStart
		struct App QuickStart = {"QuickStart",
								 {
									 {"AbiV", "$F241#0.", 19},
									 {"HA_V", "$F241#1.", 19},
									 {"NB_V", "$F241#2.", 19},
									 {"Obdn", "$F241#3.", 19},
									 {"Typo", "$F241#4.", 12},
									 {"Notn", "$F241#5.", 12},
									 {"Word", "$F241#6.", 17},
									 {"Excl", "$F241#7.", 9},
									 {"", "", 0},
									 {"", "", 0},
									 {"", "", 0},
									 {"", "", 0},
									 {"Sblm", "$F241#12.", 3},
									 {"VSCo", "$F241#13.", 15},
									 {"Ardu", "$F241#14.", 12},
									 {"ViSt", "$F241#15.", 20},

								 }};

		// Firefox
		struct App Firefox = {"Firefox",
							  {
								  {"NTab", "$F242#0.", 7},
								  {"NWin", "$F242#1.", 8},
								  {"CTab", "$F242#2.", 3},
								  {"CWin", "$F242#3.", 1},
								  {"Srch", "$F242#4.", 23},
								  {"Wiki", "$F242#5.", 23},
								  {"Leo", "$F242#6.", 23},
								  {"SrPg", "$F242#7.", 23},
								  {"Mute", "$F242#8.", 4},
								  {"Z0", "$F242#9.", 14},
								  {"Z-", "$F242#10.", 14},
								  {"Z+", "$F242#11.", 14},
								  {"Home", "$F242#12.", 16},
								  {"Refr", "$F242#13.", 16},
								  {"<T<", "$F242#14.", 17},
								  {">T>", "$F242#15.", 17},

							  }};

		// VS_Code
		struct App VS_Code = {"VS-Code",
							  {
								  {"", "", 0},
								  {"", "", 0},
								  {"", "", 0},
								  {"", "", 0},
								  {"", "", 0},
								  {"", "", 0},
								  {"", "", 0},
								  {"", "", 0},
								  {"", "", 0},
								  {"", "", 0},
								  {"", "", 0},
								  {"", "", 0},
								  {"", "", 0},
								  {"", "", 0},
								  {"", "", 0},
								  {"", "", 0},

							  }};

		// Obsidian
		struct App Obsidian = {"Obsidian",
							   {
								   {"Expl", "$F244#0.", 20},
								   {"OFil", "$F244#1.", 8},
								   {"Cmd", "$F244#2.", 11},
								   {"Tags", "$F244#3.", 14},
								   {"Srch", "$F244#4.", 20},
								   {"Mode", "$F244#5.", 17},
								   {"", "", 0},
								   {"Outl", "$F244#7.", 14},
								   {"Grph", "$F244#8.", 19},
								   {"Corr", "$F244#9.", 4},
								   {"Corr", "$F244#10.", 5},
								   {"Tabl", "$F244#11.", 15},
								   {"PDF", "$F244#12.", 19},
								   {"LPan", "$F244#13.", 18},
								   {"RPan", "$F244#14.", 16},
								   {"DayN", "$F244#15.", 15},

							   }};

		// Fusion360
		struct App Fusion360 = {"Fusion 360",
								{
									{"", "", 0},
									{"", "", 0},
									{"", "", 0},
									{"", "", 0},
									{"", "", 0},
									{"", "", 0},
									{"", "", 0},
									{"", "", 0},
									{"", "", 0},
									{"", "", 0},
									{"", "", 0},
									{"", "", 0},
									{"", "", 0},
									{"", "", 0},
									{"", "", 0},
									{"", "", 0},

								}};

		// Aseprite
		struct App Aseprite = {"Aseprite",
							   {
								   {"", "", 0},
								   {"", "", 0},
								   {"", "", 0},
								   {"", "", 0},
								   {"", "", 0},
								   {"", "", 0},
								   {"", "", 0},
								   {"", "", 0},
								   {"", "", 0},
								   {"", "", 0},
								   {"", "", 0},
								   {"", "", 0},
								   {"", "", 0},
								   {"", "", 0},
								   {"", "", 0},
								   {"", "", 0},

							   }};

		apps[0] = MAIN;
		apps[1] = QuickStart;
		apps[2] = Firefox;
		apps[3] = VS_Code;
		apps[4] = Obsidian;
		apps[5] = Fusion360;
		apps[6] = Aseprite;

		//--EOF_ShortcutDefintion--

		//debug
		// Serial.println("[Config::begin] ### ### ### ### ### ### ### ###");
		// Serial.print("0.name: ");Serial.println(apps[0].name);
		// Serial.print("0.buttons.6.name: '");Serial.print(apps[0].buttons[6].name); Serial.println("'");
		// Serial.println("[Config::begin] END ### ### ### ### ### ### ###");
	}

}

#endif
