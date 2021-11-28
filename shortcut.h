/** SHORTCUT
 * 
 * this file executes the shortcuts
 * 
 * it is, now that i am using AutoHotKey, completely over-engineered, but it can almost any shortcut you'd want
 * 
 * created by zauberwild on 16.08.2021
 * 
 */

#ifndef shortcut_h
#define shortcut_h
#include "Arduino.h"
#include <Keyboard.h>

namespace ShortcutKeyboard
{

	/** @brief starts the keyboard
	 */
	void begin()
	{

		Keyboard.begin();
		Serial.println("[ShortcutKeyboard::ShortcutKeyboard] Shortcut-Keebs ready");
	}

	/** @brief presses a key (including special ones) and releases all keys after 10ms
	 * @param key the special to press (i.e. KEY_F11). This goes after the syntax of Keyboard library
	 * (these keywords: https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/)
	*/
	void press(int key)
	{

		Keyboard.press(key);

		delay(10);

		Keyboard.releaseAll();

		//Serial.print("[ShortcutKeyboard::press] just pressed: "); Serial.println(key);
	}

	/** @brief sends the text with commands to the computer
	 * @param text The key/text combination to be pressed
	 */
	void print(char text[64])
	{

		int i = 0; // position of the searching head / current character

		// save if modifier buttons are pressed
		bool pr_win = false;
		bool pr_ctrl = false;
		bool pr_shift = false;
		bool pr_alt = false;

		// search through the string
		for (i = 0; i < 64; i++)
		{

			// break when the array is empty
			if (text[i] == 0)
			{
				// Serial.println("[ShortcutKeyboard::print] array empty, breaking loop");
				break;
			}

			//catch special keys
			if (text[i] == '$')
			{
				i++; // advance head

				switch (text[i])
				{
				case 'W': // (left) WIN key
					if (pr_win)
					{
						Keyboard.release(KEY_LEFT_GUI);
						pr_win = false;
					}
					else
					{
						Keyboard.press(KEY_LEFT_GUI);
						pr_win = true;
					}
					break;
				case 'C': // (left) CTRL key
					if (pr_ctrl)
					{
						Keyboard.release(KEY_LEFT_CTRL);
						pr_ctrl = false;
					}
					else
					{
						Keyboard.press(KEY_LEFT_CTRL);
						pr_ctrl = true;
					}
					break;
				case 'S': // (left) SHIFT key
					if (pr_shift)
					{
						Keyboard.release(KEY_LEFT_SHIFT);
						pr_shift = false;
					}
					else
					{
						Keyboard.press(KEY_LEFT_SHIFT);
						pr_shift = true;
					}
					break;
				case 'A': // (left) ALT key
					if (pr_alt)
					{
						Keyboard.release(KEY_LEFT_ALT);
						pr_alt = false;
					}
					else
					{
						Keyboard.press(KEY_LEFT_ALT);
						pr_alt = true;
					}
					break;
				// all following keys aren't toggled, but pressed once
				case 'E': // RETURN
					Keyboard.press(KEY_RETURN);
					delay(10);
					Keyboard.release(KEY_RETURN);
					break;
				case 'T': // TAB(ULATOR)
					Keyboard.press(KEY_TAB);
					delay(10);
					Keyboard.release(KEY_TAB);
					break;
				case '*': // ESC(APE)
					Keyboard.press(KEY_ESC);
					delay(10);
					Keyboard.release(KEY_ESC);
					break;
				case '1': // POS1 / HOME
					Keyboard.press(KEY_HOME);
					delay(10);
					Keyboard.release(KEY_HOME);
					break;
				case '0': // ENDE / END
					Keyboard.press(KEY_END);
					delay(10);
					Keyboard.release(KEY_END);
					break;
				case 'I': // EINFG / INSERT
					Keyboard.press(KEY_INSERT);
					delay(10);
					Keyboard.release(KEY_INSERT);
					break;
				case 'D': // ENTF / DEL(ETE)
					Keyboard.press(KEY_DELETE);
					delay(10);
					Keyboard.release(KEY_DELETE);
					break;
				case '$': // $ / DOLLAR SIGN
					Keyboard.print("$");
					break;
				case 'F':
				{ // FUNCTION KEYS
					// get the number of the f-key
					int number = 0;
					i++;
					number += int(text[i]) - 48;
					if (text[i + 1] >= 48 && text[i + 1] <= 57)
					{
						i++;
						number *= 10;
						number += int(text[i]) - 48;
					}
					// press the f-key
					switch (number)
					{
					case 1:
						Keyboard.press(KEY_F1);
						break;
					case 2:
						Keyboard.press(KEY_F2);
						break;
					case 3:
						Keyboard.press(KEY_F3);
						break;
					case 4:
						Keyboard.press(KEY_F4);
						break;
					case 5:
						Keyboard.press(KEY_F5);
						break;
					case 6:
						Keyboard.press(KEY_F6);
						break;
					case 7:
						Keyboard.press(KEY_F7);
						break;
					case 8:
						Keyboard.press(KEY_F8);
						break;
					case 9:
						Keyboard.press(KEY_F9);
						break;
					case 10:
						Keyboard.press(KEY_F10);
						break;
					case 11:
						Keyboard.press(KEY_F11);
						break;
					case 12:
						Keyboard.press(KEY_F12);
						break;
					case 13:
						Keyboard.press(KEY_F13);
						break;
					case 14:
						Keyboard.press(KEY_F14);
						break;
					case 15:
						Keyboard.press(KEY_F15);
						break;
					case 16:
						Keyboard.press(KEY_F16);
						break;
					case 17:
						Keyboard.press(KEY_F17);
						break;
					case 18:
						Keyboard.press(KEY_F18);
						break;
					case 19:
						Keyboard.press(KEY_F19);
						break;
					case 20:
						Keyboard.press(KEY_F20);
						break;
					case 21:
						Keyboard.press(KEY_F21);
						break;
					case 22:
						Keyboard.press(KEY_F22);
						break;
					case 23:
						Keyboard.press(KEY_F23);
						break;
					case 24:
						Keyboard.press(KEY_F24);
						break;
					}
					delay(10);
					switch (number)
					{
					case 1:
						Keyboard.release(KEY_F1);
						break;
					case 2:
						Keyboard.release(KEY_F2);
						break;
					case 3:
						Keyboard.release(KEY_F3);
						break;
					case 4:
						Keyboard.release(KEY_F4);
						break;
					case 5:
						Keyboard.release(KEY_F5);
						break;
					case 6:
						Keyboard.release(KEY_F6);
						break;
					case 7:
						Keyboard.release(KEY_F7);
						break;
					case 8:
						Keyboard.release(KEY_F8);
						break;
					case 9:
						Keyboard.release(KEY_F9);
						break;
					case 10:
						Keyboard.release(KEY_F10);
						break;
					case 11:
						Keyboard.release(KEY_F11);
						break;
					case 12:
						Keyboard.release(KEY_F12);
						break;
					case 13:
						Keyboard.release(KEY_F13);
						break;
					case 14:
						Keyboard.release(KEY_F14);
						break;
					case 15:
						Keyboard.release(KEY_F15);
						break;
					case 16:
						Keyboard.release(KEY_F16);
						break;
					case 17:
						Keyboard.release(KEY_F17);
						break;
					case 18:
						Keyboard.release(KEY_F18);
						break;
					case 19:
						Keyboard.release(KEY_F19);
						break;
					case 20:
						Keyboard.release(KEY_F20);
						break;
					case 21:
						Keyboard.release(KEY_F21);
						break;
					case 22:
						Keyboard.release(KEY_F22);
						break;
					case 23:
						Keyboard.release(KEY_F23);
						break;
					case 24:
						Keyboard.release(KEY_F24);
						break;
					}
					break;
				}
				case 'd':
				{ // DELAY in ms (syntax: $d1234$)
					int time = 0;
					for (int j = 0; j < 4; j++)
					{
						i++;
						if (text[i] == '$')
						{
							break;
						}
						else if (text[i] >= 48 && text[i] <= 57)
						{
							time *= 10;
							time += int(text[i]) - 48;
						}
					}
					delay(time);
					break;
				}
				}

				delay(10);
				continue; // continue with next character
			}

			Keyboard.print(text[i]);
		}

		// release everything, for safety
		Keyboard.releaseAll();
	}

}

#endif