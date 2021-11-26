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
const int color_table[][3] = 	{{0,0,0},		// 0 off
								{255,255,255},	// 1 white
								{255,0,0},		// 2 red
								{0,255,0},		// 3 green
								{0,0,255},		// 4 blue
								{255,255,0},	// 5 yellow
								{255,127,0},	// 6 orange
								{255,0,255},	// 7 purple
								{0,127,255},	// 8 blue-cyan
								{0,255,127},	// 9 green-ish cyan
								{127,255,0},	// 10 green-yellow
								};

#define C_OFF 0
#define C_WHITE 1
#define C_RED 2
#define C_GREEN 3
#define C_BLUE 4
#define C_YELLOW 5
#define C_ORANGE 6
#define C_Purple 7
#define C_GreenYellow 10

#define C_Media 5			// multimedia
#define C_Destruct 2		// everything with danger
#define C_Destruct2 6		// everything with less danger
#define C_Open 9			// open files 'n stuff
#define C_New 3				// creating new things
#define C_Nav 4				// navigating
#define C_Nav2 8			// navigating, but different
#define C_Search 7			// searching

#define C_F360_Create 3
#define C_F360_Sketch 8
#define C_F360_Modify 5



namespace Config {

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

	App apps[16];


	//* functions
	/** @brief set up all the config data. Apps and their shortcuts are hardcoded in here
	 */
	void begin(){

		struct Button emptyButton = {"-","",0};

		//* CREATE APPS AND SHORTCUTS HERE
		//--SOF_ShortcutDefintion--

		// main menu
		struct App main = {"MAIN",
			{{"Mic", "$F21", C_Media},		{"Lock", "$Wl", C_Destruct2},	{"StBy", "$F15", C_Destruct},	{"Off", "$F16", C_Destruct},
			{"Back", "$F19", C_Media}, 	{"Forw", "$F20", C_Media},		{"Min", "$F13", C_Nav},			{"Max", "$F14", C_Nav},
			{"<-", "$A$T", C_Nav},			{"->", "$S$A$T", C_Nav},		emptyButton,					emptyButton,
			{"Win1", "$W1", C_Nav},		{"Win2", "$W2", C_Nav},			{"Win3", "$W3", C_Nav},			{"Win4", "$W4", C_Nav}}
		};

		// Explorer
		struct App explorer = {"Explorer",
			{{"cmd", "$Ct", 0},		{"cmd>", "$C$Sp", 0},			{"SymF", "$C$S.", 0},		{"Find", "§Cf", 0},
			{"SVup", "$C$S$A.", 0},	{"Repl", "$S$A$F12", 0},		{"oFil", "$Co", 0},			{"oFol", "$Cko", 0},
			{"SVen", "$Cb", 0},		{"Run", "$F5", 0},				{"nFil", "$Cn", 0},				{"nFol", "$Cnf", 0},
			{"SVdn", "$C$S$A,", 0},	{"Term", "$C$Sc", 0},			{"<T<", "$C$S$1", 0},			{">T>", "$C$S$0", 0},
		}};

		// Firefox
		struct App firefox = {"Firefox",
			{{"NTab", "$Ct", C_New},		{"NWin", "$Cn", C_New},				{"CTab", "$Cw", C_Destruct2},		{"CWin", "$C$Sw", C_Destruct},
			{"Srch", "$Ck", C_Search},		{"Wiki", "$Cl$C@wiki$E", C_Search},	{"LEO", "$Cl$C@leo$E", C_Search},	{"SrPg", "$Cf", C_Search},
			{"Mute", "$Cm", C_Media},		{"Z0", "$C0", C_Nav},				{"Z+", "$C+", C_Nav},				{"Z-", "$C-", C_Nav},
			{"Home", "$A$1", C_Nav},		{"Refr", "$F5", C_Nav},				{"<T<", "$C$S$T", C_Nav},			{">T>", "$C$T", C_Nav},
		}};

		// Visual Studio Code
		struct App vs_code = {"VS-Code",
			{{"cmd", "$Cp", C_Nav},			{"cmd>", "$C$Sp", C_Nav},			{"SymF", "$C$S.", C_Search},		{"Find", "$Cf", C_Search},
			{"SVup", "$C$S$A.", C_Nav2},	{"Repl", "$S$A$F12", C_Search},		{"oFil", "$Co", C_Open},			{"oFol", "$Cko", C_Open},
			{"SVen", "$Cb", C_Nav2},		{"Run", "$F5", C_GreenYellow},				{"nFil", "$Cn", C_New},				{"nFol", "$Cnf", C_New},
			{"SVdn", "$C$S$A,", C_Nav2},	{"Term", "$C$Sc", C_Open},			{"<T<", "$C$S$1", C_Nav},			{">T>", "$C$S$0", C_Nav},
		}};

		// Autodesk Fusion 360
		struct App fusion360 = {"Fusion 360",
			{{"Sket", "k", C_F360_Create},		{"Extr", "e", C_F360_Create},		{"Dreh", "d", C_F360_Create},		{"Erhe", "$Ce", C_F360_Create},
			{"Line", "l", C_F360_Sketch},		{"Circ", "c", C_F360_Sketch},		{"Rect", "r", C_F360_Sketch},		{"Bow", "b", C_F360_Sketch},
			{"Abru", "f", C_F360_Modify},		{"Fase", "$Sf", C_F360_Modify},		{"Move", "m", C_F360_Modify},		{"Para", "$Cp", C_Purple},
			{"Mess", "i", C_Purple},		{"Plan", "u", C_ORANGE},		{"Open", "$Co", C_Open},		{"Save", "$Cs", C_Open},
		}};

		// Unity
		struct App unity = {"Unity",
			{{"-", "$Ct", 0},		{"-", "$C$Sp", 0},			{"-", "$C$S.", 0},		{"-", "§Cf", 0},
			{"-", "$C$S$A.", 0},	{"-", "$S$A$F12", 0},	{"-", "$Co", 0},			{"-", "$Cko", 0},
			{"-", "$Cb", 0},		{"-", "$F5", 0},			{"-", "$Cn", 0},			{"-", "$Cnf", 0},
			{"-", "$C$S$A,", 0},	{"-", "$C$Sc", 0},			{"-", "$C$S$1", 0},			{"-", "$C$S$0", 0},
		}};

		// Aseprite
		struct App aseprite = {"Aseprite",
			{{"-", "$Ct", 0},		{"-", "$C$Sp", 0},			{"-", "$C$S.", 0},		{"-", "§Cf", 0},
			{"-", "$C$S$A.", 0},	{"-", "$S$A$F12", 0},	{"-", "$Co", 0},			{"-", "$Cko", 0},
			{"-", "$Cb", 0},		{"-", "$F5", 0},			{"-", "$Cn", 0},			{"-", "$Cnf", 0},
			{"-", "$C$S$A,", 0},	{"-", "$C$Sc", 0},			{"-", "$C$S$1", 0},			{"-", "$C$S$0", 0},
		}};

		//* ASSIGN APPS TO POSITIONS IN THE APP LIST
		apps[0] = main;
		apps[1] = explorer;
		apps[2] = firefox;
		apps[3] = vs_code;
		apps[4] = fusion360;
		apps[5] = unity;
		apps[6] = aseprite;

		//--EOF_ShortcutDefintion--

		//debug
		// Serial.println("[Config::begin] ### ### ### ### ### ### ### ###");
		// Serial.print("0.name: ");Serial.println(apps[0].name);
		// Serial.print("0.buttons.6.name: '");Serial.print(apps[0].buttons[6].name); Serial.println("'");
		// Serial.println("[Config::begin] END ### ### ### ### ### ### ###");

	}


}


#endif